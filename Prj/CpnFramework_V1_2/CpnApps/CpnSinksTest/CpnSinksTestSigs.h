/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 19:07:35
* Description  : CpnSinksTest组件信号声明头文件
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

#ifndef CPNSINKSTESTSIGS_H_
#define CPNSINKSTESTSIGS_H_

/*头文件包含*/
#include "../../CpnRte/Rte/Rte.h"

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
typedef struct{
    uint16 index;
    float32 data;
} tStoreData, *htStoreData;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnSinksTest_init(void);
/*服务
***********************************************/
void serv_CpnSinksTest_sIsFull(void);
/*服务
***********************************************/
void serv_CpnSinksTest_sGetData(void *buff);

/*接口触发
***********************************************/
//void trig_CpnSinksTest_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSINKSTEST(_)            \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKSTEST(_)        \
    _(sig_get_CpnSinksTest_wCache,sig_set_CpnSourceTest_wOutput) \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSINKSTEST(_)            \
    _(sig_serv_CpnSinksTest_init,serv_CpnSinksTest_init)   \
    _(sig_serv_CpnSinksTest_sIsFull,serv_CpnSinksTest_sIsFull) \
    _(sig_serv_CpnSinksTest_sGetData,serv_CpnSinksTest_sGetData) \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKSTEST(_)        \
    _(sig_trig_CpnSinksTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSinksTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnSinksTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnSinksTest_delay,sig_serv_CpnSch_delay)   \
    _(sig_trig_CpnSinksTest_now,sig_serv_CpnSch_now)       \
    _(sig_trig_CpnSinksTest_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnSinksTest_readData,sig_serv_CpnSinks_readData) \
    _(sig_trig_CpnSinksTest_trigStart,sig_serv_CpnSinks_trigStart) \
    _(sig_trig_CpnSinksTest_cacheSta,sig_serv_CpnSinks_cacheSta) \
    _(sig_trig_CpnSinksTest_registCache,sig_serv_CpnSinks_registCache) \
    _(sig_trig_CpnSinksTest_reCache,sig_serv_CpnSinks_reCache) \
    _(sig_trig_CpnSinksTest_sIsFull,sig_serv_CpnSinksTest_sIsFull) \
    _(sig_trig_CpnSinksTest_sGetData,sig_serv_CpnSinksTest_sGetData) \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnSinksTest(void);

#endif /*CPNSINKSTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
