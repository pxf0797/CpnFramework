/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTaskStrategySigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 09:53:54
 * Description  : CpnTaskStrategy component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNTASKSTRATEGYSIGS_H_
#define CPNTASKSTRATEGYSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNTASKSTRATEGYSIGS_MACRO_VERSION 0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
    strategy strgMask;
    uint16 addTime;
    uint16 delTime;
} strgDelayUpdate, *hstrgDelayUpdate;
typedef struct {
    strategy strgMask;
    condition cond;
} strgCondUpdate, *hstrgCondUpdate;



/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnTaskStrategy_init(void);
/* delayUpdate Service.
 **********************************************/
void serv_CpnTaskStrategy_delayUpdate(void *buff);
/* condUpdate Service.
 **********************************************/
void serv_CpnTaskStrategy_condUpdate(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnTaskStrategy_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNTASKSTRATEGY(_)         \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNTASKSTRATEGY(_)     \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNTASKSTRATEGY(_)         \
    _(sig_serv_CpnTaskStrategy_init,serv_CpnTaskStrategy_init) \
    _(sig_serv_CpnTaskStrategy_delayUpdate,serv_CpnTaskStrategy_delayUpdate) \
    _(sig_serv_CpnTaskStrategy_condUpdate,serv_CpnTaskStrategy_condUpdate) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTASKSTRATEGY(_)     \
    _(sig_trig_CpnTaskStrategy_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnTaskStrategy_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnTaskStrategy_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnTaskStrategy_delay,sig_serv_CpnSch_delay)\
    _(sig_trig_CpnTaskStrategy_now,sig_serv_CpnSch_now)    \
    _(sig_trig_CpnTaskStrategy_setMonitor,sig_serv_CpnSch_setMonitor) \
    _(sig_trig_CpnTaskStrategy_getMonitor,sig_serv_CpnSch_getMonitor) \
    _(sig_trig_CpnTaskStrategy_updateStrategy,sig_serv_CpnSch_updateStrategy) \
    _(sig_trig_CpnTaskStrategy_getStrategy,sig_serv_CpnSch_getStrategy) \
    _(sig_trig_CpnTaskStrategy_getTaskNum,sig_serv_CpnSch_getTaskNum) \
    _(sig_trig_CpnTaskStrategy_setErr,sig_serv_CpnErr_setErr) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnTaskStrategy(void);

#endif /*CPNTASKSTRATEGYSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
