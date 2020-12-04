/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrix.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  : CpnFrameMatrix�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 201120 pxf ���ν���
***************************************************************************/

#ifndef CPNFRAMEMATRIX_H_
#define CPNFRAMEMATRIX_H_

/*ͷ�ļ�����*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"
#include "./CpnFrameMatrixCfg.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNFRAMEMATRIX_MACRO_VERSION    0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
typedef union
{
   uint8 byte[CPNFRAMEMATRIXCFG_FRAME_BYTES];
   uint32 data[CPNFRAMEMATRIXCFG_FRAME_BYTES>>2];
} TU_BYTES_DATA, *hTU_BYTES_DATA;


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
* CpnFrameMatrix�ඨ��
***********************************************************/
/*CpnFrameMatrix������
***********************************************/
CL(CpnFrameMatrix){
    hCpnFrameMatrix self;
    hCpnFrameMatrix (*init)(hCpnFrameMatrix cthis, uint32 id, TE_RXTX_TYPE rxtx, TE_FRAME_FORMAT format, uint16 period);

    // CpnFrameMatrix�����
    uint32 id;
    TE_RXTX_TYPE rxtx;
    TE_FRAME_FORMAT format;
    TU_BYTES_DATA frame;
    uint16 period; /* MS */
    uint16 counter; /* MS */

    // CpnFrameMatrix�๦�ܺ���
    void (*get_frame)(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 *value);
    void (*set_frame)(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 value);
    //TODO
};

#endif /*CPNFRAMEMATRIX_H_*/

/**************************** Copyright(C) pxf ****************************/
