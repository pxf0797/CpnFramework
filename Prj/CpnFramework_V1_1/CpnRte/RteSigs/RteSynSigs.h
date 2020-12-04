/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSynSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:24
* Description  :
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

#ifndef RTESYNSIGS_H_
#define RTESYNSIGS_H_

/*头文件包含*/
#include "./RteSigsConfigList.h"

/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
// #define SIGNAL_SERV_LIST_RTESYN(_)                         \
//         SIGNAL_SERV_LIST_RTESYN_ABI(_)                     \
//         SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                  \
//         SIGNAL_SERV_LIST_RTESYN_CPN1(_)                    \
//         SIGNAL_SERV_LIST_RTESYN_CPN2(_)                    \
//         SIGNAL_SERV_LIST_RTESYN_CPN3(_)                    \
//         SIGNAL_SERV_LIST_RTESYN_CPN4(_)                    \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
// #define SIGNAL_TRIG_MAP_LIST_RTESYN(_)                     \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_ABI(_)                 \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)              \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN1(_)                \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN2(_)                \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN3(_)                \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN4(_)                \


/***********************************************************
* 注册trig serv信号
***********************************************************/
/*注册服务信号
***********************************************/
#define SYN_SERV_SIGNAL_REGISTER(signal_serv,serv)                 SIGNAL_SERV_REGISTER(RteSynSigs,signal_serv,serv)
/*注册触发信号
***********************************************/
#define SYN_TRIG_SIGNAL_REGISTER(signal_trig,signal_serv)          SIGNAL_TRIG_REGISTER(RteSynSigs,signal_trig,signal_serv)


/***********************************************************
* trig serv信号功能模块
***********************************************************/
/*建立服务触发信号映射
***********************************************/
SIGNAL_SERVTRIG_MAP(RteSynSigs,SIGNAL_SERV_LIST_RTESYN,SIGNAL_TRIG_MAP_LIST_RTESYN);
/*同步信号初始化函数
***********************************************/
void RetSynServTrigInit(void);
/*定义服务触发类
***********************************************/
extern RteSyn clRteSynSigs;

#endif /*RTESYNSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
