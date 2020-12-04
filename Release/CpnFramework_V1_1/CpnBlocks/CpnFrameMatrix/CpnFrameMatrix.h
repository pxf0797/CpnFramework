/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrix.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  : CpnFrameMatrix类及接口声明头文件
* Others       :
* History      : 201120 pxf 初次建立
***************************************************************************/

#ifndef CPNFRAMEMATRIX_H_
#define CPNFRAMEMATRIX_H_

/*头文件包含*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"
#include "./CpnFrameMatrixCfg.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNFRAMEMATRIX_MACRO_VERSION    0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
typedef union
{
   uint8 byte[CPNFRAMEMATRIXCFG_FRAME_BYTES];
   uint32 data[CPNFRAMEMATRIXCFG_FRAME_BYTES>>2];
} TU_BYTES_DATA, *hTU_BYTES_DATA;


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
* CpnFrameMatrix类定义
***********************************************************/
/*CpnFrameMatrix类声明
***********************************************/
CL(CpnFrameMatrix){
    hCpnFrameMatrix self;
    hCpnFrameMatrix (*init)(hCpnFrameMatrix cthis, uint32 id, TE_RXTX_TYPE rxtx, TE_FRAME_FORMAT format, uint16 period);

    // CpnFrameMatrix类参数
    uint32 id;
    TE_RXTX_TYPE rxtx;
    TE_FRAME_FORMAT format;
    TU_BYTES_DATA frame;
    uint16 period; /* MS */
    uint16 counter; /* MS */

    // CpnFrameMatrix类功能函数
    void (*get_frame)(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 *value);
    void (*set_frame)(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 value);
    //TODO
};

#endif /*CPNFRAMEMATRIX_H_*/

/**************************** Copyright(C) pxf ****************************/
