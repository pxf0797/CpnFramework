/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapTest.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 20:32:16
* Description  : CpnMatrixMapTest�༰�ӿ�����ͷ�ļ�
* Others       : 
* History      : 201202 pxf ���ν���
***************************************************************************/

#ifndef CPNMATRIXMAPTEST_H_
#define CPNMATRIXMAPTEST_H_

/*ͷ�ļ�����*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNMATRIXMAPTEST_MACRO_VERSION  0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
* CpnMatrixMapTest�ඨ��
***********************************************************/
/*CpnMatrixMapTest������
***********************************************/
CL(CpnMatrixMapTest){
    hCpnMatrixMapTest self;
    hCpnMatrixMapTest (*init)(hCpnMatrixMapTest cthis);

    // CpnMatrixMapTest�����
    //TODO

    // CpnMatrixMapTest�๦�ܺ���
    void (*run)(hCpnMatrixMapTest cthis);
    //TODO
};

#endif /*CPNMATRIXMAPTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
