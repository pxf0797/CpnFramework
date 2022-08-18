/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSimpleSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2022/08/17 19:49:04
 * Description  : CpnSimple component signals definition source file.
 * Others       :
 * History      : 20220817 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnSimpleSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnSimple class definition.
 **********************************************************/
/* CpnSimple class.
 **********************************************/
// static CpnSimple clCpnSimple;
TASKDFS(SIMPLE_LIST)


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSimple_init(void){
    tsInitTask taskParam;
    /*taskParam.level = task_level_task1;
    taskParam.t = task_simples[task_index_task1];
    taskParam.prdTick = task_period_task1;
    taskParam.startTick = task_start_task1;
    taskParam.e.all = e_task1;
    SYN_TRIG(sig_trig_CpnSimple_initTask, &taskParam);*/
    #define TASK_SIMPLE_ADD(name,level_,start,period) do{         \
        taskParam.level = task_level_##name;                      \
        taskParam.t = task_simples[task_index_##name];            \
        taskParam.prdTick = task_period_##name;                   \
        taskParam.startTick = task_start_##name;                  \
        taskParam.e.all = e_##name;                               \
        SYN_TRIG(sig_trig_CpnSimple_initTask, &taskParam);        \
    }while(0);
    #define TASK_SIMPLE_ADDS(task_list) do{task_list(TASK_SIMPLE_ADD)}while(0)
    TASK_SIMPLE_ADDS(SIMPLE_LIST);
}


/***********************************************************
 * Component running task.
 **********************************************************/
/* task simple definition.
 **********************************************/
void task_task1(void){}

/* task simple definition.
 **********************************************/
void task_task2(void){}

/* task simple definition.
 **********************************************/
void task_task3(void){}

/**************************** Copyright(C) pxf ****************************/
