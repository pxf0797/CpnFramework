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
#include "../CpnBasics/FuncLib/FuncLib.h"

// #include "../../APP/Can/AppCan.h"
// #include "../../APP/Can/AppCanObc.h"

/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*ʵʱ����
***********************************************/
//uint16 uwTimeCnt = 0;
//void serv_Abi_getTime(void *buff){
//    *(uint16*)buff = uwTimeCnt;
//    uwTimeCnt += 100;
//}
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
extern void trig_Abi_sentCanFrameDrv(uint32 id, uint8 data[]);
void serv_Abi_sentCanFrame(void *buff){
    hTS_FRAME_TRANS frame = (hTS_FRAME_TRANS)buff;
    // Can_Frame tCanFrame = {0};
    // tCanFrame.id = frame->id;
    // tCanFrame.len = 8;
    // memCopy(tCanFrame.data, frame->frame->byte, tCanFrame.len);
    //CanPublic_Send_msg(CAN_MSG_ID_GET_TYPE2(tCanFrame.id), &tCanFrame);
    trig_Abi_sentCanFrameDrv(frame->id, frame->frame->data);
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
/*����֡���ݴ���
***********************************************/
void trig_Abi_updateCanFrame(uint32 id, uint8 data[]){
    TS_FRAME_TRANS frame = {id, (hTU_BYTES_DATA)data};
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_update_frame, (uint8*)&frame);
}

/**************************** Copyright(C) pxf ****************************/
