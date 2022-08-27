/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSimpleSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2022/08/17 19:49:04
 * Description  : CpnSimple component signals declaration head file.
 * Others       :
 * History      : 20220817 pxf Initially established.
 **************************************************************************/

#ifndef CPNSIMPLESIGS_H_
#define CPNSIMPLESIGS_H_

/* Include head files. */
#include "Rte.h"
#include "CpnSchCfg.h"
#include "CpnSimpleCfg.h"
#include "CpnSch.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSIMPLESIGS_MACRO_VERSION             0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * simple tasks.
 **********************************************************/
/* tasks declaration.
 **********************************************/
#define TASKDC(name,level,start,period) void task_##name(void);
#define TASKDCS(task_list) extern task task_simples[task_index_max]; task_list(TASKDC)
/* tasks definition. */
#define TASkDF(name,level,start,period) task_##name,
#define TASKDFS(task_list)                                      \
task task_simples[task_index_max] = {                           \
    task_list(TASkDF)                                           \
};

/***********************************************************
 * simple task params.
 **********************************************************/
/* simple task params.
 **********************************************/
TASK_PARAMS(SIMPLE_LIST)
TASKDCS(SIMPLE_LIST)

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
void serv_CpnSimple_init(void);

/* Trigger interface.
 **********************************************/
//void trig_CpnSimple_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSIMPLE(_)                                    \
    _(sig_set_CpnSimple_sendSig1,sizeof(uint8))                                 \
    _(sig_set_CpnSimple_sendSig2,sizeof(uint32))                                \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSIMPLE(_)                                \
    _(sig_get_CpnSimple_receiveSig1,sig_set_CpnSimple_sendSig2)                 \
    _(sig_get_CpnSimple_receiveSig2,sig_set_CpnSimple_sendSig1)                 \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSIMPLE(_)                                    \
    _(sig_serv_CpnSimple_init,serv_CpnSimple_init)                              \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSIMPLE(_)                                \
    _(sig_trig_CpnSimple_initTask,sig_serv_CpnSch_initTask)                     \
    _(sig_trig_CpnSimple_delay,sig_serv_CpnSch_delay)                           \
    _(sig_trig_CpnSimple_now,sig_serv_CpnSch_now)                               \
    _(sig_trig_CpnSimple_setErr,sig_serv_CpnErr_setErr)                         \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/

#endif /*CPNSIMPLESIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
