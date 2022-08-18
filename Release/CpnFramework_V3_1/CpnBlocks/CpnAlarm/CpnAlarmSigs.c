/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnAlarmSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/06/07 20:02:39
 * Description  : CpnAlarm component signals definition source file.
 * Others       :
 * History      : 20210607 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnAlarm.h"
#include "CpnAlarmSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnAlarm class definition.
 **********************************************************/
/* CpnAlarm class.
 **********************************************/
static CpnAlarm clCpnAlarm;

  /* alarm_,    classify_,      serious_,        name_,                alarmType_,  trig_sig_,                            get_sig_,                      setPoint_,  resetPoint_,  setLast_,  clearLast_,  alarmUp_,  seriousUp_,      time_,  count_,  decreaseTime_ */
#define LIST_ALARM(_)                                                                                                                                                                                                                                                 \
    _(alarm,    CLASS_COMMON,   SERIOUS_LOW,     "FirstAlarm",         ALARM_FLAG,  sig_trig_CpnAlarm_alarmCondTrue,      sig_get_CpnAlarm_sPluse,       0u,         0u,           500*MS_T,  500*MS_T,    alarmUp,   SERIOUS_MEDIUM,  5*M_T,  10u,     10*S_T) \
    _(alarm,    CLASS_COMMON,   SERIOUS_LOW,     "SecondAlarm",        ALRAM_UP,    sig_trig_CpnAlarm_alarmCondTrue,      sig_get_CpnAlarm_sSine,        300u,       250u,         200*MS_T,  200*MS_T,    alarmUp,   SERIOUS_NO,      0*M_T,  0u,      0*S_T) \
    _(alarm,    CLASS_COMMON,   SERIOUS_MEDIUM,  "ThirdAlarm",         ALARM_DOWN,  sig_trig_CpnAlarm_alarmCondTrue,      sig_get_CpnAlarm_sUpDown,      300u,       400u,         500*MS_T,  500*MS_T,    alarmUp,   SERIOUS_NO,      0*M_T,  0u,      0*S_T) \
    _(alarm,    CLASS_COMMON,   SERIOUS_MEDIUM,  "4thAlarm",           ALARM_DOWN,  sig_trig_CpnAlarm_alarmCondFalse,     sig_get_CpnAlarm_sUpDown,      300u,       400u,         500*MS_T,  500*MS_T,    alarmUp,   SERIOUS_NO,      0*M_T,  0u,      0*S_T) \


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnAlarm_init(void){
    tsAlarm alarm;
    tsAlarmUp alarmUp;

    CNNP(CpnAlarm,&clCpnAlarm);
    if(OPRS(clCpnAlarm) != NULL){
        tsInitTask taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnAlarm;
        taskParam.prdTick = CPNALARMCFG_TASK_SLICE_PERIOD*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.e.all = e_basic;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnAlarm_initTask, (uint8*)&taskParam);

        /* register classify alarms. */
        LIST_ALARM(REGIST_ALARM_ALARMUP)
    }
}

/* getAlarmMax Service.
 **********************************************/
void serv_CpnAlarm_getAlarmMax(void *buff){
    htsAlarmCount alarmCount = (htsAlarmCount)buff;
    alarmCount->count = clCpnAlarm.getAlarmCount(clCpnAlarm.self,alarmCount->classify,alarmCount->serious);
}
/* getAlarmCount Service.
 **********************************************/
void serv_CpnAlarm_getAlarmCount(void *buff){
    htsAlarmCount alarmCount = (htsAlarmCount)buff;
    alarmCount->count = clCpnAlarm.getAlarmCount(clCpnAlarm.self,alarmCount->classify,alarmCount->serious);
}
/* getAlarmEvents Service.
 **********************************************/
void serv_CpnAlarm_getAlarmEvents(void *buff){
    htsAlarmEvents alarmEvent = (htsAlarmEvents)buff;
    alarmEvent->events = clCpnAlarm.getAlarmEvents(clCpnAlarm.self,alarmEvent->classify,alarmEvent->serious);
}
/* isAlarmed Service.
 **********************************************/
void serv_CpnAlarm_isAlarmed(void *buff){
    htsAlarmSta alarmSta = (htsAlarmSta)buff;
    alarmSta->alarmSta = clCpnAlarm.isAlarmed(clCpnAlarm.self,alarmSta->event);
}
/* isUpgraded Service.
 **********************************************/
void serv_CpnAlarm_isUpgraded(void *buff){
    htsAlarmSta alarmSta = (htsAlarmSta)buff;
    alarmSta->alarmSta = clCpnAlarm.isUpgraded(clCpnAlarm.self,alarmSta->event);
}
/* alarmCondTrue Service.
 **********************************************/
void serv_CpnAlarm_alarmCondTrue(void *buff){
    *(uint8*)buff = TRUE;
}
/* alarmCondFalse Service.
 **********************************************/
void serv_CpnAlarm_alarmCondFalse(void *buff){
    *(uint8*)buff = FALSE;
}

/* Interface trigger.
 **********************************************/
//void trig_CpnAlarm_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnAlarm(void){
    clCpnAlarm.run(clCpnAlarm.self);
}

/**************************** Copyright(C) pxf ****************************/
