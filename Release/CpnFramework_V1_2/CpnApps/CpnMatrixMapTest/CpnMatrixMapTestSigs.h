/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapTestSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 20:32:16
* Description  : CpnMatrixMapTest����ź�����ͷ�ļ�
* Others       :
* History      : 201202 pxf ���ν���
***************************************************************************/

#ifndef CPNMATRIXMAPTESTSIGS_H_
#define CPNMATRIXMAPTESTSIGS_H_

/*ͷ�ļ�����*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNMATRIXMAPTESTSIGS_MACRO_VERSION 0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
void serv_CpnMatrixMapTest_init(void);
/*����
***********************************************/
// void serv_CpnMatrixMapTest_setDataA(void);
/*����
***********************************************/
// void serv_CpnMatrixMapTest_getData1(void);

/*�ӿڴ���
***********************************************/
//void trig_CpnMatrixMapTest_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAPTEST(_)        \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAPTEST(_)    \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAPTEST(_)        \
    _(sig_serv_CpnMatrixMapTest_init,serv_CpnMatrixMapTest_init) \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAPTEST(_)    \
    _(sig_trig_CpnMatrixMapTest_initTask,sig_serv_CpnSch_initTask) \
    _(sig_trig_CpnMatrixMapTest_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMatrixMapTest_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMatrixMapTest_delay,sig_serv_CpnSch_delay) \
    _(sig_trig_CpnMatrixMapTest_now,sig_serv_CpnSch_now)   \
    _(sig_trig_CpnMatrixMapTest_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataA,matrixMapSet(ulDataA)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataB,matrixMapSet(ulDataB)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataC,matrixMapSet(ulDataC)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataD,matrixMapSet(ulDataD)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataE,matrixMapSet(ulDataE)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataF,matrixMapSet(ulDataF)) \
    _(sig_trig_CpnMatrixMapTest_set_ulDataG,matrixMapSet(ulDataG)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData1,matrixMapGet(ulData1)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData2,matrixMapGet(ulData2)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData3,matrixMapGet(ulData3)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData4,matrixMapGet(ulData4)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData5,matrixMapGet(ulData5)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData6,matrixMapGet(ulData6)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData7,matrixMapGet(ulData7)) \
    _(sig_trig_CpnMatrixMapTest_get_ulData8,matrixMapGet(ulData8)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataA,matrixMapGet(ulDataA)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataB,matrixMapGet(ulDataB)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataC,matrixMapGet(ulDataC)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataD,matrixMapGet(ulDataD)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataE,matrixMapGet(ulDataE)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataF,matrixMapGet(ulDataF)) \
    _(sig_trig_CpnMatrixMapTest_get_ulDataG,matrixMapGet(ulDataG)) \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnMatrixMapTest(void);

#endif /*CPNMATRIXMAPTESTSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
