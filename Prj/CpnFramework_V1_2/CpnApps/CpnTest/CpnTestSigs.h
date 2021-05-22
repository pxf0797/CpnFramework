/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/23 17:26:23
* Description  : CpnTest组件信号声明头文件
* Others       :
* History      : 200723 pxf 初次建立
***************************************************************************/

#ifndef CPNTESTSIGS_H_
#define CPNTESTSIGS_H_

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



/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnTest_init(void);
/*服务
***********************************************/
void serv_CpnTest_servSig1(void);
/*服务
***********************************************/
void serv_CpnTest_servSig2_uint16(void *buff);

/*接口触发
***********************************************/
//void trig_CpnTest_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNTEST(_)                 \
    _(sig_set_CpnTest_sendSig1_uint8,sizeof(uint8))        \
    _(sig_set_CpnTest_SendSig2_uint32,sizeof(uint32))      \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNTEST(_)             \
    _(sig_get_CpnTest_receiveSig1_uint32,sig_set_CpnTest_SendSig2_uint32) \
    _(sig_get_CpnTest_receiveSig2_uint8,sig_set_CpnTest_sendSig1_uint8) \


/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNTEST(_)                 \
    _(sig_serv_CpnTest_init,serv_CpnTest_init)             \
    _(sig_serv_CpnTest_servSig1,serv_CpnTest_servSig1)     \
    _(sig_serv_CpnTest_servSig2_uint16,serv_CpnTest_servSig2_uint16) \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTEST(_)             \
    _(sig_trig_CpnTest_initTask,sig_serv_CpnSch_initTask)  \
    _(sig_trig_CpnTest_addTask,sig_serv_CpnSch_addTask)    \
    _(sig_trig_CpnTest_delTask,sig_serv_CpnSch_delTask)    \
    _(sig_trig_CpnTest_delay,sig_serv_CpnSch_delay)        \
    _(sig_trig_CpnTest_now,sig_serv_CpnSch_now)            \
    _(sig_trig_CpnTest_setErr,sig_serv_CpnErr_setErr)      \
    _(sig_trig_CpnTest_trigSig1_uint16,sig_serv_CpnTest_servSig2_uint16) \
    _(sig_trig_CpnTest_trigSig2,sig_serv_CpnTest_servSig1) \
    _(sig_trig_CpnTest_sendSig,sig_serv_CpnCan_sendSig)    \

/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnTest(void);

#endif /*CPNTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
