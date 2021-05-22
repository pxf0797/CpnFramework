/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:06:36
* Description  : CpnCal����ź�����ͷ�ļ�
* Others       :
* History      : 201212 pxf ���ν���
***************************************************************************/

#ifndef CPNCALSIGS_H_
#define CPNCALSIGS_H_

/*ͷ�ļ�����*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNCALSIGS_MACRO_VERSION        0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
void serv_CpnCal_init(void);
/*����
***********************************************/
void serv_CpnCal_getCtrlBits(void);
/*����
***********************************************/
void serv_CpnCal_getCmdBits(void);
/*����
***********************************************/
void serv_CpnCal_getFrameLen(void);
/*����
***********************************************/
void serv_CpnCal_getByte(void);
/*����
***********************************************/
void serv_CpnCal_setCtrlBits(void);
/*����
***********************************************/
void serv_CpnCal_setCmdBits(void);
/*����
***********************************************/
void serv_CpnCal_setFrameLen(void);
/*����
***********************************************/
void serv_CpnCal_setByte(void);

/*�ӿڴ���
***********************************************/
//void trig_CpnCal_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNCAL(_)                  \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNCAL(_)              \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNCAL(_)                  \
    _(sig_serv_CpnCal_init,serv_CpnCal_init)               \
    _(sig_serv_CpnCal_getCtrlBits,serv_CpnCal_getCtrlBits) \
    _(sig_serv_CpnCal_getCmdBits,serv_CpnCal_getCmdBits)   \
    _(sig_serv_CpnCal_getFrameLen,serv_CpnCal_getFrameLen) \
    _(sig_serv_CpnCal_getByte,serv_CpnCal_getByte)         \
    _(sig_serv_CpnCal_setCtrlBits,serv_CpnCal_setCtrlBits) \
    _(sig_serv_CpnCal_setCmdBits,serv_CpnCal_setCmdBits)   \
    _(sig_serv_CpnCal_setFrameLen,serv_CpnCal_setFrameLen) \
    _(sig_serv_CpnCal_setByte,serv_CpnCal_setByte)         \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNCAL(_)              \
    _(sig_trig_CpnCal_initTask,sig_serv_CpnSch_initTask)   \
    _(sig_trig_CpnCal_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnCal_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnCal_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnCal_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnCal_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnCal(void);

#endif /*CPNCALSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
