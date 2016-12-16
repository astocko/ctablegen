#ifndef _CTABLEGEN_TABLEGEN_HPP_
#define _CTABLEGEN_TABLEGEN_HPP_

#include <memory>

#include <TableGen/TGParser.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/TableGen/Error.h>
#include <llvm/TableGen/Record.h>

using namespace llvm;

namespace ctablegen {

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

template <class T> class ArrayRefIterator {
public:
  explicit ArrayRefIterator(ArrayRef<T> a) : array_(a), idx_(0), len_(a.size()) {}
  const T *Next() {
    if (idx_ < len_) {
      return &array_[idx_++];
    } else {
      return nullptr;
    }
  }

private:
  ArrayRef<T> array_;
  size_t idx_;
  const size_t len_;
};
}

#endif
