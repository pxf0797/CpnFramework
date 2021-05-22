/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SetGet.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 07:34:13
* Description  :
* Others       :
* History      : 191222 pxf 初次建立
***************************************************************************/

#ifndef SETGET_H_
#define SETGET_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 信号定义
#define SIGNAL_SET_DEFINE(signal_set,len)                       signal_set,                                             //发送信号名称定义
#define SIGNAL_GET_DEFINE(signal_get,signal_set)                signal_get,                                             //接收信号名称定义
#define SIGNAL_SET_LEN_DEFINE(signal_set,len)                   signal_set##Len = len,                                  //发送信号长度定义
#define SIGNAL_GET_INDEX_MAP_DEFINE(signal_get,signal_set)      signal_get##Map = signal_set,                           //接收信号进行映射
#define SIGNAL_SET_LEN_ADD_DEFINE(signal_set,len)               +signal_set##Len                                        //发送信号长度叠加
#define SIGNAL_SET_REGISTER(name,signal_set,len)                if(signal_set){name##SigSetIndex[signal_set] = (signal_set##Len+name##SigSetIndex[signal_set-1]);}\
                                                                else{name##SigSetIndex[signal_set] = signal_set##Len;}  //发送信号对应长度数组进行注册
#define SIGNAL_GET_REGISTER(name,signal_get,signal_set)         name##SigGetIndex[signal_get] = signal_get##Map;        //接收信号对应长度数组进行注册
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 建立发送信号索引编号
#define SIGNAL_SET_ENUM(name,list_set)                 \
enum name##SigSet{                                     \
    list_set(SIGNAL_SET_DEFINE)                        \
    name##SigSetMax                                    \
}
// 建立发送信号对应长度
#define SIGNAL_SET_LEN_MAX(name,list_set)              (0 list_set(SIGNAL_SET_LEN_ADD_DEFINE))
#define SIGNAL_SET_LEN_ENUM(name,list_set)             \
enum name##SigSetLen{                                  \
    list_set(SIGNAL_SET_LEN_DEFINE)                    \
    name##SigSetLenMax                                 \
}

// 发送信号映射关系
#define SIGNAL_SET_MAP(name,list_set)                  \
SIGNAL_SET_ENUM(name,list_set);                        \
SIGNAL_SET_LEN_ENUM(name,list_set)

// 发送信号存储定义
#define BUFF_SET_DEFINE(name,list_set)                 \
static uint16 name##SigSetIndex[name##SigSetMax];             \
static uint8 name##SigSetBuff[SIGNAL_SET_LEN_MAX(name,list_set)]
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 建立接收信号索引编号
#define SIGNAL_GET_MAP_ENUM(name,list_get)             \
enum name##SigGet{                                     \
    list_get(SIGNAL_GET_DEFINE)                        \
    name##SigGetMax                                    \
}
// 建立接收信号对应长度
#define SIGNAL_GET_INDEX_MAP_ENUM(name,list_get)       \
enum name##SigGetMap{                                  \
    list_get(SIGNAL_GET_INDEX_MAP_DEFINE)              \
    name##SigGetMapMax                                 \
}

// 接收信号映射关系
#define SIGNAL_GET_MAP(name,list_get)                  \
SIGNAL_GET_MAP_ENUM(name,list_get);                    \
SIGNAL_GET_INDEX_MAP_ENUM(name,list_get)

// 接收信号存储定义
#define BUFF_GET_DEFINE(name,list_get)                 \
static uint16 name##SigGetIndex[name##SigGetMax]
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 信号进行注册
#define SIGNALS_GETSET_REGISTER(list,signal_register)  do{ \
    list(signal_register)                              \
}while(0)

// 信号建立映射
#define SIGNAL_SETGET_MAP(name,list_set,list_get)      \
SIGNAL_SET_MAP(name,list_set);                         \
SIGNAL_GET_MAP(name,list_get)

// 信号存储定义
#define BUFF_SETGET_DEFINE(name,list_set,list_get)     \
BUFF_SET_DEFINE(name,list_set);                        \
BUFF_GET_DEFINE(name,list_get)
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif /*SETGET_H_*/

/**************************** Copyright(C) pxf ****************************/
