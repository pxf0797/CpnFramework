/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : TriggerService.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 08:25:43
* Description  :
* Others       :
* History      : 191222 pxf 初次建立
***************************************************************************/

#ifndef TRIGGERSERVICE_H_
#define TRIGGERSERVICE_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// 信号定义
#define SIGNAL_SERV_DEFINE(signal_serv,serv)                        signal_serv,                                          // 服务信号名称定义
#define SIGNAL_TRIG_DEFINE(signal_trig,signal_serv)                 signal_trig,                                          // 触发信号名称定义
#define SIGNAL_SERV_SERV_DEFINE(signal_serv,serv)                   signal_serv##Serv = serv,                             // 服务信号关联服务
#define SIGNAL_TRIG_INDEX_MAP_DEFINE(signal_trig,signal_serv)       signal_trig##Map = signal_serv,                       // 触发信号映射服务信号
#define SIGNAL_SERV_REGISTER(name,signal_serv,serv)                 name##SigServBuff[signal_serv] = (void*)serv;         // 服务信号进行注册
#define SIGNAL_TRIG_REGISTER(name,signal_trig,signal_serv)          name##SigTrigIndex[signal_trig] = signal_trig##Map;   // 触发信号进行注册

typedef void (*serv_void)(void);
typedef void (*serv_param)(void * buff);

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 建立服务信号索引编号
#define SIGNAL_SERV_ENUM(name,list_serv)                        \
enum name##SigServ{                                             \
    list_serv(SIGNAL_SERV_DEFINE)                               \
    name##SigServMax                                            \
};                                                              \
extern void * name##SigServBuff[name##SigServMax]

// 服务信号映射关系
#define SIGNAL_SERV_MAP(name,list_serv)                         \
SIGNAL_SERV_ENUM(name,list_serv)

// 发送信号存储定义
#define BUFF_SERV_DEFINE(name,list_serv)                        \
void * name##SigServBuff[name##SigServMax]

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 建立触发信号索引编号
#define SIGNAL_TRIG_ENUM(name,list_trig)                        \
enum name##SigTrig{                                             \
    list_trig(SIGNAL_TRIG_DEFINE)                               \
    name##SigTrigMax                                            \
};                                                              \
extern uint16 name##SigTrigIndex[name##SigTrigMax]

// 建立触发信号对应服务信号
#define SIGNAL_TRIG_INDEX_MAP_ENUM(name,list_trig)              \
enum name##SigTrigMap{                                          \
    list_trig(SIGNAL_TRIG_INDEX_MAP_DEFINE)                     \
    name##SigTrigMapMax                                         \
}

// 触发信号映射关系
#define SIGNAL_TRIG_MAP(name,list_trig)                         \
SIGNAL_TRIG_ENUM(name,list_trig);                               \
SIGNAL_TRIG_INDEX_MAP_ENUM(name,list_trig)

// 触发信号存储定义
#define BUFF_TRIG_DEFINE(name,list_trig)                        \
uint16 name##SigTrigIndex[name##SigTrigMax]
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 信号进行注册
#define SIGNALS_SERVTRIG_REGISTER(list,signal_register)  do{    \
    list(signal_register)                                       \
}while(0)

// 信号建立映射
#define SIGNAL_SERVTRIG_MAP(name,list_serv,list_trig)           \
SIGNAL_SERV_MAP(name,list_serv);                                \
SIGNAL_TRIG_MAP(name,list_trig)

// 信号存储定义
#define BUFF_SERVTRIG_DEFINE(name,list_serv,list_trig)          \
BUFF_SERV_DEFINE(name,list_serv);                               \
BUFF_TRIG_DEFINE(name,list_trig)

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif /*TRIGGERSERVICE_H_*/

/**************************** Copyright(C) pxf ****************************/
