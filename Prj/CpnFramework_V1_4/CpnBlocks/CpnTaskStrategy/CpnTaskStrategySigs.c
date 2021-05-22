/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTaskStrategySigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 09:53:54
 * Description  : CpnTaskStrategy component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnTaskStrategy.h"
#include "./CpnTaskStrategySigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
 * CpnTaskStrategy class definition.
 **********************************************************/
/* CpnTaskStrategy class.
 **********************************************/
CpnTaskStrategy clCpnTaskStrategy;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnTaskStrategy_init(void){
    CNNP(CpnTaskStrategy,&clCpnTaskStrategy);
    if(OPRS(clCpnTaskStrategy) != NULL){
        initTaskParam taskParam;
        taskParam.level = level2;
        taskParam.t = taskCpnTaskStrategy;
        taskParam.prdTick = CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD;
        taskParam.startTick = 3*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_initTask, (uint8*)&taskParam);
    }
}

/* delayUpdate Service.
 **********************************************/
void serv_CpnTaskStrategy_delayUpdate(void *buff){
    clCpnTaskStrategy.updateStrategy(clCpnTaskStrategy.self, ((hstrgDelayUpdate)buff)->strgMask,
            ((hstrgDelayUpdate)buff)->addTime, ((hstrgDelayUpdate)buff)->delTime);
}

/* condUpdate Service.
 **********************************************/
void serv_CpnTaskStrategy_condUpdate(void *buff){
    clCpnTaskStrategy.updateStrategyCond(clCpnTaskStrategy.self, ((hstrgCondUpdate)buff)->strgMask,
            ((hstrgCondUpdate)buff)->cond);
}

/* Interface trigger.
 **********************************************/
//void trig_CpnTaskStrategy_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnTaskStrategy(void){
    clCpnTaskStrategy.run(clCpnTaskStrategy.self);
}

/**************************** Copyright(C) pxf ****************************/
