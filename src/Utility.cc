#include "TableGen.hpp"

#include <iostream>

namespace ctablegen {

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

}

TGRecTyKind TGInitRecType(TGTypedInitRef ti) {
  CHECK_REF(ti, TGInvalidRecTyKind);
  auto ty = AS_TYPE(Init*, ti);
  auto typed_init = dyn_cast<TypedInit>(ty);
  CHECK_REF(typed_init, TGInvalidRecTyKind);
  return ctablegen::TGFromRecType(typed_init->getType());
}

TGBool TGBitInitGetValue(TGTypedInitRef ti, int8_t *bit) {
  CHECK_REF(ti, false);
  auto ty = AS_TYPE(Init*, ti);
  auto bit_init = dyn_cast<BitInit>(ty);
  CHECK_REF(bit_init, -1);
  *bit = bit_init->getValue();
  return true;
}

int8_t *TGBitsInitGetValue(TGTypedInitRef ti, size_t *len) {
  CHECK_REF(ti, nullptr);
  auto ty = AS_TYPE(Init*, ti);
  auto bits_init = dyn_cast<BitsInit>(ty);
  CHECK_REF(bits_init, nullptr);

  *len = bits_init->getNumBits();
  auto bits = new int8_t[*len];

  for (size_t i = 0; i < *len; i++) {
    bits[i] = reinterpret_cast<BitInit*>(bits_init->getBit(i))->getValue();
  }

  return bits;
}

TGBool TGIntInitGetValue(TGTypedInitRef ti, int64_t *integer) {
  CHECK_REF(ti, false);
  auto ty = AS_TYPE(Init*, ti);
  auto int_init = dyn_cast<IntInit>(ty);
  CHECK_REF(int_init, false);

  *integer = int_init->getValue();
  return true;
}

char *TGStringInitGetValueNewString(TGTypedInitRef ti) {
  CHECK_REF(ti, nullptr);
  auto ty = AS_TYPE(Init*, ti);
  auto str_init = dyn_cast<StringInit>(ty);
  CHECK_REF(str_init, nullptr);

  auto val = str_init->getValue();
  auto sz = val.size();
  auto str = new char[sz];
  val.copy(str, val.size(), 0);
  str[sz - 1] = '\0';
  return str;
}

TGRecordRef TGRecordInitGetValue(TGTypedInitRef ti) {
  CHECK_REF(ti, nullptr);
  auto ty = AS_TYPE(Init*, ti);
  auto def_init = dyn_cast<DefInit>(ty);
  CHECK_REF(def_init, nullptr);
  return AS_TYPE(TGRecordRef, def_init->getDef());
}
