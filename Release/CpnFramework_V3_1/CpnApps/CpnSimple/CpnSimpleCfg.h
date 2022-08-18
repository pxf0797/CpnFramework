/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSimpleCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2022/08/17 19:49:04
 * Description  :
 * Others       :
 * History      : 20220817 pxf Initially established.
 **************************************************************************/

#ifndef CPNSIMPLECFG_H_
#define CPNSIMPLECFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnSimpleCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNSIMPLECFG_ERR_ID                     0U    /* CpnSimpleCfg component error report ID. */

/***********************************************************
 * simple task list definition.
 **********************************************************/
/* simple task list.
 **********************************************/
/* task name,       level, start, period */
#define SIMPLE_LIST(_)                       \
    _(       task1, level1,   0,   5)        \
    _(       task2, level1,   0,   5)        \
    _(       task3, level1,   0,   5)        \

/* task params definition.
 **********************************************/
#define TASK_EVENT(name,level,start,period) e_##name,
#define TASK_EVENTS(task_list) task_list(TASK_EVENT)
#define TASK_LEVEL(name,level,start,period) task_level_##name=level,
// #define TASK_LEVELS(task_list) task_list(TASK_LEVEL)
#define TASK_START(name,level,start,period) task_start_##name=start*MS_T,
// #define TASK_STARTS(task_list) task_list(TASK_START)
#define TASK_PERIOD(name,level,start,period) task_period_##name=period*MS_T,
// #define TASK_PERIODS(task_list) task_list(TASK_PERIOD)
#define TASK_INDEX(name,level,start,period) task_index_##name,
#define TASK_PARAMS(task_list)               \
typedef enum{                                \
    task_list(TASK_INDEX)                    \
    task_index_max                           \
} teSimpleIndex;                             \
typedef enum{                                \
    task_list(TASK_LEVEL)                    \
    task_level_max                           \
} teSimpleLevel;                             \
typedef enum{                                \
    task_list(TASK_START)                    \
    task_start_max                           \
} teSimpleStart;                             \
typedef enum{                                \
    task_list(TASK_PERIOD)                   \
    task_period_max                          \
} teSimplePeriod;

#endif /*CPNSIMPLECFG_H_*/

/**************************** Copyright(C) pxf ****************************/
