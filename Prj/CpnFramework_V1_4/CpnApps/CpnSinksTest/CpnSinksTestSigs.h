/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksTestSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:53:35
 * Description  : CpnSinksTest component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSINKSTESTSIGS_H_
#define CPNSINKSTESTSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSINKSTESTSIGS_MACRO_VERSION          0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
typedef struct{
    uint16 index;
    float32 data;
} tStoreData, *htStoreData;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSinksTest_init(void);
/* sIsFull Service.
 **********************************************/
void serv_CpnSinksTest_sIsFull(void);
/* sGetData Service.
 **********************************************/
void serv_CpnSinksTest_sGetData(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnSinksTest_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSINKSTEST(_)            \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKSTEST(_)        \
    _(sig_get_CpnSinksTest_wCache,sig_set_CpnSourceTest_wOutput) \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSINKSTEST(_)            \
    _(sig_serv_CpnSinksTest_init,serv_CpnSinksTest_init)   \
    _(sig_serv_CpnSinksTest_sIsFull,serv_CpnSinksTest_sIsFull) \
    _(sig_serv_CpnSinksTest_sGetData,serv_CpnSinksTest_sGetData) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKSTEST(_)        \
    _(sig_trig_CpnSinksTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSinksTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnSinksTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnSinksTest_delay,sig_serv_CpnSch_delay)   \
    _(sig_trig_CpnSinksTest_now,sig_serv_CpnSch_now)       \
    _(sig_trig_CpnSinksTest_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnSinksTest_readData,sig_serv_CpnSinks_readData) \
    _(sig_trig_CpnSinksTest_trigStart,sig_serv_CpnSinks_trigStart) \
    _(sig_trig_CpnSinksTest_cacheState,sig_serv_CpnSinks_cacheState) \
    _(sig_trig_CpnSinksTest_registerCache,sig_serv_CpnSinks_registerCache) \
    _(sig_trig_CpnSinksTest_reCache,sig_serv_CpnSinks_reCache) \
    _(sig_trig_CpnSinksTest_sIsFull,sig_serv_CpnSinksTest_sIsFull) \
    _(sig_trig_CpnSinksTest_sGetData,sig_serv_CpnSinksTest_sGetData) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnSinksTest(void);

#endif /*CPNSINKSTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
