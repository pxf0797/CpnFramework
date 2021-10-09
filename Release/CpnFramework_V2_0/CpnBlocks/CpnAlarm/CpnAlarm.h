/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnAlarm.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/06/07 20:02:39
 * Description  : CpnAlarm class and interface declaration file.
 * Others       :
 * History      : 20210607 pxf Initially established.
 **************************************************************************/

#ifndef CPNALARM_H_
#define CPNALARM_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnAlarmCfg.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNALARM_MACRO_VERSION                  0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
// typedef enum {
//     SERIOUS_HIGH,
//     SERIOUS_MEDIUM,
//     SERIOUS_LOW,
//     SERIOUS_NO
// } teSeriousLevel;
typedef enum {
    ALRAM_UP,
    ALARM_DOWN,
    ALARM_FLAG
} teAlarmType;
// typedef enum {
//     CLASS_COMMON,
//     CLASS_SYS,
//     CLASS_BLOCK,

//     CLASS_MAX_COUNT
// } teClassify;

typedef enum {
    ALRAM_CHECKING,
    ALARM_CHECK_UP,
    ALARM_CHECK_DOWN
} teAlarmCheckSta;
typedef enum {
    ALRAM_COUNT_DEC,
    ALRAM_COUNT_INC
} teAlarmCountUpdate;

typedef struct {
    teClassify classify;
    teSeriousLevel serious;
    uint16 event;
    char *name;
    teAlarmType alarmType;
    synType trig_sig;          /* alarm precondition */
    asynType get_sig;          /* alarm get data */
    uint32 setPoint;           /* alarm setup point */
    uint32 resetPoint;         /* alarm clear point */
    uint32 setLast;            /* alarm setup last time */
    uint32 clearLast;          /* alarm clear last time */
} tsAlarm, *htsAlarm;
typedef struct {
    teSeriousLevel serious;
    uint16 event;
    uint16 alarmUpIndex;       /* alarm upgrade regist index */
    uint32 time;               /* alarm upgrade last time */
    uint16 count;              /* alarm upgrade counter. bit15 reserved for counting, 1 start/ 0 not start. */
    uint32 decreaseTime;       /* alarm upgrade decrease counter. when 0, donot decrease counter */
} tsAlarmUp, *htsAlarmUp;
#define IS_ALARMUP_COUNTING(count)      ((count)&0x8000u) /* bit15 reserved for counting, 1 start/ 0 not start. */
#define SET_ALARMUP_COUNTING(count)     ((count)|0x8000u)
#define CLEAR_ALARMUP_COUNTING(count)   ((count)&0x7fffu)

#define INIT_ALARM(alarm_, classify_,serious_,name_,alarmType_, trig_sig_,get_sig_, setPoint_,resetPoint_,setLast_,clearLast_) \
do{                                            \
    alarm_.classify = classify_;               \
    alarm_.serious = serious_;                 \
    alarm_.name = name_;                       \
    alarm_.alarmType = alarmType_;             \
    alarm_.trig_sig = trig_sig_;               \
    alarm_.get_sig = get_sig_;                 \
    alarm_.setPoint = setPoint_;               \
    alarm_.resetPoint = resetPoint_;           \
    alarm_.setLast = setLast_;                 \
    alarm_.clearLast = clearLast_;             \
}while(0)
#define INIT_ALARMUP(alarmUp_, serious_,event_, time_,count_,decreaseTime_) \
do{                                            \
    alarmUp_.serious = serious_;               \
    alarmUp_.event = event_;                   \
    alarmUp_.time = time_;                     \
    alarmUp_.count = count_;                   \
    alarmUp_.decreaseTime = decreaseTime_;     \
}while(0)
// typedef struct {
//     uint16 eventNum;    /* all detected nums */
//     uint16 *events;
//     uint16 upgradeNum;  /* part of eventNum, only upgrade part */
//     uint16 *upgrades;
// } tsEvents, *htsEvents;

#define REGIST_ALARM_ALARMUP(alarm_, classify_,serious_,name_,alarmType_, trig_sig_,get_sig_, setPoint_,resetPoint_,setLast_,clearLast_, \
    alarmUp_, seriousUp_, time_,count_,decreaseTime_)       \
do{                                                         \
    INIT_ALARM(alarm_, classify_,serious_,name_,alarmType_, trig_sig_,get_sig_, setPoint_,resetPoint_,setLast_,clearLast_); \
    clCpnAlarm.regist(clCpnAlarm.self,&alarm_);             \
    if(seriousUp_&&time_&&count_){                          \
        INIT_ALARMUP(alarmUp_, seriousUp_,alarm_.event, time_,count_,decreaseTime_); \
        clCpnAlarm.registUp(clCpnAlarm.self,&alarmUp_);     \
    }                                                       \
}while(0);

/*
#define LIST_ALARM(_) \
    _(alarm_, classify_,serious_,name_,alarmType_, trig_sig_,get_sig_, setPoint_,resetPoint_,setLast_,clearLast_, alarmUp_, seriousUp_, time_,count_,decreaseTime_)

    LIST_ALARM(REGIST_ALARM_ALARMUP)
*/

/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
//INF(get){
//  uint16(*get)(void);
//};
/* TODO */

/***********************************************************
 * CpnAlarm class definition.
 **********************************************************/
/* CpnAlarm class declaration.
 **********************************************/
CL(CpnAlarm){
    hCpnAlarm self;
    hCpnAlarm (*init)(hCpnAlarm cthis);

    /* CpnAlarm class parameters. */
    htsAlarm alarms;                /* Alarm table */
    htsAlarmUp alarmUps;            /* Alarm upgrade table */
    alarmType *alarmFlag;           /* Alarm event correspond bits */
    alarmType *alarmUpMask;         /* Alarm event for upgrade mask correspond bits */
    alarmType *alarmUpFlag;         /* Alarm upgrade event correspond bits */
    uint16 buffEventMax;            /* Memory buffer Alarm event max count */
    uint16 buffUpEventMax;          /* Memory buffer Alarm upgrade event max count */
    uint16 alarmClassifyMax;        /* Alarm classify max count */
    uint16 alarmEventMax[SERIOUS_MAX_COUNT+1u]; /* Alarm event max count. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
    uint16 alarmUpEventMax;         /* Alarm upgrade event max count */
    uint16 alarmCount[SERIOUS_MAX_COUNT+1u]; /* Alarm event has occured count. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
    uint16 *alarmClassifyEventMax/*[SERIOUS_MAX_COUNT+1u]*/;  /* Alarm classify event max count. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
    uint16 *alarmClassifyCount/*[SERIOUS_MAX_COUNT+1u]*/; /* Alarm classify event has occured count. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */

    /* schedular parameters. */
    uint32 timer;                   /* Component schedular timer. */
    uint32 *alarmTimer;             /* Alarm event schedular timer. */
    uint32 *alarmUpTimer;           /* Alarm upgrade event schedular timer. */
    uint16 *alarmUpCounter;         /* Alarm upgrade event schedular counter. */

    /* alarmed events. */
    tsEvents alarmedEvents;         /* used to getAlarmEvents get alarms for temporary store. */

    /* CpnAlarm class functions. */
    uint16 (*getAlarmMax)(hCpnAlarm cthis, teClassify classify, teSeriousLevel serious);   /* if classify is CLASS_MAX_COUNT return total max.
                                                                                            if serious is SERIOUS_MAX_COUNT return classify total max. */
    uint16 (*getAlarmCount)(hCpnAlarm cthis, teClassify classify, teSeriousLevel serious); /* if classify is CLASS_MAX_COUNT return total count.
                                                                                            if serious is SERIOUS_MAX_COUNT return classify total count. */
    htsEvents (*getAlarmEvents)(hCpnAlarm cthis, teClassify classify, teSeriousLevel serious); /* if classify is CLASS_MAX_COUNT return all alarmed events(inlcude upgrade events).
                                                                                            if serious is SERIOUS_MAX_COUNT return classify all alarmed events(inlcude upgrade events). */
    uint16 (*isAlarmed)(hCpnAlarm cthis, uint16 event);            /* Event alram, TRUE/FALSE */
    uint16 (*isUpgraded)(hCpnAlarm cthis, uint16 alarmUpIndex);   /* Event alram upgrade, TRUE/FALSE */
    void (*run)(hCpnAlarm cthis);
    void (*err)(hCpnAlarm cthis, uint16 code);
    void (*regist)(hCpnAlarm cthis, htsAlarm alram);
    void (*registUp)(hCpnAlarm cthis, htsAlarmUp alramUp);
    uint16 (*dilatation)(hCpnAlarm cthis);                            /* Expand for all events. dilatation once is CPNALAEM_TYPE_WIDTH */
    uint16 (*dilatationUp)(hCpnAlarm cthis);                          /* Expand for all upgrade events. dilatation once is CPNALAEM_TYPE_WIDTH */
    teAlarmCheckSta (*alarmSrcCheck)(hCpnAlarm cthis, htsAlarm alarm); /* Check alarm source state */
    void (*alarmCheckUpdate)(hCpnAlarm cthis, htsAlarm alarm);        /* Check alarm state, and update flags */
    void (*alarmUpdateCount)(hCpnAlarm cthis, htsAlarm alarm, teAlarmCountUpdate countType); /* Update alarm counter correspond to event */
    void (*alarmUpCheckUpdate)(hCpnAlarm cthis, htsAlarmUp alramUp);  /* Check alarm upgrade state, and update flags */
    void (*alarmUpUpdateCount)(hCpnAlarm cthis, htsAlarmUp alramUp, teAlarmCountUpdate countType); /* Update alarm counter correspond to event */
};

#endif /*CPNALARM_H_*/

/**************************** Copyright(C) pxf ****************************/
