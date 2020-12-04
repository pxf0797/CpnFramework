/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSynSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:24
* Description  :
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

#ifndef RTESYNSIGS_H_
#define RTESYNSIGS_H_

/*ͷ�ļ�����*/
#include "./RteSigsConfigList.h"

/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
// #define SIGNAL_SERV_LIST_RTESYN(_)                         \
//         SIGNAL_SERV_LIST_RTESYN_ABI(_)                     \
//         SIGNAL_SERV_LIST_RTESYN_CPNSCH(_)                  \
//         SIGNAL_SERV_LIST_RTESYN_CPN1(_)                    \
//         SIGNAL_SERV_LIST_RTESYN_CPN2(_)                    \
//         SIGNAL_SERV_LIST_RTESYN_CPN3(_)                    \
//         SIGNAL_SERV_LIST_RTESYN_CPN4(_)                    \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
// #define SIGNAL_TRIG_MAP_LIST_RTESYN(_)                     \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_ABI(_)                 \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSCH(_)              \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN1(_)                \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN2(_)                \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN3(_)                \
//         SIGNAL_TRIG_MAP_LIST_RTESYN_CPN4(_)                \


/***********************************************************
* ע��trig serv�ź�
***********************************************************/
/*ע������ź�
***********************************************/
#define SYN_SERV_SIGNAL_REGISTER(signal_serv,serv)                 SIGNAL_SERV_REGISTER(RteSynSigs,signal_serv,serv)
/*ע�ᴥ���ź�
***********************************************/
#define SYN_TRIG_SIGNAL_REGISTER(signal_trig,signal_serv)          SIGNAL_TRIG_REGISTER(RteSynSigs,signal_trig,signal_serv)


/***********************************************************
* trig serv�źŹ���ģ��
***********************************************************/
/*�������񴥷��ź�ӳ��
***********************************************/
SIGNAL_SERVTRIG_MAP(RteSynSigs,SIGNAL_SERV_LIST_RTESYN,SIGNAL_TRIG_MAP_LIST_RTESYN);
/*ͬ���źų�ʼ������
***********************************************/
void RetSynServTrigInit(void);
/*������񴥷���
***********************************************/
extern RteSyn clRteSynSigs;

#endif /*RTESYNSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
