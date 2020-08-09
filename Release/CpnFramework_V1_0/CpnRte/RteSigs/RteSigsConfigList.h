/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSigsConfigList.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/02/26 10:34:30
* Description  :
* Others       :
* History      : 200226 pxf 初次建立
***************************************************************************/

#ifndef RTESIGSCONFIGLIST_H_
#define RTESIGSCONFIGLIST_H_

/*头文件包含*/
#include "../Rte/Rte.h"

/*组件信号*/
#include "../../Abi/AbiSigs.h"
#include "../../CpnBasics/CpnSch/CpnSchSigs.h"
#include "../../CpnBasics/CpnErr/CpnErrSigs.h"
#include "../../CpnBlocks/CpnSource/CpnSourceSigs.h"
#include "../../CpnBlocks/CpnSinks/CpnSinksSigs.h"
#include "../../CpnApps/CpnTest/CpnTestSigs.h"
#include "../../CpnApps/CpnCan/CpnCanSigs.h"
#include "../../CpnApps/CpnSourceTest/CpnSourceTestSigs.h"
#include "../../CpnApps/CpnSinksTest/CpnSinksTestSigs.h"

/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN(_)                         \
        SIGNAL_SET_LIST_RTEASYN_CPNSCH(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNERR(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNSOURCE(_)               \
        SIGNAL_SET_LIST_RTEASYN_CPNSINKS(_)                \
        SIGNAL_SET_LIST_RTEASYN_CPNTEST(_)                 \
        SIGNAL_SET_LIST_RTEASYN_CPNCAN(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNSOURCETEST(_)           \
        SIGNAL_SET_LIST_RTEASYN_CPNSINKSTEST(_)            \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN(_)                     \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSCH(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNERR(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCE(_)           \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKS(_)            \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNTEST(_)             \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNCAN(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCETEST(_)       \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKSTEST(_)        \

/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN(_)                         \
        SIGNAL_SERV_LIST_RTESYN_ABI(_)                     \
        SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNERR(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNSOURCE(_)               \
        SIGNAL_SERV_LIST_RTESYN_CPNSINKS(_)                \
        SIGNAL_SERV_LIST_RTESYN_CPNTEST(_)                 \
        SIGNAL_SERV_LIST_RTESYN_CPNCAN(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNSOURCETEST(_)           \
        SIGNAL_SERV_LIST_RTESYN_CPNSINKSTEST(_)            \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN(_)                     \
        SIGNAL_TRIG_MAP_LIST_RTESYN_ABI(_)                 \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNERR(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCE(_)           \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKS(_)            \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTEST(_)             \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCAN(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCETEST(_)       \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKSTEST(_)        \



#endif /*RTESIGSCONFIGLIST_H_*/

/**************************** Copyright(C) pxf ****************************/
