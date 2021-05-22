/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SchSm.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:24:20
* Description  : 状态机SchSm声明及状态机使用示例头文件
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

#ifndef SCHSM_H_
#define SCHSM_H_

/*头文件包含*/
#include "../sm/sm.h"
#include "../standType/standType.h"
#include "./CpnSchCfg.h"

/*状态机SchSm使用示例：
* 当前状态机已在SMDF中定义出实体SchSm，需要做的只是让其运行起来
* 状态机运行方式有两种直接给时钟驱动的SMR和使用自定义记录状态后进驱动的SMRE
***********************************************
* SMR方式
***********************************************
void test(void){
    while(1){SMR(SchSm);};
}
***********************************************
* SMRE方式
***********************************************
void test2(void){
    static SchSmRec SchSmRunRec = {SchSm_sta_init};
    while(1){SMRE(SchSm, SchSmRunRec);};
}
***********************************************/

/*接口声明
***********************************************/
typedef void(*task)(void);                        // 任务定义

/*任务组声明
***********************************************/
typedef struct{
    uint16 startTick[sizeof(taskGroupType)<<3U];  // 调度周期起始节拍
    uint16 prdTick[sizeof(taskGroupType)<<3U];    // 周期调度节拍
    taskGroupType unstartMask;                    // 任务未启动掩码
    taskGroupType actMask;                        // 激活请求任务掩码
    taskGroupType taskMask;                       // 已分配任务掩码
    task taskGroup[sizeof(taskGroupType)<<3U];    // 任务组
} taskGroupSm;

/*状态机SchSm状态序列定义
* 注意其中SchSm_init,SchSm_default未在此定义，默认会给出
***********************************************/
#define SCHSM_LIST(_)         \
    _(SchSm, update)          \
    _(SchSm, execute)         \
    _(SchSm, updateBgTask)    \


/*状态机SchSm声明
* 已给出状态记录next,及上一状态last，其他参数需自行添加
***********************************************/
SMDC(SchSm, SCHSM_LIST){
    sta next;               // 运行状态记录
    sta last;               // 上一状态记录
    uint16 ticker;          // 计数
    uint16 tickerLast;      // 旧计数
    uint16 taskGroupNum;    // 任务组数
    taskGroupSm taskGroups[CPN_SCH_GROUP_TOTAL_NUMS];  // 任务组
    void *CpnSch;           // 注入组件类
};
extern SchSmRec SchSmRunRec;

#endif /*SCHSM_H_*/

/**************************** Copyright(C) pxf ****************************/
