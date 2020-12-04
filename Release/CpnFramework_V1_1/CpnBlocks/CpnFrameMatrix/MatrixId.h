/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : MatrixId.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/23 13:40:26
* Description  : MatrixId�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 201123 pxf ���ν���
***************************************************************************/

#ifndef MATRIXID_H_
#define MATRIXID_H_

/*ͷ�ļ�����*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"
#include "./CpnFrameMatrix.h"

/***********************************************************
* �汾����
***********************************************************/
#define MATRIXID_MACRO_VERSION          0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
***********************************************/
//typedef struct{
//    uint16 id;
//    uint16 code;
//} tErrCode;
//TODO
/*��������
***********************************************/
//TODO

/***********************************************************
* �ӿڶ���
***********************************************************/
/*�ӿ�����
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* MatrixId�ඨ��
***********************************************************/
/*MatrixId������
***********************************************/
CL(MatrixId){
    hMatrixId self;
    hMatrixId (*init)(hMatrixId cthis, FrameMatrix matrixDatas[], uint32 ulMatrixId[], uint16 uwMatrixIdIndex[], uint16 ulMatrixIdNum);

    // MatrixId�����
    uint32 *ulMatrixId;
    uint16 *uwMatrixIdIndex;
    uint16 ulMatrixIdNum;

    // MatrixId�๦�ܺ���
    uint16 (*getIdIndex)(hMatrixId cthis, uint32 ulMatrixId); /* id not exist, return CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS */
    //TODO
};

#endif /*MATRIXID_H_*/

/**************************** Copyright(C) pxf ****************************/
