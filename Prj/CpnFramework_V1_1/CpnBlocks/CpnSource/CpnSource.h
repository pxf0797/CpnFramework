/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSource.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  : CpnSource类及接口声明头文件
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

#ifndef CPNSOURCE_H_
#define CPNSOURCE_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnSourceCfg.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据声明
***********************************************/
typedef struct{
    uint16 sourceMask;                 /* signal register */
    tSourceParams sourceParams[16];    /* signal run params */
    uint16 sourceCounter[16];          /* signal drive counter */
} tWaveGroup, *htWaveGroup;
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
* CpnSource类定义
***********************************************************/
/*CpnSource类声明
***********************************************/
CL(CpnSource){
    hCpnSource self;
    hCpnSource (*init)(hCpnSource cthis, void (*setErr)(uint16 id, uint16 code));

    // CpnSource类参数
    tWaveGroup waveGroups[w_waveTypeMax][CPNSOURCECFG_WAVE_TYPE_GROUPS];

    // CpnSource类功能函数
    void (*regist)(hCpnSource cthis, htSourceParams source);
    void (*change)(hCpnSource cthis, htSourceParams source);
    void (*sine)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*pulse)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countUp)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countDown)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countUpDown)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*wave)(hCpnSource cthis, htSourceParams source, float32 *output);
    void (*run)(hCpnSource cthis);
    void (*err)(hCpnSource cthis, uint16 code);
    //TODO

    IMPL(iErr);
};

#endif /*CPNSOURCE_H_*/

/**************************** Copyright(C) pxf ****************************/
