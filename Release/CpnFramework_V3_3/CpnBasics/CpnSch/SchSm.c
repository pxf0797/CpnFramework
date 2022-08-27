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
#include "SchTask.h"
#include "FuncLib.h"

/* State machine SchSm definition.
 * Configure state process functions.
 **********************************************/
SMDF(SchSm, SCHSM_LIST);
// SchSmRec SchSmRunRec;
//extern SchTask clCpnSch;

/* Function : SchSm_act_init()
 * Input    : SchSmRec - state record pointer
 * Output   :
 * Others   : initial state action.
 **********************************************/
void SchSm_act_init(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    uint16 i = 0u;
    uint16 j = 0u;

    /* initial state machine params. */
    hRec->ticker = 0u;
    hRec->tickerLast = 0u;
    hRec->taskMeasureEn = CPN_SCH_TASK_MEASURE_ENABLE;
    hRec->taskGroupNum = CPN_SCH_GROUP_TOTAL_NUMS;
    //hRec->SchTask = &clCpnSch;
    #define GROUP_INDEX_SET(level_,length) do{                      \
        uint16 index = level##level_;                               \
        if(!level##level_){                                         \
            hRec->taskLevelGroupIndex[level##level_] = (hRec->taskGroupNum-(hRec->taskLevelMaxNum[level##level_]>>GROUP_TYPE_BITS)); \
            break;                                                  \
        }                                                           \
        index--;                                                    \
        hRec->taskLevelGroupIndex[index+1u] = (hRec->taskLevelGroupIndex[index]-(hRec->taskLevelMaxNum[index+1u]>>GROUP_TYPE_BITS)); \
    }while(0);
    #define GROUP_NUM_SET(level_,length) hRec->taskLevelMaxNum[level##level_] = (level##level_##_length<<GROUP_TYPE_BITS);
    #define GROUP_INDEX_NUM(level_list) do{level_list(GROUP_NUM_SET) level_list(GROUP_INDEX_SET)}while(0)
    GROUP_INDEX_NUM(LEVEL_LIST);
    for(i = 0u; i < level_max; i++){
        // hRec->taskLevelGroupIndex[i] = 0u;
        // hRec->taskLevelMaxNum[i] = 0u;
        hRec->taskLevelCounter[i] = 0u;
    }
    for(i = 0u; i < CPN_SCH_GROUP_TOTAL_NUMS; i++){
        for(j = 0u; j < (sizeof(taskGroupType)<<3U); j++){
            hRec->taskGroups[i].startTick[j] = 0u;
            hRec->taskGroups[i].prdTick[j] = 0u;
            hRec->taskGroups[i].taskGroup[j] = OOPC_NULL;
        }
        hRec->taskGroups[i].unstartMask = 0u;
        hRec->taskGroups[i].actMask = 0u;
        hRec->taskGroups[i].taskMask = 0u;
    }

    hRec->next = SchSm_sta_update;
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

    /* wait tick update */
    hRec->last = SchSm_sta_update;
    if(hRec->tickerLast == hRec->ticker){
        return;
    }
    hRec->tickerLast = hRec->ticker;
    /* update execute flag. */
    for(i = 0u; i < hRec->taskGroupNum; i++){
        /* Update tasks active state for each group. */
        taskMask = hRec->taskGroups[i].taskMask;
        while(taskMask){
            curTask = MASK_FIRST_BIT(taskMask);
            taskMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            if(hRec->taskGroups[i].unstartMask){
                /* Check current task whether in execute period, then execute it. */
                if(hRec->taskGroups[i].unstartMask&curTask){
                    /* If task activate step is less than 2, then execute it. Normally there is no step deviation. */
                    diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                    if(diffTick <= TASK_EXECUTE_DEVIATION_STEPS){
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

    /* set next state to execute. */
    hRec->next = SchSm_sta_execute;
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
    uint16 gotoUpdateFlag = 0u;
    static uint16 taskTimePot = 0u;
    static uint16 totalTimePot = 0u;
    uint16 specificFlag = 0u;
    uint16 currUsage = 0u;
    hSchTask task = ((hSchTask)(hRec->SchTask));

    if(hRec->taskMeasureEn){
        /* update for lask period usage. */
        if(hRec->last == SchSm_sta_update){
            task->now(hRec->SchTask, &totalTimePot);
        }
        /* initial for specific task time record. */
        task->now(hRec->SchTask, &taskTimePot);
    }

    hRec->last = SchSm_sta_execute;
    for(i = 0u; i < hRec->taskGroupNum; i++){
        /* Loop up all activate tasks to find highest prior task, and execute it. */
        taskMask = hRec->taskGroups[i].actMask;
        if(taskMask){
            curTask = MASK_FIRST_BIT(taskMask);
            hRec->taskGroups[i].actMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            /* Determine whether it is a one-time task, and remove the task mask. */
            if(hRec->taskGroups[i].prdTick[taskIndex] == sig_clear){
                hRec->taskGroups[i].taskMask &= (~curTask);
            }
            if(hRec->taskMeasureEn){
                /* Loop up specific task, and setup flag. */
                if((task->specificTaskMask.bit.enable)
                &&((task->specificTaskMask.bit.group) == i)
                &&((task->specificTaskMask.bit.index) == taskIndex)){
                    specificFlag = sig_set;
                }
            }
            /* Execute task. */
            task->currTaskIndex = ((i<<8)|taskIndex);
            if(hRec->taskGroups[i].taskGroup[taskIndex]){
                hRec->taskGroups[i].taskGroup[taskIndex]();
            }
            /* Judge whether goto update. */
            if((i == (hRec->taskGroupNum-1u))
            &&(hRec->taskGroups[i].actMask == sig_clear)){
                gotoUpdateFlag = sig_set;
            }
            break;
        }
    }

    if(hRec->taskMeasureEn){
        task->currTaskTime = taskTimePot;
        task->now(hRec->SchTask, &taskTimePot);
        task->currTaskTime = (taskTimePot-task->currTaskTime);
        /* Update specific task execute time. */
        if(specificFlag){
            task->specificTaskTime = task->currTaskTime;
        }
    }

    if((hRec->ticker != hRec->tickerLast)
    ||gotoUpdateFlag){
        if(hRec->taskMeasureEn){
            /* The current time measurement is accurate to 0.1us, and the usage rate is accurate to 0.1%. */
            task->totalTaskTime = totalTimePot;
            task->now(hRec->SchTask, &totalTimePot);
            task->totalTaskTime = (totalTimePot-task->totalTaskTime);
            currUsage = (((uint32)task->totalTaskTime)*100U/CPN_SCH_TASK_TICK_TIME_US);
            task->usage = (uint16)lowpassFilter(currUsage, (uint32)task->usage, 4U);
        }
        hRec->next = SchSm_sta_update;
    }
}

/**************************** Copyright(C) pxf ****************************/
