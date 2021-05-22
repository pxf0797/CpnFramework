/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 20:32:16
* Description  : CpnMatrixMapTest组件信号声明头文件
* Others       :
* History      : 201202 pxf 初次建立
***************************************************************************/

#ifndef CPNMATRIXMAPTESTSIGS_H_
#define CPNMATRIXMAPTESTSIGS_H_

/*头文件包含*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNMATRIXMAPTESTSIGS_MACRO_VERSION 0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/***********************************************************
* get set 数据类型定义
* 一般只定义set数据，get类型引用当前头文件
* 只需要把发送的数据定义出来，收发接口使用的是统一接口，无其他定义
* 信号数据类型一般来说都得强制定义一遍，否则很难知道信号对应数据是什么
***********************************************************/
/*发送数据类型
***********************************************/



/***********************************************************
* serv trig 数据类型定义
* 一般只定义serv数据，trig类型引用当前头文件
* 只需要把发送的数据定义出来，收发接口使用的是统一接口，无其他定义
* 信号数据类型一般来说都得强制定义一遍，否则很难知道信号对应数据是什么
***********************************************************/
/*服务数据类型
***********************************************/



/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnMatrixMapTest_init(void);
/*服务
***********************************************/
// void serv_CpnMatrixMapTest_setDataA(void);
/*服务
***********************************************/
// void serv_CpnMatrixMapTest_getData1(void);

/*接口触发
***********************************************/
//void trig_CpnMatrixMapTest_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAPTEST(_)        \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAPTEST(_)    \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAPTEST(_)        \
    _(sig_serv_CpnMatrixMapTest_init,serv_CpnMatrixMapTest_init) \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAPTEST(_)    \
    _(sig_trig_CpnMatrixMapTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnMatrixMapTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMatrixMapTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMatrixMapTest_delay,sig_serv_CpnSch_delay) \
    _(sig_trig_CpnMatrixMapTest_now,sig_serv_CpnSch_now)   \
    _(sig_trig_CpnMatrixMapTest_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataA,matrixMapSet(ulDataA)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataB,matrixMapSet(ulDataB)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataC,matrixMapSet(ulDataC)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataD,matrixMapSet(ulDataD)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataE,matrixMapSet(ulDataE)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataF,matrixMapSet(ulDataF)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataG,matrixMapSet(ulDataG)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData1,matrixMapGet(ulData1)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData2,matrixMapGet(ulData2)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData3,matrixMapGet(ulData3)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData4,matrixMapGet(ulData4)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData5,matrixMapGet(ulData5)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData6,matrixMapGet(ulData6)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData7,matrixMapGet(ulData7)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData8,matrixMapGet(ulData8)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataA,matrixMapGet(ulDataA)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataB,matrixMapGet(ulDataB)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataC,matrixMapGet(ulDataC)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataD,matrixMapGet(ulDataD)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataE,matrixMapGet(ulDataE)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataF,matrixMapGet(ulDataF)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataG,matrixMapGet(ulDataG)) \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnMatrixMapTest(void);

#endif /*CPNMATRIXMAPTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
