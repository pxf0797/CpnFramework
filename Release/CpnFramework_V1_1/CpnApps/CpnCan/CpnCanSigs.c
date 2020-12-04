/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCanSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 16:09:24
* Description  : CpnCan组件信号定义源文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCan.h"
#include "./CpnCanSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnCan类定义
***********************************************************/
/*CpnCan类
***********************************************/
CpnCan clCpnCan;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnCan_init(void){
    CN(CpnCan,&clCpnCan, &clFifoCpnCan);
    if(OPRS(clCpnCan) != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnCan;
        taskParam.prdTick = 19*MS_T;//201*MS_T;
        taskParam.startTick = 5*S_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCan_addTask, (uint8*)&taskParam);
    }
}

/*服务
***********************************************/
void serv_CpnCan_sendSig(void *sig){
    //clCpnCan.send(clCpnCan.self, (tDataSig*)sig);
    clCpnCan.clFifoSend->push(clCpnCan.clFifoSend, sig);
}
/*服务
***********************************************/
void serv_CpnCan_receiveSig(void *sig){}

/*接口触发
***********************************************/
//void trig_CpnCan_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnCan(void){
    clCpnCan.run(clCpnCan.self);
}

/**************************** Copyright(C) pxf ****************************/
