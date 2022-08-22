/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteSynSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:48:34
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef RTESYNSIGS_H_
#define RTESYNSIGS_H_

/* Include head files. */
#include "RteSigsConfigList.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define RTESYNSIGS_MACRO_VERSION        0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * trig serv signal list.
 **********************************************************/
/* serv signal list.
 **********************************************/
/* #define SIGNAL_SERV_LIST_RTESYN(_)                         \
         SIGNAL_SERV_LIST_RTESYN_ABI(_)                     \
         SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                  \
         SIGNAL_SERV_LIST_RTESYN_CPN1(_)                    \
         SIGNAL_SERV_LIST_RTESYN_CPN2(_)                    \
         SIGNAL_SERV_LIST_RTESYN_CPN3(_)                    \
         SIGNAL_SERV_LIST_RTESYN_CPN4(_)                    \
 */
/* trig signal list.
 * When configuring the signal, you need to check the length of the serv signal to map the signal.
 **********************************************/
/* #define SIGNAL_TRIG_MAP_LIST_RTESYN(_)                     \
         SIGNAL_TRIG_MAP_LIST_RTESYN_ABI(_)                 \
         SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)              \
         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN1(_)                \
         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN2(_)                \
         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN3(_)                \
         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN4(_)                \
 */

/***********************************************************
 * trig serv signal register.
 **********************************************************/
/* register serv signals.
 **********************************************/
#define SYN_SERV_SIGNAL_REGISTER(signal_serv,serv)                 SIGNAL_SERV_REGISTER(RteSynSigs,signal_serv,serv)
/* register trig signals.
 **********************************************/
#define SYN_TRIG_SIGNAL_REGISTER(signal_trig,signal_serv)          SIGNAL_TRIG_REGISTER(RteSynSigs,signal_trig,signal_serv)

/***********************************************************
 * trig serv signal Blocks.
 **********************************************************/
/* trig serv signals maps.
 **********************************************/
SIGNAL_SERVTRIG_MAP(RteSynSigs,SIGNAL_SERV_LIST_RTESYN,SIGNAL_TRIG_MAP_LIST_RTESYN);
/* Synchronize signals initial function.
 **********************************************/
void RetSynServTrigInit(void);
/* Synchronize class declaration.
 **********************************************/
void if_trig(synType signal, uint8 *buff);
/* Synchronize macros.
 **********************************************/
#define SYN_TRIG(sig,hdata) if_trig(sig, (uint8*)(hdata))

#endif /*RTESYNSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
