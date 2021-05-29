/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:09:52
 * Description  : CpnSinks component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnSinks.h"
#include "./CpnSinksSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * CpnSinks class definition.
 **********************************************************/
/* CpnSinks class.
 **********************************************/
CpnSinks clCpnSinks;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSinks_init(void){
    CNNP(CpnSinks,&clCpnSinks);
    if(OPRS(clCpnSinks) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSinks;
        taskParam.prdTick = 1;//11*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_sink_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_initTask, (uint8*)&taskParam);
    }
}

/* readData Service.
 **********************************************/
void serv_CpnSinks_readData(void *buff){
    if(clCpnSinks.readData(clCpnSinks.self,((htSinksOut)buff)->sinks,((htSinksOut)buff)->buff)){
        ((htSinksOut)buff)->outOperation = TRUE;
    }else{
        ((htSinksOut)buff)->outOperation = FALSE;
    }
}
/* trigStart Service.
 **********************************************/
void serv_CpnSinks_trigStart(void *buff){
    clCpnSinks.trigStart(clCpnSinks.self,(htSinksParams)buff);
}
/* cacheState Service.
 **********************************************/
void serv_CpnSinks_cacheState(void *buff){
    ((htSinksSta)buff)->sta= clCpnSinks.cacheState(clCpnSinks.self,((htSinksSta)buff)->sinks);
}
/* registerCache Service.
 **********************************************/
void serv_CpnSinks_registerCache(void *buff){
    clCpnSinks.registerCache(clCpnSinks.self,(htSinksParams)buff);
}
/* reCache Service.
 **********************************************/
void serv_CpnSinks_reCache(void *buff){
    clCpnSinks.reCache(clCpnSinks.self,(htSinksParams)buff);
}

/* Error code Interface trigger.
 **********************************************/
// void trig_CpnSinks_inf_setErr(uint16 id, uint16 code){
//     uint32 uwErrCode = (((uint32)id << 16) + code);
//     clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_setErr, (uint8*)&uwErrCode);
// }



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnSinks(void){
    clCpnSinks.run(clCpnSinks.self);
}

/**************************** Copyright(C) pxf ****************************/
