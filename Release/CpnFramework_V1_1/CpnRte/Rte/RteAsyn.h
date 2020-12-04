/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsyn.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/21 11:57:29
* Description  : RteAsyn�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 191221 pxf ���ν���
***************************************************************************/

#ifndef RTEASYN_H_
#define RTEASYN_H_

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
* RteAsyn�ඨ��
***********************************************************/
/*RteAsyn������
***********************************************/
CL(RteAsyn){
    hRteAsyn self;
    hRteAsyn (*init)(hRteAsyn cthis, uint8 *set_buff, uint16 *set_index, uint16 *get_index);

    // RteAsyn�����
    //TODO
    uint8 *set_buff;
    uint16 *set_index;
    uint16 *get_index;

    // RteAsyn�๦�ܺ���
    void (*set)(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len);
    void (*get)(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len);
    //TODO
};

#endif /*RTEASYN_H_*/

/**************************** Copyright(C) pxf ****************************/
