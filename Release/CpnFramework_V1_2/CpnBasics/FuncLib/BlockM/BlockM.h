/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : BlockM.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2021/03/20 16:42:53
* Description  : BlockM�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 210320 pxf ���ν���
***************************************************************************/

#ifndef BLOCKM_H_
#define BLOCKM_H_

/*ͷ�ļ�����*/
#include "../../../cpnBasics/standType/standType.h"
#include "../../../cpnBasics/oopc/oopc.h"
#include "BlockMCfg.h"

/***********************************************************
* �汾����
***********************************************************/
#define BLOCKM_MACRO_VERSION            0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

#define BLOCKM_INDEX_BITINDEX(index)    (((index)&BLOCKMCFG_MANAG_TYPE_MASK))
#define BLOCKM_INDEX_MASKINDEX(index)   (((index)>>BLOCKMCFG_MANAG_TYPE_BITS))
#define BLOCKM_BITINDEX_MASK(index)     ((blockMType)0x1u<<((index)&BLOCKMCFG_MANAG_TYPE_MASK))

/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
***********************************************/
//typedef struct{
//    uint16 id;
//    uint16 code;
//} tErrCode;
//TODO
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
* BlockM�ඨ��
***********************************************************/
/*BlockM������
***********************************************/
CL(BlockM){
    hBlockM self;
    hBlockM (*init)(hBlockM cthis, uint8 *blockMSpace, uint16 blockMSize, uint16 blockMMax);

    // BlockM�����
    uint8 *blockMSpace; /* ����ռ�ָ�� */
    uint8 *blockMPointer; /* ���ָ�� */
    uint16 blockMSize;
    uint16 blockMMax;
    uint16 blockMCounter;
    uint16 blockMMaskMaskMaskMax; /* MaskMaskMask������ */
    uint16 blockMMaskMaskMax; /* MaskMask������ */
    uint16 blockMMaskMax; /* Mask������ */
    blockMType *blockMMaskMaskMask; /* ÿһλ����memBlockMask����32���ֽ��Ƿ�ʹ����s��0δʹ���꣬1������ */
    blockMType *blockMMaskMask; /* ÿһλ����memBlockMask����32���ֽ��Ƿ�ʹ���꣬0δʹ���꣬1������ */
    /*
     * bit                  7  6  5  4  3  2  1  0
     * blockMMask           0  0  1  0  0  1  1  0
     * blockMMaskContinue   0  1  1  1  1  1  0  0
     * ������3���飬1�����飬2��������
     * block1,block2c3,block5c2
     * */
    blockMType *blockMMask; /* ÿһλ����һ�����Ƿ�ʹ�ã�������ֻ��ʶ��ʼλ */
    blockMType *blockMMaskContinue; /* ÿһλ�����Ƿ������飬��������ʼλ��ӦblockMMaskһ������λ */

    // BlockM�๦�ܺ���
    void * (*malloc)(hBlockM cthis, uint16 size);
    uint16 (*free)(hBlockM cthis, void *pointer);

    /* ��bit������ƺ��� */
    uint16 (*findMinIndex)(hBlockM cthis);
    void (*setMaskIndex)(hBlockM cthis, uint16 index);
    void (*clearMaskIndex)(hBlockM cthis, uint16 index);

    /* ����bit������ƺ��� */
    uint16 (*findContinueMinIndex)(hBlockM cthis, uint16 count);
    void (*setContinueMaskIndex)(hBlockM cthis, uint16 index, uint16 count);
    void (*clearContinueMaskIndex)(hBlockM cthis, uint16 index);

    uint16 (*isPointerSet)(hBlockM cthis, void *pointer);
    uint16 (*isIndexSet)(hBlockM cthis, uint16 index);
    uint16 (*isIndexContiueSet)(hBlockM cthis, uint16 index);
    uint16 (*isFull)(hBlockM cthis);

    uint16 (*getSize)(hBlockM cthis, void *pointer); /* ����0��Ϊ�쳣״̬ */
    uint16 (*getIndex)(hBlockM cthis, void *pointer); /* ����blockMMax��Ϊ�쳣״̬ */
    void* (*getAddr)(hBlockM cthis, uint16 index);

    uint16 (*getCounts)(hBlockM cthis);
    uint16 (*getMax)(hBlockM cthis);
};

#endif /*BLOCKM_H_*/

/**************************** Copyright(C) pxf ****************************/
