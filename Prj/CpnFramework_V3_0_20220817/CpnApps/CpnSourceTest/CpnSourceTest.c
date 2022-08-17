/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceTest.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:59:39
 * Description  : CpnSourceTest class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnSourceTest.h"
#include "RteSigs.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
//extern tSourceParams wSine;
extern tSourceParams wSine2;
//extern tSourceParams wSine3;
//extern tSourceParams wPluse;
//extern tSourceParams wPluse2;
//extern tSourceParams wCountUp;
//extern tSourceParams wCountDown;
//extern tSourceParams wCountUpDown;

//extern float32 wSineOutput;
extern float32 wSine2Output;
//extern float32 wSine3Output;
//extern float32 wPluseOutput;
//extern float32 wPluse2Output;
//extern float32 wCountUpOutput;
//extern float32 wCountDownOutput;
//extern float32 wCountUpDownOutput;

/***********************************************************
 * CpnSourceTest class definition.
 **********************************************************/
/* Function : CpnSourceTest_run(hCpnSourceTest cthis)
 * Input    : cthis - CpnSourceTest class pointer
 * Output   :
 * Others   : CpnSourceTest class function.
 **********************************************/
void CpnSourceTest_run(hCpnSourceTest cthis){
    cthis->testSource(cthis);
}

/* Function : CpnSourceTest_testSource(hCpnSourceTest cthis)
 * Input    : cthis - CpnSourceTest class pointer
 * Output   :
 * Others   : CpnSourceTest class function.
 **********************************************/
void CpnSourceTest_testSource(hCpnSourceTest cthis){
    //tDataSig sendStatus = {0};
    static tick waitDelay = 10*S_T;

    //sendStatus.id = 0x01;
    //sendStatus.data = (int32)wSine2Output;//wPluseOutput;
    //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_sendSig, (uint8*)&sendStatus);

    clRteAsynSigs.set(clRteAsynSigs.self, sig_set_CpnSourceTest_wOutput, (uint8*)&wSine2Output);

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

/* Function : hCpnSourceTest CpnSourceTest_init(hCpnSourceTest cthis)
 * Input    : cthis - CpnSourceTest class pointer
 * Output   : hCpnSourceTest - cthis/OOPC_NULL
 * Others   : CpnSourceTest class initial function.
 **********************************************/
hCpnSourceTest CpnSourceTest_init(hCpnSourceTest cthis){
    /* Configure functions. */
    //cthis->run = CpnSourceTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnSourceTest CpnSourceTest_ctor(hCpnSourceTest cthis)
 * Input    : cthis - CpnSourceTest class pointer
 * Output   : hCpnSourceTest - cthis/OOPC_NULL
 * Others   : CpnSourceTest class constructor.
 **********************************************/
CC(CpnSourceTest){
    cthis->init = CpnSourceTest_init;
    cthis->run = CpnSourceTest_run;
    cthis->testSource = CpnSourceTest_testSource;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCpnSourceTest CpnSourceTest_dtor(hCpnSourceTest cthis)
 * Input    : cthis - CpnSourceTest class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnSourceTest class destructor.
 **********************************************/
CD(CpnSourceTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
