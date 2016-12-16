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

typedef struct TGTypedInit *TGTypedInitRef;

typedef struct TGListItr *TGListItrRef;
typedef struct TGDagItr *TGDagItrRef;

#ifdef __cplusplus
}
#endif

#endif
