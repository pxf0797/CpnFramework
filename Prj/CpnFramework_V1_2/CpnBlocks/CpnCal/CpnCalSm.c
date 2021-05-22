/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSm.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/17 10:12:15
* Description  : ״̬��CpnCalSm���弰��״̬��������Դ�ļ�
* Others       : 
* History      : 201217 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCalSm.h"

/*״̬��CpnCalSm����
* ����״̬����ش���״̬
***********************************************/
SMDF(CpnCalSm, CPNCALSM_LIST);

/*���� : CpnCalSm_act_init()
* ���� : CpnCalSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ��ʼ״̬��������
***********************************************/
void CpnCalSm_act_init(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_init;
}

/*���� : CpnCalSm_act_idle()
* ���� : CpnCalSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ״̬idle��������
***********************************************/
void CpnCalSm_act_idle(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_idle;
}

/*���� : CpnCalSm_act_wait()
* ���� : CpnCalSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ״̬wait��������
***********************************************/
void CpnCalSm_act_wait(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_wait;
}

/*���� : CpnCalSm_act_dispose()
* ���� : CpnCalSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ״̬dispose��������
***********************************************/
void CpnCalSm_act_dispose(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_dispose;
}

/**************************** Copyright(C) pxf ****************************/
