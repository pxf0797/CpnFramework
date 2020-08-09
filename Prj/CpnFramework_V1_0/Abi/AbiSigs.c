/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : AbiSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/29 20:17:54
* Description  :
* Others       :
* History      : 191229 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./AbiSigs.h"
#include "../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*ʵʱ����
***********************************************/
uint16 uwTimeCnt = 0;
void serv_Abi_getTime(void *buff){
    *(uint16*)buff = uwTimeCnt;
    uwTimeCnt += 100;
}
/*�������ݴ������
***********************************************/
static tDataSig sendSigData;
void serv_Abi_sendSig(void *sig){
    sendSigData.id = ((tDataSig*)sig)->id;
    sendSigData.data = ((tDataSig*)sig)->data;
}
uint32 can_send_get_id(void){
    return sendSigData.id;
}
uint32 can_send_get_data(void){
    return sendSigData.data;
}

/*��ʼ������
***********************************************/
void trig_Abi_init(void){
    // ��������ɶ��źŴ�����ĳ�ʼ��
    RteAsynSetGetInit();
    RetSynServTrigInit();

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_init, NULL);
}
/*��������
***********************************************/
void trig_Abi_tick(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_tick, NULL);
}
/*ѭ�����д���
***********************************************/
void trig_Abi_run(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_run, NULL);
}

/**************************** Copyright(C) pxf ****************************/
