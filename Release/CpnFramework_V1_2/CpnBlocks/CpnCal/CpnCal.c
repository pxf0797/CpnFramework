/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCal.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:06:36
* Description  : CpnCal������ܺ�������Դ�ļ�
* Others       : 
* History      : 201212 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCal.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnCal�ඨ��
***********************************************************/
/*���� : CpnCal_run(hCpnCal cthis)
* ���� : cthis - CpnCal��ָ��
* ��� : ��
* ���� : CpnCal�๦�ܺ���
***********************************************/
void CpnCal_run(hCpnCal cthis){
    //TODO
}

/*���� : hCpnCal CpnCal_init(hCpnCal cthis)
* ���� : cthis - CpnCal��ָ��
* ��� : hCpnCal - cthis/OOPC_NULL
* ���� : CpnCal���ʼ������
***********************************************/
hCpnCal CpnCal_init(hCpnCal cthis){
    // ���ܺ�������
    //cthis->run = CpnCal_run;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnCal CpnCal_ctor(hCpnCal cthis)
* ���� : cthis - CpnCal��ָ��
* ��� : hCpnCal - cthis/OOPC_NULL
* ���� : CpnCal�๹�캯��
***********************************************/
CC(CpnCal){
    cthis->init = CpnCal_init;
    cthis->run = CpnCal_run;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCpnCal CpnCal_dtor(hCpnCal cthis)
* ���� : cthis - CpnCal��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnCal����������
***********************************************/
CD(CpnCal){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
