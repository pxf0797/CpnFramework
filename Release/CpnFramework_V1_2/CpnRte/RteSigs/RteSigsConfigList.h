/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSigsConfigList.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/02/26 10:34:30
* Description  :
* Others       :
* History      : 200226 pxf ���ν���
***************************************************************************/

#ifndef RTESIGSCONFIGLIST_H_
#define RTESIGSCONFIGLIST_H_

/*ͷ�ļ�����*/
#include "../Rte/Rte.h"

/*����ź�*/
#include "../../Abi/AbiSigs.h"
#include "../../CpnBasics/CpnSch/CpnSchSigs.h"
#include "../../CpnBasics/CpnErr/CpnErrSigs.h"
#include "../../CpnBlocks/CpnSource/CpnSourceSigs.h"
#include "../../CpnBlocks/CpnSinks/CpnSinksSigs.h"
#include "../../CpnApps/CpnCan/CpnCanSigs.h"
#include "../../CpnApps/CpnTest/CpnTestSigs.h"
#include "../../CpnApps/CpnSourceTest/CpnSourceTestSigs.h"
#include "../../CpnApps/CpnSinksTest/CpnSinksTestSigs.h"
#include "../../CpnBlocks/CpnFrameMatrix/CpnFrameMatrixSigs.h"
#include "../../CpnBlocks/CpnMatrixMap/CpnMatrixMapSigs.h"
#include "../../CpnApps/CpnCrc/CpnCrcSigs.h"
#include "../../CpnApps/CpnMatrixMapTest/CpnMatrixMapTestSigs.h"
#include "../../CpnApps/CpnMem/CpnMemSigs.h"
#include "../../CpnApps/CpnMemTest/CpnMemTestSigs.h"
#include "../../CpnBlocks/CpnCal/CpnCalSigs.h"
#include "../../CpnBlocks/CpnTaskStrategy/CpnTaskStrategySigs.h"
#include "../../CpnApps/CpnTaskCtrl/CpnTaskCtrlSigs.h"

/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN(_)                         \
        SIGNAL_SET_LIST_RTEASYN_CPNSCH(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNERR(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNSOURCE(_)               \
        SIGNAL_SET_LIST_RTEASYN_CPNSINKS(_)                \
        SIGNAL_SET_LIST_RTEASYN_CPNCAN(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNTEST(_)                 \
        SIGNAL_SET_LIST_RTEASYN_CPNSOURCETEST(_)           \
        SIGNAL_SET_LIST_RTEASYN_CPNSINKSTEST(_)            \
        SIGNAL_SET_LIST_RTEASYN_CPNFRAMEMATRIX(_)          \
        SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAP(_)            \
        SIGNAL_SET_LIST_RTEASYN_CPNCRC(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAPTEST(_)        \
        SIGNAL_SET_LIST_RTEASYN_CPNMEM(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNMEMTEST(_)              \
        SIGNAL_SET_LIST_RTEASYN_CPNCAL(_)                  \
        SIGNAL_SET_LIST_RTEASYN_CPNTASKSTRATEGY(_)         \
        SIGNAL_SET_LIST_RTEASYN_CPNTASKCTRL(_)             \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN(_)                     \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSCH(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNERR(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCE(_)           \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKS(_)            \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNCAN(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNTEST(_)             \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCETEST(_)       \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKSTEST(_)        \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNFRAMEMATRIX(_)      \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAP(_)        \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNCRC(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAPTEST(_)    \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEM(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEMTEST(_)          \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNCAL(_)              \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNTASKSTRATEGY(_)     \
        SIGNAL_GET_MAP_LIST_RTEASYN_CPNTASKCTRL(_)         \

/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN(_)                         \
        SIGNAL_SERV_LIST_RTESYN_ABI(_)                     \
        SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNERR(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNSOURCE(_)               \
        SIGNAL_SERV_LIST_RTESYN_CPNSINKS(_)                \
        SIGNAL_SERV_LIST_RTESYN_CPNCAN(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNTEST(_)                 \
        SIGNAL_SERV_LIST_RTESYN_CPNSOURCETEST(_)           \
        SIGNAL_SERV_LIST_RTESYN_CPNSINKSTEST(_)            \
        SIGNAL_SERV_LIST_RTESYN_CPNFRAMEMATRIX(_)          \
        SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAP(_)            \
        SIGNAL_SERV_LIST_RTESYN_CPNCRC(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAPTEST(_)        \
        SIGNAL_SERV_LIST_RTESYN_CPNMEM(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNMEMTEST(_)              \
        SIGNAL_SERV_LIST_RTESYN_CPNCAL(_)                  \
        SIGNAL_SERV_LIST_RTESYN_CPNTASKSTRATEGY(_)         \
        SIGNAL_SERV_LIST_RTESYN_CPNTASKCTRL(_)             \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN(_)                     \
        SIGNAL_TRIG_MAP_LIST_RTESYN_ABI(_)                 \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNERR(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCE(_)           \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKS(_)            \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCAN(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTEST(_)             \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCETEST(_)       \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKSTEST(_)        \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNFRAMEMATRIX(_)      \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAP(_)        \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCRC(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAPTEST(_)    \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEM(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEMTEST(_)          \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCAL(_)              \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTASKSTRATEGY(_)     \
        SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTASKCTRL(_)         \



#endif /*RTESIGSCONFIGLIST_H_*/

/**************************** Copyright(C) pxf ****************************/
