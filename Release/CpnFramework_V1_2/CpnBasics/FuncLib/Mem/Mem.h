/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Mem.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/05 13:45:23
* Description  : Mem类及接口声明头文件
* Others       :
* History      : 201205 pxf 初次建立
***************************************************************************/

#ifndef MEM_H_
#define MEM_H_

/*头文件包含*/
#include "../../../cpnBasics/standType/standType.h"
#include "../../../cpnBasics/oopc/oopc.h"
#include "./MemCfg.h"

/***********************************************************
* 版本定义
***********************************************************/
#define MEM_MACRO_VERSION               0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据声明
***********************************************/
typedef enum{
    mem_unused,
    mem_used
} TE_USED_STATUS;
typedef struct{
   void *memPointer;
   uint32 memSize;
   TE_USED_STATUS useStatus;
   uint16 priorIndex;
   uint16 nextIndex;
} TS_MEM_BLOCK, *hTS_MEM_BLOCK;
typedef struct{
   void *memPointer;
   uint16 memIndex;
} TS_USED_BLOCK, *hTS_USED_BLOCK;
typedef struct{
   uint32 memSize;
   uint16 memIndex;
} TS_UNUSED_BLOCK, *hTS_UNUSED_BLOCK;

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
* Mem类定义
***********************************************************/
/*Mem类声明
***********************************************/
CL(Mem){
    hMem self;
    hMem (*init)(hMem cthis, uint8 *memSpace, uint32 memSize);

    // Mem类参数
    uint8 *memSpace;
    uint32 memSize;
    uint16 memNewNum;
    uint16 memUnusedNum;
    memMType memBlockMaskMask[MEMCFG_MEM_MASK_MASK_NUM]; /* 每一位代表memBlockMask连续32个字节是否使用完，0未使用完，1已用完 */
    memMType memBlockMask[MEMCFG_MEM_BLOCK_MASK_MAX_NUM]; /* 每一位代表一个块是否被使用 */
    TS_MEM_BLOCK memBlock[MEMCFG_MEM_BLOCK_MAX_NUM];
    TS_USED_BLOCK usedBlockIndex[MEMCFG_MEM_BLOCK_MAX_NUM];
    TS_UNUSED_BLOCK unusedBlockIndex[MEMCFG_MEM_UNUSED_MAX_NUM];

    // Mem类功能函数
    void * (*malloc)(hMem cthis, uint16 size);
    uint16 (*free)(hMem cthis, void *pointer);
    uint16 (*findUnusedIndex)(hMem cthis, uint32 size, uint16 index); /* 返回MEMCFG_MEM_UNUSED_MAX_NUM作为异常状态 */
    uint16 (*findUnusedBigerIndex)(hMem cthis, uint32 size); /* 返回MEMCFG_MEM_UNUSED_MAX_NUM作为异常状态 */
    uint16 (*findUsedIndex)(hMem cthis, void *pointer); /* 返回MEMCFG_MEM_NEW_MAX_NUM作为异常状态 */
    uint16 (*findUsedBigerIndex)(hMem cthis, void *pointer);  /* 返回MEMCFG_MEM_NEW_MAX_NUM作为异常状态 */
    uint16 (*findBlockMaskMinIndex)(hMem cthis);
    void (*setBlockMaskIndex)(hMem cthis, uint16 index);
    void (*clearBlockMaskIndex)(hMem cthis, uint16 index);
    uint16 (*mergeMemBlock)(hMem cthis, uint16 index);
    void (*delUsedIndex)(hMem cthis, uint16 index);
    void (*addUsedIndex)(hMem cthis, uint16 index);
    void (*delUnusedIndex)(hMem cthis, uint16 index);
    void (*delUnusedIndexDirect)(hMem cthis, uint16 unusedIndex);
    void (*addUnusedIndex)(hMem cthis, uint16 index);
};

#endif /*MEM_H_*/

/**************************** Copyright(C) pxf ****************************/
