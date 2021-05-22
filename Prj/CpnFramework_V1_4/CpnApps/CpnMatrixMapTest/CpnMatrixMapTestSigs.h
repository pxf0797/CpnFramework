/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMatrixMapTestSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:00:03
 * Description  : CpnMatrixMapTest component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMATRIXMAPTESTSIGS_H_
#define CPNMATRIXMAPTESTSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNMATRIXMAPTESTSIGS_MACRO_VERSION 0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
void serv_CpnMatrixMapTest_init(void);

/* Trigger interface.
 **********************************************/
//void trig_CpnMatrixMapTest_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAPTEST(_)        \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAPTEST(_)    \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAPTEST(_)        \
    _(sig_serv_CpnMatrixMapTest_init,serv_CpnMatrixMapTest_init) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAPTEST(_)    \
    _(sig_trig_CpnMatrixMapTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnMatrixMapTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMatrixMapTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMatrixMapTest_delay,sig_serv_CpnSch_delay) \
    _(sig_trig_CpnMatrixMapTest_now,sig_serv_CpnSch_now)   \
    _(sig_trig_CpnMatrixMapTest_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataA,matrixMapSet(ulDataA)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataB,matrixMapSet(ulDataB)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataC,matrixMapSet(ulDataC)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataD,matrixMapSet(ulDataD)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataE,matrixMapSet(ulDataE)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataF,matrixMapSet(ulDataF)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataG,matrixMapSet(ulDataG)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData1,matrixMapGet(ulData1)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData2,matrixMapGet(ulData2)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData3,matrixMapGet(ulData3)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData4,matrixMapGet(ulData4)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData5,matrixMapGet(ulData5)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData6,matrixMapGet(ulData6)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData7,matrixMapGet(ulData7)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData8,matrixMapGet(ulData8)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataA,matrixMapGet(ulDataA)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataB,matrixMapGet(ulDataB)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataC,matrixMapGet(ulDataC)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataD,matrixMapGet(ulDataD)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataE,matrixMapGet(ulDataE)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataF,matrixMapGet(ulDataF)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataG,matrixMapGet(ulDataG)) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnMatrixMapTest(void);

#endif /*CPNMATRIXMAPTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
