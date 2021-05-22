/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalCommand.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:39:13
* Description  : CpnCalCommand类及接口声明头文件
* Others       : 
* History      : 201212 pxf 初次建立
***************************************************************************/

#ifndef CPNCALCOMMAND_H_
#define CPNCALCOMMAND_H_

/*头文件包含*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNCALCOMMAND_MACRO_VERSION     0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
* CpnCalCommand类定义
***********************************************************/
/*CpnCalCommand类声明
***********************************************/
CL(CpnCalCommand){
    hCpnCalCommand self;
    hCpnCalCommand (*init)(hCpnCalCommand cthis);

    // CpnCalCommand类参数
    //TODO

    // CpnCalCommand类功能函数
    void (*run)(hCpnCalCommand cthis);
    //TODO
};

#endif /*CPNCALCOMMAND_H_*/

/**************************** Copyright(C) pxf ****************************/
