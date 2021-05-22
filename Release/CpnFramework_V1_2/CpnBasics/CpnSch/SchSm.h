/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SchSm.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:24:20
* Description  : ״̬��SchSm������״̬��ʹ��ʾ��ͷ�ļ�
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

#ifndef SCHSM_H_
#define SCHSM_H_

/*ͷ�ļ�����*/
#include "../sm/sm.h"
#include "../standType/standType.h"
#include "./CpnSchCfg.h"

/*״̬��SchSmʹ��ʾ����
* ��ǰ״̬������SMDF�ж����ʵ��SchSm����Ҫ����ֻ��������������
* ״̬�����з�ʽ������ֱ�Ӹ�ʱ��������SMR��ʹ���Զ����¼״̬���������SMRE
***********************************************
* SMR��ʽ
***********************************************
void test(void){
    while(1){SMR(SchSm);};
}
***********************************************
* SMRE��ʽ
***********************************************
void test2(void){
    static SchSmRec SchSmRunRec = {SchSm_sta_init};
    while(1){SMRE(SchSm, SchSmRunRec);};
}
***********************************************/

/*�ӿ�����
***********************************************/
typedef void(*task)(void);                        // ������

/*����������
***********************************************/
typedef struct{
    uint16 startTick[sizeof(taskGroupType)<<3U];  // ����������ʼ����
    uint16 prdTick[sizeof(taskGroupType)<<3U];    // ���ڵ��Ƚ���
    taskGroupType unstartMask;                    // ����δ��������
    taskGroupType actMask;                        // ����������������
    taskGroupType taskMask;                       // �ѷ�����������
    task taskGroup[sizeof(taskGroupType)<<3U];    // ������
} taskGroupSm;

/*״̬��SchSm״̬���ж���
* ע������SchSm_init,SchSm_defaultδ�ڴ˶��壬Ĭ�ϻ����
***********************************************/
#define SCHSM_LIST(_)         \
    _(SchSm, update)          \
    _(SchSm, execute)         \
    _(SchSm, updateBgTask)    \


/*״̬��SchSm����
* �Ѹ���״̬��¼next,����һ״̬last�������������������
***********************************************/
SMDC(SchSm, SCHSM_LIST){
    sta next;               // ����״̬��¼
    sta last;               // ��һ״̬��¼
    uint16 ticker;          // ����
    uint16 tickerLast;      // �ɼ���
    uint16 taskGroupNum;    // ��������
    taskGroupSm taskGroups[CPN_SCH_GROUP_TOTAL_NUMS];  // ������
    void *CpnSch;           // ע�������
};
extern SchSmRec SchSmRunRec;

#endif /*SCHSM_H_*/

/**************************** Copyright(C) pxf ****************************/
