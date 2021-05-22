/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTestSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 17:06:41
 * Description  : CpnTest component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNTESTSIGS_H_
#define CPNTESTSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNTESTSIGS_MACRO_VERSION               0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
void serv_CpnTest_init(void);
/* servSig1 Service.
 **********************************************/
void serv_CpnTest_servSig1(void);
/* servSig2_uint16 Service.
 **********************************************/
void serv_CpnTest_servSig2_uint16(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnTest_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNTEST(_)                 \
    _(sig_set_CpnTest_sendSig1_uint8,sizeof(uint8))        \
    _(sig_set_CpnTest_SendSig2_uint32,sizeof(uint32))      \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNTEST(_)             \
    _(sig_get_CpnTest_receiveSig1_uint32,sig_set_CpnTest_SendSig2_uint32) \
    _(sig_get_CpnTest_receiveSig2_uint8,sig_set_CpnTest_sendSig1_uint8) \


/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNTEST(_)                 \
    _(sig_serv_CpnTest_init,serv_CpnTest_init)             \
    _(sig_serv_CpnTest_servSig1,serv_CpnTest_servSig1)     \
    _(sig_serv_CpnTest_servSig2_uint16,serv_CpnTest_servSig2_uint16) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTEST(_)             \
    _(sig_trig_CpnTest_initTask,sig_serv_CpnSch_initTask)  \
    _(sig_trig_CpnTest_addTask,sig_serv_CpnSch_addTask)    \
    _(sig_trig_CpnTest_delTask,sig_serv_CpnSch_delTask)    \
    _(sig_trig_CpnTest_delay,sig_serv_CpnSch_delay)        \
    _(sig_trig_CpnTest_now,sig_serv_CpnSch_now)            \
    _(sig_trig_CpnTest_setErr,sig_serv_CpnErr_setErr)      \
    _(sig_trig_CpnTest_trigSig1_uint16,sig_serv_CpnTest_servSig2_uint16) \
    _(sig_trig_CpnTest_trigSig2,sig_serv_CpnTest_servSig1) \

/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnTest(void);

#endif /*CPNTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
