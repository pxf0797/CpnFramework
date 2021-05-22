/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCanSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 16:09:24
* Description  : CpnCan组件信号声明头文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

#ifndef CPNCANSIGS_H_
#define CPNCANSIGS_H_

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
    uint16 id;
    uint32 data;
} tDataSig;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnCan_init(void);
/*服务
***********************************************/
void serv_CpnCan_sendSig(void *sig);
/*服务
***********************************************/
void serv_CpnCan_receiveSig(void *sig);

/*接口触发
***********************************************/
//void trig_CpnCan_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNCAN(_)                   \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNCAN(_)               \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNCAN(_)                   \
    _(sig_serv_CpnCan_init,serv_CpnCan_init)                \
    _(sig_serv_CpnCan_sendSig,serv_CpnCan_sendSig)          \
    _(sig_serv_CpnCan_receiveSig,serv_CpnCan_receiveSig)    \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCAN(_)               \
    _(sig_trig_CpnCan_initTask,sig_serv_CpnSch_initTask)    \
    _(sig_trig_CpnCan_addTask,sig_serv_CpnSch_addTask)      \
    _(sig_trig_CpnCan_delTask,sig_serv_CpnSch_delTask)      \
    _(sig_trig_CpnCan_delay,sig_serv_CpnSch_delay)          \
    _(sig_trig_CpnCan_now,sig_serv_CpnSch_now)              \
    _(sig_trig_CpnCan_setErr,sig_serv_CpnErr_setErr)        \
    _(sig_trig_CpnCan_sendSig,sig_serv_Abi_sendSig)         \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnCan(void);

#endif /*CPNCANSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
