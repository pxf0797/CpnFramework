/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapTest.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 20:32:16
* Description  : CpnMatrixMapTest类及接口声明头文件
* Others       : 
* History      : 201202 pxf 初次建立
***************************************************************************/

#ifndef CPNMATRIXMAPTEST_H_
#define CPNMATRIXMAPTEST_H_

/*头文件包含*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNMATRIXMAPTEST_MACRO_VERSION  0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
* CpnMatrixMapTest类定义
***********************************************************/
/*CpnMatrixMapTest类声明
***********************************************/
CL(CpnMatrixMapTest){
    hCpnMatrixMapTest self;
    hCpnMatrixMapTest (*init)(hCpnMatrixMapTest cthis);

    // CpnMatrixMapTest类参数
    //TODO

    // CpnMatrixMapTest类功能函数
    void (*run)(hCpnMatrixMapTest cthis);
    //TODO
};

#endif /*CPNMATRIXMAPTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
