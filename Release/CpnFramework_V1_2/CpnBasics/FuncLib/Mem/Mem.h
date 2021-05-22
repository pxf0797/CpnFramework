/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Mem.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/05 13:45:23
* Description  : Mem�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 201205 pxf ���ν���
***************************************************************************/

#ifndef MEM_H_
#define MEM_H_

/*ͷ�ļ�����*/
#include "../../../cpnBasics/standType/standType.h"
#include "../../../cpnBasics/oopc/oopc.h"
#include "./MemCfg.h"

/***********************************************************
* �汾����
***********************************************************/
#define MEM_MACRO_VERSION               0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
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

/*��������
***********************************************/
//TODO

/***********************************************************
* �ӿڶ���
***********************************************************/
/*�ӿ�����
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* Mem�ඨ��
***********************************************************/
/*Mem������
***********************************************/
CL(Mem){
    hMem self;
    hMem (*init)(hMem cthis, uint8 *memSpace, uint32 memSize);

    // Mem�����
    uint8 *memSpace;
    uint32 memSize;
    uint16 memNewNum;
    uint16 memUnusedNum;
    memMType memBlockMaskMask[MEMCFG_MEM_MASK_MASK_NUM]; /* ÿһλ����memBlockMask����32���ֽ��Ƿ�ʹ���꣬0δʹ���꣬1������ */
    memMType memBlockMask[MEMCFG_MEM_BLOCK_MASK_MAX_NUM]; /* ÿһλ����һ�����Ƿ�ʹ�� */
    TS_MEM_BLOCK memBlock[MEMCFG_MEM_BLOCK_MAX_NUM];
    TS_USED_BLOCK usedBlockIndex[MEMCFG_MEM_BLOCK_MAX_NUM];
    TS_UNUSED_BLOCK unusedBlockIndex[MEMCFG_MEM_UNUSED_MAX_NUM];

    // Mem�๦�ܺ���
    void * (*malloc)(hMem cthis, uint16 size);
    uint16 (*free)(hMem cthis, void *pointer);
    uint16 (*findUnusedIndex)(hMem cthis, uint32 size, uint16 index); /* ����MEMCFG_MEM_UNUSED_MAX_NUM��Ϊ�쳣״̬ */
    uint16 (*findUnusedBigerIndex)(hMem cthis, uint32 size); /* ����MEMCFG_MEM_UNUSED_MAX_NUM��Ϊ�쳣״̬ */
    uint16 (*findUsedIndex)(hMem cthis, void *pointer); /* ����MEMCFG_MEM_NEW_MAX_NUM��Ϊ�쳣״̬ */
    uint16 (*findUsedBigerIndex)(hMem cthis, void *pointer);  /* ����MEMCFG_MEM_NEW_MAX_NUM��Ϊ�쳣״̬ */
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
