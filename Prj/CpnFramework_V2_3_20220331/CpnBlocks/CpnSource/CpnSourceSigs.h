/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:32:56
 * Description  : CpnSource component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSOURCESIGS_H_
#define CPNSOURCESIGS_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSOURCESIGS_MACRO_VERSION     0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
typedef enum{
    w_sine,
    w_pluse,
    w_countUp,
    w_countDown,
    w_countUpDown,

    w_waveTypeMax
} tWaveType;
typedef struct{
    tWaveType type;                /* wave type */
    uint16 trig_sig;               /* service signal to be trigger */
    uint16 type_index;             /* grouped signale index */
    float32 amplitude;             /* amplitude */
    tick step;                     /* MS_T */
    tick period;                   /* MS_T */
    uint16 duty;                   /* 0.1% */
    uint16 phase;                  /* (0--3600)0.1 */
} tSourceParams, *htSourceParams;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSource_init(void);
/* registerWaveSig Service.
 **********************************************/
void serv_CpnSource_registWaveSig(void *buff);
/* changeWaveSig Service.
 **********************************************/
void serv_CpnSource_changeWaveSig(void *buff);
/* freeWaveSig Service.
 **********************************************/
void serv_CpnSource_freeWaveSig(void *buff);

/* Error code Trigger interface.
 **********************************************/
// void trig_CpnSource_inf_setErr(uint16 id, uint16 code);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSOURCE(_)               \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCE(_)           \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSOURCE(_)               \
    _(sig_serv_CpnSource_init,serv_CpnSource_init)         \
    _(sig_serv_CpnSource_registWaveSig,serv_CpnSource_registWaveSig) \
    _(sig_serv_CpnSource_changeWaveSig,serv_CpnSource_changeWaveSig) \
    _(sig_serv_CpnSource_freeWaveSig,serv_CpnSource_freeWaveSig) \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCE(_)           \
    _(sig_trig_CpnSource_initTask,sig_serv_CpnSch_initTask)\
    _(sig_trig_CpnSource_addTask,sig_serv_CpnSch_addTask)  \
    _(sig_trig_CpnSource_delTask,sig_serv_CpnSch_delTask)  \
    _(sig_trig_CpnSource_delay,sig_serv_CpnSch_delay)      \
    _(sig_trig_CpnSource_now,sig_serv_CpnSch_now)          \
    _(sig_trig_CpnSource_setErr,sig_serv_CpnErr_setErr)    \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnSource(void);

#endif /*CPNSOURCESIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
