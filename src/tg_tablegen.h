#ifndef _TG_TABLEGEN_H_
#define _TG_TABLEGEN_H_

#include <iostream>
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/TableGen/Error.h>
#include <llvm/TableGen/Record.h>
#include <TableGen/TGParser.h>

#include "tablegen.h"

using namespace llvm;

#define AS_TYPE(Type, Obj) reinterpret_cast<Type *>(Obj)
#define AS_CTYPE(Type, Obj) reinterpret_cast<const Type *>(Obj)

namespace tablegen {

  class TableGen {
  public:
    TableGen(std::string input, std::vector<std::string> includes);
    int Parse();
  private:
    std::unique_ptr<TGParser> parser_;
    std::unique_ptr<RecordKeeper> record_keeper_;
    std::unique_ptr<SourceMgr> source_mgr_;
  };

}


#endif
