/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : TriggerService.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 08:25:43
* Description  :
* Others       :
* History      : 191222 pxf ���ν���
***************************************************************************/

#ifndef TRIGGERSERVICE_H_
#define TRIGGERSERVICE_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// �źŶ���
#define SIGNAL_SERV_DEFINE(signal_serv,serv)                        signal_serv,                                          // �����ź����ƶ���
#define SIGNAL_TRIG_DEFINE(signal_trig,signal_serv)                 signal_trig,                                          // �����ź����ƶ���
#define SIGNAL_SERV_SERV_DEFINE(signal_serv,serv)                   signal_serv##Serv = serv,                             // �����źŹ�������
#define SIGNAL_TRIG_INDEX_MAP_DEFINE(signal_trig,signal_serv)       signal_trig##Map = signal_serv,                       // �����ź�ӳ������ź�
#define SIGNAL_SERV_REGISTER(name,signal_serv,serv)                 name##SigServBuff[signal_serv] = (void*)serv;         // �����źŽ���ע��
#define SIGNAL_TRIG_REGISTER(name,signal_trig,signal_serv)          name##SigTrigIndex[signal_trig] = signal_trig##Map;   // �����źŽ���ע��

typedef void (*serv_void)(void);
typedef void (*serv_param)(void * buff);

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ���������ź��������
#define SIGNAL_SERV_ENUM(name,list_serv)                        \
enum name##SigServ{                                             \
    list_serv(SIGNAL_SERV_DEFINE)                               \
    name##SigServMax                                            \
};                                                              \
extern void * name##SigServBuff[name##SigServMax]

// �����ź�ӳ���ϵ
#define SIGNAL_SERV_MAP(name,list_serv)                         \
SIGNAL_SERV_ENUM(name,list_serv)

// �����źŴ洢����
#define BUFF_SERV_DEFINE(name,list_serv)                        \
void * name##SigServBuff[name##SigServMax]

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ���������ź��������
#define SIGNAL_TRIG_ENUM(name,list_trig)                        \
enum name##SigTrig{                                             \
    list_trig(SIGNAL_TRIG_DEFINE)                               \
    name##SigTrigMax                                            \
};                                                              \
extern uint16 name##SigTrigIndex[name##SigTrigMax]

// ���������źŶ�Ӧ�����ź�
#define SIGNAL_TRIG_INDEX_MAP_ENUM(name,list_trig)              \
enum name##SigTrigMap{                                          \
    list_trig(SIGNAL_TRIG_INDEX_MAP_DEFINE)                     \
    name##SigTrigMapMax                                         \
}

// �����ź�ӳ���ϵ
#define SIGNAL_TRIG_MAP(name,list_trig)                         \
SIGNAL_TRIG_ENUM(name,list_trig);                               \
SIGNAL_TRIG_INDEX_MAP_ENUM(name,list_trig)

// �����źŴ洢����
#define BUFF_TRIG_DEFINE(name,list_trig)                        \
uint16 name##SigTrigIndex[name##SigTrigMax]
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// �źŽ���ע��
#define SIGNALS_SERVTRIG_REGISTER(list,signal_register)  do{    \
    list(signal_register)                                       \
}while(0)

// �źŽ���ӳ��
#define SIGNAL_SERVTRIG_MAP(name,list_serv,list_trig)           \
SIGNAL_SERV_MAP(name,list_serv);                                \
SIGNAL_TRIG_MAP(name,list_trig)

// �źŴ洢����
#define BUFF_SERVTRIG_DEFINE(name,list_serv,list_trig)          \
BUFF_SERV_DEFINE(name,list_serv);                               \
BUFF_TRIG_DEFINE(name,list_trig)

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif /*TRIGGERSERVICE_H_*/

/**************************** Copyright(C) pxf ****************************/
