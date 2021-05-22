/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 19:07:35
* Description  : CpnSinksTest����ź�����ͷ�ļ�
* Others       :
* History      : 200730 pxf ���ν���
***************************************************************************/

#ifndef CPNSINKSTESTSIGS_H_
#define CPNSINKSTESTSIGS_H_

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
typedef struct{
    uint16 index;
    float32 data;
} tStoreData, *htStoreData;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnSinksTest_init(void);
/*����
***********************************************/
void serv_CpnSinksTest_sIsFull(void);
/*����
***********************************************/
void serv_CpnSinksTest_sGetData(void *buff);

/*�ӿڴ���
***********************************************/
//void trig_CpnSinksTest_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSINKSTEST(_)            \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKSTEST(_)        \
    _(sig_get_CpnSinksTest_wCache,sig_set_CpnSourceTest_wOutput) \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSINKSTEST(_)            \
    _(sig_serv_CpnSinksTest_init,serv_CpnSinksTest_init)   \
    _(sig_serv_CpnSinksTest_sIsFull,serv_CpnSinksTest_sIsFull) \
    _(sig_serv_CpnSinksTest_sGetData,serv_CpnSinksTest_sGetData) \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKSTEST(_)        \
    _(sig_trig_CpnSinksTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSinksTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnSinksTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnSinksTest_delay,sig_serv_CpnSch_delay)   \
    _(sig_trig_CpnSinksTest_now,sig_serv_CpnSch_now)       \
    _(sig_trig_CpnSinksTest_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnSinksTest_readData,sig_serv_CpnSinks_readData) \
    _(sig_trig_CpnSinksTest_trigStart,sig_serv_CpnSinks_trigStart) \
    _(sig_trig_CpnSinksTest_cacheSta,sig_serv_CpnSinks_cacheSta) \
    _(sig_trig_CpnSinksTest_registCache,sig_serv_CpnSinks_registCache) \
    _(sig_trig_CpnSinksTest_reCache,sig_serv_CpnSinks_reCache) \
    _(sig_trig_CpnSinksTest_sIsFull,sig_serv_CpnSinksTest_sIsFull) \
    _(sig_trig_CpnSinksTest_sGetData,sig_serv_CpnSinksTest_sGetData) \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnSinksTest(void);

#endif /*CPNSINKSTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
