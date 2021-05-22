/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  : CpnSinks组件信号声明头文件
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

#ifndef CPNSINKSSIGS_H_
#define CPNSINKSSIGS_H_

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
    uint16 trig_getSig;            /* service signal to be trigger, to get data */
    uint16 trig_endSig;            /* service signal to be trigger, to inform cache full */
    uint16 type_index;             /* grouped signale index */
    tick period;                   /* MS_T */
    uint16 data_size;              /* sizeof data */
    uint16 buff_size;              /* sizeof data buff */
    void *buff;                    /* cache data buffer */
} tSinksParams, *htSinksParams;
typedef struct{
    htSinksParams sinks;           /* sinks */
    uint16 outOperation;           /* out operation result, TRUE/FALSE */
    void *buff;                    /* read out data buffer */
} tSinksOut, *htSinksOut;
typedef enum{
    cacheNotStart,
    cacheCaching,
    cacheFull
} tCacheProcessSta;
typedef struct{
    htSinksParams sinks;           /* sinks */
    tCacheProcessSta sta;          /* sinks state */
} tSinksSta, *htSinksSta;

/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnSinks_init(void);
/*服务
***********************************************/
void serv_CpnSinks_readData(void *buff);
/*服务
***********************************************/
void serv_CpnSinks_trigStart(void *buff);
/*服务
***********************************************/
void serv_CpnSinks_cacheSta(void *buff);
/*服务
***********************************************/
void serv_CpnSinks_registCache(void *buff);
/*服务
***********************************************/
void serv_CpnSinks_reCache(void *buff);

/*接口触发
***********************************************/
//void trig_CpnSinks_inf_infFunc(void);
/*错误码接口触发
***********************************************/
void trig_CpnSinks_inf_setErr(uint16 id, uint16 code);


/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSINKS(_)                \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKS(_)            \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSINKS(_)                \
    _(sig_serv_CpnSinks_init,serv_CpnSinks_init)           \
    _(sig_serv_CpnSinks_readData,serv_CpnSinks_readData)   \
    _(sig_serv_CpnSinks_trigStart,serv_CpnSinks_trigStart) \
    _(sig_serv_CpnSinks_cacheSta,serv_CpnSinks_cacheSta)   \
    _(sig_serv_CpnSinks_registCache,serv_CpnSinks_registCache) \
    _(sig_serv_CpnSinks_reCache,serv_CpnSinks_reCache)     \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKS(_)            \
    _(sig_trig_CpnSinks_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSinks_addTask,sig_serv_CpnSch_addTask)   \
    _(sig_trig_CpnSinks_delTask,sig_serv_CpnSch_delTask)   \
    _(sig_trig_CpnSinks_delay,sig_serv_CpnSch_delay)       \
    _(sig_trig_CpnSinks_now,sig_serv_CpnSch_now)           \
    _(sig_trig_CpnSinks_setErr,sig_serv_CpnErr_setErr)     \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnSinks(void);

#endif /*CPNSINKSSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
