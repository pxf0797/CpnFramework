/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : BlockM.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2021/03/20 16:42:53
* Description  : BlockM类及接口声明头文件
* Others       :
* History      : 210320 pxf 初次建立
***************************************************************************/

#ifndef BLOCKM_H_
#define BLOCKM_H_

/*头文件包含*/
#include "../../../cpnBasics/standType/standType.h"
#include "../../../cpnBasics/oopc/oopc.h"
#include "BlockMCfg.h"

/***********************************************************
* 版本定义
***********************************************************/
#define BLOCKM_MACRO_VERSION            0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

#define BLOCKM_INDEX_BITINDEX(index)    (((index)&BLOCKMCFG_MANAG_TYPE_MASK))
#define BLOCKM_INDEX_MASKINDEX(index)   (((index)>>BLOCKMCFG_MANAG_TYPE_BITS))
#define BLOCKM_BITINDEX_MASK(index)     ((blockMType)0x1u<<((index)&BLOCKMCFG_MANAG_TYPE_MASK))

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据声明
***********************************************/
//typedef struct{
//    uint16 id;
//    uint16 code;
//} tErrCode;
//TODO
/*数据引用
***********************************************/
//TODO

/***********************************************************
* 接口定义
***********************************************************/
/*接口声明
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* BlockM类定义
***********************************************************/
/*BlockM类声明
***********************************************/
CL(BlockM){
    hBlockM self;
    hBlockM (*init)(hBlockM cthis, uint8 *blockMSpace, uint16 blockMSize, uint16 blockMMax);

    // BlockM类参数
    uint8 *blockMSpace; /* 管理空间指针 */
    uint8 *blockMPointer; /* 块基指针 */
    uint16 blockMSize;
    uint16 blockMMax;
    uint16 blockMCounter;
    uint16 blockMMaskMaskMaskMax; /* MaskMaskMask最大个数 */
    uint16 blockMMaskMaskMax; /* MaskMask最大个数 */
    uint16 blockMMaskMax; /* Mask最大个数 */
    blockMType *blockMMaskMaskMask; /* 每一位代表memBlockMask连续32个字节是否使用完s，0未使用完，1已用完 */
    blockMType *blockMMaskMask; /* 每一位代表memBlockMask连续32个字节是否使用完，0未使用完，1已用完 */
    /*
     * bit                  7  6  5  4  3  2  1  0
     * blockMMask           0  0  1  0  0  1  1  0
     * blockMMaskContinue   0  1  1  1  1  1  0  0
     * 以上有3个块，1个单块，2个连续块
     * block1,block2c3,block5c2
     * */
    blockMType *blockMMask; /* 每一位代表一个块是否被使用，连续块只标识起始位 */
    blockMType *blockMMaskContinue; /* 每一位代表是否连续块，连续块起始位对应blockMMask一定会置位 */

    // BlockM类功能函数
    void * (*malloc)(hBlockM cthis, uint16 size);
    uint16 (*free)(hBlockM cthis, void *pointer);

    /* 单bit掩码控制函数 */
    uint16 (*findMinIndex)(hBlockM cthis);
    void (*setMaskIndex)(hBlockM cthis, uint16 index);
    void (*clearMaskIndex)(hBlockM cthis, uint16 index);

    /* 连续bit掩码控制函数 */
    uint16 (*findContinueMinIndex)(hBlockM cthis, uint16 count);
    void (*setContinueMaskIndex)(hBlockM cthis, uint16 index, uint16 count);
    void (*clearContinueMaskIndex)(hBlockM cthis, uint16 index);

    uint16 (*isPointerSet)(hBlockM cthis, void *pointer);
    uint16 (*isIndexSet)(hBlockM cthis, uint16 index);
    uint16 (*isIndexContiueSet)(hBlockM cthis, uint16 index);
    uint16 (*isFull)(hBlockM cthis);

    uint16 (*getSize)(hBlockM cthis, void *pointer); /* 返回0作为异常状态 */
    uint16 (*getIndex)(hBlockM cthis, void *pointer); /* 返回blockMMax作为异常状态 */
    void* (*getAddr)(hBlockM cthis, uint16 index);

    uint16 (*getCounts)(hBlockM cthis);
    uint16 (*getMax)(hBlockM cthis);
};

#endif /*BLOCKM_H_*/

/**************************** Copyright(C) pxf ****************************/
