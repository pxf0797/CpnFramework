/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalTimer.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:45:32
* Description  : CpnCalTimer������ܺ�������Դ�ļ�
* Others       : 
* History      : 201212 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCalTimer.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnCalTimer�ඨ��
***********************************************************/
/*���� : CpnCalTimer_run(hCpnCalTimer cthis)
* ���� : cthis - CpnCalTimer��ָ��
* ��� : ��
* ���� : CpnCalTimer�๦�ܺ���
***********************************************/
void CpnCalTimer_run(hCpnCalTimer cthis){
    //TODO
}

/*���� : hCpnCalTimer CpnCalTimer_init(hCpnCalTimer cthis)
* ���� : cthis - CpnCalTimer��ָ��
* ��� : hCpnCalTimer - cthis/OOPC_NULL
* ���� : CpnCalTimer���ʼ������
***********************************************/
hCpnCalTimer CpnCalTimer_init(hCpnCalTimer cthis){
    // ���ܺ�������
    //cthis->run = CpnCalTimer_run;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnCalTimer CpnCalTimer_ctor(hCpnCalTimer cthis)
* ���� : cthis - CpnCalTimer��ָ��
* ��� : hCpnCalTimer - cthis/OOPC_NULL
* ���� : CpnCalTimer�๹�캯��
***********************************************/
CC(CpnCalTimer){
    cthis->init = CpnCalTimer_init;
    cthis->run = CpnCalTimer_run;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCpnCalTimer CpnCalTimer_dtor(hCpnCalTimer cthis)
* ���� : cthis - CpnCalTimer��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnCalTimer����������
***********************************************/
CD(CpnCalTimer){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
