/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksTest.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 19:07:35
* Description  : CpnSinksTest�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 200730 pxf ���ν���
***************************************************************************/

#ifndef CPNSINKSTEST_H_
#define CPNSINKSTEST_H_

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
* CpnSinksTest�ඨ��
***********************************************************/
/*CpnSinksTest������
***********************************************/
CL(CpnSinksTest){
    hCpnSinksTest self;
    hCpnSinksTest (*init)(hCpnSinksTest cthis);

    // CpnSinksTest�����
    //TODO

    // CpnSinksTest�๦�ܺ���
    void (*run)(hCpnSinksTest cthis);
    void (*testSinks)(hCpnSinksTest cthis);
    //TODO
};

#endif /*CPNSINKSTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
