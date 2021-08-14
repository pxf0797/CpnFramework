/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksTestSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:53:35
 * Description  : CpnSinksTest component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnSinksTest.h"
#include "./CpnSinksTestSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * CpnSinksTest class definition.
 **********************************************************/
/* CpnSinksTest class.
 **********************************************/
CpnSinksTest clCpnSinksTest;
tSinksParams sinkXy;
tStoreData outXy;
tSinksOut sinkXyOut = {&sinkXy,FALSE,&outXy};
tSinksSta sinkXySta = {&sinkXy,cacheNotStart};
#define SINKS_XY_BUFF_LEN    2000
tStoreData sinkDataBuff[SINKS_XY_BUFF_LEN];
uint16 buffFullFlg = 0;

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSinksTest_init(void){
    CNNP(CpnSinksTest,&clCpnSinksTest);
    if(OPRS(clCpnSinksTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSinksTest;
        taskParam.prdTick = 5*MS_T;
        taskParam.startTick = 2*MS_T;
        taskParam.strgMask = task_strategy_sink_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_initTask, (uint8*)&taskParam);

        sinkXy.get_getSig = sig_get_CpnSinksTest_wCache;
        sinkXy.trig_endSig = sig_trig_CpnSinksTest_sIsFull;
        sinkXy.period = 10*MS_T;
        sinkXy.data_size = sizeof(tStoreData);
        sinkXy.buff_size = sizeof(sinkDataBuff);
        sinkXy.buff = sinkDataBuff;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_registerCache, (uint8*)&sinkXy);
    }
}

/* sIsFull Service.
 **********************************************/
void serv_CpnSinksTest_sIsFull(void){
    buffFullFlg = 1;
}

/* Interface trigger.
 **********************************************/
//void trig_CpnSinksTest_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnSinksTest(void){
    clCpnSinksTest.run(clCpnSinksTest.self);
}

/**************************** Copyright(C) pxf ****************************/
