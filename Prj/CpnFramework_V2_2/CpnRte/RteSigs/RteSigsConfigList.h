/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteSigsConfigList.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:49:01
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef RTESIGSCONFIGLIST_H_
#define RTESIGSCONFIGLIST_H_

/* Include head files. */
#include "Rte.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define RTESIGSCONFIGLIST_MACRO_VERSION 0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/* Component signals */
#include "AbiSigs.h"
#include "CpnSchSigs.h"
#include "CpnErrSigs.h"
#include "CpnSourceSigs.h"
#include "CpnSinksSigs.h"
#include "CpnTestSigs.h"
#include "CpnMemSigs.h"
#include "CpnSourceTestSigs.h"
#include "CpnSinksTestSigs.h"
#include "CpnCrcSigs.h"
#include "CpnMemTestSigs.h"
#include "CpnTaskStrategySigs.h"
#include "CpnTaskCtrlSigs.h"
#include "CpnInfoSigs.h"
#include "CpnAlarmSigs.h"
#include "CpnAlarmSourceSigs.h"
#include "CpnDataManaSigs.h"
#include "CpnDataManaTestSigs.h"

/***********************************************************
 * set get signal list.
 **********************************************************/
/* set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN(_)                                              \
        SIGNAL_SET_LIST_RTEASYN_CPNSCH(_)                                       \
        SIGNAL_SET_LIST_RTEASYN_CPNERR(_)                                       \
        SIGNAL_SET_LIST_RTEASYN_CPNSOURCE(_)                                    \
        SIGNAL_SET_LIST_RTEASYN_CPNSINKS(_)                                     \
        SIGNAL_SET_LIST_RTEASYN_CPNTEST(_)                                      \
        SIGNAL_SET_LIST_RTEASYN_CPNMEM(_)                                       \
        SIGNAL_SET_LIST_RTEASYN_CPNSOURCETEST(_)                                \
        SIGNAL_SET_LIST_RTEASYN_CPNSINKSTEST(_)                                 \
        SIGNAL_SET_LIST_RTEASYN_CPNCRC(_)                                       \
        SIGNAL_SET_LIST_RTEASYN_CPNMEMTEST(_)                                   \
        SIGNAL_SET_LIST_RTEASYN_CPNTASKSTRATEGY(_)                              \
        SIGNAL_SET_LIST_RTEASYN_CPNTASKCTRL(_)                                  \
        SIGNAL_SET_LIST_RTEASYN_CPNINFO(_)                                      \
        SIGNAL_SET_LIST_RTEASYN_CPNALARM(_)                                     \
        SIGNAL_SET_LIST_RTEASYN_CPNALARMSOURCE(_)                               \
        SIGNAL_SET_LIST_RTEASYN_CPNDATAMANA(_)                                  \
        SIGNAL_SET_LIST_RTEASYN_CPNDATAMANATEST(_)                              \

/* get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN(_)                                          \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSCH(_)                                   \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNERR(_)                                   \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCE(_)                                \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKS(_)                                 \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNTEST(_)                                  \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEM(_)                                   \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCETEST(_)                            \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKSTEST(_)                             \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNCRC(_)                                   \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEMTEST(_)                               \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNTASKSTRATEGY(_)                          \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNTASKCTRL(_)                              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNINFO(_)                                  \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNALARM(_)                                 \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNALARMSOURCE(_)                           \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNDATAMANA(_)                              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNDATAMANATEST(_)                          \

/***********************************************************
 * trig serv signal list.
 **********************************************************/
/* serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN(_)                                              \
        SIGNAL_SERV_LIST_RTESYN_ABI(_)                                          \
        SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                                       \
        SIGNAL_SERV_LIST_RTESYN_CPNERR(_)                                       \
        SIGNAL_SERV_LIST_RTESYN_CPNSOURCE(_)                                    \
        SIGNAL_SERV_LIST_RTESYN_CPNSINKS(_)                                     \
        SIGNAL_SERV_LIST_RTESYN_CPNTEST(_)                                      \
        SIGNAL_SERV_LIST_RTESYN_CPNMEM(_)                                       \
        SIGNAL_SERV_LIST_RTESYN_CPNSOURCETEST(_)                                \
        SIGNAL_SERV_LIST_RTESYN_CPNSINKSTEST(_)                                 \
        SIGNAL_SERV_LIST_RTESYN_CPNCRC(_)                                       \
        SIGNAL_SERV_LIST_RTESYN_CPNMEMTEST(_)                                   \
        SIGNAL_SERV_LIST_RTESYN_CPNTASKSTRATEGY(_)                              \
        SIGNAL_SERV_LIST_RTESYN_CPNTASKCTRL(_)                                  \
        SIGNAL_SERV_LIST_RTESYN_CPNINFO(_)                                      \
        SIGNAL_SERV_LIST_RTESYN_CPNALARM(_)                                     \
        SIGNAL_SERV_LIST_RTESYN_CPNALARMSOURCE(_)                               \
        SIGNAL_SERV_LIST_RTESYN_CPNDATAMANA(_)                                  \
        SIGNAL_SERV_LIST_RTESYN_CPNDATAMANATEST(_)                              \

/* trig signal list.
 * When configuring the signal, you need to check the length of the serv signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN(_)                                          \
        SIGNAL_TRIG_MAP_LIST_RTESYN_ABI(_)                                      \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)                                   \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNERR(_)                                   \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCE(_)                                \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKS(_)                                 \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTEST(_)                                  \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEM(_)                                   \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCETEST(_)                            \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKSTEST(_)                             \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCRC(_)                                   \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEMTEST(_)                               \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTASKSTRATEGY(_)                          \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTASKCTRL(_)                              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNINFO(_)                                  \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNALARM(_)                                 \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNALARMSOURCE(_)                           \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNDATAMANA(_)                              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNDATAMANATEST(_)                          \

#endif /*RTESIGSCONFIGLIST_H_*/

/**************************** Copyright(C) pxf ****************************/
