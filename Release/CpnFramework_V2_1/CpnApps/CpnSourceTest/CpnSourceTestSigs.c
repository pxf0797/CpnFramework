/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceTestSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:59:39
 * Description  : CpnSourceTest component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnSourceTest.h"
#include "CpnSourceTestSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnSourceTest class definition.
 **********************************************************/
/* CpnSourceTest class.
 **********************************************/
CpnSourceTest clCpnSourceTest;

tSourceParams wSine;
tSourceParams wSine2;
tSourceParams wSine3;
tSourceParams wPluse;
tSourceParams wPluse2;
tSourceParams wCountUp;
tSourceParams wCountDown;
tSourceParams wCountUpDown;

float32 wSineOutput;
float32 wSine2Output;
float32 wSine3Output;
float32 wPluseOutput;
float32 wPluse2Output;
float32 wCountUpOutput;
float32 wCountDownOutput;
float32 wCountUpDownOutput;

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSourceTest_init(void){
    CNNP(CpnSourceTest,&clCpnSourceTest);
    if(OPRS(clCpnSourceTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSourceTest;
        taskParam.prdTick = 5*MS_T;
        taskParam.startTick = 3*MS_T;
        taskParam.strgMask = task_strategy_source_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_initTask, (uint8*)&taskParam);

        wSine.type = w_sine;
        wSine.trig_sig = sig_trig_CpnSourceTest_sSine;
        wSine.amplitude = 1000;
        wSine.step = 2*MS_T;
        wSine.period = 2*S_T;
        wSine.duty = 500;
        wSine.phase = 900;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wSine);
        wSine2.type = w_sine;
        wSine2.trig_sig = sig_trig_CpnSourceTest_sSine2;
        wSine2.amplitude = 800000;
        wSine2.step = 10*MS_T;
        wSine2.period = 5*S_T;
        wSine2.duty = 800;
        wSine2.phase = 1800;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wSine2);
        wSine3.type = w_sine;
        wSine3.trig_sig = sig_trig_CpnSourceTest_sSine3;
        wSine3.amplitude = 1;
        wSine3.step = 5*MS_T;
        wSine3.period = 500*MS_T;
        wSine3.duty = 200;
        wSine3.phase = 2700;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wSine3);

        wPluse.type = w_pluse;
        wPluse.trig_sig = sig_trig_CpnSourceTest_sPluse;
        wPluse.amplitude = 80;
        wPluse.step = 10*MS_T;
        wPluse.period = 5000*MS_T;
        wPluse.duty = 300;
        wPluse.phase = 300;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wPluse);
        wPluse2.type = w_pluse;
        wPluse2.trig_sig = sig_trig_CpnSourceTest_sPluse2;
        wPluse2.amplitude = 5;
        wPluse2.step = 1*MS_T;
        wPluse2.period = 1000*MS_T;
        wPluse2.duty = 800;
        wPluse2.phase = 2100;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wPluse2);

        wCountUp.type = w_countUp;
        wCountUp.trig_sig = sig_trig_CpnSourceTest_sCountUp;
        wCountUp.amplitude = 5;
        wCountUp.step = 3*MS_T;
        wCountUp.period = 1000*MS_T;
        wCountUp.duty = 800;
        wCountUp.phase = 2100;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wCountUp);

        wCountDown.type = w_countDown;
        wCountDown.trig_sig = sig_trig_CpnSourceTest_sCountDown;
        wCountDown.amplitude = 5;
        wCountDown.step = 5*MS_T;
        wCountDown.period = 2500*MS_T;
        wCountDown.duty = 0;
        wCountDown.phase = 450;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wCountDown);

        wCountUpDown.type = w_countUpDown;
        wCountUpDown.trig_sig = sig_trig_CpnSourceTest_sCountUpDown;
        wCountUpDown.amplitude = 5;
        wCountUpDown.step = 1*MS_T;
        wCountUpDown.period = 3500*MS_T;
        wCountUpDown.duty = 0;
        wCountUpDown.phase = 450;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_registWaveSig, (uint8*)&wCountUpDown);
    }
}

/* sSine Service.
 **********************************************/
void serv_CpnSourceTest_sSine(void *buff){
    wSineOutput = *(float32*)buff;
}
/* sPluse Service.
 **********************************************/
void serv_CpnSourceTest_sPluse(void *buff){
    wPluseOutput = *(float32*)buff;
}
/* sCountUp Service.
 **********************************************/
void serv_CpnSourceTest_sCountUp(void *buff){
    wCountUpOutput = *(float32*)buff;
}
/* sCountDown Service.
 **********************************************/
void serv_CpnSourceTest_sCountDown(void *buff){
    wCountDownOutput = *(float32*)buff;
}
/* sCountUpDown Service.
 **********************************************/
void serv_CpnSourceTest_sCountUpDown(void *buff){
    wCountUpDownOutput = *(float32*)buff;
}
/* sSine2 Service.
 **********************************************/
void serv_CpnSourceTest_sSine2(void *buff){
    wSine2Output = *(float32*)buff;
}
/* sSine3 Service.
 **********************************************/
void serv_CpnSourceTest_sSine3(void *buff){
    wSine3Output = *(float32*)buff;
}
/* sPluse2 Service.
 **********************************************/
void serv_CpnSourceTest_sPluse2(void *buff){
    wPluse2Output = *(float32*)buff;
}

/* Interface trigger.
 **********************************************/
//void trig_CpnSourceTest_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnSourceTest(void){
    clCpnSourceTest.run(clCpnSourceTest.self);
}

/**************************** Copyright(C) pxf ****************************/
