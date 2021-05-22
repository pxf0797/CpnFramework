/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnErrSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 14:10:28
 * Description  : CpnErr component signals definition source file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnErr.h"
#include "./CpnErrSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * CpnErr class definition.
 **********************************************************/
/* CpnErr class.
 **********************************************/
CpnErr clCpnErr;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnErr_init(void){
    CN(CpnErr,&clCpnErr, &clFifoCpnErr);
    if(OPRS(clCpnErr) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnErr;
        taskParam.prdTick = 2*MS_T;
        taskParam.startTick = 1*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_initTask, (uint8*)&taskParam);
    }
}

/* Service.
 **********************************************/
void serv_CpnErr_setErr(void *buff){
    uint32 ulErrCode = *(uint32*)buff;
    clCpnErr.setErr(clCpnErr.self, ulErrCode);
}

/* Interface trigger.
 **********************************************/
//void trig_CpnErr_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnErr(void){
    static tick sendDelay = 1000*MS_T;
//    tDataSig sendErrNum = {0u};
//
//    sendErrNum.id = 0x10u;
//    sendErrNum.data = clCpnErr.uwTotalErrNum;

    clCpnErr.run(clCpnErr.self);

    /* delay send */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_delay, (uint8*)&sendDelay);
    if(IS_TIMEOUT(sendDelay)){
        sendDelay = 5000*MS_T;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_sendSig, (uint8*)&sendErrNum);
    }
}

/**************************** Copyright(C) pxf ****************************/
