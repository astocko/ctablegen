// Copyright 2016 Alexander Stocko <as@coder.gg>. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

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
