/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  : CpnSinks����ź�����ͷ�ļ�
* Others       :
* History      : 200730 pxf ���ν���
***************************************************************************/

#ifndef CPNSINKSSIGS_H_
#define CPNSINKSSIGS_H_

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
    uint16 trig_getSig;            /* service signal to be trigger, to get data */
    uint16 trig_endSig;            /* service signal to be trigger, to inform cache full */
    uint16 type_index;             /* grouped signale index */
    tick period;                   /* MS_T */
    uint16 data_size;              /* sizeof data */
    uint16 buff_size;              /* sizeof data buff */
    void *buff;                    /* cache data buffer */
} tSinksParams, *htSinksParams;
typedef struct{
    htSinksParams sinks;           /* sinks */
    uint16 outOperation;           /* out operation result, TRUE/FALSE */
    void *buff;                    /* read out data buffer */
} tSinksOut, *htSinksOut;
typedef enum{
    cacheNotStart,
    cacheCaching,
    cacheFull
} tCacheProcessSta;
typedef struct{
    htSinksParams sinks;           /* sinks */
    tCacheProcessSta sta;          /* sinks state */
} tSinksSta, *htSinksSta;

/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnSinks_init(void);
/*����
***********************************************/
void serv_CpnSinks_readData(void *buff);
/*����
***********************************************/
void serv_CpnSinks_trigStart(void *buff);
/*����
***********************************************/
void serv_CpnSinks_cacheSta(void *buff);
/*����
***********************************************/
void serv_CpnSinks_registCache(void *buff);
/*����
***********************************************/
void serv_CpnSinks_reCache(void *buff);

/*�ӿڴ���
***********************************************/
//void trig_CpnSinks_inf_infFunc(void);
/*������ӿڴ���
***********************************************/
void trig_CpnSinks_inf_setErr(uint16 id, uint16 code);


/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNSINKS(_)                \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNSINKS(_)            \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNSINKS(_)                \
    _(sig_serv_CpnSinks_init,serv_CpnSinks_init)           \
    _(sig_serv_CpnSinks_readData,serv_CpnSinks_readData)   \
    _(sig_serv_CpnSinks_trigStart,serv_CpnSinks_trigStart) \
    _(sig_serv_CpnSinks_cacheSta,serv_CpnSinks_cacheSta)   \
    _(sig_serv_CpnSinks_registCache,serv_CpnSinks_registCache) \
    _(sig_serv_CpnSinks_reCache,serv_CpnSinks_reCache)     \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNSINKS(_)            \
    _(sig_trig_CpnSinks_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnSinks_addTask,sig_serv_CpnSch_addTask)   \
    _(sig_trig_CpnSinks_delTask,sig_serv_CpnSch_delTask)   \
    _(sig_trig_CpnSinks_delay,sig_serv_CpnSch_delay)       \
    _(sig_trig_CpnSinks_now,sig_serv_CpnSch_now)           \
    _(sig_trig_CpnSinks_setErr,sig_serv_CpnErr_setErr)     \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnSinks(void);

#endif /*CPNSINKSSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
