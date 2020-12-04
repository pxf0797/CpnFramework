/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinks.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  : CpnSinks类及接口声明头文件
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

#ifndef CPNSINKS_H_
#define CPNSINKS_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "./CpnSinksCfg.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据声明
***********************************************/
typedef struct{
    uint16 cacheMask;                  /* signal register */
    uint16 startMask;                  /* start to cache mask */
    tSinksParams sinksParams[16];      /* signal run params */
    uint16 cacheCounter[16];           /* signal drive counter */
    Fifo cacheFifo[16];                /* fifo cache data */
} tCacheGroup, *htCacheGroup;
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
* CpnSinks类定义
***********************************************************/
/*CpnSinks类声明
***********************************************/
CL(CpnSinks){
    hCpnSinks self;
    hCpnSinks (*init)(hCpnSinks cthis, void (*setErr)(uint16 id, uint16 code));

    // CpnSinks类参数
    tCacheGroup cacheGroups[CPNSINKSCFG_CACHE_TYPE_GROUPS];

    // CpnSinks类功能函数
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
