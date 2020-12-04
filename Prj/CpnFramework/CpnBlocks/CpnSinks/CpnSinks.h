/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinks.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  : CpnSinks�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 200730 pxf ���ν���
***************************************************************************/

#ifndef CPNSINKS_H_
#define CPNSINKS_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "./CpnSinksCfg.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
***********************************************/
typedef struct{
    uint16 cacheMask;                  /* signal register */
    uint16 startMask;                  /* start to cache mask */
    tSinksParams sinksParams[16];      /* signal run params */
    uint16 cacheCounter[16];           /* signal drive counter */
    Fifo cacheFifo[16];                /* fifo cache data */
} tCacheGroup, *htCacheGroup;
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
* CpnSinks�ඨ��
***********************************************************/
/*CpnSinks������
***********************************************/
CL(CpnSinks){
    hCpnSinks self;
    hCpnSinks (*init)(hCpnSinks cthis, void (*setErr)(uint16 id, uint16 code));

    // CpnSinks�����
    tCacheGroup cacheGroups[CPNSINKSCFG_CACHE_TYPE_GROUPS];

    // CpnSinks�๦�ܺ���
    void (*run)(hCpnSinks cthis);
    uint16 (*readData)(hCpnSinks cthis, htSinksParams sinks, void *buff);
    void (*trigStart)(hCpnSinks cthis, htSinksParams sinks);
    void (*cacheData)(hCpnSinks cthis, htSinksParams sinks);
    tCacheProcessSta (*cacheSta)(hCpnSinks cthis, htSinksParams sinks);
    void (*cacheEnd)(hCpnSinks cthis, htSinksParams sinks);
    void (*registCache)(hCpnSinks cthis, htSinksParams sinks);
    void (*reCache)(hCpnSinks cthis, htSinksParams sinks);
    void (*err)(hCpnSinks cthis, uint16 code);
    //TODO

    IMPL(iErr);
};

#endif /*CPNSINKS_H_*/

/**************************** Copyright(C) pxf ****************************/
