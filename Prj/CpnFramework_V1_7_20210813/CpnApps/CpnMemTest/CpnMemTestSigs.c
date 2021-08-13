/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemTestSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:45:13
 * Description  : CpnMemTest component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnMemTest.h"
#include "./CpnMemTestSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * CpnMemTest class definition.
 **********************************************************/
/* CpnMemTest class.
 **********************************************/
CpnMemTest clCpnMemTest;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
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


/* Interface trigger.
 **********************************************/
//void trig_CpnMemTest_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnMemTest(void){
    clCpnMemTest.run(clCpnMemTest.self);
}

/**************************** Copyright(C) pxf ****************************/
