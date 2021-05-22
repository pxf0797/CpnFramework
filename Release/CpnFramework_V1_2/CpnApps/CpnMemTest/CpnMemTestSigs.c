/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMemTestSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/09 11:41:03
* Description  : CpnMemTest组件信号定义源文件
* Others       :
* History      : 201209 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnMemTest.h"
#include "./CpnMemTestSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnMemTest类定义
***********************************************************/
/*CpnMemTest类
***********************************************/
CpnMemTest clCpnMemTest;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnMemTest_init(void){
    CNNP(CpnMemTest,&clCpnMemTest);
    if(OPRS(clCpnMemTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnMemTest;
        taskParam.prdTick = 19*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_test_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMemTest_initTask, (uint8*)&taskParam);
    }
}


/*接口触发
***********************************************/
//void trig_CpnMemTest_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnMemTest(void){
    clCpnMemTest.run(clCpnMemTest.self);
}

/**************************** Copyright(C) pxf ****************************/
