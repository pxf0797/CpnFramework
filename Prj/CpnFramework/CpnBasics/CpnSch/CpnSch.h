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

    // CpnSch类参数
    uint16 usage;            // cpu使用率，如112表示11.2%
    uint16 currTaskTime;     // 当前任务执行时间
    uint16 totalTaskTime;    // 总任务执行时间

    // 组件运行状态机
    hSchSmRec SchSmRec;
    hstaAct SchSm;

    // 组件服务函数（需要被调用）
    void (*tick)(hCpnSch cthis);
    void (*run)(hCpnSch cthis);
    void (*addTask)(hCpnSch cthis, taskLevel level, task t, uint16 prd, uint16 start);
    void (*delTask)(hCpnSch cthis, taskLevel level, task t);
    void (*delay)(hCpnSch cthis, uint32 *tick);

    // 组件触发函数（调用其他函数）
    void (*now)(hCpnSch cthis, uint16 *point); /* 0.1us */
    void (*err)(hCpnSch cthis, uint16 code);

    // 接口函数
    IMPL(iTime);
    IMPL(iErr);
    IMPL(iInitCpn);
};

#endif /*CPNSCH_H_*/

/**************************** Copyright(C) pxf ****************************/
