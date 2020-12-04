/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCan.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 16:09:24
* Description  : CpnCan�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

#ifndef CPNCAN_H_
#define CPNCAN_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "./CpnCanCfg.h"

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
extern Fifo clFifoCpnCan;

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
* CpnCan�ඨ��
***********************************************************/
/*CpnCan������
***********************************************/
CL(CpnCan){
    hCpnCan self;
    hCpnCan (*init)(hCpnCan cthis, hFifo clFifoSend);

    // CpnCan�����
    //TODO

    // CpnCan�๦�ܺ���
    void (*run)(hCpnCan cthis);
    void (*send)(hCpnCan cthis);
    void (*receive)(hCpnCan cthis);

    INJ(Fifo, clFifoSend);
};

#endif /*CPNCAN_H_*/

/**************************** Copyright(C) pxf ****************************/
