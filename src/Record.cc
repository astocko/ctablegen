// Copyright 2016 Alexander Stocko <as@coder.gg>. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

#include "Iterator.hpp"
#include "TableGen.hpp"

using ctablegen::TGFromRecType;

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

const char *TGRecordAsNewString(TGRecordRef record_ref) {
  CHECK_REF(record_ref, nullptr);
  auto record = AS_TYPE(Record *, record_ref);
  auto name = record->getNameInitAsString();

  auto sz = name.size() + 1;
  auto str = new char[sz];
  name.copy(str, name.size(), 0);
  str[sz - 1] = '\0';
  return str;
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
  auto record = AS_TYPE(Record *, record_ref);
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
