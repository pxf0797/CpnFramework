/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 17:01:04
* Description  : CpnSourceTest����ź�����ͷ�ļ�
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

#ifndef CPNSOURCETESTSIGS_H_
#define CPNSOURCETESTSIGS_H_

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
void serv_CpnSourceTest_init(void);
/*����
***********************************************/
void serv_CpnSourceTest_sSine(void *buff);
/*����
***********************************************/
void serv_CpnSourceTest_sPluse(void *buff);
/*����
***********************************************/
void serv_CpnSourceTest_sCountUp(void *buff);
/*����
***********************************************/
void serv_CpnSourceTest_sCountDown(void *buff);
/*����
***********************************************/
void serv_CpnSourceTest_sCountUpDown(void *buff);
/*����
***********************************************/
void serv_CpnSourceTest_sSine2(void *buff);
/*����
***********************************************/
void serv_CpnSourceTest_sSine3(void *buff);
/*����
***********************************************/
void serv_CpnSourceTest_sPluse2(void *buff);

/*�ӿڴ���
***********************************************/
//void trig_CpnSourceTest_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSOURCETEST(_)           \
    _(sig_set_CpnSourceTest_wOutput,sizeof(float32))       \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCETEST(_)       \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSOURCETEST(_)           \
    _(sig_serv_CpnSourceTest_init,serv_CpnSourceTest_init) \
    _(sig_serv_CpnSourceTest_sSine,serv_CpnSourceTest_sSine) \
    _(sig_serv_CpnSourceTest_sPluse,serv_CpnSourceTest_sPluse) \
    _(sig_serv_CpnSourceTest_sCountUp,serv_CpnSourceTest_sCountUp) \
    _(sig_serv_CpnSourceTest_sCountDown,serv_CpnSourceTest_sCountDown) \
    _(sig_serv_CpnSourceTest_sCountUpDown,serv_CpnSourceTest_sCountUpDown) \
    _(sig_serv_CpnSourceTest_sSine2,serv_CpnSourceTest_sSine2) \
    _(sig_serv_CpnSourceTest_sSine3,serv_CpnSourceTest_sSine3) \
    _(sig_serv_CpnSourceTest_sPluse2,serv_CpnSourceTest_sPluse2) \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCETEST(_)       \
    _(sig_trig_CpnSourceTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnSourceTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnSourceTest_delay,sig_serv_CpnSch_delay)  \
    _(sig_trig_CpnSourceTest_now,sig_serv_CpnSch_now)      \
    _(sig_trig_CpnSourceTest_setErr,sig_serv_CpnErr_setErr)\
    _(sig_trig_CpnSourceTest_registWaveSig,sig_serv_CpnSource_registWaveSig)\
    _(sig_trig_CpnSourceTest_changeWaveSig,sig_serv_CpnSource_changeWaveSig)\
    _(sig_trig_CpnSourceTest_sendSig,sig_serv_CpnCan_sendSig)\
    _(sig_trig_CpnSourceTest_sSine,sig_serv_CpnSourceTest_sSine) \
    _(sig_trig_CpnSourceTest_sSine2,sig_serv_CpnSourceTest_sSine2) \
    _(sig_trig_CpnSourceTest_sSine3,sig_serv_CpnSourceTest_sSine3) \
    _(sig_trig_CpnSourceTest_sPluse,sig_serv_CpnSourceTest_sPluse) \
    _(sig_trig_CpnSourceTest_sPluse2,sig_serv_CpnSourceTest_sPluse2) \
    _(sig_trig_CpnSourceTest_sCountUp,sig_serv_CpnSourceTest_sCountUp) \
    _(sig_trig_CpnSourceTest_sCountDown,sig_serv_CpnSourceTest_sCountDown) \
    _(sig_trig_CpnSourceTest_sCountUpDown,sig_serv_CpnSourceTest_sCountUpDown) \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnSourceTest(void);

#endif /*CPNSOURCETESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
