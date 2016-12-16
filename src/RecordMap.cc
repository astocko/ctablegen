#include "TableGen.hpp"

using ctablegen::RecordMap;

TGRecordRef TGRecordMapGetFirst(TGRecordMapRef rm_ref) {
  CHECK_REF(rm_ref, nullptr);
  auto rm = AS_TYPE(RecordMap *, rm_ref);
  return AS_TYPE(TGRecordRef, rm->begin()->second.get());
}

TGRecordRef TGRecordMapGet(TGRecordMapRef rm_ref, const char* name) {
  CHECK_REF(rm_ref, nullptr);
  auto rm = AS_TYPE(RecordMap *, rm_ref);
  auto val = rm->find(name);
  if (val != rm->end()) {
    return AS_TYPE(TGRecordRef, rm->find(name)->second.get());
  }
  return nullptr;
}

const char** TGRecordMapGetKeys(TGRecordMapRef rm_ref, size_t *len) {
  CHECK_REF(rm_ref, nullptr);
  auto rm = AS_TYPE(RecordMap *, rm_ref);
  auto sz = rm->size();
  auto str_array = new const char*[sz];
  *len = sz;
  size_t idx = 0;

  for (auto &i : *rm) {
    str_array[idx++] = i.first.c_str();
  }

  return str_array;
}
