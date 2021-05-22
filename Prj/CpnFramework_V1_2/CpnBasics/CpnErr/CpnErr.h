/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErr.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  : CpnErr�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

#ifndef CPNERR_H_
#define CPNERR_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "./CpnErrCfg.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
***********************************************/
typedef struct{
    uint16 id;
    uint16 code;
} tErrCode;

extern Fifo clFifoCpnErr;

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
* CpnErr�ඨ��
***********************************************************/
/*CpnErr������
***********************************************/
CL(CpnErr){
    hCpnErr self;
    hCpnErr (*init)(hCpnErr cthis, hFifo clFifo);

    // CpnErr�����
    uint16 uwTotalErrNum;

    // CpnErr�๦�ܺ���
    void (*run)(hCpnErr cthis);
    uint16 (*setErr)(hCpnErr cthis, uint32 errCode);
    //TODO

    INJ(Fifo, clFifo);
};

#endif /*CPNERR_H_*/

/**************************** Copyright(C) pxf ****************************/
