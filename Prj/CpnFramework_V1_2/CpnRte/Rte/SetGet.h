/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SetGet.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 07:34:13
* Description  :
* Others       :
* History      : 191222 pxf ���ν���
***************************************************************************/

#ifndef SETGET_H_
#define SETGET_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// �źŶ���
#define SIGNAL_SET_DEFINE(signal_set,len)                       signal_set,                                             //�����ź����ƶ���
#define SIGNAL_GET_DEFINE(signal_get,signal_set)                signal_get,                                             //�����ź����ƶ���
#define SIGNAL_SET_LEN_DEFINE(signal_set,len)                   signal_set##Len = len,                                  //�����źų��ȶ���
#define SIGNAL_GET_INDEX_MAP_DEFINE(signal_get,signal_set)      signal_get##Map = signal_set,                           //�����źŽ���ӳ��
#define SIGNAL_SET_LEN_ADD_DEFINE(signal_set,len)               +signal_set##Len                                        //�����źų��ȵ���
#define SIGNAL_SET_REGISTER(name,signal_set,len)                if(signal_set){name##SigSetIndex[signal_set] = (signal_set##Len+name##SigSetIndex[signal_set-1]);}\
                                                                else{name##SigSetIndex[signal_set] = signal_set##Len;}  //�����źŶ�Ӧ�����������ע��
#define SIGNAL_GET_REGISTER(name,signal_get,signal_set)         name##SigGetIndex[signal_get] = signal_get##Map;        //�����źŶ�Ӧ�����������ע��
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ���������ź��������
#define SIGNAL_SET_ENUM(name,list_set)                 \
enum name##SigSet{                                     \
    list_set(SIGNAL_SET_DEFINE)                        \
    name##SigSetMax                                    \
}
// ���������źŶ�Ӧ����
#define SIGNAL_SET_LEN_MAX(name,list_set)              (0 list_set(SIGNAL_SET_LEN_ADD_DEFINE))
#define SIGNAL_SET_LEN_ENUM(name,list_set)             \
enum name##SigSetLen{                                  \
    list_set(SIGNAL_SET_LEN_DEFINE)                    \
    name##SigSetLenMax                                 \
}

// �����ź�ӳ���ϵ
#define SIGNAL_SET_MAP(name,list_set)                  \
SIGNAL_SET_ENUM(name,list_set);                        \
SIGNAL_SET_LEN_ENUM(name,list_set)

// �����źŴ洢����
#define BUFF_SET_DEFINE(name,list_set)                 \
static uint16 name##SigSetIndex[name##SigSetMax];             \
static uint8 name##SigSetBuff[SIGNAL_SET_LEN_MAX(name,list_set)]
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ���������ź��������
#define SIGNAL_GET_MAP_ENUM(name,list_get)             \
enum name##SigGet{                                     \
    list_get(SIGNAL_GET_DEFINE)                        \
    name##SigGetMax                                    \
}
// ���������źŶ�Ӧ����
#define SIGNAL_GET_INDEX_MAP_ENUM(name,list_get)       \
enum name##SigGetMap{                                  \
    list_get(SIGNAL_GET_INDEX_MAP_DEFINE)              \
    name##SigGetMapMax                                 \
}

// �����ź�ӳ���ϵ
#define SIGNAL_GET_MAP(name,list_get)                  \
SIGNAL_GET_MAP_ENUM(name,list_get);                    \
SIGNAL_GET_INDEX_MAP_ENUM(name,list_get)

// �����źŴ洢����
#define BUFF_GET_DEFINE(name,list_get)                 \
static uint16 name##SigGetIndex[name##SigGetMax]
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// �źŽ���ע��
#define SIGNALS_GETSET_REGISTER(list,signal_register)  do{ \
    list(signal_register)                              \
}while(0)

// �źŽ���ӳ��
#define SIGNAL_SETGET_MAP(name,list_set,list_get)      \
SIGNAL_SET_MAP(name,list_set);                         \
SIGNAL_GET_MAP(name,list_get)

// �źŴ洢����
#define BUFF_SETGET_DEFINE(name,list_set,list_get)     \
BUFF_SET_DEFINE(name,list_set);                        \
BUFF_GET_DEFINE(name,list_get)
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif /*SETGET_H_*/

/**************************** Copyright(C) pxf ****************************/
