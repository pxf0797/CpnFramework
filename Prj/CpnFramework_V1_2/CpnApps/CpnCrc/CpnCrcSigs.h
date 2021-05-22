/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCrcSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/26 15:14:48
* Description  : CpnCrc组件信号声明头文件
* Others       :
* History      : 201126 pxf 初次建立
***************************************************************************/

#ifndef CPNCRCSIGS_H_
#define CPNCRCSIGS_H_

/*头文件包含*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNCRCSIGS_MACRO_VERSION        0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
    uint8* s;
    uint32 len;
    uint32 crc;
} TS_CRC_DATA, *hTS_CRC_DATA;



/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnCrc_init(void);
/*服务
***********************************************/
void serv_CpnCrc_getCrc8(void *buff);
/*服务
***********************************************/
void serv_CpnCrc_getCrc16(void *buff);
/*服务
***********************************************/
void serv_CpnCrc_getCrc32(void *buff);

/*接口触发
***********************************************/
//void trig_CpnCrc_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNCRC(_)                  \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNCRC(_)              \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNCRC(_)                  \
    _(sig_serv_CpnCrc_init,serv_CpnCrc_init)               \
    _(sig_serv_CpnCrc_getCrc8,serv_CpnCrc_getCrc8)         \
    _(sig_serv_CpnCrc_getCrc16,serv_CpnCrc_getCrc16)       \
    _(sig_serv_CpnCrc_getCrc32,serv_CpnCrc_getCrc32)       \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCRC(_)              \
    _(sig_trig_CpnCrc_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnCrc_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnCrc_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnCrc_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnCrc_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnCrc(void);

#endif /*CPNCRCSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
