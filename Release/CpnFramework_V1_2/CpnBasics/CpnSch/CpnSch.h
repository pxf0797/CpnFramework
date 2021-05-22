/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSch.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:16:09
* Description  : CpnSch类及接口声明头文件
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

#ifndef CPNSCH_H_
#define CPNSCH_H_

/*头文件包含*/
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnBasics/standType/standType.h"
#include "./CpnSchCfg.h"
#include "./SchSm.h"
#include "./CpnSchSigs.h"

/***********************************************************
* serv trig 数据类型定义
* 一般只定义serv数据，trig类型引用当前头文件
***********************************************************/
/*服务数据类型
***********************************************/
/*任务策略类型
* 最高位为保留，在初始化参数initTaskParam中表示任务激活
***********************************************/
typedef uint16 strategy;
#define TASK_STRATEGY_ACT_MASK         ((strategy)(0x1UL<<((sizeof(strategy)<<3U)-1U)))
/*初始化任务服务参数
***********************************************/
typedef struct initTaskParam{
    uint16 level;
    task t;
    uint16 prdTick;
    uint16 startTick;
    strategy strgMask;
}initTaskParam, *hinitTaskParam;
/*任务服务参数
***********************************************/
typedef struct taskParam{
    uint16 level;
    task t;
}taskParam, *htaskParam;
/*延时服务参数
***********************************************/
typedef uint32 tick;
/*实时服务参数
***********************************************/
typedef uint16 point;

/***********************************************************
* 接口定义
***********************************************************/
/*接口声明
***********************************************/
INF(iTime){
    void (*getTime)(uint16 *point);
};
INF(iErr){
    void (*setErr)(uint16 id, uint16 code);
};
INF(iInitCpn){
    void (*initCpn)(void);
};

/***********************************************************
* CpnSch类定义
***********************************************************/
/*任务等级
***********************************************/
typedef enum{
    level0 = 0,
    level1,
    level2,
    level3
} taskLevel;

/*CpnSch类声明
***********************************************/
CL(CpnSch){
    hCpnSch self;
    hCpnSch (*init)(hCpnSch cthis, hSchSmRec SchSmRec, hstaAct SchSm,
            void (*getTime)(uint16 *point),
            void (*setErr)(uint16 id, uint16 code),
            void (*initCpn)(void));

    /* CpnSch类参数 */
    uint16 usage;            /* cpu使用率，如112表示11.2% */
    uint16 currTaskIndex;    /* 当前任务索引指示; bit15--8 任务组索引； bit7--0 组内编号索引 */
    uint16 currTaskTime;     /* 当前任务执行时间,0.1us */
    uint16 totalTaskTime;    /* 总任务执行时间,0.1us */
    uint16 specificTaskMask; /* bit15 任务是否使能； bit14--8 任务组索引； bit7--0 组内编号索引 */
    uint16 specificTaskTime; /* 指定任务执行时间,0.1us */

    /* 策略组参数 */
    strategy strgMask;
    uint16 taskNum;
    initTaskParam taskList[CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG]; /* 最大个数为调度器任务组数2倍 */

    /* 组件运行状态机 */
    hSchSmRec SchSmRec;
    hstaAct SchSm;

    /* 组件服务函数（需要被调用） */
    void (*tick)(hCpnSch cthis);
    void (*run)(hCpnSch cthis);
    void (*addList)(hCpnSch cthis, taskLevel level, task t, uint16 prd, uint16 start, strategy strgMask);
    void (*delList)(hCpnSch cthis, task t);
    void (*addTask)(hCpnSch cthis, taskLevel level, task t, uint16 prd, uint16 start);
    void (*delTask)(hCpnSch cthis, taskLevel level, task t);
    void (*delay)(hCpnSch cthis, uint32 *tick);
    void (*setMonitor)(hCpnSch cthis, taskLevel level, task t);
    void (*getMonitor)(hCpnSch cthis, uint16 *point); /* 0.1us */
    void (*setStrategy)(hCpnSch cthis, strategy strgMask);
    void (*getStrategy)(hCpnSch cthis, strategy *strgMask);
    void (*getTaskNum)(hCpnSch cthis, uint16 *taskNum);

    /* 组件触发函数（调用其他函数） */
    void (*now)(hCpnSch cthis, uint16 *point); /* 0.1us */
    void (*err)(hCpnSch cthis, uint16 code);

    /* 接口函数 */
    IMPL(iTime);
    IMPL(iErr);
    IMPL(iInitCpn);
};

#endif /*CPNSCH_H_*/

/**************************** Copyright(C) pxf ****************************/
