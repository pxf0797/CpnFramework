/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErr.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  : CpnErr类及接口声明头文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

#ifndef CPNERR_H_
#define CPNERR_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "./CpnErrCfg.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据声明
***********************************************/
typedef struct{
    uint16 id;
    uint16 code;
} tErrCode;

extern Fifo clFifoCpnErr;

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
* CpnErr类定义
***********************************************************/
/*CpnErr类声明
***********************************************/
CL(CpnErr){
    hCpnErr self;
    hCpnErr (*init)(hCpnErr cthis, hFifo clFifo);

    // CpnErr类参数
    uint16 uwTotalErrNum;

    // CpnErr类功能函数
    void (*run)(hCpnErr cthis);
    uint16 (*setErr)(hCpnErr cthis, uint32 errCode);
    //TODO

    INJ(Fifo, clFifo);
};

#endif /*CPNERR_H_*/

/**************************** Copyright(C) pxf ****************************/
