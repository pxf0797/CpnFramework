/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : AbiSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 17:11:21
 * Description  : Abi component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "AbiSigs.h"
#include "RteSigs.h"
#include "FuncLib.h"
#include <time.h>
#include <windows.h>

/***********************************************************
 * Abi class definition.
 **********************************************************/
/* Abi class.
 **********************************************/
//Abi clAbi;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
/* void serv_Abi_init(void){
    CNNP(Abi,&clAbi);
    if(OPRS(clAbi) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskAbi;
        taskParam.prdTick = 11*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_initTask, (uint8*)&taskParam);
    }
}
*/
/* getTime Service.
 **********************************************/
//uint16 uwTimeCnt = 0;
void serv_Abi_getTime(void *buff){
//    *(uint16*)buff = uwTimeCnt;
//    uwTimeCnt += 100;
    //*(uint16*)buff = (uint16)clock();
/*
#ifdef _WIN32
// 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)
    FILETIME ft;
    LARGE_INTEGER li;
    int64 tt = 0;
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    // 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
    tt = (li.QuadPart - EPOCHFILETIME) /10;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
*/
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    *(uint16*)buff = (uint16)ft.dwLowDateTime;
}
/* sendSig Service.
 **********************************************/
//static tDataSig sendSigData;
void serv_Abi_sendSig(void *sig){
//    sendSigData.id = ((tDataSig*)sig)->id;
//    sendSigData.data = ((tDataSig*)sig)->data;
}
 uint32 can_send_get_id(void){
    return 0;//sendSigData.id;
}
uint32 can_send_get_data(void){
    return 0;//sendSigData.data;
}
/* sendCanFrame Service.
 **********************************************/
 extern void trig_Abi_sendCanFrameDrv(uint32 id, uint8 data[]);
void serv_Abi_sendCanFrame(void *buff){
//    htsFrameTrans frame = (htsFrameTrans)buff;
    // Can_Frame tCanFrame = {0};
    // tCanFrame.id = frame->id;
    // tCanFrame.len = 8;
    // memCopy(tCanFrame.data, frame->frame->byte, tCanFrame.len);
    //CanPublic_Send_msg(CAN_MSG_ID_GET_TYPE2(tCanFrame.id), &tCanFrame);
//    trig_Abi_sendCanFrameDrv(frame->id, frame->frame->byte);
}

/* Interface trigger.
 **********************************************/
void trig_Abi_init(void){
    /* Must complete the initialization of the signal transmission class before Scheduler initial. */
    RteAsynSetGetInit();
    RetSynServTrigInit();

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_init, NULL);
}
/* Step Interface trigger.
 **********************************************/
void trig_Abi_tick(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_tick, NULL);
}
 /* Runnig Interface trigger.
 **********************************************/
void trig_Abi_run(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_run, NULL);
}
 /* Data frame Interface trigger.
 **********************************************/
void trig_Abi_updateCanFrame(uint32 id, uint8 data[]){
//    tsFrameTrans frame = {id, (htuBytesData)data};
//    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_Abi_updateFrame, (uint8*)&frame);
}

/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
//void taskAbi(void){}

/**************************** Copyright(C) pxf ****************************/
