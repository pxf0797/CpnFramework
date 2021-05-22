/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategyCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  :
* Others       :
* History      : 201218 pxf ���ν���
***************************************************************************/

#ifndef CPNTASKSTRATEGYCFG_H_
#define CPNTASKSTRATEGYCFG_H_

/*ͷ�ļ�����*/
#include "../../cpnBasics/CpnErr/CpnErrCfg.h"
#include "../../cpnBasics/standType/standType.h"

/***********************************************************
* ���ò���
***********************************************************/
/*���������Ͷ���
* ������������Ϊsizeof(strategy)*8u-1u,���λΪԤ��
* basic,source,sink,matrix,cal
* �����⼸���ǹ̶����ͣ�ʣ��ɸ�����Ŀ�Զ���
***********************************************/
#define TASK_STRATEGY_GROUP_LIST(_)     \
    _(basic)                            \
    _(source)                           \
    _(sink)                             \
    _(matrix)                           \
    _(cal)                              \
    _(test)                             \

/*���������ɺ��Ӧ����
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

/*����������
***********************************************/
STRATEGY_GROUPS_EXPANTION(TASK_STRATEGY_GROUP_LIST);

/*Ĭ�ϲ�����
***********************************************/
#define DEFAULT_STRATEGY_TASK_GROUPS                    (task_strategy_basic_mask|task_strategy_matrix_mask)

/*������ִ������
***********************************************/
#define CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD             (1*MS_T)

/*������ִ������
***********************************************/
typedef uint16 (*condition)(void); /* true/false */

/*CpnTaskStrategyCfg�����ϱ�ID����Ҫ��CpnErrCfg.h�ļ��ڽ���ע��
***********************************************/
//#define CPNTASKSTRATEGYCFG_ERR_ID       0U    /* CpnTaskStrategyCfg�����������ID */

#endif /*CPNTASKSTRATEGYCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
