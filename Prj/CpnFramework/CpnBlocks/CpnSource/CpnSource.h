/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSource.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  : CpnSource�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

#ifndef CPNSOURCE_H_
#define CPNSOURCE_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnSourceCfg.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
***********************************************/
typedef struct{
    uint16 sourceMask;                 /* signal register */
    tSourceParams sourceParams[16];    /* signal run params */
    uint16 sourceCounter[16];          /* signal drive counter */
} tWaveGroup, *htWaveGroup;
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
* CpnSource�ඨ��
***********************************************************/
/*CpnSource������
***********************************************/
CL(CpnSource){
    hCpnSource self;
    hCpnSource (*init)(hCpnSource cthis, void (*setErr)(uint16 id, uint16 code));

    // CpnSource�����
    tWaveGroup waveGroups[w_waveTypeMax][CPNSOURCECFG_WAVE_TYPE_GROUPS];

    // CpnSource�๦�ܺ���
    void (*regist)(hCpnSource cthis, htSourceParams source);
    void (*change)(hCpnSource cthis, htSourceParams source);
    void (*sine)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*pulse)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countUp)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countDown)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countUpDown)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*wave)(hCpnSource cthis, htSourceParams source, float32 *output);
    void (*run)(hCpnSource cthis);
    void (*err)(hCpnSource cthis, uint16 code);
    //TODO

    IMPL(iErr);
};

#endif /*CPNSOURCE_H_*/

/**************************** Copyright(C) pxf ****************************/
