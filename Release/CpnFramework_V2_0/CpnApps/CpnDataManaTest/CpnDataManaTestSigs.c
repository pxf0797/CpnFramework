/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaTestSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/08 11:41:08
 * Description  : CpnDataManaTest component signals definition source file.
 * Others       :
 * History      : 20211008 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnDataManaTest.h"
#include "./CpnDataManaTestSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * CpnDataManaTest class definition.
 **********************************************************/
/* CpnDataManaTest class.
 **********************************************/
static CpnDataManaTest clCpnDataManaTest;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnDataManaTest_init(void){
    CNNP(CpnDataManaTest,&clCpnDataManaTest);
    if(OPRS(clCpnDataManaTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnDataManaTest;
        taskParam.prdTick = 101*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_test_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_initTask, (uint8*)&taskParam);
    }
}


/* Interface trigger.
 **********************************************/
//void trig_CpnDataManaTest_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnDataManaTest(void){
    clCpnDataManaTest.run(clCpnDataManaTest.self);
}

/**************************** Copyright(C) pxf ****************************/
