/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsynSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:12
* Description  :
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

#ifndef RTEASYNSIGS_H_
#define RTEASYNSIGS_H_

/*头文件包含*/
#include "./RteSigsConfigList.h"


/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
// #define SIGNAL_SET_LIST_RTEASYN(_)                         \
//         SIGNAL_SET_LIST_RTEASYN_CPN1(_)                    \
//         SIGNAL_SET_LIST_RTEASYN_CPN3(_)                    \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
// #define SIGNAL_GET_MAP_LIST_RTEASYN(_)                     \
//         SIGNAL_GET_MAP_LIST_RTEASYN_CPN2(_)                \
//         SIGNAL_GET_MAP_LIST_RTEASYN_CPN4(_)                \


/***********************************************************
* 注册get set信号
***********************************************************/
/*注册发送信号
***********************************************/
#define ASYN_SET_SIGNAL_REGISTER(signal_set,len)                SIGNAL_SET_REGISTER(RteAsynSigs,signal_set,len)
/*注册接收信号
***********************************************/
#define ASYN_GET_SIGNAL_REGISTER(signal_get,signal_set)         SIGNAL_GET_REGISTER(RteAsynSigs,signal_get,signal_set)

/***********************************************************
* get set信号功能模块
***********************************************************/
/*建立收发信号各自映射关系
***********************************************/
SIGNAL_SETGET_MAP(RteAsynSigs,SIGNAL_SET_LIST_RTEASYN,SIGNAL_GET_MAP_LIST_RTEASYN);
/*异步信号初始化函数
***********************************************/
void RteAsynSetGetInit(void);
/*定义收发类
***********************************************/
extern RteAsyn clRteAsynSigs;

#endif /*RTEASYNSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
