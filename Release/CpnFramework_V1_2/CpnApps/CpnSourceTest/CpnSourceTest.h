/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceTest.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 17:01:04
* Description  : CpnSourceTest�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

#ifndef CPNSOURCETEST_H_
#define CPNSOURCETEST_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/oopc/oopc.h"

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
* CpnSourceTest�ඨ��
***********************************************************/
/*CpnSourceTest������
***********************************************/
CL(CpnSourceTest){
    hCpnSourceTest self;
    hCpnSourceTest (*init)(hCpnSourceTest cthis);

    // CpnSourceTest�����
    //TODO

    // CpnSourceTest�๦�ܺ���
    void (*run)(hCpnSourceTest cthis);
    void (*testSource)(hCpnSourceTest cthis);
    //TODO
};

#endif /*CPNSOURCETEST_H_*/

/**************************** Copyright(C) pxf ****************************/
