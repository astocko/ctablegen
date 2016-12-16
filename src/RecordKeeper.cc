#include "TableGen.hpp"

using ctablegen::RecordMap;

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
