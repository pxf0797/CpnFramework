/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCan.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 16:09:24
* Description  : CpnCan类及接口声明头文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

#ifndef CPNCAN_H_
#define CPNCAN_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "./CpnCanCfg.h"

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
extern Fifo clFifoCpnCan;

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
* CpnCan类定义
***********************************************************/
/*CpnCan类声明
***********************************************/
CL(CpnCan){
    hCpnCan self;
    hCpnCan (*init)(hCpnCan cthis, hFifo clFifoSend);

    // CpnCan类参数
    //TODO

    // CpnCan类功能函数
    void (*run)(hCpnCan cthis);
    void (*send)(hCpnCan cthis);
    void (*receive)(hCpnCan cthis);

    INJ(Fifo, clFifoSend);
};

#endif /*CPNCAN_H_*/

/**************************** Copyright(C) pxf ****************************/
