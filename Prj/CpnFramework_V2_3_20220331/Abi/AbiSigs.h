/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : AbiSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 17:11:21
 * Description  : Abi component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef ABISIGS_H_
#define ABISIGS_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define ABISIGS_MACRO_VERSION                   0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
//void serv_Abi_init(void);
/* getTime Service.
 **********************************************/
void serv_Abi_getTime(void *buff);
/* sendSig Service.
 **********************************************/
void serv_Abi_sendSig(void *buff);
/* sendCanFrame Service.
 **********************************************/
void serv_Abi_sendCanFrame(void *buff);

/* Trigger interface.
 **********************************************/
void trig_Abi_init(void);
void trig_Abi_tick(void);
void trig_Abi_run(void);
void trig_Abi_updateCanFrame(uint32 id, uint8 data[]);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_ABI(_)                     \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_ABI(_)                 \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_ABI(_)                     \
    _(sig_serv_Abi_getTime,serv_Abi_getTime)               \
    _(sig_serv_Abi_sendSig,serv_Abi_sendSig)               \
    _(sig_serv_Abi_sendCanFrame,serv_Abi_sendCanFrame)     \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_ABI(_)                 \
    _(sig_trig_Abi_init,sig_serv_CpnSch_init)              \
    _(sig_trig_Abi_tick,sig_serv_CpnSch_tick)              \
    _(sig_trig_Abi_run,sig_serv_CpnSch_run)                \
//    _(sig_trig_Abi_updateFrame,sig_serv_CpnFrameMatrix_updateFrame) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
// void taskAbi(void);

#endif /*ABISIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
