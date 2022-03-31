/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSch.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  : CpnSch class and interface declaration file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CPNSCH_H_
#define CPNSCH_H_

/* Include head files. */
#include "Oopc.h"
#include "StandType.h"
#include "CpnSchCfg.h"
#include "SchSm.h"
#include "CpnSchSigs.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSCH_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Task strategy data type declaration.
 * The highest bit is reserved, and the task is activated in the initialization parameter initTaskParam.
 **********************************************/
typedef uint16 strategy;
#define TASK_STRATEGY_ACT_MASK         ((strategy)(0x1UL<<((sizeof(strategy)<<3U)-1U)))
/* Initial task parameter declaration.
 **********************************************/
typedef struct initTaskParam{
    uint16 level;
    task t;
    uint16 prdTick;
    uint16 startTick;
    strategy strgMask;
}initTaskParam, *hinitTaskParam;
/* Task service data type declaration.
 **********************************************/
typedef struct taskParam{
    uint16 level;
    task t;
}taskParam, *htaskParam;
/* Delay service data type declaration.
 **********************************************/
typedef uint32 tick;
/* Real time service data type declaration.
 **********************************************/
typedef uint16 point;
/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
INF(iTime){
    void (*getTime)(uint16 *point);
};
INF(iInitCpn){
    void (*initCpn)(void);
};

/***********************************************************
 * CpnSch class definition.
 **********************************************************/
/* Task level declaration.
 **********************************************/
typedef enum{
    level0 = 0,
    level1,
    level2,
    level3
} taskLevel;
/* CpnSch class declaration.
 **********************************************/
CL(CpnSch){
    hCpnSch self;
    hCpnSch (*init)(hCpnSch cthis, hSchSmRec SchSmRec, hstaAct SchSm,
            void (*getTime)(uint16 *point),
            void (*initCpn)(void));

    /* CpnSch class parameters. */
    uint16 usage;            /* cpu usage, such as 112 represent 11.2%. */
    uint16 currTaskIndex;    /* Current task index; bit15--8 represent task group; bit7--0 represent index in group. */
    uint16 currTaskTime;     /* Current task execute time, unit 0.1us. */
    uint16 totalTaskTime;    /* Total task execute time, unit 0.1us. */
    uint16 specificTaskMask; /* bit15 represent whether task enable£» bit14--8 represent task group£» bit7--0 represent index in group. */
    uint16 specificTaskTime; /* Specific task execute time, unit 0.1us. */

    /* Strategy group parameters. */
    strategy strgMask;
    uint16 taskNum;
    initTaskParam taskList[CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG]; /* The maximum number is twice the number of scheduler task groups. */

    /* Component run state machine. */
    hSchSmRec SchSmRec;
    hstaAct SchSm;

    /* CpnSch class functions. */
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
    /* Component trigger functions(call other functions). */
    void (*now)(hCpnSch cthis, uint16 *point); /* 0.1us */
    void (*err)(hCpnSch cthis, uint16 code);
    /* Interfaces */
    IMPL(iTime);
    IMPL(iInitCpn);
};

#endif /*CPNSCH_H_*/

/**************************** Copyright(C) pxf ****************************/
