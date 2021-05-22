/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSchCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:02:40
* Description  :
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

#ifndef CPNSCHCFG_H_
#define CPNSCHCFG_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"
#include "../../CpnBlocks/CpnTaskStrategy/CpnTaskStrategyCfg.h"

// 任务功能参数配置
typedef uint16 taskGroupType;                                                                // 任务组类型 可选 uint8 uint16 uint32
#define CPN_SCH_TASK_MEASURE_ENABLE                  TRUE                                    // 任务运行时间测量 TRUE FALSE
#define CPN_SCH_TASK_TICK_TIME_US                    1000U                                    // 单步时间500US

// 每个任务组可以存放sizeof(taskGroupType)*8个任务，每个任务等级可以配置不同任务组数
#define CPN_SCH_LEVEL0_GROUP_NUM_CFG                 2U                                      // level0（背景）任务组数配置
#define CPN_SCH_LEVEL1_GROUP_NUM_CFG                 2U                                      // level1任务组数配置
#define CPN_SCH_LEVEL2_GROUP_NUM_CFG                 1U                                      // level2任务组数配置
#define CPN_SCH_LEVEL3_GROUP_NUM_CFG                 0U                                      // level3任务组数配置
#define CPN_SCH_GROUP_TOTAL_NUMS                     (CPN_SCH_LEVEL0_GROUP_NUM_CFG  \
                                                     + CPN_SCH_LEVEL1_GROUP_NUM_CFG \
                                                     + CPN_SCH_LEVEL2_GROUP_NUM_CFG \
                                                     + CPN_SCH_LEVEL3_GROUP_NUM_CFG)         // 总任务组数

/* 任务策略组参数 */
/* 任务列表个数是调度任务组任务个数2倍 */
#define CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG            (((CPN_SCH_GROUP_TOTAL_NUMS<<1u)*sizeof(taskGroupType))<<3u)


// 延时步长时间换算参数，当前最大延时长度为32767*CPN_SCH_TASK_TICK_TIME_US us
// 如果步长为500us，单次最大延时?16.3835?s
// 如果步长为1000us，单次最大延时32.767?s
#define MS_T                                         (1000UL/CPN_SCH_TASK_TICK_TIME_US)      // 延时1MS单位
#define S_T                                          (1000000UL/CPN_SCH_TASK_TICK_TIME_US)   // 延时1S单位
#define M_T                                          (60000000UL/CPN_SCH_TASK_TICK_TIME_US)  // 延时1MIN单位
#define IS_TIMEOUT(tick)                             ((tick) & 0x00008000UL)                 // 延时已到为0x00008000，否则为0

// 组件对应错误标志ID
//#define CPNSCHCFG_ERR_ID                             0U                                      // 错误上报ID
/*errDefine
***********************************************************************************************************************/
#define CPN_SCH_ADD_TASK_LEVEVL_NOT_EIXST            0x0000U                                 // 添加任务组不存在
#define CPN_SCH_ADD_TASK_LEVEVL0GROUP_FULL           0x0001U                                 // 零级任务组已满
#define CPN_SCH_ADD_TASK_LEVEVL1GROUP_FULL           0x0002U                                 // 一级任务组已满
#define CPN_SCH_ADD_TASK_LEVEVL2GROUP_FULL           0x0003U                                 // 二级任务组已满
#define CPN_SCH_ADD_TASK_LEVEVL3GROUP_FULL           0x0004U                                 // 三级任务组已满
/**********************************************************************************************************************/
#define CPN_SCH_DEL_TASK_LEVEVL_NOT_EIXST            0x0010U                                 // 删除任务组不存在
#define CPN_SCH_DEL_TASK_LEVEVL0GROUP_NOT_EIXST      0x0011U                                 // 零级任务组不存在此任务
#define CPN_SCH_DEL_TASK_LEVEVL1GROUP_NOT_EIXST      0x0012U                                 // 一级任务组不存在此任务
#define CPN_SCH_DEL_TASK_LEVEVL2GROUP_NOT_EIXST      0x0013U                                 // 二级任务组不存在此任务
#define CPN_SCH_DEL_TASK_LEVEVL3GROUP_NOT_EIXST      0x0014U                                 // 三级任务组不存在此任务
/**********************************************************************************************************************/
#define CPN_SCH_SPECIFIC_TASK_LEVEVL_NOT_EIXST       0x0020U                                 // 指定任务组不存在
#define CPN_SCH_SPECIFIC_TASK_NOT_FOUND              0x0021U                                 // 指定任务未找到
/**********************************************************************************************************************/
#define CPN_SCH_TASK_LIST_IS_FULL                    0x0030U                                 // 任务列表已满
#define CPN_SCH_TASK_LIST_TASK_NOT_FOUND             0x0031U                                 // 任务列表未找到任务


#endif /*CPNSCHCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
