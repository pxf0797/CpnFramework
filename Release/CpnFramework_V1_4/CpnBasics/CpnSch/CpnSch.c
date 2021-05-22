/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSch.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  : CpnSch class functions definition source files.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnSch.h"
#include "../FuncLib/FuncLib.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnSch class definition.
 **********************************************************/
/* Function : CpnSch_tick(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_tick(hCpnSch cthis){
    cthis->SchSmRec->ticker++;
}

/* Function : CpnSch_run(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_run(hCpnSch cthis){
    if(cthis->SchSm){
        SMREH(cthis->SchSm, cthis->SchSmRec);
    }
}

/* Function : CpnSch_addList(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_addList(hCpnSch cthis, taskLevel level, task t, uint16 prd, uint16 start, strategy strgMask){
    if(cthis->taskNum >= CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG){
        cthis->err(cthis, CPN_SCH_TASK_LIST_IS_FULL);
        return;
    }
    cthis->taskList[cthis->taskNum].level = level;
    cthis->taskList[cthis->taskNum].t = t;
    cthis->taskList[cthis->taskNum].prdTick = prd;
    cthis->taskList[cthis->taskNum].startTick = start;
    cthis->taskList[cthis->taskNum].strgMask = strgMask;
    cthis->taskNum++;
}


/* Function : CpnSch_delList(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_delList(hCpnSch cthis, task t){
    uint16 i = 0u;
    uint16 taskNum = cthis->taskNum;

    if(!cthis->taskNum){
        cthis->err(cthis, CPN_SCH_TASK_LIST_TASK_NOT_FOUND);
        return;
    }
    for(i = 0u; i < cthis->taskNum; i++){
        if(cthis->taskList[i].t == t){
            if(i < (cthis->taskNum-1u)){
                memCopy(&cthis->taskList[i], &cthis->taskList[i+1u], (sizeof(initTaskParam)*(cthis->taskNum-i-1u)));
            }
            cthis->taskNum--;
        }
    }
    if(cthis->taskNum == taskNum){
        cthis->err(cthis, CPN_SCH_TASK_LIST_TASK_NOT_FOUND);
    }
}


/* Function : CpnSch_addTask(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_addTask(hCpnSch cthis, taskLevel level, task t, uint16 prd, uint16 start){
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 groupIndex = 0u;
    uint16 levelGroupEnd = 0u;

    if(level == level0){
        groupIndex = (CPN_SCH_LEVEL3_GROUP_NUM_CFG+CPN_SCH_LEVEL2_GROUP_NUM_CFG+CPN_SCH_LEVEL1_GROUP_NUM_CFG);
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL0_GROUP_NUM_CFG);
    }else if(level == level1){
        groupIndex = (CPN_SCH_LEVEL3_GROUP_NUM_CFG+CPN_SCH_LEVEL2_GROUP_NUM_CFG);
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL1_GROUP_NUM_CFG);
    }else if(level == level2){
        groupIndex = CPN_SCH_LEVEL3_GROUP_NUM_CFG;
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL2_GROUP_NUM_CFG);
    }else if(level == level3){
        groupIndex = 0u;
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL3_GROUP_NUM_CFG);
    }else{
        cthis->err(cthis, CPN_SCH_ADD_TASK_LEVEVL_NOT_EIXST);
        return;
    }

    while(groupIndex < levelGroupEnd){
        taskMask = cthis->SchSmRec->taskGroups[groupIndex].taskMask;
        if(taskMask+1u){ /*taskMask!=0xFFFFFFF*/
            /* Add new task. */
            curTask = (~taskMask);
            //curTask = (curTask&(curTask^(curTask-1u)));
            curTask = (curTask&(-curTask));
            taskIndex = log_2n((uint32)curTask);

            if(groupIndex < (cthis->SchSmRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG)){
                cthis->SchSmRec->taskGroups[groupIndex].unstartMask |= curTask;
            }
            cthis->SchSmRec->taskGroups[groupIndex].taskMask |= curTask;
            cthis->SchSmRec->taskGroups[groupIndex].taskGroup[taskIndex] = t;
            cthis->SchSmRec->taskGroups[groupIndex].prdTick[taskIndex] = prd;
            cthis->SchSmRec->taskGroups[groupIndex].startTick[taskIndex] = (cthis->SchSmRec->ticker+start);
            break;
        }else{
            groupIndex++;
        }
    }
    /* If all group is full, then report error. */
    if(groupIndex >= levelGroupEnd){
        if(level == level0){
            cthis->err(cthis, CPN_SCH_ADD_TASK_LEVEVL0GROUP_FULL);
        }else if(level == level1){
            cthis->err(cthis, CPN_SCH_ADD_TASK_LEVEVL1GROUP_FULL);
        }else if(level == level2){
            cthis->err(cthis, CPN_SCH_ADD_TASK_LEVEVL2GROUP_FULL);
        }else if(level == level3){
            cthis->err(cthis, CPN_SCH_ADD_TASK_LEVEVL3GROUP_FULL);
        }else{
            cthis->err(cthis, CPN_SCH_ADD_TASK_LEVEVL_NOT_EIXST);
        }
    }
}


/* Function : CpnSch_delTask(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_delTask(hCpnSch cthis, taskLevel level, task t){
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 groupIndex = 0u;
    uint16 levelGroupEnd = 0u;
    uint16 taskFoundFlg = 0u;

    if(level == level0){
        groupIndex = (CPN_SCH_LEVEL3_GROUP_NUM_CFG+CPN_SCH_LEVEL2_GROUP_NUM_CFG+CPN_SCH_LEVEL1_GROUP_NUM_CFG);
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL0_GROUP_NUM_CFG);
    }else if(level == level1){
        groupIndex = (CPN_SCH_LEVEL3_GROUP_NUM_CFG+CPN_SCH_LEVEL2_GROUP_NUM_CFG);
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL1_GROUP_NUM_CFG);
    }else if(level == level2){
        groupIndex = CPN_SCH_LEVEL3_GROUP_NUM_CFG;
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL2_GROUP_NUM_CFG);
    }else if(level == level3){
        groupIndex = 0u;
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL3_GROUP_NUM_CFG);
    }else{
        cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL_NOT_EIXST);
        return;
    }

    while(groupIndex < levelGroupEnd){
        taskMask = cthis->SchSmRec->taskGroups[groupIndex].taskMask;
        while(taskMask){
            curTask = taskMask;
            //curTask = (curTask&(curTask^(curTask-1)));
            curTask = (curTask&(-curTask));
            taskIndex = log_2n((uint32)curTask);

            if(cthis->SchSmRec->taskGroups[groupIndex].taskGroup[taskIndex] == t){
                cthis->SchSmRec->taskGroups[groupIndex].taskMask &= (~curTask);
                cthis->SchSmRec->taskGroups[groupIndex].actMask &= (~curTask);
                taskFoundFlg = 1u;
                break;
            }
            /* Continue to find. */
            taskMask &= (~curTask);
        }
        /* If found, then return. */
        if(taskFoundFlg){
            break;
        }else{
            groupIndex++;
        }
    }
    /* If not found, then report error. */
    if(groupIndex >= levelGroupEnd){
        if(level == level0){
            cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL0GROUP_NOT_EIXST);
        }else if(level == level1){
            cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL1GROUP_NOT_EIXST);
        }else if(level == level2){
            cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL2GROUP_NOT_EIXST);
        }else if(level == level3){
            cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL3GROUP_NOT_EIXST);
        }else{
            cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL_NOT_EIXST);
        }
    }
}

/* Function : CpnSch_delay(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_delay(hCpnSch cthis, uint32 *tick){
    uint32 tickTemp = 0ul;

    /* If highest bit is 0, then start a new delay. */
    if(!((*tick)&0xFFFF0000u)){
        tickTemp = cthis->SchSmRec->ticker;
        tickTemp = (tickTemp<<16u);
        //*tick |= tickTemp;
        *tick = (*tick|tickTemp);
    }

    tickTemp = ((*tick)>>16u);
    if((cthis->SchSmRec->ticker-tickTemp) >= ((*tick)&0x00007FFFu)){
        //*tick |= 0x00008000u;
        *tick = (*tick|0x00008000u); /* If highest bit is 1, means that delay time is expired. */
    }
}

/* Function : CpnSch_setMonitor(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_setMonitor(hCpnSch cthis, taskLevel level, task t){
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 groupIndex = 0u;
    uint16 levelGroupEnd = 0u;

    if(level == level0){
        groupIndex = (CPN_SCH_LEVEL3_GROUP_NUM_CFG+CPN_SCH_LEVEL2_GROUP_NUM_CFG+CPN_SCH_LEVEL1_GROUP_NUM_CFG);
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL0_GROUP_NUM_CFG);
    }else if(level == level1){
        groupIndex = (CPN_SCH_LEVEL3_GROUP_NUM_CFG+CPN_SCH_LEVEL2_GROUP_NUM_CFG);
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL1_GROUP_NUM_CFG);
    }else if(level == level2){
        groupIndex = CPN_SCH_LEVEL3_GROUP_NUM_CFG;
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL2_GROUP_NUM_CFG);
    }else if(level == level3){
        groupIndex = 0u;
        levelGroupEnd = (groupIndex+CPN_SCH_LEVEL3_GROUP_NUM_CFG);
    }else{
        cthis->err(cthis, CPN_SCH_SPECIFIC_TASK_LEVEVL_NOT_EIXST);
        return;
    }

    cthis->specificTaskMask = 0u;
    while(groupIndex < levelGroupEnd){
        taskMask = cthis->SchSmRec->taskGroups[groupIndex].taskMask;
        while(taskMask){
            curTask = taskMask;
            curTask = (curTask&(-curTask));
            taskIndex = log_2n((uint32)curTask);
            taskMask &= (~curTask);
            if(cthis->SchSmRec->taskGroups[groupIndex].taskGroup[taskIndex] == t){
                cthis->specificTaskMask = (0x8000u|(groupIndex<<8u)|taskIndex);
                break;
            }
        }
        groupIndex++;
    }
    if(!cthis->specificTaskMask){
        cthis->err(cthis, CPN_SCH_SPECIFIC_TASK_NOT_FOUND);
    }
}

/* Function : CpnSch_getMonitor(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_getMonitor(hCpnSch cthis, uint16 *point){
    *point = cthis->specificTaskTime;
}

/* Function : CpnSch_setStrategy(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_setStrategy(hCpnSch cthis, strategy strgMask){
    cthis->strgMask = strgMask;
}

/* Function : CpnSch_getStrategy(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_getStrategy(hCpnSch cthis, strategy *strgMask){
    *strgMask = cthis->strgMask;
}

/* Function : CpnSch_getTaskNum(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_getTaskNum(hCpnSch cthis, uint16 *taskNum){
    *taskNum = cthis->taskNum;
}

/* Function : CpnSch_now(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_now(hCpnSch cthis, uint16 *point){
    cthis->iTime.getTime(point);
}


/* Function : CpnSch_err(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_err(hCpnSch cthis, uint16 code){
    cthis->iErr.setErr(CPNSCHCFG_ERR_ID, code);
}

/* Function : hCpnSch CpnSch_init(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   : hCpnSch - cthis/OOPC_NULL
 * Others   : CpnSch class initial function.
 **********************************************/
hCpnSch CpnSch_init(hCpnSch cthis, hSchSmRec SchSmRec, hstaAct SchSm,
            void (*getTime)(uint16 *point),
            void (*setErr)(uint16 id, uint16 code),
            void (*initCpn)(void)){
    cthis->iTime.getTime = getTime;
    cthis->iErr.setErr = setErr;
    cthis->iInitCpn.initCpn = initCpn;

    cthis->SchSmRec = SchSmRec;
    cthis->SchSmRec->next = SchSm_sta_init;
    cthis->SchSm = SchSm;

    cthis->run(cthis);            /* Initial state machine. */
    cthis->iInitCpn.initCpn();    /* Initial component. */

    return cthis;
}

/* Function : hCpnSch CpnSch_ctor(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   : hCpnSch - cthis/OOPC_NULL
 * Others   : CpnSch class constructor.
 **********************************************/
CC(CpnSch){
    cthis->init = CpnSch_init;
    cthis->tick = CpnSch_tick;
    cthis->run = CpnSch_run;
    cthis->addList = CpnSch_addList;
    cthis->delList = CpnSch_delList;
    cthis->addTask = CpnSch_addTask;
    cthis->delTask = CpnSch_delTask;
    cthis->delay = CpnSch_delay;
    cthis->setMonitor = CpnSch_setMonitor;
    cthis->getMonitor = CpnSch_getMonitor;
    cthis->setStrategy = CpnSch_setStrategy;
    cthis->getStrategy = CpnSch_getStrategy;
    cthis->getTaskNum = CpnSch_getTaskNum;
    cthis->now = CpnSch_now;
    cthis->err = CpnSch_err;
    /* TODO */

    /* Configure parameters. */
    cthis->usage = 0u;
    cthis->currTaskIndex = 0u;
    cthis->currTaskTime = 0u;
    cthis->totalTaskTime = 0u;
    cthis->specificTaskMask = 0u;
    cthis->specificTaskTime = 0u;
    cthis->strgMask = DEFAULT_STRATEGY_TASK_GROUPS;
    cthis->taskNum = 0u;
    cthis->SchSm = NULL;
    cthis->SchSmRec = NULL;

    return cthis;
}

/* Function : hCpnSch CpnSch_dtor(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnSch class destructor.
 **********************************************/
CD(CpnSch){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
