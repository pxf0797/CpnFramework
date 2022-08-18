/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteAsynSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:48:45
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef RTEASYNSIGS_H_
#define RTEASYNSIGS_H_

/* Include head files. */
#include "RteSigsConfigList.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define RTEASYNSIGS_MACRO_VERSION       0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * set get signal list.
 **********************************************************/
/* set signal list.
 **********************************************/
/* #define SIGNAL_SET_LIST_RTEASYN(_)                         \
         SIGNAL_SET_LIST_RTEASYN_CPN1(_)                    \
         SIGNAL_SET_LIST_RTEASYN_CPN3(_)                    \
 */
/* get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
/* #define SIGNAL_GET_MAP_LIST_RTEASYN(_)                     \
         SIGNAL_GET_MAP_LIST_RTEASYN_CPN2(_)                \
         SIGNAL_GET_MAP_LIST_RTEASYN_CPN4(_)                \
 */

/***********************************************************
 * set get signal register.
 **********************************************************/
/* register set signals.
 **********************************************/
#define ASYN_SET_SIGNAL_REGISTER(signal_set,len)                SIGNAL_SET_REGISTER(RteAsynSigs,signal_set,len)
/* register get signals.
 **********************************************/
#define ASYN_GET_SIGNAL_REGISTER(signal_get,signal_set)         SIGNAL_GET_REGISTER(RteAsynSigs,signal_get,signal_set)

/***********************************************************
 * set get signal Blocks.
 **********************************************************/
/* get set signals maps.
 **********************************************/
SIGNAL_SETGET_MAP(RteAsynSigs,SIGNAL_SET_LIST_RTEASYN,SIGNAL_GET_MAP_LIST_RTEASYN);
/* Asynchronize signals initial function.
 **********************************************/
void RteAsynSetGetInit(void);
/* Asynchronize class declaration.
 **********************************************/
extern RteAsyn clRteAsynSigs;
/* Asynchronize macros.
 **********************************************/
#define ASYN_SET(sig,hdata) clRteAsynSigs.set(clRteAsynSigs.self,sig,(uint8*)(hdata))
#define ASYN_GET(sig,hdata) clRteAsynSigs.get(clRteAsynSigs.self,sig,(uint8*)(hdata))
#define ASYN_ADDR(sig,haddr) clRteAsynSigs.get(clRteAsynSigs.self,sig,(void **)(haddr))

#endif /*RTEASYNSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
