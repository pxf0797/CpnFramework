/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSchSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  : CpnSch component signals definition source file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnSch.h"
#include "./CpnSchSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * CpnSch class definition.
 **********************************************************/
/* CpnSch class.
 **********************************************/
CpnSch clCpnSch;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSch_initTask(void *buff){
    uint16 addIndex = 0u;

    if(clCpnSch.taskNum >= CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG){
        clCpnSch.addList(clCpnSch.self, ((hinitTaskParam)buff)->level,
                ((hinitTaskParam)buff)->t, ((hinitTaskParam)buff)->prdTick,
                ((hinitTaskParam)buff)->startTick, ((hinitTaskParam)buff)->strgMask);
        return;
    }
    clCpnSch.addList(clCpnSch.self, ((hinitTaskParam)buff)->level,
            ((hinitTaskParam)buff)->t, ((hinitTaskParam)buff)->prdTick,
            ((hinitTaskParam)buff)->startTick, ((hinitTaskParam)buff)->strgMask);
    addIndex = (clCpnSch.taskNum-1u);
    if(clCpnSch.strgMask&clCpnSch.taskList[addIndex].strgMask){
        clCpnSch.addTask(clCpnSch.self, clCpnSch.taskList[addIndex].level,
                clCpnSch.taskList[addIndex].t, clCpnSch.taskList[addIndex].prdTick,
                clCpnSch.taskList[addIndex].startTick);
        clCpnSch.taskList[addIndex].strgMask |= TASK_STRATEGY_ACT_MASK;
    }
}
/* Add task Service.
 **********************************************/
void serv_CpnSch_addTask(void *buff){
    clCpnSch.addTask(clCpnSch.self, ((hinitTaskParam)buff)->level, ((hinitTaskParam)buff)->t, ((hinitTaskParam)buff)->prdTick, ((hinitTaskParam)buff)->startTick);
}
/* Delete task Service.
 **********************************************/
void serv_CpnSch_delTask(void *buff){
    clCpnSch.delTask(clCpnSch.self, ((htaskParam)buff)->level, ((htaskParam)buff)->t);
}
/* Delay Service.
 **********************************************/
void serv_CpnSch_delay(void *buff){
    clCpnSch.delay(clCpnSch.self, buff);
}
/* Real time Service.
 **********************************************/
void serv_CpnSch_now(void *buff){
    clCpnSch.now(clCpnSch.self, buff);
}
/* Set monitor Service.
 **********************************************/
void serv_CpnSch_setMonitor(void *buff){
    clCpnSch.setMonitor(clCpnSch.self, ((htaskParam)buff)->level, ((htaskParam)buff)->t);
}
/* Get monitor Service.
 **********************************************/
void serv_CpnSch_getMonitor(void *buff){
    clCpnSch.getMonitor(clCpnSch.self, ((uint16*)buff));
}
/* Update strategy Service.
 **********************************************/
void serv_CpnSch_updateStrategy(void *buff){
    strategy newStrgMask = *((strategy*)buff);
    //strategy strgMask;
    //uint16 taskNum;
    uint16 i = 0u;

    //clCpnSch.getStrategy(clCpnSch.self, &strgMask);
    //clCpnSch.getTaskNum(clCpnSch.self, &taskNum);
    if(newStrgMask != clCpnSch.strgMask){
        while(i < clCpnSch.taskNum){
            if((clCpnSch.taskList[i].strgMask&(~TASK_STRATEGY_ACT_MASK))&newStrgMask){
                /* Task in new strategy, activate task. */
                if(!(clCpnSch.taskList[i].strgMask&TASK_STRATEGY_ACT_MASK)){
                    clCpnSch.addTask(clCpnSch.self, clCpnSch.taskList[i].level, clCpnSch.taskList[i].t,
                            clCpnSch.taskList[i].prdTick, clCpnSch.taskList[i].startTick);
                    clCpnSch.taskList[i].strgMask |= TASK_STRATEGY_ACT_MASK;
                }
            }else{
                /* Task not in new strategy, deactivate task. */
                if(clCpnSch.taskList[i].strgMask&TASK_STRATEGY_ACT_MASK){
                    clCpnSch.delTask(clCpnSch.self, clCpnSch.taskList[i].level, clCpnSch.taskList[i].t);
                    clCpnSch.taskList[i].strgMask &= (~TASK_STRATEGY_ACT_MASK);
                }
            }
            i++;
        }
        clCpnSch.strgMask = newStrgMask;
    }
}
/* Get strategy Service.
 **********************************************/
void serv_CpnSch_getStrategy(void *buff){
    clCpnSch.getStrategy(clCpnSch.self, ((strategy*)buff));
}
/* Get all schduler task counters Service.
 **********************************************/
void serv_CpnSch_getTaskNum(void *buff){
    clCpnSch.getTaskNum(clCpnSch.self, ((uint16*)buff));
}
/* Component initial Service.
 **********************************************/
void serv_CpnSch_init(void){
    CN(CpnSch, &clCpnSch, &SchSmRunRec, SchSm, trig_CpnSch_inf_getTime, trig_CpnSch_inf_setErr, trig_CpnSch_inf_initCpn);
    if(OPRS(clCpnSch) != NULL){}
}
/* Component run Service.
 **********************************************/
void serv_CpnSch_run(void){
    clCpnSch.run(clCpnSch.self);

    static tick sendDelay = 1000*MS_T;
    //tDataSig sendStatus = {0};

    /* delay send */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_delay, (uint8*)&sendDelay);
    if(IS_TIMEOUT(sendDelay)){
        sendDelay = 3000*MS_T;
        //sendStatus.id = 0x00;
        //sendStatus.data = clCpnSch.usage;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
        //sendStatus.id = 0x01;
        //sendStatus.data = clCpnSch.currTaskTime;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
        //sendStatus.id = 0x02;
        //sendStatus.data = clCpnSch.totalTaskTime;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
    }
}
/* Step Service.
 **********************************************/
void serv_CpnSch_tick(void){
    clCpnSch.tick(clCpnSch.self);
}

/* Real time Interface trigger.
 **********************************************/
void trig_CpnSch_inf_getTime(uint16 *point){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_inf_getTime, (uint8*)point);
}

/* Error code Interface trigger.
 **********************************************/
void trig_CpnSch_inf_setErr(uint16 id, uint16 code){
    uint32 uwErrCode = (((uint32)id << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_inf_setErr, (uint8*)&uwErrCode);
}

/* Initial component Interface trigger.
 **********************************************/
void trig_CpnSch_inf_initCpn(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMem_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMemTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFrameMatrix_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMap_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCrc_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMem_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMemTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskCtrl_init, NULL);
}

/**************************** Copyright(C) pxf ****************************/
