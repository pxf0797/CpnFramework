/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SchSm.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:12:12
 * Description  : State machine SchSm definition and state action definition.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "SchSm.h"
#include "CpnSch.h"
#include "FuncLib.h"

/* State machine SchSm definition.
 * Configure state process functions.
 **********************************************/
SMDF(SchSm, SCHSM_LIST);
SchSmRec SchSmRunRec;
extern CpnSch clCpnSch;

/* Function : SchSm_act_init()
 * Input    : SchSmRec - state record pointer
 * Output   :
 * Others   : initial state action.
 **********************************************/
void SchSm_act_init(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    uint16 i = 0u;
    uint16 j = 0u;

    hRec->ticker = 0u;
    hRec->taskGroupNum = CPN_SCH_GROUP_TOTAL_NUMS;
    hRec->CpnSch = &clCpnSch;
    for(i = 0u; i < CPN_SCH_GROUP_TOTAL_NUMS; i++){
        for(j = 0u; j < (sizeof(taskGroupType)<<3U); j++){
            hRec->taskGroups[i].startTick[j] = 0u;
            hRec->taskGroups[i].prdTick[j] = 0u;
            hRec->taskGroups[i].taskGroup[j] = NULL;
        }
        hRec->taskGroups[i].unstartMask = 0u;
        hRec->taskGroups[i].actMask = 0u;
        hRec->taskGroups[i].taskMask = 0u;
    }

    hRec->next = SchSm_sta_execute;
    hRec->last = SchSm_sta_init;
}

/* Function : SchSm_act_update()
 * Input    : SchSmRec - state record pointer
 * Output   :
 * Others   : state update action.
 **********************************************/
void SchSm_act_update(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 i = 0u;
    uint16 diffTick = 0u;

    /* Exclude background tasks, and update execute flag. */
    for(i = 0u; i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG); i++){
        /* Update tasks active state for each group. */
        taskMask = hRec->taskGroups[i].taskMask;
        while(taskMask != 0u){
            //curTask = (taskMask&(taskMask^(taskMask-1u)));
            curTask = (taskMask&(-taskMask));
            //taskMask ^= curTask;
            taskMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            if(hRec->taskGroups[i].unstartMask){
                /* Check current task whether in execute period, then execute it. */
                if(hRec->taskGroups[i].unstartMask&curTask){
                    /* If task activate step is less than 2, then execute it. Normally there is no step difference. */
                    diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                    if(diffTick <= 5U/*2U*/){
                        hRec->taskGroups[i].unstartMask &= (~curTask);
                        /* Update task activate state and next activate step. */
                        hRec->taskGroups[i].actMask |= curTask;
                        //hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                    }
                }else{
                    diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                    if(diffTick >= hRec->taskGroups[i].prdTick[taskIndex]){
                        /* Update task activate state and next activate step. */
                        hRec->taskGroups[i].actMask |= curTask;
                        hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                    }
                }
            }else{
                /* All tasks in the execute period. */
                diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                if(diffTick >= hRec->taskGroups[i].prdTick[taskIndex]){
                    /* Update task activate state and next activate step. */
                    hRec->taskGroups[i].actMask |= curTask;
                    hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                }
            }
        }
    }

    hRec->next = SchSm_sta_execute;
    hRec->last = SchSm_sta_update;
}

/* Function : SchSm_act_execute()
 * Input    : SchSmRec - state record pointer
 * Output   :
 * Others   : state execute action.
 **********************************************/
void SchSm_act_execute(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 i = 0u;
    uint16 specificFlg = 0u;
#if (CPN_SCH_TASK_MEASURE_ENABLE == TRUE)
    static uint16 taskTimePot = 0u;
    uint16 currUsage = 0u;
    ((hCpnSch)(hRec->CpnSch))->now(hRec->CpnSch, &taskTimePot);
#endif

    for(i = 0u; i < hRec->taskGroupNum; i++){
        /* Loop up all activate tasks to find highest prior task, and execute it. */
        taskMask = hRec->taskGroups[i].actMask;
        if(taskMask != 0u){
            //curTask = (taskMask&(taskMask^(taskMask-1u)));
            curTask = (taskMask&(-taskMask));
            //hRec->taskGroups[i].actMask ^= curTask; /* Easy to cause uncontrollable results. */
            hRec->taskGroups[i].actMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            /* Determine whether it is a one-time task, and remove the task mask if it is not a level0 background task. */
            if((hRec->taskGroups[i].prdTick[taskIndex] == 0u) && (i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG))){
                hRec->taskGroups[i].taskMask &= (~curTask);
            }

            /* Loop up specific task, and setup flag. */
            if((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x8000u)
            &&(((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x7F00u)>>8u)==i)
            &&((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x00FFu)==taskIndex)){
                specificFlg = 1u;
            }

            /* Execute task. */
            ((hCpnSch)(hRec->CpnSch))->currTaskIndex = ((i<<8u)|taskIndex);
            if(hRec->taskGroups[i].taskGroup[taskIndex]){
                hRec->taskGroups[i].taskGroup[taskIndex]();
            }
            break;
        }
    }

#if (CPN_SCH_TASK_MEASURE_ENABLE == TRUE)
    ((hCpnSch)(hRec->CpnSch))->currTaskTime = taskTimePot;
    ((hCpnSch)(hRec->CpnSch))->now(hRec->CpnSch, &taskTimePot);
    ((hCpnSch)(hRec->CpnSch))->currTaskTime = (taskTimePot-((hCpnSch)(hRec->CpnSch))->currTaskTime);
    /* Update specific task execute time. */
    if(specificFlg){
        ((hCpnSch)(hRec->CpnSch))->specificTaskTime = ((hCpnSch)(hRec->CpnSch))->currTaskTime;
    }
    /* The current time measurement is accurate to 0.1us, and the usage rate is accurate to 0.1%. */
    if(i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG)){
        ((hCpnSch)(hRec->CpnSch))->totalTaskTime += ((hCpnSch)(hRec->CpnSch))->currTaskTime;
    }else{
        if(((hCpnSch)(hRec->CpnSch))->totalTaskTime){
            currUsage = ((uint32)((hCpnSch)(hRec->CpnSch))->totalTaskTime*100U/CPN_SCH_TASK_TICK_TIME_US);
            ((hCpnSch)(hRec->CpnSch))->usage = (uint16)lowpassFilter(currUsage, (uint32)((hCpnSch)(hRec->CpnSch))->usage, 4U);
            ((hCpnSch)(hRec->CpnSch))->totalTaskTime = 0U;
        }
    }
#endif

    if(hRec->ticker != hRec->tickerLast){
        hRec->tickerLast = hRec->ticker;
        hRec->next = SchSm_sta_update;
    }else if((i >= hRec->taskGroupNum) && (!hRec->taskGroups[hRec->taskGroupNum-1u].actMask)){
        hRec->next = SchSm_sta_updateBgTask;
    }else{
        hRec->next = SchSm_sta_execute;
    }
    hRec->last = SchSm_sta_execute;
}

/* Function : SchSm_act_updateBgTask()
 * Input    : SchSmRec - state record pointer
 * Output   :
 * Others   : state updateBgTask action.
 **********************************************/
void SchSm_act_updateBgTask(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    uint16 i = 0u;

    for(i = (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG); i < hRec->taskGroupNum; i++){
        hRec->taskGroups[i].actMask = hRec->taskGroups[i].taskMask;
    }

    if(hRec->ticker != hRec->tickerLast){
        hRec->tickerLast = hRec->ticker;
        hRec->next = SchSm_sta_update;
    }else{
        hRec->next = SchSm_sta_execute;
    }
    hRec->last = SchSm_sta_updateBgTask;
}

/**************************** Copyright(C) pxf ****************************/
