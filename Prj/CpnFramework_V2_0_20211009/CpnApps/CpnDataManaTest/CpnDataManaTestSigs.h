/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaTestSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/08 11:41:08
 * Description  : CpnDataManaTest component signals declaration head file.
 * Others       :
 * History      : 20211008 pxf Initially established.
 **************************************************************************/

#ifndef CPNDATAMANATESTSIGS_H_
#define CPNDATAMANATESTSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNDATAMANATESTSIGS_MACRO_VERSION       0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
void serv_CpnDataManaTest_init(void);

/* Trigger interface.
 **********************************************/
//void trig_CpnDataManaTest_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNDATAMANATEST(_)                              \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNDATAMANATEST(_)                          \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNDATAMANATEST(_)                              \
    _(sig_serv_CpnDataManaTest_init,serv_CpnDataManaTest_init)                  \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNDATAMANATEST(_)                          \
    _(sig_trig_CpnDataManaTest_initTask,sig_serv_CpnSch_initTask)               \
    _(sig_trig_CpnDataManaTest_addTask,sig_serv_CpnSch_addTask)                 \
    _(sig_trig_CpnDataManaTest_delTask,sig_serv_CpnSch_delTask)                 \
    _(sig_trig_CpnDataManaTest_delay,sig_serv_CpnSch_delay)                     \
    _(sig_trig_CpnDataManaTest_now,sig_serv_CpnSch_now)                         \
    _(sig_trig_CpnDataManaTest_setErr,sig_serv_CpnErr_setErr)                   \
    _(sig_trig_CpnDataManaTest_set_TxCanAAB_ulDataA,DataSetMapSet(TxCanAAB,ulDataA)) \
    _(sig_trig_CpnDataManaTest_set_TxCanAAB_ulDataB,DataSetMapSet(TxCanAAB,ulDataB)) \
    _(sig_trig_CpnDataManaTest_set_TxCan100_ulDataC,DataSetMapSet(TxCan100,ulDataC)) \
    _(sig_trig_CpnDataManaTest_set_TxCan100_ulDataD,DataSetMapSet(TxCan100,ulDataD)) \
    _(sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataE,DataSetMapSet(TxCanF0A,ulDataE)) \
    _(sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataF,DataSetMapSet(TxCanF0A,ulDataF)) \
    _(sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataG,DataSetMapSet(TxCanF0A,ulDataG)) \
    _(sig_trig_CpnDataManaTest_get_RxCan22F_ulData1,DataSetMapGet(RxCan22F,ulData1)) \
    _(sig_trig_CpnDataManaTest_get_RxCan22F_ulData2,DataSetMapGet(RxCan22F,ulData2)) \
    _(sig_trig_CpnDataManaTest_get_RxCan22F_ulData3,DataSetMapGet(RxCan22F,ulData3)) \
    _(sig_trig_CpnDataManaTest_get_RxCan22F_ulData4,DataSetMapGet(RxCan22F,ulData4)) \
    _(sig_trig_CpnDataManaTest_get_RxCan554E_ulData5,DataSetMapGet(RxCan554E,ulData5)) \
    _(sig_trig_CpnDataManaTest_get_RxCan554E_ulData6,DataSetMapGet(RxCan554E,ulData6)) \
    _(sig_trig_CpnDataManaTest_get_RxCan554E_ulData7,DataSetMapGet(RxCan554E,ulData7)) \
    _(sig_trig_CpnDataManaTest_get_RxCan554E_ulData8,DataSetMapGet(RxCan554E,ulData8)) \
    _(sig_trig_CpnDataManaTest_get_TxCanAAB_ulDataA,DataSetMapGet(TxCanAAB,ulDataA)) \
    _(sig_trig_CpnDataManaTest_get_TxCanAAB_ulDataB,DataSetMapGet(TxCanAAB,ulDataB)) \
    _(sig_trig_CpnDataManaTest_get_TxCan100_ulDataC,DataSetMapGet(TxCan100,ulDataC)) \
    _(sig_trig_CpnDataManaTest_get_TxCan100_ulDataD,DataSetMapGet(TxCan100,ulDataD)) \
    _(sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataE,DataSetMapGet(TxCanF0A,ulDataE)) \
    _(sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataF,DataSetMapGet(TxCanF0A,ulDataF)) \
    _(sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataG,DataSetMapGet(TxCanF0A,ulDataG)) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnDataManaTest(void);

#endif /*CPNDATAMANATESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
