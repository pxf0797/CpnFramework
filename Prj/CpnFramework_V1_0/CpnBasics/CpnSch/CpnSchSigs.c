/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSchSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 21:27:20
* Description  :
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnSchSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnSch.h"

/***********************************************************
* CpnSch类定义
***********************************************************/
/*CpnSch类
***********************************************/
CpnSch clCpnSch;



/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*添加任务服务
***********************************************/
void serv_CpnSch_addTask(void *buff){
    clCpnSch.addTask(clCpnSch.self, ((haddTaskParam)buff)->level, ((haddTaskParam)buff)->t, ((haddTaskParam)buff)->prdTick, ((haddTaskParam)buff)->startTick);
}
/*删除任务服务
***********************************************/
void serv_CpnSch_delTask(void *buff){
    clCpnSch.delTask(clCpnSch.self, ((hdelTaskParam)buff)->level, ((hdelTaskParam)buff)->t);
}
/*延时服务
***********************************************/
void serv_CpnSch_delay(void *buff){
    clCpnSch.delay(clCpnSch.self, buff);
}
/*实时服务
***********************************************/
void serv_CpnSch_now(void *buff){
    clCpnSch.now(clCpnSch.self, buff);
}
/*初始化服务
***********************************************/
void serv_CpnSch_init(void){
    CN(CpnSch, &clCpnSch, &SchSmRunRec, SchSm, trig_CpnSch_inf_getTime, trig_CpnSch_inf_setErr, trig_CpnSch_inf_initCpn);
    if(OPRS(clCpnSch) != NULL){}
}
/*运行服务
***********************************************/
void serv_CpnSch_run(void){
    clCpnSch.run(clCpnSch.self);

    static tick sendDelay = 1000*MS_T;
    tDataSig sendStatus = {0};

    /* delay send */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_delay, (uint8*)&sendDelay);
    if(IS_TIMEOUT(sendDelay)){
        sendDelay = 3000*MS_T;
        sendStatus.id = 0x00;
        sendStatus.data = clCpnSch.usage;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
        sendStatus.id = 0x01;
        sendStatus.data = clCpnSch.currTaskTime;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
        sendStatus.id = 0x02;
        sendStatus.data = clCpnSch.totalTaskTime;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
    }
}
/*步长服务
***********************************************/
void serv_CpnSch_tick(void){
    clCpnSch.tick(clCpnSch.self);
}


/*读取实时接口触发
***********************************************/
void trig_CpnSch_inf_getTime(uint16 *point){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_inf_getTime, (uint8*)point);
}
/*错误码接口触发
***********************************************/
void trig_CpnSch_inf_setErr(uint16 id, uint16 code){
    uint32 uwErrCode = (((uint32)id << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_inf_setErr, (uint8*)&uwErrCode);
}
/*初始化组件接口触发
***********************************************/
void trig_CpnSch_inf_initCpn(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCan_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_init, NULL);
}

/**************************** Copyright(C) pxf ****************************/
