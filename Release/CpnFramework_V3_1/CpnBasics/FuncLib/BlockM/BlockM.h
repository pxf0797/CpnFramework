/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : BlockM.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 08:56:12
 * Description  : BlockM class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef BLOCKM_H_
#define BLOCKM_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "BlockMCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define BLOCKM_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

#define BLOCKM_INDEX_BITINDEX(index)    (((index)&BLOCKMCFG_MANAG_TYPE_MASK))
#define BLOCKM_INDEX_MASKINDEX(index)   (((index)>>BLOCKMCFG_MANAG_TYPE_BITS))
#define BLOCKM_BITINDEX_MASK(index)     ((blockMType)0x1u<<((index)&BLOCKMCFG_MANAG_TYPE_MASK))

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
/* typedef struct{
    uint16 id;
    uint16 code;
} tErrCode;
 */
/* TODO */
/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
//INF(get){
//  uint16(*get)(void);
//};
/* TODO */

/***********************************************************
 * BlockM class definition.
 **********************************************************/
/* BlockM class declaration.
 **********************************************/
CL(BlockM){
    hBlockM self;
    hBlockM (*init)(hBlockM cthis, uint8 *blockMSpace, uint16 blockMSize, blockMType blockMMax);

    /* BlockM class parameters. */
    uint8 *blockMSpace;                 /* Manage space pointer. */
    uint8 *blockMPointer;               /* Block basic pointer. */
    uint16 blockMSize;
    blockMType blockMMax;
    blockMType blockMCounter;
    blockMType blockMMaskMaskMaskMax;   /* MaskMaskMask maximum counters. */
    blockMType blockMMaskMaskMax;       /* MaskMask maximum counters. */
    blockMType blockMMaskMax;           /* Mask maximum counters. */
    blockMType *blockMMaskMaskMask;     /* Each bit represents whether 32 consecutive bytes of memBlockMaskMask have been used up,
                                           0 has not been used up, and 1 has been used up. */
    blockMType *blockMMaskMask;         /* Each bit represents whether 32 consecutive bytes of memBlockMask have been used up,
                                         * 0 has not been used up, and 1 has been used up. */
    /*
     * bit                  7  6  5  4  3  2  1  0
     * blockMMask           0  0  1  0  0  1  1  0
     * blockMMaskContinue   0  1  1  1  1  1  0  0
     * There are 3 blocks above, 1 single block, 2 continuous blocks.
     * block1,block2c3,block5c2
     */
    blockMType *blockMMask;             /* Each bit represents whether a block is used, and continuous blocks only identify the start bit. */
    blockMType *blockMMaskContinue;     /* Each bit represents whether the block is continuous,
                                         * and the start bit of the continuous block corresponding to blockMMask must be set. */

    /* BlockM class functions. */
    void * (*malloc)(hBlockM cthis, uint16 size);
    uint8 (*free)(hBlockM cthis, void *pointer);                   /* TRUE/FALSE */
    /* Single bit mask control functions. */
    blockMType (*findMinIndex)(hBlockM cthis);
    void (*setMaskIndex)(hBlockM cthis, blockMType index);
    void (*clearMaskIndex)(hBlockM cthis, blockMType index);
    /* Continue bits mask control functions. */
    blockMType (*findContinueMinIndex)(hBlockM cthis, uint16 count);
    void (*setContinueMaskIndex)(hBlockM cthis, blockMType index, uint16 count);
    void (*clearContinueMaskIndex)(hBlockM cthis, blockMType index);

    uint8 (*isPointerSet)(hBlockM cthis, void *pointer);           /* TRUE/FALSE */
    uint8 (*isIndexSet)(hBlockM cthis, blockMType index);          /* TRUE/FALSE */
    uint8 (*isIndexContinueSet)(hBlockM cthis, blockMType index);  /* TRUE/FALSE */
    uint8 (*isFull)(hBlockM cthis);                                /* TRUE/FALSE */

    uint16 (*getSize)(hBlockM cthis, void *pointer);               /* return 0 as abnormal. */
    blockMType (*getIndex)(hBlockM cthis, void *pointer);          /* return blockMMax as abnormal. */
    void* (*getAddr)(hBlockM cthis, blockMType index);

    blockMType (*getCounts)(hBlockM cthis);
    blockMType (*getMax)(hBlockM cthis);
};

#endif /*BLOCKM_H_*/

/**************************** Copyright(C) pxf ****************************/
