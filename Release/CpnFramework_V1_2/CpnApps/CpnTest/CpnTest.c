/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTest.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/23 17:26:23
* Description  : CpnTest������ܺ�������Դ�ļ�
* Others       : 
* History      : 200723 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnTest.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnTest�ඨ��
***********************************************************/
/*���� : CpnTest_run(hCpnTest cthis)
* ���� : cthis - CpnTest��ָ��
* ��� : ��
* ���� : CpnTest�๦�ܺ���
***********************************************/
void CpnTest_run(hCpnTest cthis){
    //TODO
}

/*���� : hCpnTest CpnTest_init(hCpnTest cthis)
* ���� : cthis - CpnTest��ָ��
* ��� : hCpnTest - cthis/OOPC_NULL
* ���� : CpnTest���ʼ������
***********************************************/
hCpnTest CpnTest_init(hCpnTest cthis){
    // ���ܺ�������
    //cthis->run = CpnTest_run;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnTest CpnTest_ctor(hCpnTest cthis)
* ���� : cthis - CpnTest��ָ��
* ��� : hCpnTest - cthis/OOPC_NULL
* ���� : CpnTest�๹�캯��
***********************************************/
CC(CpnTest){
    cthis->init = CpnTest_init;
    cthis->run = CpnTest_run;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCpnTest CpnTest_dtor(hCpnTest cthis)
* ���� : cthis - CpnTest��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnTest����������
***********************************************/
CD(CpnTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
