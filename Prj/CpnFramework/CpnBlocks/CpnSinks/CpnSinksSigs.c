/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  : CpnSinks组件信号定义源文件
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnSinks.h"
#include "./CpnSinksSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnSinks类定义
***********************************************************/
/*CpnSinks类
***********************************************/
CpnSinks clCpnSinks;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnSinks_init(void){
    CN(CpnSinks,&clCpnSinks,trig_CpnSinks_inf_setErr);
    if(OPRS(clCpnSinks) != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSinks;
        taskParam.prdTick = 1;//11*MS_T;
        taskParam.startTick = 5*MS_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_addTask, (uint8*)&taskParam);
    }
}

/*服务
***********************************************/
void serv_CpnSinks_readData(void *buff){
    if(clCpnSinks.readData(clCpnSinks.self,((htSinksOut)buff)->sinks,((htSinksOut)buff)->buff)){
        ((htSinksOut)buff)->outOperation = TRUE;
    }else{
        ((htSinksOut)buff)->outOperation = FALSE;
    }
}
/*服务
***********************************************/
void serv_CpnSinks_trigStart(void *buff){
    clCpnSinks.trigStart(clCpnSinks.self,(htSinksParams)buff);
}
/*服务
***********************************************/
void serv_CpnSinks_cacheSta(void *buff){
    ((htSinksSta)buff)->sta= clCpnSinks.cacheSta(clCpnSinks.self,((htSinksSta)buff)->sinks);
}
/*服务
***********************************************/
void serv_CpnSinks_registCache(void *buff){
    clCpnSinks.registCache(clCpnSinks.self,(htSinksParams)buff);
}
/*服务
***********************************************/
void serv_CpnSinks_reCache(void *buff){
    clCpnSinks.reCache(clCpnSinks.self,(htSinksParams)buff);
}

/*接口触发
***********************************************/
//void trig_CpnSinks_inf_infFunc(void){}
/*错误码接口触发
***********************************************/
void trig_CpnSinks_inf_setErr(uint16 id, uint16 code){
    uint32 uwErrCode = (((uint32)id << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_setErr, (uint8*)&uwErrCode);
}


/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnSinks(void){
    clCpnSinks.run(clCpnSinks.self);
}

/**************************** Copyright(C) pxf ****************************/
