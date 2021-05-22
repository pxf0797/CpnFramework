/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsynSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:12
* Description  :
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

#ifndef RTEASYNSIGS_H_
#define RTEASYNSIGS_H_

/*ͷ�ļ�����*/
#include "./RteSigsConfigList.h"


/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
// #define SIGNAL_SET_LIST_RTEASYN(_)                         \
//         SIGNAL_SET_LIST_RTEASYN_CPN1(_)                    \
//         SIGNAL_SET_LIST_RTEASYN_CPN3(_)                    \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
// #define SIGNAL_GET_MAP_LIST_RTEASYN(_)                     \
//         SIGNAL_GET_MAP_LIST_RTEASYN_CPN2(_)                \
//         SIGNAL_GET_MAP_LIST_RTEASYN_CPN4(_)                \


/***********************************************************
* ע��get set�ź�
***********************************************************/
/*ע�ᷢ���ź�
***********************************************/
#define ASYN_SET_SIGNAL_REGISTER(signal_set,len)                SIGNAL_SET_REGISTER(RteAsynSigs,signal_set,len)
/*ע������ź�
***********************************************/
#define ASYN_GET_SIGNAL_REGISTER(signal_get,signal_set)         SIGNAL_GET_REGISTER(RteAsynSigs,signal_get,signal_set)

/***********************************************************
* get set�źŹ���ģ��
***********************************************************/
/*�����շ��źŸ���ӳ���ϵ
***********************************************/
SIGNAL_SETGET_MAP(RteAsynSigs,SIGNAL_SET_LIST_RTEASYN,SIGNAL_GET_MAP_LIST_RTEASYN);
/*�첽�źų�ʼ������
***********************************************/
void RteAsynSetGetInit(void);
/*�����շ���
***********************************************/
extern RteAsyn clRteAsynSigs;

#endif /*RTEASYNSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
