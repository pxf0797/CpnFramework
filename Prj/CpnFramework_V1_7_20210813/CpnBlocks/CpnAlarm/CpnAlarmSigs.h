/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnAlarmSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/06/07 20:02:39
 * Description  : CpnAlarm component signals declaration head file.
 * Others       :
 * History      : 20210607 pxf Initially established.
 **************************************************************************/

#ifndef CPNALARMSIGS_H_
#define CPNALARMSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"
#include "./CpnAlarmCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNALARMSIGS_MACRO_VERSION              0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Get Set data type definition.
 * Generally, only the set data is defined, and the get type refers to the current header file.
 * Only need to define the data send, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Send data type.
 **********************************************/



/***********************************************************
 * Serv Trig data type definition.
 * Generally, only the serv data is defined, and the trig type refers to the current header file.
 * Only need to define the data send, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Serv data type.
 **********************************************/
typedef struct {
    teClassify classify;
    teSeriousLevel serious;
    uint16 count;                 /* if get alarm max retrun max, else return alarmed counter. */
} tsAlarmCount, *htsAlarmCount;
typedef struct {
    teClassify classify;
    teSeriousLevel serious;
    htsEvents events;
} tsAlarmEvents, *htsAlarmEvents;
typedef struct {
    uint16 event;                 /* event or alarmUpIndex */
    uint16 alarmSta;
} tsAlarmSta, *htsAlarmSta;
typedef struct {
    uint16 event;                 /* event or alarmUpIndex */
    char *name;
} tsEventName, *htsEventName;

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnAlarm_init(void);
/* getAlarmMax Service.
 **********************************************/
void serv_CpnAlarm_getAlarmMax(void *buff);
/* getAlarmCount Service.
 **********************************************/
void serv_CpnAlarm_getAlarmCount(void *buff);
/* getAlarmEvents Service.
 **********************************************/
void serv_CpnAlarm_getAlarmEvents(void *buff);
/* isAlarmed Service.
 **********************************************/
void serv_CpnAlarm_isAlarmed(void *buff);
/* isUpgraded Service.
 **********************************************/
void serv_CpnAlarm_isUpgraded(void *buff);
/* getEventName Service.
 **********************************************/
void serv_CpnAlarm_getEventName(void *buff);
/* getUpEventName Service.
 **********************************************/
void serv_CpnAlarm_getUpEventName(void *buff);
/* alarmCondTrue Service.
 **********************************************/
void serv_CpnAlarm_alarmCondTrue(void *buff);
/* alarmCondFalse Service.
 **********************************************/
void serv_CpnAlarm_alarmCondFalse(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnAlarm_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNALARM(_)                \


/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNALARM(_)            \
    _(sig_get_CpnAlarm_sSine,sig_set_CpnAlarmSource_sSine) \
    _(sig_get_CpnAlarm_sPluse,sig_set_CpnAlarmSource_sPluse) \
    _(sig_get_CpnAlarm_sUpDown,sig_set_CpnAlarmSource_sUpDown) \
    _(sig_get_CpnAlarm_sUp,sig_set_CpnAlarmSource_sUp)     \
    _(sig_get_CpnAlarm_sDown,sig_set_CpnAlarmSource_sDown) \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNALARM(_)                \
    _(sig_serv_CpnAlarm_init,serv_CpnAlarm_init)           \
    _(sig_serv_CpnAlarm_getAlarmCount,serv_CpnAlarm_getAlarmCount) \
    _(sig_serv_CpnAlarm_getAlarmEvents,serv_CpnAlarm_getAlarmEvents) \
    _(sig_serv_CpnAlarm_isAlarmed,serv_CpnAlarm_isAlarmed) \
    _(sig_serv_CpnAlarm_isUpgraded,serv_CpnAlarm_isUpgraded) \
    _(sig_serv_CpnAlarm_alarmCondTrue,serv_CpnAlarm_alarmCondTrue) \
    _(sig_serv_CpnAlarm_alarmCondFalse,serv_CpnAlarm_alarmCondFalse) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNALARM(_)            \
    _(sig_trig_CpnAlarm_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnAlarm_addTask,sig_serv_CpnSch_addTask)   \
    _(sig_trig_CpnAlarm_delTask,sig_serv_CpnSch_delTask)   \
    _(sig_trig_CpnAlarm_delay,sig_serv_CpnSch_delay)       \
    _(sig_trig_CpnAlarm_now,sig_serv_CpnSch_now)           \
    _(sig_trig_CpnAlarm_setErr,sig_serv_CpnErr_setErr)     \
    _(sig_trig_CpnAlarm_memMalloc,sig_serv_CpnMem_memMalloc) \
    _(sig_trig_CpnAlarm_memFree,sig_serv_CpnMem_memFree)   \
    _(sig_trig_CpnAlarm_isPointerSet,sig_serv_CpnMem_isPointerSet) \
    _(sig_trig_CpnAlarm_getSize,sig_serv_CpnMem_getSize)   \
    _(sig_trig_CpnAlarm_getIndex,sig_serv_CpnMem_getIndex) \
    _(sig_trig_CpnAlarm_memStatus,sig_serv_CpnMem_memStatus) \
    _(sig_trig_CpnAlarm_alarmCondTrue,sig_serv_CpnAlarm_alarmCondTrue) \
    _(sig_trig_CpnAlarm_alarmCondFalse,sig_serv_CpnAlarm_alarmCondFalse) \
    _(sig_trig_CpnAlarm_sSineUpCOnd,sig_serv_CpnAlarmSource_sSineUpCOnd) \
    _(sig_trig_CpnAlarm_sUpCOnd,sig_serv_CpnAlarmSource_sUpCOnd) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnAlarm(void);

#endif /*CPNALARMSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
