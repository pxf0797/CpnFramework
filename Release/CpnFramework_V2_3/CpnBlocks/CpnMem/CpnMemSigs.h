/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:39:10
 * Description  : CpnMem component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMEMSIGS_H_
#define CPNMEMSIGS_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNMEMSIGS_MACRO_VERSION                0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
    void *pointer;
    /* if function is memMalloc and getSize, then indication is size;
     * if function is isPointerSet, then indication is TRUE/FALSE;
     * if function is getIndex, then indication is index;
     * */
    uint32 indication;
} tsMemPointer, *htsMemPointer;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnMem_init(void);
/* memMalloc Service.
 **********************************************/
void serv_CpnMem_memMalloc(void *buff);
/* memFree Service.
 **********************************************/
void serv_CpnMem_memFree(void *buff);
/* isPointerSet Service.
 **********************************************/
void serv_CpnMem_isPointerSet(void *buff);
/* getSize Service.
 **********************************************/
void serv_CpnMem_getSize(void *buff);
/* getIndex Service.
 **********************************************/
void serv_CpnMem_getIndex(void *buff);
/* memStatus Service.
 **********************************************/
void serv_CpnMem_memStatus(void *buff);

/* Trigger interface.
 **********************************************/
//void trig_CpnMem_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMEM(_)                  \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEM(_)              \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMEM(_)                  \
    _(sig_serv_CpnMem_init,serv_CpnMem_init)               \
    _(sig_serv_CpnMem_memMalloc,serv_CpnMem_memMalloc)     \
    _(sig_serv_CpnMem_memFree,serv_CpnMem_memFree)         \
    _(sig_serv_CpnMem_isPointerSet,serv_CpnMem_isPointerSet) \
    _(sig_serv_CpnMem_getSize,serv_CpnMem_getSize)         \
    _(sig_serv_CpnMem_getIndex,serv_CpnMem_getIndex)       \
    _(sig_serv_CpnMem_memStatus,serv_CpnMem_memStatus)     \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEM(_)              \
    _(sig_trig_CpnMem_initTask,sig_serv_CpnSch_initTask)   \
    _(sig_trig_CpnMem_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnMem_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnMem_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnMem_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnMem_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
// void taskCpnMem(void);

#endif /*CPNMEMSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
