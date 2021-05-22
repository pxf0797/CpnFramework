/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceTest.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 17:01:04
* Description  : CpnSourceTest类各功能函数定义源文件
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnSourceTest.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
extern tSourceParams wSine;
extern tSourceParams wSine2;
extern tSourceParams wSine3;
extern tSourceParams wPluse;
extern tSourceParams wPluse2;
extern tSourceParams wCountUp;
extern tSourceParams wCountDown;
extern tSourceParams wCountUpDown;

extern float32 wSineOutput;
extern float32 wSine2Output;
extern float32 wSine3Output;
extern float32 wPluseOutput;
extern float32 wPluse2Output;
extern float32 wCountUpOutput;
extern float32 wCountDownOutput;
extern float32 wCountUpDownOutput;

/***********************************************************
* CpnSourceTest类定义
***********************************************************/
/*名称 : CpnSourceTest_run(hCpnSourceTest cthis)
* 输入 : cthis - CpnSourceTest类指针
* 输出 : 无
* 其他 : CpnSourceTest类功能函数
***********************************************/
void CpnSourceTest_run(hCpnSourceTest cthis){
    cthis->testSource(cthis);
}

/*名称 : CpnSourceTest_testSource(hCpnSourceTest cthis)
* 输入 : cthis - CpnSourceTest类指针
* 输出 : 无
* 其他 : CpnSourceTest类功能函数
***********************************************/
void CpnSourceTest_testSource(hCpnSourceTest cthis){
    tDataSig sendStatus = {0};
    static tick waitDelay = 10*S_T;

    sendStatus.id = 0x01;
    sendStatus.data = (int32)wSine2Output;//wPluseOutput;
    //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_sendSig, (uint8*)&sendStatus);

    clRteAsynSigs.set(clRteAsynSigs.self, sig_set_CpnSourceTest_wOutput, (uint8*)&wSine2Output, sizeof(float32));

    /* wait delay */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_delay, (uint8*)&waitDelay);
    if(IS_TIMEOUT(waitDelay)){
        waitDelay = 10*S_T;

        //wSine2.type = w_sine;
        //wSine2.trig_sig = sig_trig_CpnSourceTest_sSine2;
        //wSine2.amplitude = 800000;
        //wSine2.step = 10*MS_T;
        //wSine2.period = 5*S_T;
        wSine2.period += 2*S_T;
        if(wSine2.period >= 8*S_T){
            wSine2.period = 2*S_T;
        }
        //wSine2.duty = 800;
        wSine2.phase = 1800;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_changeWaveSig, (uint8*)&wSine2);
    }
}

/*名称 : hCpnSourceTest CpnSourceTest_init(hCpnSourceTest cthis)
* 输入 : cthis - CpnSourceTest类指针
* 输出 : hCpnSourceTest - cthis/OOPC_NULL
* 其他 : CpnSourceTest类初始化函数
***********************************************/
hCpnSourceTest CpnSourceTest_init(hCpnSourceTest cthis){
    // 功能函数配置
    //cthis->run = CpnSourceTest_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnSourceTest CpnSourceTest_ctor(hCpnSourceTest cthis)
* 输入 : cthis - CpnSourceTest类指针
* 输出 : hCpnSourceTest - cthis/OOPC_NULL
* 其他 : CpnSourceTest类构造函数
***********************************************/
CC(CpnSourceTest){
    cthis->init = CpnSourceTest_init;
    cthis->run = CpnSourceTest_run;
    cthis->testSource = CpnSourceTest_testSource;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnSourceTest CpnSourceTest_dtor(hCpnSourceTest cthis)
* 输入 : cthis - CpnSourceTest类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnSourceTest类析构函数
***********************************************/
CD(CpnSourceTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
