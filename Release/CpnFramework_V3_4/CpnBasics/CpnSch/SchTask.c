/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SchTask.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2022/08/06 14:37:14
 * Description  : SchTask class functions definition source file.
 * Others       :
 * History      : 20220806 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "SchTask.h"
#include "CpnSchCfg.h"
#include "CpnSch.h"
#include "RteSigs.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
static hCpnSch clCpnSch = OOPC_NULL;

SLICE_TASK_DF_ALL(SLICE_LIST)
BASIC_TASK_DF_ALL(SLICE_LIST)


/***********************************************************
 * SchTask class definition.
 **********************************************************/
/* Function : SchTask_tick(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_tick(hSchTask cthis){
    cthis->smRec.ticker++;
}

/* Function : SchTask_run(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_run(hSchTask cthis){
    if(cthis->sm){
        SMRE(cthis->sm, cthis->smRec);
    }
}

/* Function : SchTask_addTask(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_addTask(hSchTask cthis, htsTask task){
    uint16 taskIndex = 0u;
    uint16 groupIndex = 0u;
    taskGroupType curTask = 0u;
    taskGroupType taskMask = 0u;

    do{
        if(task->init.level >= level_max){
            cthis->err(cthis, CPN_SCH_ADD_TASK_LEVEVL_NOT_EIXST);
            break;
        }
        /* judge task max counter. */
        if(cthis->smRec.taskLevelCounter[task->init.level] >= cthis->smRec.taskLevelMaxNum[task->init.level]){
            cthis->err(cthis, CPN_SCH_ADD_TASK_GROUP_TASK_IS_FULL);
            break;
        }
        /* if task active, directly return. */
        if(task->sta.active){
            break;
        }
        /* get group index and task mask */
        groupIndex = cthis->smRec.taskLevelGroupIndex[task->init.level];
        taskMask = cthis->smRec.taskGroups[groupIndex].taskMask;
        /* find the unmasked group. */
        while(!(taskMask+1u)){ /*taskMask!=0xFFFFFFF*/
            groupIndex++;
            taskMask = cthis->smRec.taskGroups[groupIndex].taskMask;
        }
        /* get the mask and index. */
        curTask = ~taskMask;
        curTask = MASK_FIRST_BIT(curTask);
        taskIndex = log_2n((uint32)curTask);
        /* set the task. */
        cthis->smRec.taskGroups[groupIndex].unstartMask |= curTask;
        cthis->smRec.taskGroups[groupIndex].taskMask |= curTask;
        cthis->smRec.taskGroups[groupIndex].taskGroup[taskIndex] = task->init.t;
        cthis->smRec.taskGroups[groupIndex].prdTick[taskIndex] = task->init.prdTick;
        cthis->smRec.taskGroups[groupIndex].startTick[taskIndex] = (cthis->smRec.ticker+task->init.startTick);
        cthis->smRec.taskLevelCounter[task->init.level]++;
        /* update task status. */
        if(task->init.prdTick){
            /* one time task will keep inactieve, so that it can be added any time. */
            task->sta.active = sig_set;
        }
        task->sta.groupIndex = groupIndex;
    }while(0);
}

/* Function : SchTask_addLowestTask(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_addLowestTask(hSchTask cthis, htsTask task){
    uint16 groupIndex = cthis->getGroupIndex(cthis, task->init.prdTick);
    taskGroupType *taskMask = cthis->slices[groupIndex].taskMask;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 taskGroup = 0u;
    do{
        if(cthis->slices[groupIndex].taskCounter >= cthis->slices[groupIndex].taskMaxNum){
            cthis->err(cthis, CPN_SCH_LOWEST_TASK_GROUP_IS_FULL);
            break;
        }
        /* if task active, directly return. */
        if(task->sta.active){
            break;
        }
        while(!(taskMask[taskGroup]+1u)){ /*taskMask!=0xFFFFFFF*/
            taskGroup++;
        }
        /* get first unmasked bit. */
        curTask = (~taskMask[taskGroup]);
        curTask = MASK_FIRST_BIT(curTask);
        /* get corresponding index. */
        taskIndex = log_2n((uint32)curTask);
        taskIndex += (taskGroup<<GROUP_TYPE_BITS);
        /* set the task and mask bit. */
        cthis->slices[groupIndex].sliceTask[taskIndex] = task->init.t;
        cthis->slices[groupIndex].taskMask[taskGroup] |= curTask;
        cthis->slices[groupIndex].taskCounter++;
        /* update task status. */
        task->sta.active = sig_set;
        task->sta.lowestGroup = groupIndex;
        task->sta.groupIndex = taskIndex;
    }while(0);
}

/* Function : SchTask_delTask(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_delTask(hSchTask cthis, htsTask task){
    uint16 taskIndex = 0u;
    uint16 groupIndex = 0u;
    taskGroupType curTask = 0u;

    do{
        if(task->init.level >= level_max){
            cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL_NOT_EIXST);
            break;
        }
        if(task->sta.groupIndex >= cthis->smRec.taskLevelMaxNum[task->init.level]){
            cthis->err(cthis, CPN_SCH_DEL_TASK_LEVEVL_LENGTH_NOT_EXIST);
            break;
        }
        /* get group index and task index */
        groupIndex = cthis->smRec.taskLevelGroupIndex[task->init.level];
        groupIndex += (task->sta.groupIndex>>GROUP_TYPE_BITS);
        taskIndex = (task->sta.groupIndex&GROUP_TYPE_BITS);
        curTask = ((taskGroupType)1u<<taskIndex);
        /* judge task exist */
        if(cthis->smRec.taskGroups[groupIndex].taskGroup[taskIndex] != task->init.t){
            cthis->err(cthis, CPN_SCH_DEL_TASK_TASK_IS_NOT_RIGHT);
            break;
        }
        /* delete task */
        curTask = ~curTask;
        cthis->smRec.taskGroups[groupIndex].taskMask &= curTask;
        cthis->smRec.taskGroups[groupIndex].actMask &= curTask;
        /* updtate task status. */
        task->sta.active = sig_clear;
    }while(0);
}

/* Function : SchTask_addLowestTask(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_delLowestTask(hSchTask cthis, htsTask task){
    taskGroupType curTask = 0u;
    uint16 taskGroup = 0u;

    do{
        if(cthis->slices[task->sta.lowestGroup].sliceTask[task->sta.groupIndex] != task->init.t){
            cthis->err(cthis, CPN_SCH_LOWEST_TASK_TASK_IS_NOT_RIGHT);
            break;
        }
        /* delete the task. */
        taskGroup = (task->sta.groupIndex>>GROUP_TYPE_BITS);
        curTask = ((taskGroupType)1u<<(task->sta.groupIndex&GROUP_TYPE_BITS));
        curTask = ~curTask;
        cthis->slices[task->sta.lowestGroup].taskMask[taskGroup] &= curTask;
        cthis->slices[task->sta.lowestGroup].taskCounter--;
        /* updtate task status. */
        task->sta.active = sig_clear;
    }while(0);
}

/* Function : SchTask_getGroupIndex(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
uint16 SchTask_getGroupIndex(hSchTask cthis, uint16 prd){
    uint16 groupIndex = te_task_period_index_max;

    while((groupIndex > 0u) && (prd < cthis->slices[groupIndex].taskParam.init.prdTick)){
        groupIndex--;
    }
    if(groupIndex == te_task_period_index_max){
        groupIndex--;
    }
    return groupIndex;
}

/* Function : SchTask_setMonitor(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_setMonitor(hSchTask cthis, htsTask task){
    uint16 taskIndex = 0u;
    uint16 groupIndex = 0u;
    uint16 index = task->sta.groupIndex;

    do{
        if(task->init.level >= level_max){
            cthis->err(cthis, CPN_SCH_SPECIFIC_TASK_LEVEVL_NOT_EIXST);
            break;
        }
        if(index >= cthis->smRec.taskLevelMaxNum[task->init.level]){
            cthis->err(cthis, CPN_SCH_SPECIFIC_TASK_NOT_FOUND);
            break;
        }
        /* get group index and task index */
        groupIndex = cthis->smRec.taskLevelGroupIndex[task->init.level];
        groupIndex += (index>>GROUP_TYPE_BITS);
        taskIndex = (index&GROUP_TYPE_BITS);
        //curTask = ((taskGroupType)1u<<taskIndex);
        /* judge task exist */
        if(cthis->smRec.taskGroups[groupIndex].taskGroup[taskIndex] != task->init.t){
            cthis->err(cthis, CPN_SCH_SPECIFIC_TASK_NOT_FOUND);
            break;
        }

        cthis->specificTaskMask.bit.enable = sig_set;
        cthis->specificTaskMask.bit.group = groupIndex;
        cthis->specificTaskMask.bit.index = taskIndex;
    }while(0);
}

/* Function : SchTask_getMonitor(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_getMonitor(hSchTask cthis, uint16 *point){
    *point = cthis->specificTaskTime;
}

/* Function : SchTask_now(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_now(hSchTask cthis, uint16 *point){
    cthis->iTime.getTime(point);
}

/* Function : SchTask_delay(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_delay(hSchTask cthis, uint32 *tick){
    /* If highest bit is 0, then start a new delay. */
    if(!((hdelayTick)tick)->bit.record){
        ((hdelayTick)tick)->bit.record = cthis->smRec.ticker;
    }
    /* If expired bit is 1, means that delay time is expired. */
    if((cthis->smRec.ticker-((hdelayTick)tick)->bit.record) >= ((hdelayTick)tick)->bit.delay){
        ((hdelayTick)tick)->bit.expired = sig_set;
    }
}

/* Function : SchTask_err(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchTask_err(hSchTask cthis, uint16 code){
    tsErrCode errCode;
    errCode.code = code;
    errCode.id = CPNSCHCFG_ERR_ID;
    SYN_TRIG(sig_trig_CpnSch_setErr, &errCode);
}

/* Function : hSchTask SchTask_init(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   : hSchTask - cthis/OOPC_NULL
 * Others   : SchTask class initial function.
 **********************************************/
hSchTask SchTask_init(hSchTask cthis, hstaAct sm, hsliceParam slices, void *CpnSch){
    hSchTask retRes = cthis;
    uint16 i = 0u;
    do{
        /* specific failure detected */
        if(!(sm && slices)){
            retRes = OOPC_NULL;
            break;
        }

        /* Configure parameters. */
        cthis->CpnSch = CpnSch;
        clCpnSch = CpnSch;
        cthis->smRec.SchTask = cthis;
        cthis->sm = sm;
        /* Initial state machine. */
        cthis->smRec.next = SchSm_sta_init;
        cthis->run(cthis);

        /* configure basic task and slice parameters. */
        #define INIT_SLICE_PARAM(basic,period,num) do{ \
            cthis->slices[te_task_##period##ms_index].taskParam.init.t = BASIC_TASK_FUNC(period); \
            cthis->slices[te_task_##period##ms_index].taskParam.init.level = level0; \
            cthis->slices[te_task_##period##ms_index].taskParam.init.prdTick = te_task_##period##ms_tick; \
            cthis->slices[te_task_##period##ms_index].taskParam.init.startTick = sig_clear; \
            cthis->slices[te_task_##period##ms_index].taskParam.init.e.all = e_slice_sch; \
            cthis->slices[te_task_##period##ms_index].slice = SLICE_TASK_FUNC(period); \
            cthis->slices[te_task_##period##ms_index].taskCounter=0u;\
            cthis->slices[te_task_##period##ms_index].taskMaxNum = te_task_##period##ms_num;\
        }while(0);
        #define INIT_SLICE_PARAMS(slice_list) do{slice_list(INIT_SLICE_PARAM)}while(0)
        INIT_SLICE_PARAMS(SLICE_LIST);

        /* configure slice schedule */
        #define INIT_SLICESCH(basic,period,num) CN(SliceSch, &cthis->slices[te_task_##period##ms_index].sliceSch, cthis->slices[te_task_##period##ms_index].taskMaxNum, \
        te_task_##period##ms_basic_##basic##ms_tick, cthis->slices[te_task_##period##ms_index].taskParam.init.prdTick, \
        cthis->slices[te_task_##period##ms_index].sliceTable, cthis->slices[te_task_##period##ms_index].slice);
        #define INIT_SLICESCH_ALL(slice_list) do{slice_list(INIT_SLICESCH)}while(0)
        INIT_SLICESCH_ALL(SLICE_LIST);

        /* set the task start time. */
        for(i = 0u; i < te_task_period_index_max; i++){
            if(i < te_task_5ms_basic_3ms_tick){
                cthis->slices[i].taskParam.init.startTick = i;
            }else{
                cthis->slices[i].taskParam.init.startTick = (te_task_5ms_basic_3ms_tick-1u);
            }
        }

        /* configure basic slice task. */
        #define ADD_CPNSCH(basic,period,num) cthis->addTask(cthis,&cthis->slices[te_task_##period##ms_index].taskParam);
        #define INIT_BASIC_ALL(slice_list) do{slice_list(ADD_CPNSCH)}while(0)
        INIT_BASIC_ALL(SLICE_LIST);
    }while(0);
    return retRes;
}

/* Function : hSchTask SchTask_ctor(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   : hSchTask - cthis/OOPC_NULL
 * Others   : SchTask class constructor.
 **********************************************/
CC(SchTask){
    hSchTask retRes = cthis;

    do{
        /* Configure functions. */
        cthis->init = SchTask_init;
        cthis->tick = SchTask_tick;
        cthis->run = SchTask_run;
        cthis->addTask = SchTask_addTask;
        cthis->addLowestTask = SchTask_addLowestTask;
        cthis->delTask = SchTask_delTask;
        cthis->delLowestTask = SchTask_delLowestTask;
        cthis->getGroupIndex = SchTask_getGroupIndex;
        cthis->setMonitor = SchTask_setMonitor;
        cthis->getMonitor = SchTask_getMonitor;
        cthis->now = SchTask_now;
        cthis->delay = SchTask_delay;
        cthis->err = SchTask_err;
    }while(0);
    return retRes;
}

/* Function : hSchTask SchTask_dtor(hSchTask cthis)
 * Input    : cthis - SchTask class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : SchTask class destructor.
 **********************************************/
CD(SchTask){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
