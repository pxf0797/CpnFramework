/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSyn.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 10:05:34
* Description  : RteSyn�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 191222 pxf ���ν���
***************************************************************************/

#ifndef RTESYN_H_
#define RTESYN_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"

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
* RteSyn�ඨ��
***********************************************************/
/*RteSyn������
***********************************************/
CL(RteSyn){
    hRteSyn self;
    hRteSyn (*init)(hRteSyn cthis, void **serv_ServBuff, uint16 *trig_index);

    // RteSyn�����
    void **serv_ServBuff;
    uint16 *trig_index;

    // RteSyn�๦�ܺ���
    void (*serv)(hRteSyn cthis, uint16 signal, uint8 *buff);
    void (*trig)(hRteSyn cthis, uint16 signal, uint8 *buff);
    //TODO
};

#endif /*RTESYN_H_*/

/**************************** Copyright(C) pxf ****************************/
