/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSchCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  :
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CPNSCHCFG_H_
#define CPNSCHCFG_H_

/* Include head files. */
#include "StandType.h"
#include "CpnErrCfg.h"


/* Task configure parameters. */
typedef uint16 taskGroupType;                                                                /* Task group type, optional uint8 uint16 uint32 */
#define GROUP_TYPE_BITS                              ((sizeof(taskGroupType)>>1u)+3u)//0x5u//0x4u//
#define GROUP_TYPE_WIDTH                             (1u<<GROUP_TYPE_BITS)
#define GROUP_TYPE_MASK                              (GROUP_TYPE_WIDTH-1u)
#define CPN_SCH_TASK_MEASURE_ENABLE                  TRUE                                    /* Task measure enable */
#define CPN_SCH_TASK_TICK_TIME_US                    1000U                                   /* Single step, unit 1us. */
/* Each task group can store sizeof(taskGroupType)*8 tasks, and each task level can be configured with different number of task groups. */
/* level classify, level length */
#define LEVEL_LIST(_)                                \
    _(0,   1) /* Configure level0(background task) task groups. */ \
    _(1,   2) /* Configure level1 task groups. */    \
    _(2,   1) /* Configure level2 task groups. */    \
    _(3,   0) /* Configure level3 task groups. */    \

#define LEVEL_TYPE(level_,length) level##level_,
#define LEVEL_LENGTH(level_,length) level##level_##_length=length,
#define LEVEL_DF(levle_list) typedef enum{           \
    levle_list(LEVEL_TYPE)                           \
    level_max                                        \
} taskLevel;                                         \
typedef enum{                                        \
    levle_list(LEVEL_LENGTH)                         \
    level_length_max                                 \
} taskLevelLength;
LEVEL_DF(LEVEL_LIST)

#define LEVEL_LENGTH_ADD(level_,length) level##level_##_length+
#define LEVEL_LENGTH_ALL(levle_list) (levle_list(LEVEL_LENGTH_ADD) 0u)
#define CPN_SCH_GROUP_TOTAL_NUMS LEVEL_LENGTH_ALL(LEVEL_LIST)

#define CPNSCH_INIT_TASK_MAX_NUM                     256u                                    /* Initial tasks max counter. if it is not big enough, you can expansion. */
#define CPNSCH_EXTRA_MEM_SPACE_SIZE                  20u                                     /* Dynamic memory size. */
#define CPNSCH_SCHEVENT_FIFO_COUNT                   (sizeof(taskGroupType)*8u*CPN_SCH_GROUP_TOTAL_NUMS)

/* default signal state. */
typedef enum{
    sig_clear,
    sig_set,
    sig_lock
} sig;

/* Task strategy group parameters.
 * The number of task lists is twice the number of tasks in the scheduled task group. */
// #define CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG            (((CPN_SCH_GROUP_TOTAL_NUMS<<1u)*sizeof(taskGroupType))<<3u)

/* Delay step time conversion parameter, the current maximum delay length is 32767*CPN_SCH_TASK_TICK_TIME_US us.
 * If the step length is 500us, the maximum single time delay is 16.3835s.
 * If the step length is 1000us, the maximum single time delay is 32.767s. */
#define MS_T                                         (1000UL/CPN_SCH_TASK_TICK_TIME_US)      /* Delay 1MS unit. */
#define S_T                                          (1000000UL/CPN_SCH_TASK_TICK_TIME_US)   /* Delay 1S unit. */
#define M_T                                          (60000000UL/CPN_SCH_TASK_TICK_TIME_US)  /* Delay 1MIN unit. */
//#define IS_TIMEOUT(tick)                             ((tick) & 0x00008000UL)                 /* Delay expired, result 0x00008000, otherwise 0.  */
/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnSchCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNSCHCFG_ERR_ID                0U    /* CpnSchCfg component error report ID. */
typedef enum{
    ERR_CPNSCH_REGIST,
    ERR_CPNSCH_ADD_TASK,
    ERR_CPNSCH_DEL_TASK,
    ERR_CPNSCH_GROUP,
    ERR_CPNSCH_LIST,
    ERR_CPNSCH_LOWEST_TASK,
    ERR_CPNSCH_EVENT,
} TE_CPNSCH_ERR_CLASSIFY;
/*errDefine
***********************************************************************************************************************/
#define CPN_SCH_REGIST_BUFF_IS_FULL                  (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_REGIST<<ERR_CLASSIFY_SHIFT)|0) /* Task regist buff is full. */
/**********************************************************************************************************************/
#define CPN_SCH_ADD_TASK_LEVEVL_NOT_EIXST            (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_ADD_TASK<<ERR_CLASSIFY_SHIFT)|0) /* Task level not exit. */
#define CPN_SCH_ADD_TASK_GROUP_TASK_IS_FULL          (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_ADD_TASK<<ERR_CLASSIFY_SHIFT)|1) /* Task level not exit. */
/**********************************************************************************************************************/
#define CPN_SCH_DEL_TASK_LEVEVL_NOT_EIXST            (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|0) /* Task level not exit. */
#define CPN_SCH_DEL_TASK_LEVEVL_LENGTH_NOT_EXIST     (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|1) /* Task level not exit. */
#define CPN_SCH_DEL_TASK_TASK_IS_NOT_RIGHT           (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|2) /* Task level not exit. */
/**********************************************************************************************************************/
#define CPN_SCH_SPECIFIC_TASK_LEVEVL_NOT_EIXST       (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_GROUP<<ERR_CLASSIFY_SHIFT)|0) /* Specific task group not exit. */
#define CPN_SCH_SPECIFIC_TASK_NOT_FOUND              (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_GROUP<<ERR_CLASSIFY_SHIFT)|1) /* Specific task not exit. */
/**********************************************************************************************************************/
#define CPN_SCH_TASK_LIST_IS_FULL                    (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_LIST<<ERR_CLASSIFY_SHIFT)|0) /* Task list is full. */
#define CPN_SCH_TASK_LIST_TASK_NOT_FOUND             (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_LIST<<ERR_CLASSIFY_SHIFT)|1) /* Task not found in task list. */
/**********************************************************************************************************************/
#define CPN_SCH_LOWEST_TASK_GROUP_IS_FULL            (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_LOWEST_TASK<<ERR_CLASSIFY_SHIFT)|0) /* Task lowest group is full. */
#define CPN_SCH_LOWEST_TASK_TASK_IS_NOT_RIGHT        (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_LOWEST_TASK<<ERR_CLASSIFY_SHIFT)|1) /* Task lowest group task is not right. */
/**********************************************************************************************************************/
#define CPN_SCH_EVENT_EVENT_REFERTASK_OVERFLOW       (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_EVENT<<ERR_CLASSIFY_SHIFT)|0) /* Event refter task bigger than the max. */


/* Event register. */
// typedef uint16 event;
typedef union{
    uint16 all;
    struct{
        uint16 e    : 15;
        uint16 dele : 1;  /* del: 0 is add event, 1 is delete event. */
    }bit;
}event;

/* Event definition.
 **********************************************/
typedef enum{
    e_slice_sch,
    e_event_task,
    e_basic,
    e_info,
    /* CpnSource */
    e_CpnSource,
    /* CpnSinks */
    e_CpnSinks,
    e_CpnTest,

    e_max
} teEvent;
#define E_ADD(e) (e&0x7FFFFu)
#define E_DEL(e) (e|0x8000u)
#define SYN_EVENT(e) do{uint16 e_ = e; SYN_TRIG(sig_trig_CpnSch_event, &e_);}while(0)

#endif /*CPNSCHCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
