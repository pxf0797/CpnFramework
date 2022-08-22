/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFuncLibTestSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/11/03 14:55:04
 * Description  : CpnFuncLibTest component signals definition source file.
 * Others       :
 * History      : 20211103 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnFuncLibTest.h"
#include "CpnFuncLibTestSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnFuncLibTest class definition.
 **********************************************************/
/* CpnFuncLibTest class.
 **********************************************/
static CpnFuncLibTest clCpnFuncLibTest;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnFuncLibTest_init(void){
    CNNP(CpnFuncLibTest,&clCpnFuncLibTest);
    if(OPRS(clCpnFuncLibTest) != NULL){
        tsInitTask taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnFuncLibTest;
        taskParam.prdTick = 11*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.e.all = e_CpnTest;
        SYN_TRIG(sig_trig_CpnFuncLibTest_initTask, &taskParam);

        clCpnFuncLibTest.crcTest(clCpnFuncLibTest.self);
    }
}


/* Interface trigger.
 **********************************************/
//void trig_CpnFuncLibTest_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnFuncLibTest(void){
    clCpnFuncLibTest.run(clCpnFuncLibTest.self);
}

/**************************** Copyright(C) pxf ****************************/
