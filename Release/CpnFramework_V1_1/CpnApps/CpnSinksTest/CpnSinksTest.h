/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksTest.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 19:07:35
* Description  : CpnSinksTest类及接口声明头文件
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

#ifndef CPNSINKSTEST_H_
#define CPNSINKSTEST_H_

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
* CpnSinksTest类定义
***********************************************************/
/*CpnSinksTest类声明
***********************************************/
CL(CpnSinksTest){
    hCpnSinksTest self;
    hCpnSinksTest (*init)(hCpnSinksTest cthis);

    // CpnSinksTest类参数
    //TODO

    // CpnSinksTest类功能函数
    void (*run)(hCpnSinksTest cthis);
    void (*testSinks)(hCpnSinksTest cthis);
    //TODO
};

#endif /*CPNSINKSTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
