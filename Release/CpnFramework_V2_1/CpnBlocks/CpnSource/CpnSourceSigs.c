/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:32:56
 * Description  : CpnSource component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnSource.h"
#include "CpnSourceSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnSource class definition.
 **********************************************************/
/* CpnSource class.
 **********************************************/
CpnSource clCpnSource;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSource_init(void){
    CNNP(CpnSource,&clCpnSource);
    if(OPRS(clCpnSource) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSource;
        taskParam.prdTick = 1;//1*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_source_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_initTask, (uint8*)&taskParam);
    }
}

/* registerWaveSig Service.
 **********************************************/
void serv_CpnSource_registWaveSig(void *buff){
    clCpnSource.regist(clCpnSource.self, (htSourceParams)buff);
}
/* changeWaveSig Service.
 **********************************************/
void serv_CpnSource_changeWaveSig(void *buff){
    clCpnSource.change(clCpnSource.self, (htSourceParams)buff);
}

/* freeWaveSig Service.
 **********************************************/
void serv_CpnSource_freeWaveSig(void *buff){
    clCpnSource.free(clCpnSource.self, (htSourceParams)buff);
}

/* Error code Interface trigger.
 **********************************************/
// void trig_CpnSource_inf_setErr(uint16 id, uint16 code){
//     uint32 uwErrCode = (((uint32)id<<16u)+code);
//     clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_setErr, (uint8*)&uwErrCode);
// }



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnSource(void){
    clCpnSource.run(clCpnSource.self);
}

/**************************** Copyright(C) pxf ****************************/
