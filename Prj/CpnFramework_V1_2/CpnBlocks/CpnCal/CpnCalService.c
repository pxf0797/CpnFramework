/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalService.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:39:49
* Description  : CpnCalService������ܺ�������Դ�ļ�
* Others       : 
* History      : 201212 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCalService.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnCalService�ඨ��
***********************************************************/
/*���� : CpnCalService_run(hCpnCalService cthis)
* ���� : cthis - CpnCalService��ָ��
* ��� : ��
* ���� : CpnCalService�๦�ܺ���
***********************************************/
void CpnCalService_run(hCpnCalService cthis){
    //TODO
}

/*���� : hCpnCalService CpnCalService_init(hCpnCalService cthis)
* ���� : cthis - CpnCalService��ָ��
* ��� : hCpnCalService - cthis/OOPC_NULL
* ���� : CpnCalService���ʼ������
***********************************************/
hCpnCalService CpnCalService_init(hCpnCalService cthis){
    // ���ܺ�������
    //cthis->run = CpnCalService_run;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnCalService CpnCalService_ctor(hCpnCalService cthis)
* ���� : cthis - CpnCalService��ָ��
* ��� : hCpnCalService - cthis/OOPC_NULL
* ���� : CpnCalService�๹�캯��
***********************************************/
CC(CpnCalService){
    cthis->init = CpnCalService_init;
    cthis->run = CpnCalService_run;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCpnCalService CpnCalService_dtor(hCpnCalService cthis)
* ���� : cthis - CpnCalService��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnCalService����������
***********************************************/
CD(CpnCalService){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
