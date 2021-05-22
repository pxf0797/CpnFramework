/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SchSm.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:24:20
* Description  : 状态机SchSm定义及各状态动作定义源文件
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./SchSm.h"
#include "./CpnSch.h"
#include "../FuncLib/FuncLib.h"

/*状态机SchSm定义
* 配置状态机相关处理状态
***********************************************/
SMDF(SchSm, SCHSM_LIST);
SchSmRec SchSmRunRec;
extern CpnSch clCpnSch;

/*名称 : SchSm_act_init()
* 输入 : SchSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 初始状态操作函数
***********************************************/
void SchSm_act_init(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    uint16 i = 0u;
    uint16 j = 0u;

    hRec->ticker = 0u;
    hRec->taskGroupNum = CPN_SCH_GROUP_TOTAL_NUMS;
    hRec->CpnSch = &clCpnSch;
    for(i = 0u; i < CPN_SCH_GROUP_TOTAL_NUMS; i++){
        for(j = 0u; j < (sizeof(taskGroupType)<<3U); j++){
            hRec->taskGroups[i].startTick[j] = 0u;
            hRec->taskGroups[i].prdTick[j] = 0u;
            hRec->taskGroups[i].taskGroup[j] = NULL;
        }
        hRec->taskGroups[i].unstartMask = 0u;
        hRec->taskGroups[i].actMask = 0u;
        hRec->taskGroups[i].taskMask = 0u;
    }

    hRec->next = SchSm_sta_execute;
    hRec->last = SchSm_sta_init;
}

/*名称 : SchSm_act_update()
* 输入 : SchSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态update操作函数
***********************************************/
void SchSm_act_update(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 i = 0u;
    uint16 diffTick = 0u;

    // 剔除背景任务更新执行标志
    for(i = 0u; i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG); i++){
        /* 更新各组激活任务 */
        taskMask = hRec->taskGroups[i].taskMask;
        while(taskMask != 0u){
            //curTask = (taskMask&(taskMask^(taskMask-1u)));
            curTask = (taskMask&(-taskMask));
            //taskMask ^= curTask;
            taskMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            if(hRec->taskGroups[i].unstartMask){
                /* 检查当前任务是否进入周期执行 */
                if(hRec->taskGroups[i].unstartMask&curTask){
                    /* 小于2个步长偏差也可以正常激活任务，正常情况下是没有偏差的 */
                    diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                    if(diffTick <= 5U/*2U*/){
                        hRec->taskGroups[i].unstartMask &= (~curTask);
                        /* 更新激活状态以及下一激活起始节拍 */
                        hRec->taskGroups[i].actMask |= curTask;
                        //hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                    }
                }else{
                    diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                    if(diffTick >= hRec->taskGroups[i].prdTick[taskIndex]){
                        /* 更新激活状态以及下一激活起始节拍 */
                        hRec->taskGroups[i].actMask |= curTask;
                        hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                    }
                }
            }else{
                /* 全部进入周期执行 */
                diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                if(diffTick >= hRec->taskGroups[i].prdTick[taskIndex]){
                    /* 更新激活状态以及下一激活起始节拍 */
                    hRec->taskGroups[i].actMask |= curTask;
                    hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                }
            }
        }
    }

    hRec->next = SchSm_sta_execute;
    hRec->last = SchSm_sta_update;
}

/*名称 : SchSm_act_execute()
* 输入 : SchSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态execute操作函数
***********************************************/
void SchSm_act_execute(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 i = 0u;
    uint16 specificFlg = 0u;
#if (CPN_SCH_TASK_MEASURE_ENABLE == TRUE)
    static uint16 taskTimePot = 0u;
    uint16 currUsage = 0u;
    ((hCpnSch)(hRec->CpnSch))->now(hRec->CpnSch, &taskTimePot);
#endif

    for(i = 0u; i < hRec->taskGroupNum; i++){
        /* 查看激活任务，并执行最高优先级任务 */
        taskMask = hRec->taskGroups[i].actMask;
        if(taskMask != 0u){
            //curTask = (taskMask&(taskMask^(taskMask-1u)));
            curTask = (taskMask&(-taskMask));
            //hRec->taskGroups[i].actMask ^= curTask; // 容易引发不可控结果
            hRec->taskGroups[i].actMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            /* 判断是否为一次性任务，如果非level0背景任务则把任务掩码去除 */
            if((hRec->taskGroups[i].prdTick[taskIndex] == 0u) && (i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG))){
                hRec->taskGroups[i].taskMask &= (~curTask);
            }

            /* 查找指定任务置位标志 */
            if((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x8000u)
            &&(((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x7F00u)>>8u)==i)
            &&((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x00FFu)==taskIndex)){
                specificFlg = 1u;
            }

            /* 执行任务 */
            ((hCpnSch)(hRec->CpnSch))->currTaskIndex = ((i<<8u)|taskIndex);
            if(hRec->taskGroups[i].taskGroup[taskIndex]){
                hRec->taskGroups[i].taskGroup[taskIndex]();
            }
            break;
        }
    }

#if (CPN_SCH_TASK_MEASURE_ENABLE == TRUE)
    ((hCpnSch)(hRec->CpnSch))->currTaskTime = taskTimePot;
    ((hCpnSch)(hRec->CpnSch))->now(hRec->CpnSch, &taskTimePot);
    ((hCpnSch)(hRec->CpnSch))->currTaskTime = (taskTimePot-((hCpnSch)(hRec->CpnSch))->currTaskTime);
    /* 更新指定任务执行时间 */
    if(specificFlg){
        ((hCpnSch)(hRec->CpnSch))->specificTaskTime = ((hCpnSch)(hRec->CpnSch))->currTaskTime;
    }
    /* 目前时间测量精确到0.1us，使用率精确到0.1% */
    if(i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG)){
        ((hCpnSch)(hRec->CpnSch))->totalTaskTime += ((hCpnSch)(hRec->CpnSch))->currTaskTime;
    }else{
        if(((hCpnSch)(hRec->CpnSch))->totalTaskTime){
            currUsage = ((uint32)((hCpnSch)(hRec->CpnSch))->totalTaskTime*100U/CPN_SCH_TASK_TICK_TIME_US);
            ((hCpnSch)(hRec->CpnSch))->usage = (uint16)lowpassFilter(currUsage, (uint32)((hCpnSch)(hRec->CpnSch))->usage, 4U);
            ((hCpnSch)(hRec->CpnSch))->totalTaskTime = 0U;
        }
    }
#endif

    if(hRec->ticker != hRec->tickerLast){
        hRec->tickerLast = hRec->ticker;
        hRec->next = SchSm_sta_update;
    }else if((i >= hRec->taskGroupNum) && (!hRec->taskGroups[hRec->taskGroupNum-1u].actMask)){
        hRec->next = SchSm_sta_updateBgTask;
    }else{
        hRec->next = SchSm_sta_execute;
    }
    hRec->last = SchSm_sta_execute;
}

/*名称 : SchSm_act_updateBgTask()
* 输入 : SchSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态updateBgTask操作函数
***********************************************/
void SchSm_act_updateBgTask(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    uint16 i = 0u;

    for(i = (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG); i < hRec->taskGroupNum; i++){
        hRec->taskGroups[i].actMask = hRec->taskGroups[i].taskMask;
    }

    if(hRec->ticker != hRec->tickerLast){
        hRec->tickerLast = hRec->ticker;
        hRec->next = SchSm_sta_update;
    }else{
        hRec->next = SchSm_sta_execute;
    }
    hRec->last = SchSm_sta_updateBgTask;
}

/**************************** Copyright(C) pxf ****************************/
