#include <iostream>
#include "TableGen.hpp"
#include "Iterator.hpp"

using ctablegen::RecordMap;
using ctablegen::TGFromRecType;

// TableGen
TGTableGenRef TGInitialize(const char *source, const size_t includes_sz,
                           const char *includes[]) {
  auto rk = new RecordKeeper;
  auto sm = new SourceMgr;

  // Check that the input table definition exists
  ErrorOr<std::unique_ptr<MemoryBuffer>> FileOrErr =
      MemoryBuffer::getFileOrSTDIN(source);

  if (std::error_code EC = FileOrErr.getError()) {
    return nullptr;
  }

  // Add the table definition source
  sm->AddNewSourceBuffer(std::move(*FileOrErr), SMLoc());

  // Add the include directories for any table definition dependencies
  std::vector<std::string> includes_v;
  for (size_t i = 0; i < includes_sz; i++) {
    includes_v.push_back(std::string(includes[i]));
  }
  sm->setIncludeDirs(includes_v);

  auto parser = new TGParser(*sm, *rk);
  return AS_TYPE(TGTableGenRef, new ctablegen::TableGen(parser, rk, sm));
}

void TGFree(TGTableGenRef tg_ref) {
  CHECK_REF(tg_ref, );
  delete AS_TYPE(ctablegen::TableGen *, tg_ref);
}

TGRecordKeeperRef TGGetRecordKeeper(TGTableGenRef tg_ref) {
  CHECK_REF(tg_ref, nullptr);
  auto tg = AS_TYPE(ctablegen::TableGen *, tg_ref);
  return AS_TYPE(TGRecordKeeperRef, tg->record_keeper());
}

TGBool TGParse(TGTableGenRef tg_ref) {
  CHECK_REF(tg_ref,false);
  auto tg = AS_TYPE(ctablegen::TableGen *, tg_ref);
  return !tg->Parse();
}


// LLVM RecordVal Iterators
TGRecordValRef TGRecordValItrNext(TGRecordValItrRef rvi_ref) {
  CHECK_REF(rvi_ref, nullptr);
  auto rv = AS_TYPE(ctablegen::ArrayRefIterator<RecordVal>*, rvi_ref)->Next();
  return AS_TYPE(TGRecordValRef, CONST_REF(RecordVal*, rv));
}

// LLVM ListType
TGRecTyKind TGListRecordGetType(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, TGInvalidRecTyKind);
  auto rv = AS_TYPE(RecordVal*, rv_ref);

  if (rv->getType()->getRecTyKind() == RecTy::ListRecTyKind) {
    auto list = rv->getType()->getListTy();
    return TGFromRecType(list->getElementType());
  }

  return TGInvalidRecTyKind;
}

// TGRecordValItrRef TGListRecordGetValues(TGRecordValRef rv_ref) {
//   CHECK_REF(rv_ref, nullptr);
//   auto rv = AS_TYPE(RecordVal*, rv_ref);

//   auto list = dyn_cast<ListInit>(rv);
//   if (!list) return nullptr;

//   auto cast_list = reinterpret_cast<ArrayRef<RecordVal*>>(list->getValues());

//   auto listitr = new ctablegen::ArrayRefIterator<RecordVal>(cast_list);
//   return AS_TYPE(TGRecordValItrRef, itr);
// }

// LLVM ListType
TGListItrRef TGListRecordGetValues(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);

  auto list = dyn_cast<ListInit>(rv->getValue());
  CHECK_REF(list, nullptr);

  auto itr = new ctablegen::ListRefIterator(list);
  return AS_TYPE(TGListItrRef, itr);
}

TGTypedInitRef TGListItrNext(TGListItrRef li_ref) {
  CHECK_REF(li_ref, nullptr);
  auto ti = AS_TYPE(ctablegen::ListRefIterator*, li_ref)->Next();
  return AS_TYPE(TGTypedInitRef, ti);
}

// LLVM DagType
TGDagItrRef TGDagRecordGetValues(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);

  auto dag = dyn_cast<DagInit>(rv->getValue());
  CHECK_REF(dag, nullptr);

  auto itr = new ctablegen::DagRefIterator(dag);
  return AS_TYPE(TGDagItrRef, itr);
}

TGTypedInitRef TGDagItrNext(TGDagItrRef di_ref) {
  CHECK_REF(di_ref, nullptr);
  auto ti = AS_TYPE(ctablegen::DagRefIterator*, di_ref)->Next();
  return AS_TYPE(TGTypedInitRef, ti);
}


// Memory
void TGBitArrayFree(int8_t bit_array[]) {
  delete [] bit_array;
}

void TGStringFree(const char *str) {
  delete str;
}

void TGStringArrayFree(const char **str_array) {
  delete str_array;
}

void TGRecordValItrFree(TGRecordValItrRef rvi_ref) {
  CHECK_REF(rvi_ref, );
  delete AS_TYPE(ctablegen::ArrayRefIterator<RecordVal> *, rvi_ref);
}

void TGListItrFree(TGListItrRef li_ref) {
  CHECK_REF(li_ref, );
  delete AS_TYPE(ctablegen::ListRefIterator*, li_ref);
}

void TGDagItrFree(TGDagItrRef di_ref) {
  CHECK_REF(di_ref, );
  delete AS_TYPE(ctablegen::DagRefIterator*, di_ref);
}
