/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  : CpnSource����ź�����ͷ�ļ�
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

#ifndef CPNSOURCESIGS_H_
#define CPNSOURCESIGS_H_

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
typedef enum{
    w_sine,
    w_pluse,
    w_countUp,
    w_countDown,
    w_countUpDown,

    w_waveTypeMax
} tWaveType;
typedef struct{
    tWaveType type;                /* wave type */
    uint16 trig_sig;               /* service signal to be trigger */
    uint16 type_index;             /* grouped signale index */
    float32 amplitude;             /* amplitude */
    tick step;                     /* MS_T */
    tick period;                   /* MS_T */
    uint16 duty;                   /* 0.1% */
    uint16 phase;                  /* (0--3600)0.1 */
} tSourceParams, *htSourceParams;

/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnSource_init(void);
/*����
***********************************************/
void serv_CpnSource_registWaveSig(void *buff);
/*����
***********************************************/
void serv_CpnSource_changeWaveSig(void *buff);

/*�ӿڴ���
***********************************************/
//void trig_CpnSource_inf_infFunc(void);
/*������ӿڴ���
***********************************************/
void trig_CpnSource_inf_setErr(uint16 id, uint16 code);


/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSOURCE(_)               \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSOURCE(_)           \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSOURCE(_)               \
    _(sig_serv_CpnSource_init,serv_CpnSource_init)         \
    _(sig_serv_CpnSource_registWaveSig,serv_CpnSource_registWaveSig) \
    _(sig_serv_CpnSource_changeWaveSig,serv_CpnSource_changeWaveSig) \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSOURCE(_)           \
    _(sig_trig_CpnSource_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSource_addTask,sig_serv_CpnSch_addTask)  \
    _(sig_trig_CpnSource_delTask,sig_serv_CpnSch_delTask)  \
    _(sig_trig_CpnSource_delay,sig_serv_CpnSch_delay)      \
    _(sig_trig_CpnSource_now,sig_serv_CpnSch_now)          \
    _(sig_trig_CpnSource_setErr,sig_serv_CpnErr_setErr)    \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnSource(void);

#endif /*CPNSOURCESIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
