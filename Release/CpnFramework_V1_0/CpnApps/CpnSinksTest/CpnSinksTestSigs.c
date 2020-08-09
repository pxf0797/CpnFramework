/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksTestSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 19:07:35
* Description  : CpnSinksTest组件信号定义源文件
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnSinksTest.h"
#include "./CpnSinksTestSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnSinksTest类定义
***********************************************************/
/*CpnSinksTest类
***********************************************/
CpnSinksTest clCpnSinksTest;
tSinksParams sinkXy;
tStoreData outXy;
tSinksOut sinkXyOut = {&sinkXy,FALSE,&outXy};
tSinksSta sinkXySta = {&sinkXy,cacheNotStart};
#define SINKS_XY_BUFF_LEN    2000
tStoreData sinkDataBuff[SINKS_XY_BUFF_LEN];
uint16 buffFullFlg = 0;

/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnSinksTest_init(void){
    CNNP(CpnSinksTest,&clCpnSinksTest);
    if(OPRS(clCpnSinksTest) != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSinksTest;
        taskParam.prdTick = 5*MS_T;
        taskParam.startTick = 2*MS_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_addTask, (uint8*)&taskParam);

        sinkXy.trig_getSig = sig_trig_CpnSinksTest_sGetData;
        sinkXy.trig_endSig = sig_trig_CpnSinksTest_sIsFull;
        sinkXy.period = 5*MS_T;
        sinkXy.data_size = sizeof(tStoreData);
        sinkXy.buff_size = sizeof(sinkDataBuff);
        sinkXy.buff = sinkDataBuff;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_registCache, (uint8*)&sinkXy);
    }
}

/*服务
***********************************************/
void serv_CpnSinksTest_sIsFull(void){
    buffFullFlg = 1;
}
/*服务
***********************************************/
void serv_CpnSinksTest_sGetData(void *buff){
    static uint16 index = 0;
    clRteAsynSigs.get(clRteAsynSigs.self, sig_get_CpnSinksTest_wCache, (uint8*)&((htStoreData)buff)->data, sizeof(float32));
    index++;
    ((htStoreData)buff)->index = index;
}

/*接口触发
***********************************************/
//void trig_CpnSinksTest_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnSinksTest(void){
    clCpnSinksTest.run(clCpnSinksTest.self);
}

/**************************** Copyright(C) pxf ****************************/
