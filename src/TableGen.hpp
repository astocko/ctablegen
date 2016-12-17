#ifndef _CTABLEGEN_TABLEGEN_HPP_
#define _CTABLEGEN_TABLEGEN_HPP_

#include <memory>
#include <utility>

#include <TableGen/TGParser.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/TableGen/Error.h>
#include <llvm/TableGen/Record.h>

#include "TableGen.h"

#define CHECK_REF(ref, val)                                                    \
  if (!ref)                                                                    \
  return val
#define AS_TYPE(Type, Obj) reinterpret_cast<Type>(Obj)
#define AS_CTYPE(Type, Obj) reinterpret_cast<const Type>(Obj)
#define CONST_REF(Type, Obj) const_cast<Type>(static_cast<const Type>(Obj))

using namespace llvm;

namespace ctablegen {

typedef std::map<std::string, std::unique_ptr<Record>> RecordMap;
typedef std::pair<std::string, TypedInit*> DagPair;

class TableGen {
public:
  TableGen(TGParser *parser, RecordKeeper *rk, SourceMgr *sm)
      : parser_(parser), record_keeper_(rk), source_mgr_(sm) {}
  bool Parse() { return parser_->ParseFile(); }
  inline RecordKeeper *record_keeper() const { return record_keeper_.get(); }

private:
  std::unique_ptr<TGParser> parser_;
  std::unique_ptr<RecordKeeper> record_keeper_;
  std::unique_ptr<SourceMgr> source_mgr_;
};

// Utility
TGRecTyKind TGFromRecType(RecTy *rt);
}

#endif
