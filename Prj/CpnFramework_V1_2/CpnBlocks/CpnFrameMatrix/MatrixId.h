/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : MatrixId.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/23 13:40:26
* Description  : MatrixId类及接口声明头文件
* Others       :
* History      : 201123 pxf 初次建立
***************************************************************************/

#ifndef MATRIXID_H_
#define MATRIXID_H_

/*头文件包含*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"
#include "./CpnFrameMatrix.h"

/***********************************************************
* 版本定义
***********************************************************/
#define MATRIXID_MACRO_VERSION          0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
* MatrixId类定义
***********************************************************/
/*MatrixId类声明
***********************************************/
CL(MatrixId){
    hMatrixId self;
    hMatrixId (*init)(hMatrixId cthis, FrameMatrix matrixDatas[], uint32 ulMatrixId[], uint16 uwMatrixIdIndex[], uint16 ulMatrixIdNum);

    // MatrixId类参数
    uint32 *ulMatrixId;
    uint16 *uwMatrixIdIndex;
    uint16 ulMatrixIdNum;

    // MatrixId类功能函数
    uint16 (*getIdIndex)(hMatrixId cthis, uint32 ulMatrixId); /* id not exist, return CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS */
    //TODO
};

#endif /*MATRIXID_H_*/

/**************************** Copyright(C) pxf ****************************/
