#include <iostream>
#include <cstdio>
#include "TableGenWrapper.h"

using namespace llvm;


TableGen* tablegen_new(const char* input, size_t includesc, const char* includesv[]) {
  auto rk = new RecordKeeper;
  auto sm = new SourceMgr;

  ErrorOr<std::unique_ptr<MemoryBuffer>> FileOrErr =
    MemoryBuffer::getFileOrSTDIN(input);

  if (std::error_code EC = FileOrErr.getError()) {
    return nullptr;
  }

  sm->AddNewSourceBuffer(std::move(*FileOrErr), SMLoc());

  std::vector<std::string> includes;

  for (size_t i = 0; i < includesc; i++) {
    auto inc = std::string(includesv[i]);
    includes.push_back(inc);
  }

  sm->setIncludeDirs(includes);

  auto parser = new TGParser(*sm, *rk);

  auto tg = new TableGen;
  tg->parser = parser;
  tg->records = rk;
  tg->source_mgr = sm;

  return tg;
}

void tablegen_destroy(const TableGen* tg) {
  delete tg->parser;
  delete tg->records;
  delete tg->source_mgr;
  delete tg;
}

void tablegen_parse_file(const TableGen* tg) {
  tg->parser->ParseFile();
}

const char* tablegen_get_def(const TableGen* tg, const char* name) {
  for (const auto &d : tg->records->getDefs()) {
    if (d.second.get()->getName() == std::string(name)) {
      return d.second.get()->getName().c_str();
    }
  }
  return nullptr;
}
