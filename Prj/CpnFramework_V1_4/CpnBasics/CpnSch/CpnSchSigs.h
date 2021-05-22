/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSchSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  : CpnSch component signals declaration head file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CPNSCHSIGS_H_
#define CPNSCHSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"
#include "./CpnSch.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSCHSIGS_MACRO_VERSION        0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Get Set data type definition.
 * Generally, only the set data is defined, and the get type refers to the current header file.
 * Only need to define the data sent, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Sent data type.
 **********************************************/



/***********************************************************
 * Serv Trig data type definition.
 * Generally, only the serv data is defined, and the trig type refers to the current header file.
 * Only need to define the data sent, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Serv data type.
 **********************************************/



/***********************************************************
 * serv trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSch_initTask(void *buff);
/* Add task Service.
 **********************************************/
void serv_CpnSch_addTask(void *buff);
/* Delete task Service.
 **********************************************/
void serv_CpnSch_delTask(void *buff);
/* Delay Service.
 **********************************************/
void serv_CpnSch_delay(void *buff);
/* Real time Service.
 **********************************************/
void serv_CpnSch_now(void *buff);
/* Set monitor Service.
 **********************************************/
void serv_CpnSch_setMonitor(void *buff);
/* Get monitor Service.
 **********************************************/
void serv_CpnSch_getMonitor(void *buff);
/* Update strategy Service.
 **********************************************/
void serv_CpnSch_updateStrategy(void *buff);
/* Get strategy Service.
 **********************************************/
void serv_CpnSch_getStrategy(void *buff);
/* Get all schduler task counters Service.
 **********************************************/
void serv_CpnSch_getTaskNum(void *buff);
/* Component initial Service.
 **********************************************/
void serv_CpnSch_init(void);
/* Component run Service.
 **********************************************/
void serv_CpnSch_run(void);
/* Step Service.
 **********************************************/
void serv_CpnSch_tick(void);

/* Real time Interface trigger.
 **********************************************/
void trig_CpnSch_inf_getTime(uint16 *point);
/* Error code Interface trigger.
 **********************************************/
void trig_CpnSch_inf_setErr(uint16 id, uint16 code);
/* Initial component Interface trigger.
 **********************************************/
void trig_CpnSch_inf_initCpn(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSCH(_)                  \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSCH(_)              \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                  \
    _(sig_serv_CpnSch_initTask,serv_CpnSch_initTask)       \
    _(sig_serv_CpnSch_addTask,serv_CpnSch_addTask)         \
    _(sig_serv_CpnSch_delTask,serv_CpnSch_delTask)         \
    _(sig_serv_CpnSch_delay,serv_CpnSch_delay)             \
    _(sig_serv_CpnSch_now,serv_CpnSch_now)                 \
    _(sig_serv_CpnSch_setMonitor,serv_CpnSch_setMonitor)   \
    _(sig_serv_CpnSch_getMonitor,serv_CpnSch_getMonitor)   \
    _(sig_serv_CpnSch_updateStrategy,serv_CpnSch_updateStrategy) \
    _(sig_serv_CpnSch_getStrategy,serv_CpnSch_getStrategy) \
    _(sig_serv_CpnSch_getTaskNum,serv_CpnSch_getTaskNum)   \
    _(sig_serv_CpnSch_init,serv_CpnSch_init)               \
    _(sig_serv_CpnSch_run,serv_CpnSch_run)                 \
    _(sig_serv_CpnSch_tick,serv_CpnSch_tick)               \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)              \
    _(sig_trig_CpnSch_initTask,sig_serv_CpnSch_initTask)   \
    _(sig_trig_CpnSch_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnSch_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnSch_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnSch_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnSch_inf_getTime,sig_serv_Abi_getTime)    \
    _(sig_trig_CpnSch_inf_setErr,sig_serv_CpnErr_setErr)   \
    _(sig_trig_CpnErr_init,sig_serv_CpnErr_init)           \
    _(sig_trig_CpnSource_init,sig_serv_CpnSource_init)     \
    _(sig_trig_CpnSinks_init,sig_serv_CpnSinks_init)       \
    _(sig_trig_CpnTest_init,sig_serv_CpnTest_init)         \
    _(sig_trig_CpnSourceTest_init,sig_serv_CpnSourceTest_init) \
    _(sig_trig_CpnSinksTest_init,sig_serv_CpnSinksTest_init) \
    _(sig_trig_CpnFrameMatrix_init,sig_serv_CpnFrameMatrix_init) \
    _(sig_trig_CpnMatrixMap_init,sig_serv_CpnMatrixMap_init) \
    _(sig_trig_CpnCrc_init,sig_serv_CpnCrc_init)           \
    _(sig_trig_CpnMatrixMapTest_init,sig_serv_CpnMatrixMapTest_init) \
    _(sig_trig_CpnMem_init,sig_serv_CpnMem_init)           \
    _(sig_trig_CpnMemTest_init,sig_serv_CpnMemTest_init)   \
    _(sig_trig_CpnTaskStrategy_init,sig_serv_CpnTaskStrategy_init) \
    _(sig_trig_CpnTaskCtrl_init,sig_serv_CpnTaskCtrl_init) \


/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
//void taskCpnSch(void);

#endif /*CPNSCHSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
