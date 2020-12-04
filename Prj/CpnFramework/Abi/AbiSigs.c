/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : AbiSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/29 20:17:54
* Description  :
* Others       :
* History      : 191229 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./AbiSigs.h"
#include "../CpnRte/RteSigs/RteSigs.h"
#include "../CpnBasics/FuncLib/FuncLib.h"

// #include "../../APP/Can/AppCan.h"
// #include "../../APP/Can/AppCanObc.h"

/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*实时服务
***********************************************/
//uint16 uwTimeCnt = 0;
//void serv_Abi_getTime(void *buff){
//    *(uint16*)buff = uwTimeCnt;
//    uwTimeCnt += 100;
//}
/*发送数据处理服务
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

/*初始化触发
***********************************************/
void trig_Abi_init(void){
    // 必须先完成对信号传输类的初始化
    RteAsynSetGetInit();
    RetSynServTrigInit();

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_init, NULL);
}
/*步长触发
***********************************************/
void trig_Abi_tick(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_tick, NULL);
}
/*循环运行触发
***********************************************/
void trig_Abi_run(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_run, NULL);
}
/*更新帧数据触发
***********************************************/
void trig_Abi_updateCanFrame(uint32 id, uint8 data[]){
    TS_FRAME_TRANS frame = {id, (hTU_BYTES_DATA)data};
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_update_frame, (uint8*)&frame);
}

/**************************** Copyright(C) pxf ****************************/
