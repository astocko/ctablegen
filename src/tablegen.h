#ifndef _CTABLEGEN_TABLEGEN_H_
#define _CTABLEGEN_TABLEGEN_H_

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum {
    TGBitRecTyKind,
    TGBitsRecTyKind,
    TGCodeRecTyKind,
    TGIntRecTyKind,
    TGStringRecTyKind,
    TGListRecTyKind,
    TGDagRecTyKind,
    TGRecordRecTyKind,
    TGInvalidRecTyKind
  } TGRecTyKind;

  TGTableGenRef TGInitialize(const char* source, const size_t includes_sz, const char* includes[]);
  void TGFree(TGTableGenRef tg_ref);
  TGRecordKeeperRef TGGetRecordKeeper(TGTableGenRef tg_ref);

  // TGParser
  TGBool TGParse(TGTableGenRef tg_ref);

  // LLVM RecordKeeper
  TGRecordMapRef TGRecordKeeperGetClasses(TGRecordKeeperRef rk_ref);
  TGRecordMapRef TGRecordKeeperGetDefs(TGRecordKeeperRef rk_ref);
  TGRecordRef TGRecordKeeperGetClass(TGRecordKeeperRef rk_ref, const char* name);
  TGRecordRef TGRecordKeeperGetDef(TGRecordKeeperRef rk_ref, const char* name);

  // LLVM RecordMap
  TGRecordRef TGRecordMapGetFirst(TGRecordMapRef rm_ref);
  TGRecordRef TGRecordMapGet(TGRecordMapRef rm_ref, const char* name);
  const char** TGRecordMapGetKeys(TGRecordMapRef rm_ref, size_t *len);

  // LLVM Record
  TGRecordKeeperRef TGRecordGetRecords(TGRecordRef record_ref);
  const char* TGRecordGetName(TGRecordRef record_ref);
  TGRecordValRef TGRecordGetValue(TGRecordRef record_ref, const char* name);
  TGRecTyKind TGRecordGetFieldType(TGRecordRef record_ref, const char* name);
  TGRecordValItrRef TGRecordGetValuesItr(TGRecordRef record_ref);
  TGBool TGRecordIsAnonymous(TGRecordRef record_ref);
  TGBool TGRecordIsResolveFirst(TGRecordRef record_ref);

  // LLVM RecordVal
  const char* TGRecordValGetName(TGRecordValRef rv_ref);
  TGRecTyKind TGRecordValGetType(TGRecordValRef rv_ref);
  char* TGRecordValGetValAsString(TGRecordValRef rv_ref);
  TGBool TGRecordValGetValAsBit(TGRecordValRef rv_ref, int8_t* bit);
  int8_t* TGRecordValGetValAsBits(TGRecordValRef rv_ref, size_t *len);
  TGBool TGRecordValGetValAsInt(TGRecordValRef rv_ref, int64_t *integer);
  TGRecordRef TGRecordValGetValAsRecord(TGRecordValRef rv_ref);

  // LLVM RecordVal Iterators
  TGRecordValRef TGRecordValItrNext(TGRecordValItrRef rvi_ref);

  // LLVM ListType
  TGRecTyKind TGListRecordGetType(TGRecordValRef rv_ref);

  // Memory
  void TGBitArrayFree(int8_t bit_array[]);
  void TGStringFree(const char* str);
  void TGStringArrayFree(const char **str_array);
  void TGRecordValItrFree(TGRecordValItrRef rvi_ref);


#ifdef __cplusplus
}
#endif
#endif
