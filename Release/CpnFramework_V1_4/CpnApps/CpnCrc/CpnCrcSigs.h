/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnCrcSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:29:06
 * Description  : CpnCrc component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNCRCSIGS_H_
#define CPNCRCSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNCRCSIGS_MACRO_VERSION                0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
    uint8* s;
    uint32 len;
    uint32 crc;
} TS_CRC_DATA, *hTS_CRC_DATA;



/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnCrc_init(void);
/* getCrc8 Service.
 **********************************************/
void serv_CpnCrc_getCrc8(void *buff);
/* getCrc16 Service.
 **********************************************/
void serv_CpnCrc_getCrc16(void *buff);
/* getCrc32 Service.
 **********************************************/
void serv_CpnCrc_getCrc32(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnCrc_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNCRC(_)                  \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNCRC(_)              \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNCRC(_)                  \
    _(sig_serv_CpnCrc_init,serv_CpnCrc_init)               \
    _(sig_serv_CpnCrc_getCrc8,serv_CpnCrc_getCrc8)         \
    _(sig_serv_CpnCrc_getCrc16,serv_CpnCrc_getCrc16)       \
    _(sig_serv_CpnCrc_getCrc32,serv_CpnCrc_getCrc32)       \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCRC(_)              \
    _(sig_trig_CpnCrc_initTask,sig_serv_CpnSch_initTask)   \
    _(sig_trig_CpnCrc_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnCrc_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnCrc_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnCrc_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnCrc_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnCrc(void);

#endif /*CPNCRCSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
