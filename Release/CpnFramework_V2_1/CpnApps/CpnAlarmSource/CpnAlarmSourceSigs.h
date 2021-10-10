/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnAlarmSourceSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/06/26 09:54:34
 * Description  : CpnAlarmSource component signals declaration head file.
 * Others       :
 * History      : 20210626 pxf Initially established.
 **************************************************************************/

#ifndef CPNALARMSOURCESIGS_H_
#define CPNALARMSOURCESIGS_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNALARMSOURCESIGS_MACRO_VERSION        0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
void serv_CpnAlarmSource_init(void);
/* getSine Service.
 **********************************************/
void serv_CpnAlarmSource_sSine(void *buff);
/* getPluse Service.
 **********************************************/
void serv_CpnAlarmSource_sPluse(void *buff);
/* getUpDown Service.
 **********************************************/
void serv_CpnAlarmSource_sUpDown(void *buff);
/* getUp Service.
 **********************************************/
void serv_CpnAlarmSource_sUp(void *buff);
/* getDown Service.
 **********************************************/
void serv_CpnAlarmSource_sDown(void *buff);
/* sSineUpCOnd Service.
 **********************************************/
void serv_CpnAlarmSource_sSineUpCOnd(void *buff);
/* sUpCOnd Service.
 **********************************************/
void serv_CpnAlarmSource_sUpCOnd(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnAlarmSource_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNALARMSOURCE(_)          \
    _(sig_set_CpnAlarmSource_sSine,sizeof(uint32*))        \
    _(sig_set_CpnAlarmSource_sPluse,sizeof(uint32*))       \
    _(sig_set_CpnAlarmSource_sUpDown,sizeof(uint32*))      \
    _(sig_set_CpnAlarmSource_sUp,sizeof(uint32*))          \
    _(sig_set_CpnAlarmSource_sDown,sizeof(uint32*))        \


/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNALARMSOURCE(_)      \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNALARMSOURCE(_)          \
    _(sig_serv_CpnAlarmSource_init,serv_CpnAlarmSource_init) \
    _(sig_serv_CpnAlarmSource_sSine,serv_CpnAlarmSource_sSine) \
    _(sig_serv_CpnAlarmSource_sPluse,serv_CpnAlarmSource_sPluse) \
    _(sig_serv_CpnAlarmSource_sUpDown,serv_CpnAlarmSource_sUpDown) \
    _(sig_serv_CpnAlarmSource_sUp,serv_CpnAlarmSource_sUp) \
    _(sig_serv_CpnAlarmSource_sDown,serv_CpnAlarmSource_sDown) \
    _(sig_serv_CpnAlarmSource_sSineUpCOnd,serv_CpnAlarmSource_sSineUpCOnd) \
    _(sig_serv_CpnAlarmSource_sUpCOnd,serv_CpnAlarmSource_sUpCOnd) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNALARMSOURCE(_)      \
    _(sig_trig_CpnAlarmSource_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnAlarmSource_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnAlarmSource_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnAlarmSource_delay,sig_serv_CpnSch_delay) \
    _(sig_trig_CpnAlarmSource_now,sig_serv_CpnSch_now)     \
    _(sig_trig_CpnAlarmSource_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnAlarmSource_registWaveSig,sig_serv_CpnSource_registWaveSig)\
    _(sig_trig_CpnAlarmSource_changeWaveSig,sig_serv_CpnSource_changeWaveSig)\
    _(sig_trig_CpnAlarmSource_freeWaveSig,sig_serv_CpnSource_freeWaveSig)\
    _(sig_trig_CpnAlarmSource_sSine,sig_serv_CpnAlarmSource_sSine)\
    _(sig_trig_CpnAlarmSource_sPluse,sig_serv_CpnAlarmSource_sPluse)\
    _(sig_trig_CpnAlarmSource_sUpDown,sig_serv_CpnAlarmSource_sUpDown)\
    _(sig_trig_CpnAlarmSource_sUp,sig_serv_CpnAlarmSource_sUp)\
    _(sig_trig_CpnAlarmSource_sDown,sig_serv_CpnAlarmSource_sDown)\



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnAlarmSource(void);

#endif /*CPNALARMSOURCESIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
