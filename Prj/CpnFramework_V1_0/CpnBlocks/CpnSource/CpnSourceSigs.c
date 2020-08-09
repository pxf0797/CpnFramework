/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  : CpnSource组件信号定义源文件
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnSource.h"
#include "./CpnSourceSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnSource类定义
***********************************************************/
/*CpnSource类
***********************************************/
CpnSource clCpnSource;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnSource_init(void){
    CN(CpnSource,&clCpnSource,trig_CpnSource_inf_setErr);
    if(OPRS(clCpnSource) != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSource;
        taskParam.prdTick = 1;//1*MS_T;
        taskParam.startTick = 5*MS_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_addTask, (uint8*)&taskParam);
    }
}

/*服务
***********************************************/
void serv_CpnSource_registWaveSig(void *buff){
    clCpnSource.regist(clCpnSource.self, (htSourceParams)buff);
}
/*服务
***********************************************/
void serv_CpnSource_changeWaveSig(void *buff){
    clCpnSource.change(clCpnSource.self, (htSourceParams)buff);
}

/*接口触发
***********************************************/
//void trig_CpnSource_inf_infFunc(void){}
/*错误码接口触发
***********************************************/
void trig_CpnSource_inf_setErr(uint16 id, uint16 code){
    uint32 uwErrCode = (((uint32)id << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_setErr, (uint8*)&uwErrCode);
}


/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnSource(void){
    clCpnSource.run(clCpnSource.self);
}

/**************************** Copyright(C) pxf ****************************/
