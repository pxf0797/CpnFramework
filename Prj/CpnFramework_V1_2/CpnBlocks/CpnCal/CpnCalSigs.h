/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:06:36
* Description  : CpnCal组件信号声明头文件
* Others       :
* History      : 201212 pxf 初次建立
***************************************************************************/

#ifndef CPNCALSIGS_H_
#define CPNCALSIGS_H_

/*头文件包含*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNCALSIGS_MACRO_VERSION        0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
void serv_CpnCal_init(void);
/*服务
***********************************************/
void serv_CpnCal_getCtrlBits(void);
/*服务
***********************************************/
void serv_CpnCal_getCmdBits(void);
/*服务
***********************************************/
void serv_CpnCal_getFrameLen(void);
/*服务
***********************************************/
void serv_CpnCal_getByte(void);
/*服务
***********************************************/
void serv_CpnCal_setCtrlBits(void);
/*服务
***********************************************/
void serv_CpnCal_setCmdBits(void);
/*服务
***********************************************/
void serv_CpnCal_setFrameLen(void);
/*服务
***********************************************/
void serv_CpnCal_setByte(void);

/*接口触发
***********************************************/
//void trig_CpnCal_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNCAL(_)                  \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNCAL(_)              \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNCAL(_)                  \
    _(sig_serv_CpnCal_init,serv_CpnCal_init)               \
    _(sig_serv_CpnCal_getCtrlBits,serv_CpnCal_getCtrlBits) \
    _(sig_serv_CpnCal_getCmdBits,serv_CpnCal_getCmdBits)   \
    _(sig_serv_CpnCal_getFrameLen,serv_CpnCal_getFrameLen) \
    _(sig_serv_CpnCal_getByte,serv_CpnCal_getByte)         \
    _(sig_serv_CpnCal_setCtrlBits,serv_CpnCal_setCtrlBits) \
    _(sig_serv_CpnCal_setCmdBits,serv_CpnCal_setCmdBits)   \
    _(sig_serv_CpnCal_setFrameLen,serv_CpnCal_setFrameLen) \
    _(sig_serv_CpnCal_setByte,serv_CpnCal_setByte)         \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCAL(_)              \
    _(sig_trig_CpnCal_initTask,sig_serv_CpnSch_initTask)   \
    _(sig_trig_CpnCal_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnCal_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnCal_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnCal_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnCal_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnCal(void);

#endif /*CPNCALSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
