/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:09:52
 * Description  : CpnSinks component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSINKSSIGS_H_
#define CPNSINKSSIGS_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSINKSSIGS_MACRO_VERSION      0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
    uint16 get_getSig;             /* get signal to be trigger, to get data */
    uint16 trig_endSig;            /* service signal to be trigger, to inform cache full */
    uint16 type_index;             /* grouped signale index */
    tick period;                   /* MS_T */
    uint16 data_size;              /* sizeof data */
    uint16 buff_size;              /* sizeof data buff */
    void *buff;                    /* cache data buffer */
} tSinksParams, *htSinksParams;
typedef struct{
    htSinksParams sinks;           /* sinks */
    uint16 outOperation;           /* out operation result, TRUE/FALSE */
    void *buff;                    /* read out data buffer */
} tSinksOut, *htSinksOut;
typedef enum{
    cacheNotStart,
    cacheCaching,
    cacheFull
} tCacheProcessSta;
typedef struct{
    htSinksParams sinks;           /* sinks */
    tCacheProcessSta sta;          /* sinks state */
} tSinksSta, *htSinksSta;

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSinks_init(void);
/* readData Service.
 **********************************************/
void serv_CpnSinks_readData(void *buff);
/* trigStart Service.
 **********************************************/
void serv_CpnSinks_trigStart(void *buff);
/* cacheState Service.
 **********************************************/
void serv_CpnSinks_cacheState(void *buff);
/* registerCache Service.
 **********************************************/
void serv_CpnSinks_registerCache(void *buff);
/* reCache Service.
 **********************************************/
void serv_CpnSinks_reCache(void *buff);

/* Error code Trigger interface.
 **********************************************/
// void trig_CpnSinks_inf_setErr(uint16 id, uint16 code);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSINKS(_)                \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKS(_)            \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSINKS(_)                \
    _(sig_serv_CpnSinks_init,serv_CpnSinks_init)           \
    _(sig_serv_CpnSinks_readData,serv_CpnSinks_readData)   \
    _(sig_serv_CpnSinks_trigStart,serv_CpnSinks_trigStart) \
    _(sig_serv_CpnSinks_cacheState,serv_CpnSinks_cacheState) \
    _(sig_serv_CpnSinks_registerCache,serv_CpnSinks_registerCache) \
    _(sig_serv_CpnSinks_reCache,serv_CpnSinks_reCache)     \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKS(_)            \
    _(sig_trig_CpnSinks_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSinks_addTask,sig_serv_CpnSch_addTask)   \
    _(sig_trig_CpnSinks_delTask,sig_serv_CpnSch_delTask)   \
    _(sig_trig_CpnSinks_delay,sig_serv_CpnSch_delay)       \
    _(sig_trig_CpnSinks_now,sig_serv_CpnSch_now)           \
    _(sig_trig_CpnSinks_setErr,sig_serv_CpnErr_setErr)     \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnSinks(void);

#endif /*CPNSINKSSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
