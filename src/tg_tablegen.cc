#include <iostream>

#include "TableGen.hpp"
#include "tablegen.h"

#define CHECK_REF(ref, val) if (!ref) return val
#define AS_TYPE(Type, Obj) reinterpret_cast<Type>(Obj)
#define AS_CTYPE(Type, Obj) reinterpret_cast<const Type>(Obj)
#define CONST_REF(Type, Obj) const_cast<Type>(static_cast<const Type>(Obj))

typedef std::map<std::string, std::unique_ptr<Record>> RecordMap;

// Helper

TGRecTyKind TGFromRecType(RecTy *rt) {
  switch (rt->getRecTyKind()) {
  case RecTy::BitRecTyKind:
    return TGBitRecTyKind;
  case RecTy::BitsRecTyKind:
    return TGBitsRecTyKind;
  case RecTy::CodeRecTyKind:
    return TGCodeRecTyKind;
  case RecTy::IntRecTyKind:
    return TGIntRecTyKind;
  case RecTy::StringRecTyKind:
    return TGStringRecTyKind;
  case RecTy::ListRecTyKind:
    return TGListRecTyKind;
  case RecTy::DagRecTyKind:
    return TGDagRecTyKind;
  case RecTy::RecordRecTyKind:
    return TGRecordRecTyKind;
  default:
    return TGInvalidRecTyKind;
  }
}

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

// LLVM RecordKeeper

TGRecordMapRef TGRecordKeeperGetClasses(TGRecordKeeperRef rk_ref) {
  CHECK_REF(rk_ref, nullptr);
  auto rk = AS_TYPE(RecordKeeper *, rk_ref);
  auto classes = CONST_REF(RecordMap *, &rk->getClasses());
  return AS_TYPE(TGRecordMapRef, classes);
}

TGRecordMapRef TGRecordKeeperGetDefs(TGRecordKeeperRef rk_ref) {
  CHECK_REF(rk_ref, nullptr);
  auto rk = AS_TYPE(RecordKeeper *, rk_ref);
  auto defs = CONST_REF(RecordMap *, &rk->getDefs());
  return AS_TYPE(TGRecordMapRef, defs);
}

TGRecordRef TGRecordKeeperGetClass(TGRecordKeeperRef rk_ref, const char *name) {
  CHECK_REF(rk_ref, nullptr);
  auto rk = AS_TYPE(RecordKeeper *, rk_ref);
  return AS_TYPE(TGRecordRef, rk->getClass(std::string(name)));
}

TGRecordRef TGRecordKeeperGetDef(TGRecordKeeperRef rk_ref, const char *name) {
  CHECK_REF(rk_ref, nullptr);
  auto rk = AS_TYPE(RecordKeeper *, rk_ref);
  return AS_TYPE(TGRecordRef, rk->getDef(std::string(name)));
}

// LLVM RecordMap
TGRecordRef TGRecordMapGetFirst(TGRecordMapRef rm_ref) {
  CHECK_REF(rm_ref, nullptr);
  auto rm = AS_TYPE(RecordMap *, rm_ref);
  return AS_TYPE(TGRecordRef, rm->begin()->second.get());
}

// LLVM Record
TGRecordKeeperRef TGRecordGetRecords(TGRecordRef record_ref) {
  CHECK_REF(record_ref, nullptr);
  auto record = AS_TYPE(Record *, record_ref);
  return AS_TYPE(TGRecordKeeperRef, &record->getRecords());
}

const char *TGRecordGetName(TGRecordRef record_ref) {
  CHECK_REF(record_ref, nullptr);
  auto record = AS_TYPE(Record *, record_ref);
  return record->getName().c_str();
}

TGRecordValRef TGRecordGetValue(TGRecordRef record_ref, const char *name) {
  CHECK_REF(record_ref, nullptr);
  CHECK_REF(name, nullptr);
  auto record = AS_TYPE(Record *, record_ref);
  return AS_TYPE(TGRecordValRef, record->getValue(std::string(name)));
}

TGRecTyKind TGRecordGetFieldType(TGRecordRef record_ref, const char *name) {
  CHECK_REF(record_ref, TGInvalidRecTyKind);
  CHECK_REF(name, TGInvalidRecTyKind);
  auto record = AS_TYPE(Record *, record_ref);
  auto value = record->getValue(std::string(name));
  CHECK_REF(value, TGInvalidRecTyKind);
  return TGFromRecType(value->getType());
}

TGRecordValItrRef TGRecordGetValuesItr(TGRecordRef record_ref) {
  CHECK_REF(record_ref, nullptr);
  auto record = AS_TYPE(Record*, record_ref);
  auto itr = new ctablegen::ArrayRefIterator<RecordVal>(record->getValues());
  return AS_TYPE(TGRecordValItrRef, itr);
}

TGBool TGRecordIsAnonymous(TGRecordRef record_ref) {
  CHECK_REF(record_ref, false);
  auto record = AS_TYPE(Record *, record_ref);
  return record->isAnonymous();
}

TGBool TGRecordIsResolveFirst(TGRecordRef record_ref) {
  CHECK_REF(record_ref, false);
  auto record = AS_TYPE(Record *, record_ref);
  return record->isResolveFirst();
}

// LLVM RecordVal
const char* TGRecordValGetName(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  return rv->getName().c_str();
}

TGRecTyKind TGRecordValGetType(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, TGInvalidRecTyKind);
  auto rt = AS_TYPE(RecordVal*, rv_ref)->getType();
  return TGFromRecType(rt);
}

char* TGRecordValGetValAsString(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  auto val = rv->getValue()->getAsString();
  auto sz = val.size() + 1;
  auto str = new char[sz];
  val.copy(str, val.size(), 0);
  str[sz-1] = '\0';
  return str;
}

TGBool TGRecordValGetValAsBit(TGRecordValRef rv_ref, int8_t* bit) {
  CHECK_REF(rv_ref, TGInvalidRecTyKind);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  if (rv->getType()->getRecTyKind() == RecTy::BitRecTyKind) {
    *bit = reinterpret_cast<BitInit*>(rv->getValue())->getValue();
    return true;
  }
  return false;
}

int8_t* TGRecordValGetValAsBits(TGRecordValRef rv_ref, size_t *len) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  if (rv->getType()->getRecTyKind() == RecTy::BitsRecTyKind) {
    auto val = reinterpret_cast<BitsInit*>(rv->getValue());
    *len = val->getNumBits();
    auto bits = new int8_t[*len];

    for (size_t i = 0; i < *len; i++) {
      bits[i] = reinterpret_cast<BitInit*>(val->getBit(i))->getValue();
    }
    return bits;
  }
  return nullptr;
}

TGBool TGRecordValGetValAsInt(TGRecordValRef rv_ref, int64_t* integer) {
  CHECK_REF(rv_ref, TGInvalidRecTyKind);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  if (rv->getType()->getRecTyKind() == RecTy::BitsRecTyKind) {
    *integer = reinterpret_cast<IntInit*>(rv->getValue())->getValue();
    return true;
  }
  return false;
}

TGRecordRef TGRecordValGetValAsRecord(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  if (rv->getType()->getRecTyKind() == RecTy::RecordRecTyKind) {
    auto rec = reinterpret_cast<RecordRecTy*>(rv->getType())->getRecord();
    return AS_TYPE(TGRecordRef, rec);
  }
  return nullptr;
}


// LLVM RecordVal Iterators
TGRecordValRef TGRecordValItrNext(TGRecordValItrRef rvi_ref) {
  CHECK_REF(rvi_ref, nullptr);
  auto rv = AS_TYPE(ctablegen::ArrayRefIterator<RecordVal>*, rvi_ref)->Next();
  return AS_TYPE(TGRecordValRef, CONST_REF(RecordVal*, rv));
}

// LLVM ListRecordType
TGRecTyKind TGListRecordGetType(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, TGInvalidRecTyKind);
  auto rv = AS_TYPE(RecordVal*, rv_ref);

  if (rv->getType()->getRecTyKind() == RecTy::ListRecTyKind) {
    auto list = rv->getType()->getListTy();
    return TGFromRecType(list->getElementType());
  }

  return TGInvalidRecTyKind;
}


// Memory
void TGBitArrayFree(int8_t bit_array[]) {
  delete [] bit_array;
}

void TGStringFree(char *str) {
  delete str;
}

void TGRecordValItrFree(TGRecordValItrRef rvi_ref) {
  CHECK_REF(rvi_ref, );
  delete AS_TYPE(ctablegen::ArrayRefIterator<RecordVal> *, rvi_ref);
}
