/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceTest.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 17:01:04
* Description  : CpnSourceTest类及接口声明头文件
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

#ifndef CPNSOURCETEST_H_
#define CPNSOURCETEST_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"

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
* CpnSourceTest类定义
***********************************************************/
/*CpnSourceTest类声明
***********************************************/
CL(CpnSourceTest){
    hCpnSourceTest self;
    hCpnSourceTest (*init)(hCpnSourceTest cthis);

    // CpnSourceTest类参数
    //TODO

    // CpnSourceTest类功能函数
    void (*run)(hCpnSourceTest cthis);
    void (*testSource)(hCpnSourceTest cthis);
    //TODO
};

#endif /*CPNSOURCETEST_H_*/

/**************************** Copyright(C) pxf ****************************/
