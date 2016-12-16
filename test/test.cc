#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

extern "C" {
#include "../src/TableGen.h"
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
  auto defs = TGRecordKeeperGetDefs(rk);


  size_t keys_len = 0;
  auto keys = TGRecordMapGetKeys(defs, &keys_len);

  for (size_t i = 0; i < keys_len; i++) {
    auto record =  TGRecordMapGet(defs, keys[i]);
    REQUIRE(!std::string(TGRecordGetName(record)).empty());
    auto itr = TGRecordGetValuesItr(record);
    REQUIRE(itr);
    TGRecordValRef rv;

    TGListItrRef list_itr;
    TGDagItrRef dag_itr;
    TGTypedInitRef init_ref;

    int8_t bit;
    int8_t *bits;
    int64_t integer;
    char *str;
    size_t len;
    TGBool ret;

    //    std::cout << "RECORD: " << TGRecordGetName(record) << std::endl;

    while (rv = TGRecordValItrNext(itr)) {
      auto name = TGRecordValGetName(rv);
      auto type = TGRecordValGetType(rv);
      REQUIRE(name);
      REQUIRE((type >= 0 && type <= 7));


      switch(type) {
      case TGInvalidRecTyKind:
        REQUIRE(type != TGInvalidRecTyKind);
        break;
      case TGBitRecTyKind:
        ret = TGRecordValGetValAsBit(rv, &bit);
        REQUIRE((ret == -1 || ret == 0 || ret == 1));
        REQUIRE((bit == 0 || bit == 1));
        break;
      case TGBitsRecTyKind:
        bits = TGRecordValGetValAsBits(rv, &len);
        for (size_t i = 0; i < len; i++) REQUIRE((bits[i] == 0 || bits[i] == 1));
        TGBitArrayFree(bits);
        break;
      case TGCodeRecTyKind:
        str = TGRecordValGetValAsNewString(rv);
        REQUIRE(str);
        REQUIRE_NOTHROW(TGStringFree(str));
        break;
      case TGIntRecTyKind:
        ret = TGRecordValGetValAsInt(rv, &integer);
        REQUIRE(ret);
        break;
      case TGStringRecTyKind:
        str = TGRecordValGetValAsNewString(rv);
        REQUIRE(str);
        REQUIRE_NOTHROW(TGStringFree(str));
        break;
      case TGListRecTyKind:
        list_itr = TGListRecordGetValues(rv);
        if (!list_itr) break;
        while (init_ref = TGListItrNext(list_itr)) {
          if (TGInitRecType(init_ref) == TGRecordRecTyKind) {
            std::cout << TGRecordGetName(TGRecordInitGetValue(init_ref)) << ", ";
          }
        }
        TGListItrFree(list_itr);
        std::cout << std::endl << "---------" << std::endl;
      case TGDagRecTyKind:
        dag_itr = TGDagRecordGetValues(rv);
        if (!dag_itr) break;
        // while (init_ref = TGDagItrNext(dag_itr)) {
        //   std:: cout << "DAG et: " << TGInitRecType(init_ref) << ", ";
        //   if (TGInitRecType(init_ref) == TGRecordRecTyKind) {
        //     std::cout << TGRecordGetName(TGRecordInitGetValue(init_ref)) << " :: ";
        //   }
        // }
        // std::cout << std::endl << "---" << std::endl;
        if (dag_itr) TGDagItrFree(dag_itr);
        break;
      default:
        str = TGRecordValGetValAsNewString(rv);
        REQUIRE(str);
        REQUIRE_NOTHROW(TGStringFree(str));
        break;
      }
    }

    REQUIRE_NOTHROW(TGRecordValItrFree(itr));
  }

  REQUIRE_NOTHROW(TGStringArrayFree(keys));
  REQUIRE_NOTHROW(TGFree(tg));
}
