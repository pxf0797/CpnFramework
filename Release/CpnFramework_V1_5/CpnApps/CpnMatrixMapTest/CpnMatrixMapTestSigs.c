/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMatrixMapTestSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:00:03
 * Description  : CpnMatrixMapTest component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnMatrixMapTest.h"
#include "./CpnMatrixMapTestSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * CpnMatrixMapTest class definition.
 **********************************************************/
/* CpnMatrixMapTest class.
 **********************************************/
CpnMatrixMapTest clCpnMatrixMapTest;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
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


/* Interface trigger.
 **********************************************/
//void trig_CpnMatrixMapTest_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnMatrixMapTest(void){
    clCpnMatrixMapTest.run(clCpnMatrixMapTest.self);
}

/**************************** Copyright(C) pxf ****************************/
