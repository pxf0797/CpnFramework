/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrix.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  : CpnFrameMatrix类各功能函数定义源文件
* Others       :
* History      : 201120 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnFrameMatrix.h"
#include "./FrameBitLib.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* CpnFrameMatrix类定义
***********************************************************/
/*名称 : CpnFrameMatrix_get_frame(hCpnFrameMatrix cthis)
* 输入 : cthis - CpnFrameMatrix类指针
* 输出 : 无
* 其他 : CpnFrameMatrix类功能函数
***********************************************/
void CpnFrameMatrix_get_frame(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 *value){
    getFrameData(cthis->frame.data, cthis->format, bit_start, bit_len, value);
}

/*名称 : CpnFrameMatrix_set_frame(hCpnFrameMatrix cthis)
* 输入 : cthis - CpnFrameMatrix类指针
* 输出 : 无
* 其他 : CpnFrameMatrix类功能函数
***********************************************/
void CpnFrameMatrix_set_frame(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 value){
    setFrameData(cthis->frame.data, cthis->format, bit_start, bit_len, value);
}

/*名称 : hCpnFrameMatrix CpnFrameMatrix_init(hCpnFrameMatrix cthis)
* 输入 : cthis - CpnFrameMatrix类指针
* 输出 : hCpnFrameMatrix - cthis/OOPC_NULL
* 其他 : CpnFrameMatrix类初始化函数
***********************************************/
hCpnFrameMatrix CpnFrameMatrix_init(hCpnFrameMatrix cthis, uint32 id, TE_RXTX_TYPE rxtx, TE_FRAME_FORMAT format, uint16 period){
    // 功能函数配置
    //cthis->get_frame = CpnFrameMatrix_get_frame;
    //TODO

    // 参数配置
    cthis->id = id;
    cthis->rxtx = rxtx;
    cthis->format = format;
    cthis->period = period;

    return cthis;
}

/*名称 : hCpnFrameMatrix CpnFrameMatrix_ctor(hCpnFrameMatrix cthis)
* 输入 : cthis - CpnFrameMatrix类指针
* 输出 : hCpnFrameMatrix - cthis/OOPC_NULL
* 其他 : CpnFrameMatrix类构造函数
***********************************************/
CC(CpnFrameMatrix){
    cthis->init = CpnFrameMatrix_init;
    cthis->get_frame = CpnFrameMatrix_get_frame;
    cthis->set_frame = CpnFrameMatrix_set_frame;
    //TODO

    // 参数配置
    cthis->counter = 0;
    memSet(cthis->frame.data, 0, sizeof(cthis->frame.data));

    return cthis;
}

/*名称 : hCpnFrameMatrix CpnFrameMatrix_dtor(hCpnFrameMatrix cthis)
* 输入 : cthis - CpnFrameMatrix类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnFrameMatrix类析构函数
***********************************************/
CD(CpnFrameMatrix){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
