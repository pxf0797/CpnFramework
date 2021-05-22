/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategySigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy组件信号定义源文件
* Others       :
* History      : 201218 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnTaskStrategy.h"
#include "./CpnTaskStrategySigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
* CpnTaskStrategy类定义
***********************************************************/
/*CpnTaskStrategy类
***********************************************/
CpnTaskStrategy clCpnTaskStrategy;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnTaskStrategy_init(void){
    CNNP(CpnTaskStrategy,&clCpnTaskStrategy);
    if(OPRS(clCpnTaskStrategy) != NULL){
        initTaskParam taskParam;
        taskParam.level = level2;
        taskParam.t = taskCpnTaskStrategy;
        taskParam.prdTick = CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD;
        taskParam.startTick = 3*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_initTask, (uint8*)&taskParam);
    }
}

/*延时更新任务组服务
***********************************************/
void serv_CpnTaskStrategy_delayUpdate(void *buff){
    clCpnTaskStrategy.updateStrategy(clCpnTaskStrategy.self, ((hstrgDelayUpdate)buff)->strgMask, ((hstrgDelayUpdate)buff)->addTime, ((hstrgDelayUpdate)buff)->delTime);
}
/*条件更新任务组服务
***********************************************/
void serv_CpnTaskStrategy_condUpdate(void *buff){
    clCpnTaskStrategy.updateStrategyCond(clCpnTaskStrategy.self, ((hstrgCondUpdate)buff)->strgMask, ((hstrgCondUpdate)buff)->cond);
}

/*接口触发
***********************************************/
//void trig_CpnTaskStrategy_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnTaskStrategy(void){
    clCpnTaskStrategy.run(clCpnTaskStrategy.self);
}

/**************************** Copyright(C) pxf ****************************/
