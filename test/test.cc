#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

extern "C" {
#include "../src/tablegen.h"
}

std::pair<std::string, std::vector<std::string>> GetTestConfig() {
  std::string source;
  std::vector<std::string> includes;

  std::ifstream source_file("test_config.cfg");

  std::string line;

  if (!std::getline(source_file, source) && source.empty()) {
    throw std::runtime_error("test_config.cfg is empty");
  }

  while (std::getline(source_file, line)) {
    includes.push_back(line);
  }

  if (includes.empty()) {
    throw std::runtime_error("no include directories in test_config.cfg");
  }

  return std::make_pair(source, includes);
}

TEST_CASE("Create TableGen", "[create]") {
  std::pair<std::string, std::vector<std::string>> config;

  REQUIRE_NOTHROW(config = GetTestConfig());

  auto source = config.first;
  auto includes = config.second;
  std::vector<const char *> includes_cstr;

  std::transform(includes.begin(), includes.end(),
                 std::back_inserter(includes_cstr),
                 [](const std::string &s) { return s.c_str(); });

  auto tg = TGInitialize(source.c_str(), includes_cstr.size(), &includes_cstr[0]);
  REQUIRE(tg != nullptr);

  REQUIRE(TGParse(tg));

  auto rk = TGGetRecordKeeper(tg);
  auto classes = TGRecordKeeperGetDefs(rk);

  auto first = TGRecordMapGetFirst(classes);

  std::cout << TGRecordGetName(first) << std::endl;

  auto itr = TGRecordGetValuesItr(first);
  REQUIRE(itr);

  TGRecordValRef rv;
  int8_t bit;
  size_t len;

  while (rv = TGRecordValItrNext(itr)) {
    auto type = TGRecordValGetType(rv);
    auto name = TGRecordValGetName(rv);

    REQUIRE(name);

    std::cout << name << std::endl;

    auto str = TGRecordValGetValAsString(rv);
    std::cout << str << std::endl;
    TGStringFree(str);


    if (type == TGBitRecTyKind) {
      if (TGRecordValGetValAsBit(rv, &bit)) {
        std::cout << "BIT: " << (int) bit << std::endl;
      }
    } else if (type == TGRecordRecTyKind) {
      auto rec = TGRecordValGetValAsRecord(rv);
      if (rec) {
        std::cout << "RECORD: " << TGRecordGetName(rec) << std::endl;
      }
    }

    std::cout << "---------------" << std::endl;
  }

  REQUIRE_NOTHROW(TGRecordValItrFree(itr));
  REQUIRE_NOTHROW(TGFree(tg));
}
