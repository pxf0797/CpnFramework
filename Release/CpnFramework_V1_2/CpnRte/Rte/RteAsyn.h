/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsyn.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/21 11:57:29
* Description  : RteAsyn类及接口声明头文件
* Others       :
* History      : 191221 pxf 初次建立
***************************************************************************/

#ifndef RTEASYN_H_
#define RTEASYN_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"

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
* RteAsyn类定义
***********************************************************/
/*RteAsyn类声明
***********************************************/
CL(RteAsyn){
    hRteAsyn self;
    hRteAsyn (*init)(hRteAsyn cthis, uint8 *set_buff, uint16 *set_index, uint16 *get_index);

    // RteAsyn类参数
    //TODO
    uint8 *set_buff;
    uint16 *set_index;
    uint16 *get_index;

    // RteAsyn类功能函数
    void (*set)(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len);
    void (*get)(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len);
    //TODO
};

#endif /*RTEASYN_H_*/

/**************************** Copyright(C) pxf ****************************/
