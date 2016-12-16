#include "TableGen.hpp"
#include "Iterator.hpp"

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
