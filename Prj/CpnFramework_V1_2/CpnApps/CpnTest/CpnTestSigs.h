/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/23 17:26:23
* Description  : CpnTest����ź�����ͷ�ļ�
* Others       :
* History      : 200723 pxf ���ν���
***************************************************************************/

#ifndef CPNTESTSIGS_H_
#define CPNTESTSIGS_H_

/*ͷ�ļ�����*/
#include "../../CpnRte/Rte/Rte.h"

/***********************************************************
* get set �������Ͷ���
* һ��ֻ����set���ݣ�get�������õ�ǰͷ�ļ�
* ֻ��Ҫ�ѷ��͵����ݶ���������շ��ӿ�ʹ�õ���ͳһ�ӿڣ�����������
* �ź���������һ����˵����ǿ�ƶ���һ�飬�������֪���źŶ�Ӧ������ʲô
***********************************************************/
/*������������
***********************************************/



/***********************************************************
* serv trig �������Ͷ���
* һ��ֻ����serv���ݣ�trig�������õ�ǰͷ�ļ�
* ֻ��Ҫ�ѷ��͵����ݶ���������շ��ӿ�ʹ�õ���ͳһ�ӿڣ�����������
* �ź���������һ����˵����ǿ�ƶ���һ�飬�������֪���źŶ�Ӧ������ʲô
***********************************************************/
/*������������
***********************************************/



/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnTest_init(void);
/*����
***********************************************/
void serv_CpnTest_servSig1(void);
/*����
***********************************************/
void serv_CpnTest_servSig2_uint16(void *buff);

/*�ӿڴ���
***********************************************/
//void trig_CpnTest_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNTEST(_)                 \
    _(sig_set_CpnTest_sendSig1_uint8,sizeof(uint8))        \
    _(sig_set_CpnTest_SendSig2_uint32,sizeof(uint32))      \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNTEST(_)             \
    _(sig_get_CpnTest_receiveSig1_uint32,sig_set_CpnTest_SendSig2_uint32) \
    _(sig_get_CpnTest_receiveSig2_uint8,sig_set_CpnTest_sendSig1_uint8) \


/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNTEST(_)                 \
    _(sig_serv_CpnTest_init,serv_CpnTest_init)             \
    _(sig_serv_CpnTest_servSig1,serv_CpnTest_servSig1)     \
    _(sig_serv_CpnTest_servSig2_uint16,serv_CpnTest_servSig2_uint16) \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTEST(_)             \
    _(sig_trig_CpnTest_initTask,sig_serv_CpnSch_initTask)  \
    _(sig_trig_CpnTest_addTask,sig_serv_CpnSch_addTask)    \
    _(sig_trig_CpnTest_delTask,sig_serv_CpnSch_delTask)    \
    _(sig_trig_CpnTest_delay,sig_serv_CpnSch_delay)        \
    _(sig_trig_CpnTest_now,sig_serv_CpnSch_now)            \
    _(sig_trig_CpnTest_setErr,sig_serv_CpnErr_setErr)      \
    _(sig_trig_CpnTest_trigSig1_uint16,sig_serv_CpnTest_servSig2_uint16) \
    _(sig_trig_CpnTest_trigSig2,sig_serv_CpnTest_servSig1) \
    _(sig_trig_CpnTest_sendSig,sig_serv_CpnCan_sendSig)    \

/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnTest(void);

#endif /*CPNTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
