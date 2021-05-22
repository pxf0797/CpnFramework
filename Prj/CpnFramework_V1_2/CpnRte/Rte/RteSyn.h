/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSyn.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 10:05:34
* Description  : RteSyn类及接口声明头文件
* Others       :
* History      : 191222 pxf 初次建立
***************************************************************************/

#ifndef RTESYN_H_
#define RTESYN_H_

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
* RteSyn类定义
***********************************************************/
/*RteSyn类声明
***********************************************/
CL(RteSyn){
    hRteSyn self;
    hRteSyn (*init)(hRteSyn cthis, void **serv_ServBuff, uint16 *trig_index);

    // RteSyn类参数
    void **serv_ServBuff;
    uint16 *trig_index;

    // RteSyn类功能函数
    void (*serv)(hRteSyn cthis, uint16 signal, uint8 *buff);
    void (*trig)(hRteSyn cthis, uint16 signal, uint8 *buff);
    //TODO
};

#endif /*RTESYN_H_*/

/**************************** Copyright(C) pxf ****************************/
