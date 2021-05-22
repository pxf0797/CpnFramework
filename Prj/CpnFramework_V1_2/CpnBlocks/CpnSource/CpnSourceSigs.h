/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  : CpnSource组件信号声明头文件
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

#ifndef CPNSOURCESIGS_H_
#define CPNSOURCESIGS_H_

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
typedef enum{
    w_sine,
    w_pluse,
    w_countUp,
    w_countDown,
    w_countUpDown,

    w_waveTypeMax
} tWaveType;
typedef struct{
    tWaveType type;                /* wave type */
    uint16 trig_sig;               /* service signal to be trigger */
    uint16 type_index;             /* grouped signale index */
    float32 amplitude;             /* amplitude */
    tick step;                     /* MS_T */
    tick period;                   /* MS_T */
    uint16 duty;                   /* 0.1% */
    uint16 phase;                  /* (0--3600)0.1 */
} tSourceParams, *htSourceParams;

/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnSource_init(void);
/*服务
***********************************************/
void serv_CpnSource_registWaveSig(void *buff);
/*服务
***********************************************/
void serv_CpnSource_changeWaveSig(void *buff);

/*接口触发
***********************************************/
//void trig_CpnSource_inf_infFunc(void);
/*错误码接口触发
***********************************************/
void trig_CpnSource_inf_setErr(uint16 id, uint16 code);


/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSOURCE(_)               \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCE(_)           \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSOURCE(_)               \
    _(sig_serv_CpnSource_init,serv_CpnSource_init)         \
    _(sig_serv_CpnSource_registWaveSig,serv_CpnSource_registWaveSig) \
    _(sig_serv_CpnSource_changeWaveSig,serv_CpnSource_changeWaveSig) \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCE(_)           \
    _(sig_trig_CpnSource_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSource_addTask,sig_serv_CpnSch_addTask)  \
    _(sig_trig_CpnSource_delTask,sig_serv_CpnSch_delTask)  \
    _(sig_trig_CpnSource_delay,sig_serv_CpnSch_delay)      \
    _(sig_trig_CpnSource_now,sig_serv_CpnSch_now)          \
    _(sig_trig_CpnSource_setErr,sig_serv_CpnErr_setErr)    \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnSource(void);

#endif /*CPNSOURCESIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
