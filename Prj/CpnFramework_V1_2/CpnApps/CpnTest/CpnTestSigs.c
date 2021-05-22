/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTestSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/23 17:26:23
* Description  : CpnTest组件信号定义源文件
* Others       :
* History      : 200723 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnTest.h"
#include "./CpnTestSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnTest类定义
***********************************************************/
/*CpnTest类
***********************************************/
CpnTest clCpnTest;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnTest_init(void){
    CNNP(CpnTest,&clCpnTest);
    if(OPRS(clCpnTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnTest;
        taskParam.prdTick = 13*MS_T;
        taskParam.startTick = 8000*MS_T;
        taskParam.strgMask = task_strategy_test_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_initTask, (uint8*)&taskParam);
    }
}

/*服务
***********************************************/
uint16 uwServCnt1 = 0;
void serv_CpnTest_servSig1(void){
    uwServCnt1++;
}
/*服务
***********************************************/
uint16 uwGetData = 0;
uint16 uwServCnt2 = 0;
void serv_CpnTest_servSig2_uint16(void *buff){
    uwGetData = *(uint16*)buff;
    uwServCnt2++;
}

/*接口触发
***********************************************/
//void trig_CpnTest_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
uint16 uwTrigData = 0;
void taskCpnTest(void){
    static tick waitDelay = 50*MS_T;
    static tick waitDelay2 = 10*MS_T;
    tDataSig sendServTrig = {0};

    uwTrigData++;

    /* wait delay */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_delay, (uint8*)&waitDelay);
    if(IS_TIMEOUT(waitDelay)){
        waitDelay = 300*MS_T;

        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_trigSig1_uint16, (uint8*)&uwTrigData);
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_trigSig2, NULL);
    }

    /* wait delay */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_delay, (uint8*)&waitDelay2);
    if(IS_TIMEOUT(waitDelay2)){
        waitDelay2 = 2000*MS_T;

#define U8SHIFT_U32_BIT(value,bit) (((uint32)((value)&0xFFU))<<(bit))
        sendServTrig.id = 0x20;
        //sendServTrig.data = (((uint32)uwServCnt1<<24)|((uint32)uwServCnt2<<16)|((uint32)uwTrigData<<8)|((uint32)uwGetData<<0));
        sendServTrig.data = U8SHIFT_U32_BIT(uwServCnt1,24)|U8SHIFT_U32_BIT(uwServCnt2,16)|U8SHIFT_U32_BIT(uwTrigData,8)|U8SHIFT_U32_BIT(uwGetData,0);
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_sendSig, (uint8*)&sendServTrig);
    }
}

/**************************** Copyright(C) pxf ****************************/
