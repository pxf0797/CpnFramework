/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 17:01:04
* Description  : CpnSourceTest组件信号声明头文件
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

#ifndef CPNSOURCETESTSIGS_H_
#define CPNSOURCETESTSIGS_H_

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
void serv_CpnSourceTest_init(void);
/*服务
***********************************************/
void serv_CpnSourceTest_sSine(void *buff);
/*服务
***********************************************/
void serv_CpnSourceTest_sPluse(void *buff);
/*服务
***********************************************/
void serv_CpnSourceTest_sCountUp(void *buff);
/*服务
***********************************************/
void serv_CpnSourceTest_sCountDown(void *buff);
/*服务
***********************************************/
void serv_CpnSourceTest_sCountUpDown(void *buff);
/*服务
***********************************************/
void serv_CpnSourceTest_sSine2(void *buff);
/*服务
***********************************************/
void serv_CpnSourceTest_sSine3(void *buff);
/*服务
***********************************************/
void serv_CpnSourceTest_sPluse2(void *buff);

/*接口触发
***********************************************/
//void trig_CpnSourceTest_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSOURCETEST(_)           \
    _(sig_set_CpnSourceTest_wOutput,sizeof(float32))       \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCETEST(_)       \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSOURCETEST(_)           \
    _(sig_serv_CpnSourceTest_init,serv_CpnSourceTest_init) \
    _(sig_serv_CpnSourceTest_sSine,serv_CpnSourceTest_sSine) \
    _(sig_serv_CpnSourceTest_sPluse,serv_CpnSourceTest_sPluse) \
    _(sig_serv_CpnSourceTest_sCountUp,serv_CpnSourceTest_sCountUp) \
    _(sig_serv_CpnSourceTest_sCountDown,serv_CpnSourceTest_sCountDown) \
    _(sig_serv_CpnSourceTest_sCountUpDown,serv_CpnSourceTest_sCountUpDown) \
    _(sig_serv_CpnSourceTest_sSine2,serv_CpnSourceTest_sSine2) \
    _(sig_serv_CpnSourceTest_sSine3,serv_CpnSourceTest_sSine3) \
    _(sig_serv_CpnSourceTest_sPluse2,serv_CpnSourceTest_sPluse2) \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCETEST(_)       \
    _(sig_trig_CpnSourceTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnSourceTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnSourceTest_delay,sig_serv_CpnSch_delay)  \
    _(sig_trig_CpnSourceTest_now,sig_serv_CpnSch_now)      \
    _(sig_trig_CpnSourceTest_setErr,sig_serv_CpnErr_setErr)\
    _(sig_trig_CpnSourceTest_registWaveSig,sig_serv_CpnSource_registWaveSig)\
    _(sig_trig_CpnSourceTest_changeWaveSig,sig_serv_CpnSource_changeWaveSig)\
    _(sig_trig_CpnSourceTest_sendSig,sig_serv_CpnCan_sendSig)\
    _(sig_trig_CpnSourceTest_sSine,sig_serv_CpnSourceTest_sSine) \
    _(sig_trig_CpnSourceTest_sSine2,sig_serv_CpnSourceTest_sSine2) \
    _(sig_trig_CpnSourceTest_sSine3,sig_serv_CpnSourceTest_sSine3) \
    _(sig_trig_CpnSourceTest_sPluse,sig_serv_CpnSourceTest_sPluse) \
    _(sig_trig_CpnSourceTest_sPluse2,sig_serv_CpnSourceTest_sPluse2) \
    _(sig_trig_CpnSourceTest_sCountUp,sig_serv_CpnSourceTest_sCountUp) \
    _(sig_trig_CpnSourceTest_sCountDown,sig_serv_CpnSourceTest_sCountDown) \
    _(sig_trig_CpnSourceTest_sCountUpDown,sig_serv_CpnSourceTest_sCountUpDown) \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnSourceTest(void);

#endif /*CPNSOURCETESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
