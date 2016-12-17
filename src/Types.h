// Copyright 2016 Alexander Stocko <as@coder.gg>. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

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

typedef struct TGDagPair *TGDagPairRef;

#ifdef __cplusplus
}
#endif

#endif
