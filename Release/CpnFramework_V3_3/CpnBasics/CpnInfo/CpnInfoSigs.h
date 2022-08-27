/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnInfoSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/05/24 11:54:40
 * Description  : CpnInfo component signals declaration head file.
 * Others       :
 * History      : 20210524 pxf Initially established.
 **************************************************************************/

#ifndef CPNINFOSIGS_H_
#define CPNINFOSIGS_H_

/* Include head files. */
#include "Rte.h"
#include "CpnInfoCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNINFOSIGS_MACRO_VERSION               0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
void serv_CpnInfo_init(void);
/* info Service.
 **********************************************/
void serv_CpnInfo_info(const char *file, const char *func, const uint16 line, const char *format, ...);
#if (CPNINFOCFG_REPORT_ENABLE == TRUE)
#define INFO(...) serv_CpnInfo_info(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#else
#define INFO(...) ((void*)0)
#endif

/* Trigger interface.
 **********************************************/
void trig_CpnInfo_inf_infoout(uint8* buff, uint16 len);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNINFO(_)                 \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNINFO(_)             \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNINFO(_)                 \
    _(sig_serv_CpnInfo_init,serv_CpnInfo_init)             \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNINFO(_)             \
    _(sig_trig_CpnInfo_initTask,sig_serv_CpnSch_initTask)  \
    _(sig_trig_CpnInfo_delay,sig_serv_CpnSch_delay)        \
    _(sig_trig_CpnInfo_now,sig_serv_CpnSch_now)            \
    _(sig_trig_CpnInfo_setErr,sig_serv_CpnErr_setErr)      \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnInfo(void);

#endif /*CPNINFOSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
