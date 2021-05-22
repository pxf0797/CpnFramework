/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:06:36
* Description  : CpnCal组件信号定义源文件
* Others       :
* History      : 201212 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCal.h"
#include "./CpnCalSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnCal类定义
***********************************************************/
/*CpnCal类
***********************************************/
CpnCal clCpnCal;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnCal_init(void){
    CNNP(CpnCal,&clCpnCal);
    if(OPRS(clCpnCal) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnCal;
        taskParam.prdTick = 11*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_cal_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCal_initTask, (uint8*)&taskParam);
    }
}

/*服务
***********************************************/
void serv_CpnCal_getCtrlBits(void){}
/*服务
***********************************************/
void serv_CpnCal_getCmdBits(void){}
/*服务
***********************************************/
void serv_CpnCal_getFrameLen(void){}
/*服务
***********************************************/
void serv_CpnCal_getByte(void){}
/*服务
***********************************************/
void serv_CpnCal_setCtrlBits(void){}
/*服务
***********************************************/
void serv_CpnCal_setCmdBits(void){}
/*服务
***********************************************/
void serv_CpnCal_setFrameLen(void){}
/*服务
***********************************************/
void serv_CpnCal_setByte(void){}

/*接口触发
***********************************************/
//void trig_CpnCal_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnCal(void){}

/**************************** Copyright(C) pxf ****************************/
