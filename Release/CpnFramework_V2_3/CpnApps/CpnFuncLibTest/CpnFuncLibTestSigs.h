/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFuncLibTestSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/11/03 14:55:04
 * Description  : CpnFuncLibTest component signals declaration head file.
 * Others       : 
 * History      : 20211103 pxf Initially established.
 **************************************************************************/

#ifndef CPNFUNCLIBTESTSIGS_H_
#define CPNFUNCLIBTESTSIGS_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNFUNCLIBTESTSIGS_MACRO_VERSION        0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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



/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnFuncLibTest_init(void);

/* Trigger interface.
 **********************************************/
//void trig_CpnFuncLibTest_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNFUNCLIBTEST(_)                               \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNFUNCLIBTEST(_)                           \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNFUNCLIBTEST(_)                               \
    _(sig_serv_CpnFuncLibTest_init,serv_CpnFuncLibTest_init)                    \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNFUNCLIBTEST(_)                           \
    _(sig_trig_CpnFuncLibTest_initTask,sig_serv_CpnSch_initTask)                \
    _(sig_trig_CpnFuncLibTest_addTask,sig_serv_CpnSch_addTask)                  \
    _(sig_trig_CpnFuncLibTest_delTask,sig_serv_CpnSch_delTask)                  \
    _(sig_trig_CpnFuncLibTest_delay,sig_serv_CpnSch_delay)                      \
    _(sig_trig_CpnFuncLibTest_now,sig_serv_CpnSch_now)                          \
    _(sig_trig_CpnFuncLibTest_setErr,sig_serv_CpnErr_setErr)                    \
    _(sig_trig_CpnFuncLibTest_memMalloc,sig_serv_CpnMem_memMalloc)              \
    _(sig_trig_CpnFuncLibTest_memFree,sig_serv_CpnMem_memFree)                  \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnFuncLibTest(void);

#endif /*CPNFUNCLIBTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
