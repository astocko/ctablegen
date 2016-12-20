// Copyright 2016 Alexander Stocko <as@coder.gg>. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

#include "TableGen.hpp"

const char* TGRecordValGetName(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  return rv->getName().c_str();
}

TGRecTyKind TGRecordValGetType(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, TGInvalidRecTyKind);
  auto rt = AS_TYPE(RecordVal*, rv_ref)->getType();
  return ctablegen::TGFromRecType(rt);
}

// TGInitKind TGRecordValGetInitKind(TGRecordValRef rv_ref) {
//   CHECK_REF(rv_ref, TGInvalidInitKind);
//   auto rv = AS_TYPE(RecordVal*, rv_ref);
//   auto val = rv->getValue()->getKind();
//   return val;
// }

// void TGRecordValTest(TGRecordValRef rv_ref) {
//   CHECK_REF(rv_ref, );
//   auto rv = AS_TYPE(RecordVal*, rv_ref);
//   auto val = rv->getValue();
//   auto blah = dyn_cast<DefInit>(val);
//   auto vals = blah->getDef()->getValues();
//   for (auto i = vals.begin(); i < vals.end(); i++) {
//     std::cout << i->getValue()->getAsString() << std::endl;
//   }
// }

char* TGRecordValGetValAsNewString(TGRecordValRef rv_ref) {
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
  CHECK_REF(rv_ref, false);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  return TGBitInitGetValue(AS_TYPE(TGTypedInitRef, rv->getValue()), bit);
}

int8_t* TGRecordValGetValAsBits(TGRecordValRef rv_ref, size_t *len) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  return TGBitsInitGetValue(AS_TYPE(TGTypedInitRef, rv->getValue()), len);
}

TGBool TGRecordValGetValAsInt(TGRecordValRef rv_ref, int64_t* integer) {
  CHECK_REF(rv_ref, false);
  auto rv = AS_TYPE(RecordVal*, rv_ref);
  return TGIntInitGetValue(AS_TYPE(TGTypedInitRef, rv->getValue()), integer);
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

TGRecordRef TGRecordValGetValAsDefRecord(TGRecordValRef rv_ref) {
  CHECK_REF(rv_ref, nullptr);
  auto rv = AS_TYPE(RecordVal*, rv_ref);

  if (rv->getType()->getRecTyKind() == RecTy::RecordRecTyKind) {
    auto val = rv->getValue();
    auto def = dyn_cast<DefInit>(val);
    if (!def) return nullptr;
    return AS_TYPE(TGRecordRef, def->getDef());
  }

  return nullptr;
}
