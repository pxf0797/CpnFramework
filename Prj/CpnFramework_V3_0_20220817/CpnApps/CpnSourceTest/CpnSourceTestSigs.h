/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceTestSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:59:39
 * Description  : CpnSourceTest component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSOURCETESTSIGS_H_
#define CPNSOURCETESTSIGS_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSOURCETESTSIGS_MACRO_VERSION         0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
void serv_CpnSourceTest_init(void);
/* sSine Service.
 **********************************************/
void serv_CpnSourceTest_sSine(void *buff);
/* sPluse Service.
 **********************************************/
void serv_CpnSourceTest_sPluse(void *buff);
/* sCountUp Service.
 **********************************************/
void serv_CpnSourceTest_sCountUp(void *buff);
/* sCountDown Service.
 **********************************************/
void serv_CpnSourceTest_sCountDown(void *buff);
/* sCountUpDown Service.
 **********************************************/
void serv_CpnSourceTest_sCountUpDown(void *buff);
/* sSine2 Service.
 **********************************************/
void serv_CpnSourceTest_sSine2(void *buff);
/* sSine3 Service.
 **********************************************/
void serv_CpnSourceTest_sSine3(void *buff);
/* sPluse2 Service.
 **********************************************/
void serv_CpnSourceTest_sPluse2(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnSourceTest_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSOURCETEST(_)           \
    _(sig_set_CpnSourceTest_wOutput,sizeof(float32))       \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCETEST(_)       \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSOURCETEST(_)           \
    _(sig_serv_CpnSourceTest_init,serv_CpnSourceTest_init) \
    _(sig_serv_CpnSourceTest_sSine,serv_CpnSourceTest_sSine) \
    _(sig_serv_CpnSourceTest_sPluse,serv_CpnSourceTest_sPluse) \
    _(sig_serv_CpnSourceTest_sCountUp,serv_CpnSourceTest_sCountUp) \
    _(sig_serv_CpnSourceTest_sCountDown,serv_CpnSourceTest_sCountDown) \
    _(sig_serv_CpnSourceTest_sCountUpDown,serv_CpnSourceTest_sCountUpDown) \
    _(sig_serv_CpnSourceTest_sSine2,serv_CpnSourceTest_sSine2) \
    _(sig_serv_CpnSourceTest_sSine3,serv_CpnSourceTest_sSine3) \
    _(sig_serv_CpnSourceTest_sPluse2,serv_CpnSourceTest_sPluse2) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCETEST(_)       \
    _(sig_trig_CpnSourceTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSourceTest_delay,sig_serv_CpnSch_delay)  \
    _(sig_trig_CpnSourceTest_now,sig_serv_CpnSch_now)      \
    _(sig_trig_CpnSourceTest_setErr,sig_serv_CpnErr_setErr)\
    _(sig_trig_CpnSourceTest_registWaveSig,sig_serv_CpnSource_registWaveSig)\
    _(sig_trig_CpnSourceTest_changeWaveSig,sig_serv_CpnSource_changeWaveSig)\
    _(sig_trig_CpnSourceTest_freeWaveSig,sig_serv_CpnSource_freeWaveSig)\
    _(sig_trig_CpnSourceTest_sSine,sig_serv_CpnSourceTest_sSine) \
    _(sig_trig_CpnSourceTest_sSine2,sig_serv_CpnSourceTest_sSine2) \
    _(sig_trig_CpnSourceTest_sSine3,sig_serv_CpnSourceTest_sSine3) \
    _(sig_trig_CpnSourceTest_sPluse,sig_serv_CpnSourceTest_sPluse) \
    _(sig_trig_CpnSourceTest_sPluse2,sig_serv_CpnSourceTest_sPluse2) \
    _(sig_trig_CpnSourceTest_sCountUp,sig_serv_CpnSourceTest_sCountUp) \
    _(sig_trig_CpnSourceTest_sCountDown,sig_serv_CpnSourceTest_sCountDown) \
    _(sig_trig_CpnSourceTest_sCountUpDown,sig_serv_CpnSourceTest_sCountUpDown) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnSourceTest(void);

#endif /*CPNSOURCETESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
