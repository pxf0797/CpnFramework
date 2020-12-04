/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrix.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  : CpnFrameMatrix������ܺ�������Դ�ļ�
* Others       :
* History      : 201120 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnFrameMatrix.h"
#include "./FrameBitLib.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnFrameMatrix�ඨ��
***********************************************************/
/*���� : CpnFrameMatrix_get_frame(hCpnFrameMatrix cthis)
* ���� : cthis - CpnFrameMatrix��ָ��
* ��� : ��
* ���� : CpnFrameMatrix�๦�ܺ���
***********************************************/
void CpnFrameMatrix_get_frame(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 *value){
    getFrameData(cthis->frame.data, cthis->format, bit_start, bit_len, value);
}

/*���� : CpnFrameMatrix_set_frame(hCpnFrameMatrix cthis)
* ���� : cthis - CpnFrameMatrix��ָ��
* ��� : ��
* ���� : CpnFrameMatrix�๦�ܺ���
***********************************************/
void CpnFrameMatrix_set_frame(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 value){
    setFrameData(cthis->frame.data, cthis->format, bit_start, bit_len, value);
}

/*���� : hCpnFrameMatrix CpnFrameMatrix_init(hCpnFrameMatrix cthis)
* ���� : cthis - CpnFrameMatrix��ָ��
* ��� : hCpnFrameMatrix - cthis/OOPC_NULL
* ���� : CpnFrameMatrix���ʼ������
***********************************************/
hCpnFrameMatrix CpnFrameMatrix_init(hCpnFrameMatrix cthis, uint32 id, TE_RXTX_TYPE rxtx, TE_FRAME_FORMAT format, uint16 period){
    // ���ܺ�������
    //cthis->get_frame = CpnFrameMatrix_get_frame;
    //TODO

    // ��������
    cthis->id = id;
    cthis->rxtx = rxtx;
    cthis->format = format;
    cthis->period = period;

    return cthis;
}

/*���� : hCpnFrameMatrix CpnFrameMatrix_ctor(hCpnFrameMatrix cthis)
* ���� : cthis - CpnFrameMatrix��ָ��
* ��� : hCpnFrameMatrix - cthis/OOPC_NULL
* ���� : CpnFrameMatrix�๹�캯��
***********************************************/
CC(CpnFrameMatrix){
    cthis->init = CpnFrameMatrix_init;
    cthis->get_frame = CpnFrameMatrix_get_frame;
    cthis->set_frame = CpnFrameMatrix_set_frame;
    //TODO

    // ��������
    cthis->counter = 0;
    memSet(cthis->frame.data, 0, sizeof(cthis->frame.data));

    return cthis;
}

/*���� : hCpnFrameMatrix CpnFrameMatrix_dtor(hCpnFrameMatrix cthis)
* ���� : cthis - CpnFrameMatrix��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnFrameMatrix����������
***********************************************/
CD(CpnFrameMatrix){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
