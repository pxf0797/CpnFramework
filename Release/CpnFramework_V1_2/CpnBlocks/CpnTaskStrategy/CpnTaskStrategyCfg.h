/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategyCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  :
* Others       :
* History      : 201218 pxf 初次建立
***************************************************************************/

#ifndef CPNTASKSTRATEGYCFG_H_
#define CPNTASKSTRATEGYCFG_H_

/*头文件包含*/
#include "../../cpnBasics/CpnErr/CpnErrCfg.h"
#include "../../cpnBasics/standType/standType.h"

/***********************************************************
* 配置参数
***********************************************************/
/*策略组类型定义
* 策略组最大个数为sizeof(strategy)*8u-1u,最高位为预留
* basic,source,sink,matrix,cal
* 以上这几个是固定类型，剩余可根据项目自定义
***********************************************/
#define TASK_STRATEGY_GROUP_LIST(_)     \
    _(basic)                            \
    _(source)                           \
    _(sink)                             \
    _(matrix)                           \
    _(cal)                              \
    _(test)                             \

/*策略组生成宏对应配置
***********************************************/
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

/*策略组生成
***********************************************/
STRATEGY_GROUPS_EXPANTION(TASK_STRATEGY_GROUP_LIST);

/*默认策略组
***********************************************/
#define DEFAULT_STRATEGY_TASK_GROUPS                    (task_strategy_basic_mask|task_strategy_matrix_mask)

/*策略组执行周期
***********************************************/
#define CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD             (1*MS_T)

/*策略组执行条件
***********************************************/
typedef uint16 (*condition)(void); /* true/false */

/*CpnTaskStrategyCfg错误上报ID，需要在CpnErrCfg.h文件内进行注册
***********************************************/
//#define CPNTASKSTRATEGYCFG_ERR_ID       0U    /* CpnTaskStrategyCfg组件报错配置ID */

#endif /*CPNTASKSTRATEGYCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
