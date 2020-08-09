/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSchSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 21:27:20
* Description  :
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

#ifndef CPNSCHSIGS_H_
#define CPNSCHSIGS_H_

/*头文件包含*/
#include "../../CpnRte/Rte/Rte.h"
#include "./CpnSch.h"

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
* 信号数据类型一般来说都得强制定义一遍，否则很难知道信号对应数据是什么
***********************************************************/
/*服务数据类型
***********************************************/
/*添加任务服务参数
***********************************************/
typedef struct addTaskParam{
    uint16 level;
    task t;
    uint16 prdTick;
    uint16 startTick;
}addTaskParam, *haddTaskParam;
/*删除任务服务参数
***********************************************/
typedef struct delTaskParam{
    uint16 level;
    task t;
}delTaskParam, *hdelTaskParam;
/*延时服务参数
***********************************************/
typedef uint32 tick;
/*实时服务参数
***********************************************/
typedef uint16 point;



/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*添加任务服务
***********************************************/
void serv_CpnSch_addTask(void *buff);
/*删除任务服务
***********************************************/
void serv_CpnSch_delTask(void *buff);
/*延时服务
***********************************************/
void serv_CpnSch_delay(void *buff);
/*实时服务
***********************************************/
void serv_CpnSch_now(void *buff);
/*初始化服务
***********************************************/
void serv_CpnSch_init(void);
/*运行服务
***********************************************/
void serv_CpnSch_run(void);
/*步长服务
***********************************************/
void serv_CpnSch_tick(void);


/*读取实时接口触发
***********************************************/
void trig_CpnSch_inf_getTime(uint16 *point);
/*错误码接口触发
***********************************************/
void trig_CpnSch_inf_setErr(uint16 id, uint16 code);
/*初始化组件接口触发
***********************************************/
void trig_CpnSch_inf_initCpn(void);




/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSCH(_)                  \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSCH(_)              \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                  \
    _(sig_serv_CpnSch_addTask,serv_CpnSch_addTask)         \
    _(sig_serv_CpnSch_delTask,serv_CpnSch_delTask)         \
    _(sig_serv_CpnSch_delay,serv_CpnSch_delay)             \
    _(sig_serv_CpnSch_now,serv_CpnSch_now)                 \
    _(sig_serv_CpnSch_init,serv_CpnSch_init)               \
    _(sig_serv_CpnSch_run,serv_CpnSch_run)                 \
    _(sig_serv_CpnSch_tick,serv_CpnSch_tick)               \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)              \
    _(sig_trig_CpnSch_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnSch_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnSch_inf_getTime,sig_serv_Abi_getTime)    \
    _(sig_trig_CpnSch_inf_setErr,sig_serv_CpnErr_setErr)   \
    _(sig_trig_CpnSch_sendSig,sig_serv_CpnCan_sendSig)     \
    _(sig_trig_CpnErr_init,sig_serv_CpnErr_init)           \
    _(sig_trig_CpnSource_init,sig_serv_CpnSource_init)     \
    _(sig_trig_CpnSinks_init,sig_serv_CpnSinks_init)       \
    _(sig_trig_CpnTest_init,sig_serv_CpnTest_init)         \
    _(sig_trig_CpnCan_init,sig_serv_CpnCan_init)           \
    _(sig_trig_CpnSourceTest_init,sig_serv_CpnSourceTest_init) \
    _(sig_trig_CpnSinksTest_init,sig_serv_CpnSinksTest_init) \


/***********************************************************
* 组件运行任务
***********************************************************/
// void taskCpnSch(void);

#endif /*CPNSCHSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
