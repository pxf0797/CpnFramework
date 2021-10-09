/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTaskStrategyCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 09:53:54
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNTASKSTRATEGYCFG_H_
#define CPNTASKSTRATEGYCFG_H_

/* Include head files. */
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"
#include "../../CpnBasics/StandType/StandType.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnTaskStrategyCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNTASKSTRATEGYCFG_ERR_ID       0U    /* CpnTaskStrategyCfg component error report ID. */

/* Policy group type definition
 * The maximum number of strategy groups is sizeof(strategy)*8u-1u, and the highest bit is reserved.
 * basic,source,sink,matrix,cal.
 * The above are fixed types, the rest can be customized according to the project.
 **********************************************/
#define TASK_STRATEGY_GROUP_LIST(_)     \
    _(basic)                            \
    _(info)                             \
    _(source)                           \
    _(sink)                             \
    _(matrix)                           \
    _(cal)                              \
    _(test)                             \

/* Strategy group generated macro corresponding configuration.
 **********************************************/
#define STRATEGY_INDEX_COMBINE(group)                   task_strategy_##group##_index,
#define STRATEGY_MASK_COMBINE(group)                    task_strategy_##group##_mask=(1u<<task_strategy_##group##_index),
#define STRATEGY_GROUPS_EXPANTION(group_list)           \
typedef enum task_strategy_group_index{                 \
    group_list(STRATEGY_INDEX_COMBINE)                  \
    task_strategy_group_index_num_max                   \
} task_strategy_group_index;                            \
typedef enum task_strategy_group_mask{                  \
    group_list(STRATEGY_MASK_COMBINE)                   \
    task_strategy_group_mask_num_max                    \
} task_strategy_group_mask                              \

/* Strategy group generated.
 **********************************************/
STRATEGY_GROUPS_EXPANTION(TASK_STRATEGY_GROUP_LIST);

/* Default Strategy group.
 **********************************************/
#define DEFAULT_STRATEGY_TASK_GROUPS                    (task_strategy_basic_mask|task_strategy_matrix_mask)

/* Strategy group execute period.
 **********************************************/
#define CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD             (10*MS_T)

/* Strategy group execute condition.
 **********************************************/
typedef uint16 (*condition)(void); /* true/false */

#endif /*CPNTASKSTRATEGYCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
