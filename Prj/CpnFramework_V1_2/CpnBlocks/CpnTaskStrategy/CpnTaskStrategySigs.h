/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategySigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy组件信号声明头文件
* Others       :
* History      : 201218 pxf 初次建立
***************************************************************************/

#ifndef CPNTASKSTRATEGYSIGS_H_
#define CPNTASKSTRATEGYSIGS_H_

/*头文件包含*/
#include "../../cpnRte/Rte/Rte.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNTASKSTRATEGYSIGS_MACRO_VERSION 0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
// typedef uint16 (*condition)(void); /* true/false */
typedef struct {
    strategy strgMask;
    uint16 addTime;
    uint16 delTime;
} strgDelayUpdate, *hstrgDelayUpdate;
typedef struct {
    strategy strgMask;
    condition cond;
} strgCondUpdate, *hstrgCondUpdate;



/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnTaskStrategy_init(void);
/*延时更新任务组服务
***********************************************/
void serv_CpnTaskStrategy_delayUpdate(void *buff);
/*条件更新任务组服务
***********************************************/
void serv_CpnTaskStrategy_condUpdate(void *buff);


/*接口触发
***********************************************/
//void trig_CpnTaskStrategy_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNTASKSTRATEGY(_)         \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNTASKSTRATEGY(_)     \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNTASKSTRATEGY(_)         \
    _(sig_serv_CpnTaskStrategy_init,serv_CpnTaskStrategy_init) \
    _(sig_serv_CpnTaskStrategy_delayUpdate,serv_CpnTaskStrategy_delayUpdate) \
    _(sig_serv_CpnTaskStrategy_condUpdate,serv_CpnTaskStrategy_condUpdate) \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTASKSTRATEGY(_)     \
    _(sig_trig_CpnTaskStrategy_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnTaskStrategy_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnTaskStrategy_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnTaskStrategy_delay,sig_serv_CpnSch_delay)\
    _(sig_trig_CpnTaskStrategy_now,sig_serv_CpnSch_now)    \
    _(sig_trig_CpnTaskStrategy_setMonitor,sig_serv_CpnSch_setMonitor) \
    _(sig_trig_CpnTaskStrategy_getMonitor,sig_serv_CpnSch_getMonitor) \
    _(sig_trig_CpnTaskStrategy_updateStrategy,sig_serv_CpnSch_updateStrategy) \
    _(sig_trig_CpnTaskStrategy_getStrategy,sig_serv_serv_CpnSch_getStrategy) \
    _(sig_trig_CpnTaskStrategy_getTaskNum,sig_serv_serv_CpnSch_getTaskNum) \
    _(sig_trig_CpnTaskStrategy_setErr,sig_serv_CpnErr_setErr) \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnTaskStrategy(void);

#endif /*CPNTASKSTRATEGYSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
