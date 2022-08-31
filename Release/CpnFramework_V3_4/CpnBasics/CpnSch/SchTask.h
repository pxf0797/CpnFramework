/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SchTask.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2022/08/06 14:37:14
 * Description  : SchTask class and interface declaration file.
 * Others       :
 * History      : 20220806 pxf Initially established.
 **************************************************************************/

#ifndef SCHTASK_H_
#define SCHTASK_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "FuncLib.h"
#include "SchSm.h"
#include "CpnSchCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define SCHTASK_MACRO_VERSION                   0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Initial task parameter declaration.
 **********************************************/
typedef struct {
    task t;
    uint16 level;
    uint16 prdTick;
    uint16 startTick;
    event e;
} tsInitTask, *htsInitTask;
/* Task status declaration.
 **********************************************/
typedef struct {
    uint16 active      : 1;
    uint16 lowestGroup : 3;
    uint16 groupIndex  : 8; /* schedule group index or lowest group index max counter is 255. */
    uint16 rsvd        : 4;
    uint16 registIndex;     /* task in regist table index. */
} tsTaskSta, *htsTaskSta;
/* Task service data type declaration.
 **********************************************/
typedef struct {
    tsInitTask init;
    tsTaskSta sta;
} tsTask, *htsTask;
/* Task level declaration.
 **********************************************/
typedef union{
    uint32 all;
    struct{
        uint32 delay   : 15;
        uint32 expired : 1;
        uint32 record  : 16;
    } bit;
} delayTick, *hdelayTick;
#define IS_TIMEOUT(tick)          ((hdelayTick)&tick)->bit.expired
/* define slice macros */
#define PERIOD_INDEX(basic,period,num) te_task_##period##ms_index,
#define PERIOD_TICK(basic,period,num) te_task_##period##ms_basic_##basic##ms_tick=basic*MS_T,te_task_##period##ms_tick=period*MS_T,
#define PERIOD_NUM(basic,period,num) te_task_##period##ms_num=num,
#define SLICE_DC(slice_list)                                    \
typedef enum {                                                  \
    slice_list(PERIOD_INDEX)                                    \
    te_task_period_index_max                                    \
} sliePeriodIndex;                                              \
typedef enum {                                                  \
    slice_list(PERIOD_TICK)                                     \
    te_task_period_tick_max                                     \
} sliePeriodTick;                                               \
typedef enum {                                                  \
    slice_list(PERIOD_NUM)                                      \
    te_task_period_num_max                                      \
} sliePeriodNum;                                                \

/* basic slice period, task period, predefine task nums */
//#define BASIC_SLICE_PERIOD    3    /* ms */
/*#define SLICE_LIST(_)              \
    _( 3,     5,    32)            \
    _( 3,    10,    32)            \
    _( 3,    20,    32)            \
    _( 3,   100,    32)            \
*/
/* define slices */
SLICE_DC(SLICE_LIST)

/* define slice tasks. */
typedef struct{
    tsTask taskParam;            /* basic task to drive. */
    SliceSch sliceSch;           /* total sliceSch task is te_task_period_max */
    slice slice;                 /* slice to execute */
    uint16 sliceTable[te_task_5ms_basic_3ms_tick]; /* table to store execute tick */
    uint16 taskCounter;          /* the task num to schedule */
    uint16 taskMaxNum;           /* the task max num to set */
    taskGroupType *taskMask;     /* the task mask to schedule */
    task *sliceTask;             /* task to execute */
} sliceParam, *hsliceParam;

/* Basic slice running task define. */
#define SLICE_TASK_DC(basic,period,num)           void task_##period##ms_basic_slice(uint16 index);
#define SLICE_TASK_DF(basic,period,num)           static void task_##period##ms_basic_slice(uint16 index){ \
    uint16 groupIndex = (uint16)(index>>GROUP_TYPE_BITS);                                           \
    taskGroupType groupMask = (taskGroupType)(1ul<<(index&GROUP_TYPE_MASK));                        \
    if((index<te_task_##period##ms_num)                                                             \
    &&(clCpnSch->taskM->slices[te_task_##period##ms_index].taskMask[groupIndex]&groupMask)          \
    &&clCpnSch->taskM->slices[te_task_##period##ms_index].sliceTask[index]){                        \
        clCpnSch->taskM->slices[te_task_##period##ms_index].sliceTask[index]();                     \
    }                                                                                               \
}
#define BASIC_TASK_DC(basic,period,num)           void task_##period##ms_basic(void);
#define BASIC_TASK_DF(basic,period,num)           static void task_##period##ms_basic(void){ \
    clCpnSch->taskM->slices[te_task_##period##ms_index].sliceSch.run(clCpnSch->taskM->slices[te_task_##period##ms_index].sliceSch.self);\
}
/* basic slice function declaration. */
#define SLICE_TASK_DC_ALL(slice_list)              slice_list(SLICE_TASK_DC)
#define SLICE_TASK_DF_ALL(slice_list)              slice_list(SLICE_TASK_DF)
#define BASIC_TASK_DC_ALL(slice_list)              slice_list(BASIC_TASK_DC)
#define BASIC_TASK_DF_ALL(slice_list)              slice_list(BASIC_TASK_DF)
//SLICE_TASK_DC_ALL(SLICE_LIST)
//BASIC_TASK_DC_ALL(SLICE_LIST)

/* basic slice function and calling. */
#define SLICE_TASK_FUNC(period)                    task_##period##ms_basic_slice
#define SLICE_TASK_CALL(period,index)              task_##period##ms_basic_slice(index)
#define BASIC_TASK_FUNC(period)                    task_##period##ms_basic
#define BASIC_TASK_CALL(period)                    task_##period##ms_basic()

/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
INF(iTime){
    void (*getTime)(uint16 *point);
};

/***********************************************************
 * SchTask class definition.
 **********************************************************/
/* SchTask class declaration.
 **********************************************/
CL(SchTask){
    hSchTask self;
    hSchTask (*init)(hSchTask cthis, hstaAct sm, hsliceParam slices, void *CpnSch);

    /* SchTask class parameters. */
    uint16 usage;            /* cpu usage, such as 112 represent 11.2%. */
    uint16 currTaskIndex;    /* Current task index; bit15--8 represent task group; bit7--0 represent index in group. */
    uint16 currTaskTime;     /* Current task execute time, unit 0.1us. */
    uint16 totalTaskTime;    /* Total task execute time, unit 0.1us. */
    //uint16 specificTaskMask; /* bit15 represent whether task enable£» bit14--8 represent task group£» bit7--0 represent index in group. */
    union {
        uint16 all;
        struct {
            uint16 index  : 8;
            uint16 group  : 7;
            uint16 enable : 1;
        } bit;
    } specificTaskMask;
    uint16 specificTaskTime; /* Specific task execute time, unit 0.1us. */

    /* Component run state machine. */
    SchSmRec smRec;
    hstaAct sm;

    /* slice schedule */
    hsliceParam slices;      /* slice tasks only have period task, and the task start when configured. */

    /* SchTask class functions. */
    void (*tick)(hSchTask cthis);
    void (*run)(hSchTask cthis);

    void (*addTask)(hSchTask cthis, htsTask task);
    void (*addLowestTask)(hSchTask cthis, htsTask task);  /* task priority is lowest, and it is scheduled in SliceSch */
    void (*delTask)(hSchTask cthis, htsTask task);
    void (*delLowestTask)(hSchTask cthis, htsTask task); /* task priority is lowest, and it is scheduled in SliceSch */
    uint16 (*getGroupIndex)(hSchTask cthis, uint16 prd); /* get lowest tast group index */

    void (*setMonitor)(hSchTask cthis, htsTask task);
    void (*getMonitor)(hSchTask cthis, uint16 *point); /* 0.1us */
    void (*now)(hSchTask cthis, uint16 *point); /* 0.1us */
    void (*delay)(hSchTask cthis, uint32 *tick);
    void (*err)(hSchTask cthis, uint16 code);

    /* Implement abstract class */
    IMPL(iTime);
    void *CpnSch;          /* Inject Component class. */
};

#endif /*SCHTASK_H_*/

/**************************** Copyright(C) pxf ****************************/
