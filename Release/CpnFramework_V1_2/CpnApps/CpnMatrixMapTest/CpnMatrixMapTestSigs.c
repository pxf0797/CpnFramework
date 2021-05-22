/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapTestSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 20:32:16
* Description  : CpnMatrixMapTest组件信号定义源文件
* Others       :
* History      : 201202 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnMatrixMapTest.h"
#include "./CpnMatrixMapTestSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnMatrixMapTest类定义
***********************************************************/
/*CpnMatrixMapTest类
***********************************************/
CpnMatrixMapTest clCpnMatrixMapTest;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnMatrixMapTest_init(void){
    CNNP(CpnMatrixMapTest,&clCpnMatrixMapTest);
    if(OPRS(clCpnMatrixMapTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnMatrixMapTest;
        taskParam.prdTick = 101*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_matrix_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_initTask, (uint8*)&taskParam);
    }
}

/*服务
***********************************************/
// void serv_CpnMatrixMapTest_setDataA(void){}
/*服务
***********************************************/
// void serv_CpnMatrixMapTest_getData1(void){}

/*接口触发
***********************************************/
//void trig_CpnMatrixMapTest_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnMatrixMapTest(void){
    clCpnMatrixMapTest.run(clCpnMatrixMapTest.self);
}

/**************************** Copyright(C) pxf ****************************/
