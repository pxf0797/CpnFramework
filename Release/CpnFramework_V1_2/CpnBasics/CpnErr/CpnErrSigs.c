/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErrSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  : CpnErr组件信号定义源文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnErr.h"
#include "./CpnErrSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnErr类定义
***********************************************************/
/*CpnErr类
***********************************************/
CpnErr clCpnErr;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnErr_init(void){
    CN(CpnErr,&clCpnErr, &clFifoCpnErr);
    if(OPRS(clCpnErr) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnErr;
        taskParam.prdTick = 2*MS_T;
        taskParam.startTick = 1*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_initTask, (uint8*)&taskParam);
    }
}

/*服务
***********************************************/
void serv_CpnErr_setErr(void *buff){
    uint32 ulErrCode = *(uint32*)buff;
    clCpnErr.setErr(clCpnErr.self, ulErrCode);
}

/*接口触发
***********************************************/
//void trig_CpnErr_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnErr(void){
    static tick sendDelay = 1000*MS_T;
//    tDataSig sendErrNum = {0u};
//
//    sendErrNum.id = 0x10u;
//    sendErrNum.data = clCpnErr.uwTotalErrNum;

    clCpnErr.run(clCpnErr.self);

    /* delay send */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_delay, (uint8*)&sendDelay);
    if(IS_TIMEOUT(sendDelay)){
        sendDelay = 5000*MS_T;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_sendSig, (uint8*)&sendErrNum);
    }
}

/**************************** Copyright(C) pxf ****************************/
