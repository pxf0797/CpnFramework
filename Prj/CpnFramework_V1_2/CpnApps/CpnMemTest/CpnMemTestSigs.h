/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMemTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/09 11:41:03
* Description  : CpnMemTest����ź�����ͷ�ļ�
* Others       :
* History      : 201209 pxf ���ν���
***************************************************************************/

#ifndef CPNMEMTESTSIGS_H_
#define CPNMEMTESTSIGS_H_

/*ͷ�ļ�����*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNMEMTESTSIGS_MACRO_VERSION    0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
void serv_CpnMemTest_init(void);

/*�ӿڴ���
***********************************************/
//void trig_CpnMemTest_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMEMTEST(_)              \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEMTEST(_)          \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMEMTEST(_)              \
    _(sig_serv_CpnMemTest_init,serv_CpnMemTest_init)       \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEMTEST(_)          \
    _(sig_trig_CpnMemTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnMemTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMemTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMemTest_delay,sig_serv_CpnSch_delay)     \
    _(sig_trig_CpnMemTest_now,sig_serv_CpnSch_now)         \
    _(sig_trig_CpnMemTest_setErr,sig_serv_CpnErr_setErr)   \
    _(sig_trig_CpnMemTest_memMalloc,sig_serv_CpnMem_memMalloc) \
    _(sig_trig_CpnMemTest_memFree,sig_serv_CpnMem_memFree) \
    _(sig_trig_CpnMemTest_isPointerSet,sig_serv_CpnMem_isPointerSet) \
    _(sig_trig_CpnMemTest_getSize,sig_serv_CpnMem_getSize) \
    _(sig_trig_CpnMemTest_getIndex,sig_serv_CpnMem_getIndex) \
    _(sig_trig_CpnMemTest_memStatus,sig_serv_CpnMem_memStatus) \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnMemTest(void);

#endif /*CPNMEMTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
