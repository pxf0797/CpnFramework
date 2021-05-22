/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategySigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy����ź�����ͷ�ļ�
* Others       :
* History      : 201218 pxf ���ν���
***************************************************************************/

#ifndef CPNTASKSTRATEGYSIGS_H_
#define CPNTASKSTRATEGYSIGS_H_

/*ͷ�ļ�����*/
#include "../../cpnRte/Rte/Rte.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNTASKSTRATEGYSIGS_MACRO_VERSION 0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
// typedef uint16 (*condition)(void); /* true/false */
typedef struct {
    strategy strgMask;
    uint16 addTime;
    uint16 delTime;
} strgDelayUpdate, *hstrgDelayUpdate;
typedef struct {
    strategy strgMask;
    condition cond;
} strgCondUpdate, *hstrgCondUpdate;



/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnTaskStrategy_init(void);
/*��ʱ�������������
***********************************************/
void serv_CpnTaskStrategy_delayUpdate(void *buff);
/*�����������������
***********************************************/
void serv_CpnTaskStrategy_condUpdate(void *buff);


/*�ӿڴ���
***********************************************/
//void trig_CpnTaskStrategy_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNTASKSTRATEGY(_)         \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNTASKSTRATEGY(_)     \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNTASKSTRATEGY(_)         \
    _(sig_serv_CpnTaskStrategy_init,serv_CpnTaskStrategy_init) \
    _(sig_serv_CpnTaskStrategy_delayUpdate,serv_CpnTaskStrategy_delayUpdate) \
    _(sig_serv_CpnTaskStrategy_condUpdate,serv_CpnTaskStrategy_condUpdate) \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNTASKSTRATEGY(_)     \
    _(sig_trig_CpnTaskStrategy_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnTaskStrategy_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnTaskStrategy_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnTaskStrategy_delay,sig_serv_CpnSch_delay)\
    _(sig_trig_CpnTaskStrategy_now,sig_serv_CpnSch_now)    \
    _(sig_trig_CpnTaskStrategy_setMonitor,sig_serv_CpnSch_setMonitor) \
    _(sig_trig_CpnTaskStrategy_getMonitor,sig_serv_CpnSch_getMonitor) \
    _(sig_trig_CpnTaskStrategy_updateStrategy,sig_serv_CpnSch_updateStrategy) \
    _(sig_trig_CpnTaskStrategy_getStrategy,sig_serv_serv_CpnSch_getStrategy) \
    _(sig_trig_CpnTaskStrategy_getTaskNum,sig_serv_serv_CpnSch_getTaskNum) \
    _(sig_trig_CpnTaskStrategy_setErr,sig_serv_CpnErr_setErr) \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnTaskStrategy(void);

#endif /*CPNTASKSTRATEGYSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
