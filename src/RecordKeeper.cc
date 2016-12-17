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
