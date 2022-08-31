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
#include "CpnErr.h"
#include "CpnErrSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnErr class definition.
 **********************************************************/
/* CpnErr class.
 **********************************************/
static CpnErr clCpnErr;
static Fifo clFifoCpnErr;
static uint32 ulErrCodeBuff[CPNERR_FIFO_BUFF_LENGTH];

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnErr_init(void){
    CN(CpnErr,&clCpnErr, &clFifoCpnErr, (void*)ulErrCodeBuff, sizeof(ulErrCodeBuff), sizeof(uint32));
    if(OPRS(clCpnErr) != NULL){
        tsInitTask taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnErr;
        taskParam.prdTick = 2*MS_T;
        taskParam.startTick = 1*MS_T;
        taskParam.e.all = e_err;
        SYN_TRIG(sig_trig_CpnErr_initTask, &taskParam);
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

    clCpnErr.run(clCpnErr.self);

    /* delay send */
    SYN_TRIG(sig_trig_CpnErr_delay, &sendDelay);
    if(IS_TIMEOUT(sendDelay)){
        sendDelay = 2000*MS_T;
//        INFO("ERR_TYPE_SYS:%d ERR_TYPE_BLOCK:%d ERR_TYPE_FUNC:%d",
//        clCpnErr.uwErrNum[ERR_TYPE_SYS>>ERR_TYPE_SHIFT],clCpnErr.uwErrNum[ERR_TYPE_BLOCK>>ERR_TYPE_SHIFT],
//        clCpnErr.uwErrNum[ERR_TYPE_FUNC>>ERR_TYPE_SHIFT]);
//        INFO("ERR_SEVERITY_NO:%d ERR_SEVERITY_LOW:%d ERR_SEVERITY_MEDIUM:%d ERR_SEVERITY_HIGH:%d",
//        clCpnErr.uwErrNum[(ERR_SEVERITY_NO>>ERR_SEVERITY_SHIFT)+16u],clCpnErr.uwErrNum[(ERR_SEVERITY_LOW>>ERR_SEVERITY_SHIFT)+16u],
//        clCpnErr.uwErrNum[(ERR_SEVERITY_MEDIUM>>ERR_SEVERITY_SHIFT)+16u],clCpnErr.uwErrNum[(ERR_SEVERITY_HIGH>>ERR_SEVERITY_SHIFT)+16u]);
//        INFO("TOTAL_ERROR_COUNTER:%d",clCpnErr.uwErrNum[20u]);
    }
}

/**************************** Copyright(C) pxf ****************************/
