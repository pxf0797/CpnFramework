/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFrameMatrixSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:56:01
 * Description  : CpnFrameMatrix component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNFRAMEMATRIXSIGS_H_
#define CPNFRAMEMATRIXSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"
#include "./CpnFrameMatrixCfg.h"
#include "./CpnFrameMatrix.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNFRAMEMATRIXSIGS_MACRO_VERSION 0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
typedef struct{
    uint32 id;
    htuBytesData frame;
} tsFrameTrans, *htsFrameTrans;
typedef struct{
    uint32 id;
    uint16 bit_start;
    uint16 bit_len;
    uint32* value;
} tsFramsGetSet, *htsFramsGetSet;
typedef struct{
    uint32 id;
    uint16 byte_index;
    uint8* value;
} tsFrameByte, *htsFrameByte;

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnFrameMatrix_init(void);
/* getFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_getFrame(void *buff);
/* setFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_setFrame(void *buff);
/* updateFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_updateFrame(void *buff);
/* getFrameByte Service.
 **********************************************/
void serv_CpnFrameMatrix_getFrameByte(void *buff);
/* setFrameByte Service.
 **********************************************/
void serv_CpnFrameMatrix_setFrameByte(void *buff);
/* sendFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_sendFrame(void *buff);

/* Trigger interface.
 **********************************************/
void trig_CpnFrameMatrix_inf_sendFrame(uint32 id, htuBytesData frame);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNFRAMEMATRIX(_)          \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNFRAMEMATRIX(_)      \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNFRAMEMATRIX(_)          \
    _(sig_serv_CpnFrameMatrix_init,serv_CpnFrameMatrix_init) \
    _(sig_serv_CpnFrameMatrix_getFrame,serv_CpnFrameMatrix_getFrame) \
    _(sig_serv_CpnFrameMatrix_setFrame,serv_CpnFrameMatrix_setFrame) \
    _(sig_serv_CpnFrameMatrix_updateFrame,serv_CpnFrameMatrix_updateFrame) \
    _(sig_serv_CpnFrameMatrix_getFrameByte,serv_CpnFrameMatrix_getFrameByte) \
    _(sig_serv_CpnFrameMatrix_setFrameByte,serv_CpnFrameMatrix_setFrameByte) \
    _(sig_serv_CpnFrameMatrix_sendFrame,serv_CpnFrameMatrix_sendFrame) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNFRAMEMATRIX(_)      \
    _(sig_trig_CpnFrameMatrix_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnFrameMatrix_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnFrameMatrix_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnFrameMatrix_delay,sig_serv_CpnSch_delay) \
    _(sig_trig_CpnFrameMatrix_now,sig_serv_CpnSch_now)     \
    _(sig_trig_CpnFrameMatrix_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnFrameMatrix_sendFrame,sig_serv_Abi_sendCanFrame) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnFrameMatrix(void);

#endif /*CPNFRAMEMATRIXSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
