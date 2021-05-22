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
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"
#include "../../CpnBlocks/CpnTaskStrategy/CpnTaskStrategyCfg.h"

/* Task configure parameters. */
typedef uint16 taskGroupType;                                                                /* Task group type, optional uint8 uint16 uint32 */
#define CPN_SCH_TASK_MEASURE_ENABLE                  TRUE                                    /* Task measure enable */
#define CPN_SCH_TASK_TICK_TIME_US                    1000U                                   /* Single step, unit 1us. */
/* Each task group can store sizeof(taskGroupType)*8 tasks, and each task level can be configured with different number of task groups. */
#define CPN_SCH_LEVEL0_GROUP_NUM_CFG                 2U                                      /* Configure level0(background task) task groups. */
#define CPN_SCH_LEVEL1_GROUP_NUM_CFG                 2U                                      /* Configure level1 task groups. */
#define CPN_SCH_LEVEL2_GROUP_NUM_CFG                 1U                                      /* Configure level2 task groups. */
#define CPN_SCH_LEVEL3_GROUP_NUM_CFG                 0U                                      /* Configure level3 task groups. */
#define CPN_SCH_GROUP_TOTAL_NUMS                     (CPN_SCH_LEVEL0_GROUP_NUM_CFG  \
                                                     + CPN_SCH_LEVEL1_GROUP_NUM_CFG \
                                                     + CPN_SCH_LEVEL2_GROUP_NUM_CFG \
                                                     + CPN_SCH_LEVEL3_GROUP_NUM_CFG)         /* Total task groups. */

/* Task strategy group parameters.
 * The number of task lists is twice the number of tasks in the scheduled task group. */
#define CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG            (((CPN_SCH_GROUP_TOTAL_NUMS<<1u)*sizeof(taskGroupType))<<3u)

/* Delay step time conversion parameter, the current maximum delay length is 32767*CPN_SCH_TASK_TICK_TIME_US us.
 * If the step length is 500us, the maximum single time delay is 16.3835s.
 * If the step length is 1000us, the maximum single time delay is 32.767s. */
#define MS_T                                         (1000UL/CPN_SCH_TASK_TICK_TIME_US)      /* Delay 1MS unit. */
#define S_T                                          (1000000UL/CPN_SCH_TASK_TICK_TIME_US)   /* Delay 1S unit. */
#define M_T                                          (60000000UL/CPN_SCH_TASK_TICK_TIME_US)  /* Delay 1MIN unit. */
#define IS_TIMEOUT(tick)                             ((tick) & 0x00008000UL)                 /* Delay expired, result 0x00008000, otherwise 0.  */
/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnSchCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNSCHCFG_ERR_ID                0U    /* CpnSchCfg component error report ID. */
typedef enum{
    ERR_CPNSCH_ADD_TASK,
    ERR_CPNSCH_DEL_TASK,
    ERR_CPNSCH_GROUP,
    ERR_CPNSCH_LIST,
} TE_CPNSCH_ERR_CLASSIFY;
/*errDefine
***********************************************************************************************************************/
#define CPN_SCH_ADD_TASK_LEVEVL_NOT_EIXST            (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_ADD_TASK<<ERR_CLASSIFY_SHIFT)|0) /* Task level not exit. */
#define CPN_SCH_ADD_TASK_LEVEVL0GROUP_FULL           (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_ADD_TASK<<ERR_CLASSIFY_SHIFT)|1) /* Task level 0 not exit. */
#define CPN_SCH_ADD_TASK_LEVEVL1GROUP_FULL           (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_ADD_TASK<<ERR_CLASSIFY_SHIFT)|2) /* Task level 1 not exit. */
#define CPN_SCH_ADD_TASK_LEVEVL2GROUP_FULL           (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_ADD_TASK<<ERR_CLASSIFY_SHIFT)|3) /* Task level 2 not exit. */
#define CPN_SCH_ADD_TASK_LEVEVL3GROUP_FULL           (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_ADD_TASK<<ERR_CLASSIFY_SHIFT)|4) /* Task level 3 not exit. */
/**********************************************************************************************************************/
#define CPN_SCH_DEL_TASK_LEVEVL_NOT_EIXST            (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|0) /* Task level not exit. */
#define CPN_SCH_DEL_TASK_LEVEVL0GROUP_NOT_EIXST      (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|1) /* Task level 0 not exit. */
#define CPN_SCH_DEL_TASK_LEVEVL1GROUP_NOT_EIXST      (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|2) /* Task level 1 not exit. */
#define CPN_SCH_DEL_TASK_LEVEVL2GROUP_NOT_EIXST      (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|3) /* Task level 2 not exit. */
#define CPN_SCH_DEL_TASK_LEVEVL3GROUP_NOT_EIXST      (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_DEL_TASK<<ERR_CLASSIFY_SHIFT)|4) /* Task level 3 not exit. */
/**********************************************************************************************************************/
#define CPN_SCH_SPECIFIC_TASK_LEVEVL_NOT_EIXST       (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_GROUP<<ERR_CLASSIFY_SHIFT)|0) /* Specific task group not exit. */
#define CPN_SCH_SPECIFIC_TASK_NOT_FOUND              (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_GROUP<<ERR_CLASSIFY_SHIFT)|1) /* Specific task not exit. */
/**********************************************************************************************************************/
#define CPN_SCH_TASK_LIST_IS_FULL                    (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_LIST<<ERR_CLASSIFY_SHIFT)|0) /* Task list is full. */
#define CPN_SCH_TASK_LIST_TASK_NOT_FOUND             (ERR_TYPE_SYS|ERR_SEVERITY_HIGH|(ERR_CPNSCH_LIST<<ERR_CLASSIFY_SHIFT)|1) /* Task not found in task list. */

#endif /*CPNSCHCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
