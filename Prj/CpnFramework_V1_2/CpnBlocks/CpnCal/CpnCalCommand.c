/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalCommand.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:39:13
* Description  : CpnCalCommand������ܺ�������Դ�ļ�
* Others       : 
* History      : 201212 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCalCommand.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnCalCommand�ඨ��
***********************************************************/
/*���� : CpnCalCommand_run(hCpnCalCommand cthis)
* ���� : cthis - CpnCalCommand��ָ��
* ��� : ��
* ���� : CpnCalCommand�๦�ܺ���
***********************************************/
void CpnCalCommand_run(hCpnCalCommand cthis){
    //TODO
}

/*���� : hCpnCalCommand CpnCalCommand_init(hCpnCalCommand cthis)
* ���� : cthis - CpnCalCommand��ָ��
* ��� : hCpnCalCommand - cthis/OOPC_NULL
* ���� : CpnCalCommand���ʼ������
***********************************************/
hCpnCalCommand CpnCalCommand_init(hCpnCalCommand cthis){
    // ���ܺ�������
    //cthis->run = CpnCalCommand_run;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnCalCommand CpnCalCommand_ctor(hCpnCalCommand cthis)
* ���� : cthis - CpnCalCommand��ָ��
* ��� : hCpnCalCommand - cthis/OOPC_NULL
* ���� : CpnCalCommand�๹�캯��
***********************************************/
CC(CpnCalCommand){
    cthis->init = CpnCalCommand_init;
    cthis->run = CpnCalCommand_run;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCpnCalCommand CpnCalCommand_dtor(hCpnCalCommand cthis)
* ���� : cthis - CpnCalCommand��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnCalCommand����������
***********************************************/
CD(CpnCalCommand){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
