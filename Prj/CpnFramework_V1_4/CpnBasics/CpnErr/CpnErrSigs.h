/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnErrSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 14:10:28
 * Description  : CpnErr component signals declaration head file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CPNERRSIGS_H_
#define CPNERRSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNERRSIGS_MACRO_VERSION        0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * get set data typed definition.
 * Generally, only the set data is defined, and the get type refers to the current header file.
 * Only need to define the data sent, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Sent data type.
 **********************************************/



/***********************************************************
 * serv trig data typed definition.
 * Generally, only the serv data is defined, and the trig type refers to the current header file.
 * Only need to define the data sent, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Serv data type.
 **********************************************/



/***********************************************************
 * serv trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnErr_init(void);
/* Service.
 **********************************************/
void serv_CpnErr_setErr(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnErr_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNERR(_)                  \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNERR(_)              \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNERR(_)                  \
    _(sig_serv_CpnErr_init,serv_CpnErr_init)               \
    _(sig_serv_CpnErr_setErr,serv_CpnErr_setErr)           \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNERR(_)              \
    _(sig_trig_CpnErr_initTask,sig_serv_CpnSch_initTask)   \
    _(sig_trig_CpnErr_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnErr_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnErr_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnErr_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnErr_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnErr(void);

#endif /*CPNERRSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
