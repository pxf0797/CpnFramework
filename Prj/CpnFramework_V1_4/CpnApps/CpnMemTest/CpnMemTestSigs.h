/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemTestSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:45:13
 * Description  : CpnMemTest component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMEMTESTSIGS_H_
#define CPNMEMTESTSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNMEMTESTSIGS_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnMemTest_init(void);

/* Trigger interface.
 **********************************************/
//void trig_CpnMemTest_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMEMTEST(_)              \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEMTEST(_)          \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMEMTEST(_)              \
    _(sig_serv_CpnMemTest_init,serv_CpnMemTest_init)       \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEMTEST(_)          \
    _(sig_trig_CpnMemTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnMemTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMemTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMemTest_delay,sig_serv_CpnSch_delay)     \
    _(sig_trig_CpnMemTest_now,sig_serv_CpnSch_now)         \
    _(sig_trig_CpnMemTest_setErr,sig_serv_CpnErr_setErr)   \
    _(sig_trig_CpnMemTest_memMalloc,sig_serv_CpnMem_memMalloc) \
    _(sig_trig_CpnMemTest_memFree,sig_serv_CpnMem_memFree) \
    _(sig_trig_CpnMemTest_isPointerSet,sig_serv_CpnMem_isPointerSet) \
    _(sig_trig_CpnMemTest_getSize,sig_serv_CpnMem_getSize) \
    _(sig_trig_CpnMemTest_getIndex,sig_serv_CpnMem_getIndex) \
    _(sig_trig_CpnMemTest_memStatus,sig_serv_CpnMem_memStatus) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnMemTest(void);

#endif /*CPNMEMTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
