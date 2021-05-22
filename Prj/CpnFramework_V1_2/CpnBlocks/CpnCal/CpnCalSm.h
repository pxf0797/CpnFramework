/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSm.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/17 10:12:15
* Description  : ״̬��CpnCalSm������״̬��ʹ��ʾ��ͷ�ļ�
* Others       : 
* History      : 201217 pxf ���ν���
***************************************************************************/

#ifndef CPNCALSM_H_
#define CPNCALSM_H_

/*ͷ�ļ�����*/
#include "../../cpnBasics/sm/sm.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNCALSM_MACRO_VERSION          0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

/*״̬��CpnCalSmʹ��ʾ����
* ��ǰ״̬������SMDF�ж����ʵ��CpnCalSm����Ҫ����ֻ��������������
* ״̬�����з�ʽ������ֱ�Ӹ�ʱ��������SMR��ʹ���Զ����¼״̬���������SMRE
***********************************************
* SMR��ʽ
***********************************************
void test(void){
    while(1){SMR(CpnCalSm);};
}
***********************************************
* SMRE��ʽ
***********************************************
void test2(void){
    static CpnCalSmRec CpnCalSmRunRec = {CpnCalSm_sta_init};
    while(1){SMRE(CpnCalSm, CpnCalSmRunRec);};
}
***********************************************/


/*״̬��CpnCalSm״̬���ж���
* ע������CpnCalSm_init,CpnCalSm_defaultδ�ڴ˶��壬Ĭ�ϻ����
***********************************************/
#define CPNCALSM_LIST(_)    \
    _(CpnCalSm, idle)       \
    _(CpnCalSm, wait)       \
    _(CpnCalSm, dispose)    \


/*״̬��CpnCalSm����
* �Ѹ���״̬��¼next,����һ״̬last�������������������
***********************************************/
SMDC(CpnCalSm, CPNCALSM_LIST){
    sta next; // ����״̬��¼
    sta last; // ��һ״̬��¼
    // TODO
};

#endif /*CPNCALSM_H_*/

/**************************** Copyright(C) pxf ****************************/
