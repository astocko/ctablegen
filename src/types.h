#ifndef _CTABLEGEN_TYPES_H_
#define _CTABLEGEN_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef int TGBool;

typedef struct TGTableGen *TGTableGenRef;
typedef struct TGRecordKeeper *TGRecordKeeperRef;

typedef struct TGRecordMap *TGRecordMapRef;
typedef struct TGRecordArray *TGRecordArrayRef;

typedef struct TGRecord *TGRecordRef;
typedef struct TGRecordVal *TGRecordValRef;
typedef struct TGRecordValItr *TGRecordValItrRef;


// typedef struct TGMultiClass *TGMultiClassRef;

// // Record Types
// typedef struct TGBitRecTy TGBitRecTyRef;
// typedef struct TGBitsRecTy TGBitsRecTyRef;
// typedef struct TGCodeRecTy TGCodeRecTyRef;
// typedef struct TGIntRecTy TGIntRecTyRef;
// typedef struct TGStringRecTy TGStringRecTyRef;
// typedef struct TGListRecTy TGListRecTyRef;
// typedef struct TGDagRecTy TGDagRecTyRef;
// typedef struct TGRecordRecTy TGRecordRecTyRef;
// typedef struct TGListRecordTy *TGListRecordTyRef;

#ifdef __cplusplus
}
#endif

#endif
