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
    uint16 startTick[sizeof(taskGroupType)*8];    // ����������ʼ����
    uint16 prdTick[sizeof(taskGroupType)*8];      // ���ڵ��Ƚ���
    taskGroupType unstartMask;                    // ����δ��������
    taskGroupType actMask;                        // ����������������
    taskGroupType taskMask;                       // �ѷ�����������
    task taskGroup[sizeof(taskGroupType)*8];      // ������
} taskGroupSm;

/*״̬��SchSm״̬���ж���
* ע������SchSm_init,SchSm_defaultδ�ڴ˶��壬Ĭ�ϻ����
***********************************************/
#define SCHSM_LIST(_)         \
    _(SchSm, update)          \
    _(SchSm, execute)         \
    _(SchSm, updateBgTask)


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

/*log_2n ������2^n�Ķ�Ӧ�Ķ���n
* ����: 2^n
* ���: n
***********************************************/
static inline uint16 log_2n(uint32 num){
    uint16 n = 0;
    if(num & 0xFFFF0000U){n += 16;}
    if(num & 0xFF00FF00U){n += 8;}
    if(num & 0xF0F0F0F0U){n += 4;}
    if(num & 0xCCCCCCCCU){n += 2;}
    if(num & 0xAAAAAAAAU){n += 1;}
    return n;
}

// ��ͨ�˲�(Low-pass filter)
// a=0-1�������˲����=(1-a)*���β���ֵ+a*�ϴ��˲����
// Y(n) = ��X(n)+(1-��)Y(n-1)
// Ϊ���Ż�����Ч�ʣ�aֻȡ1/(2^N)����СֵΪ1/2
// Y(n)= (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
//     = (X(n)+((2^N)-1)Y(n-1))/(2^N)
#define lowpassFilter(newValue, lastValue, n)  (((newValue) + (((lastValue) << (n)) - (lastValue))) >> (n))

#endif /*SCHSM_H_*/

/**************************** Copyright(C) pxf ****************************/
