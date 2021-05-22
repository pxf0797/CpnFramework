/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSch.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:16:09
* Description  : CpnSch�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

#ifndef CPNSCH_H_
#define CPNSCH_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/oopc/oopc.h"
#include "../../CpnBasics/standType/standType.h"
#include "./CpnSchCfg.h"
#include "./SchSm.h"
#include "./CpnSchSigs.h"

/***********************************************************
* serv trig �������Ͷ���
* һ��ֻ����serv���ݣ�trig�������õ�ǰͷ�ļ�
***********************************************************/
/*������������
***********************************************/
/*�����������
* ���λΪ�������ڳ�ʼ������initTaskParam�б�ʾ���񼤻�
***********************************************/
typedef uint16 strategy;
#define TASK_STRATEGY_ACT_MASK         ((strategy)(0x1UL<<((sizeof(strategy)<<3U)-1U)))
/*��ʼ������������
***********************************************/
typedef struct initTaskParam{
    uint16 level;
    task t;
    uint16 prdTick;
    uint16 startTick;
    strategy strgMask;
}initTaskParam, *hinitTaskParam;
/*����������
***********************************************/
typedef struct taskParam{
    uint16 level;
    task t;
}taskParam, *htaskParam;
/*��ʱ�������
***********************************************/
typedef uint32 tick;
/*ʵʱ�������
***********************************************/
typedef uint16 point;

/***********************************************************
* �ӿڶ���
***********************************************************/
/*�ӿ�����
***********************************************/
INF(iTime){
    void (*getTime)(uint16 *point);
};
INF(iErr){
    void (*setErr)(uint16 id, uint16 code);
};
INF(iInitCpn){
    void (*initCpn)(void);
};

/***********************************************************
* CpnSch�ඨ��
***********************************************************/
/*����ȼ�
***********************************************/
typedef enum{
    level0 = 0,
    level1,
    level2,
    level3
} taskLevel;

/*CpnSch������
***********************************************/
CL(CpnSch){
    hCpnSch self;
    hCpnSch (*init)(hCpnSch cthis, hSchSmRec SchSmRec, hstaAct SchSm,
            void (*getTime)(uint16 *point),
            void (*setErr)(uint16 id, uint16 code),
            void (*initCpn)(void));

    /* CpnSch����� */
    uint16 usage;            /* cpuʹ���ʣ���112��ʾ11.2% */
    uint16 currTaskIndex;    /* ��ǰ��������ָʾ; bit15--8 ������������ bit7--0 ���ڱ������ */
    uint16 currTaskTime;     /* ��ǰ����ִ��ʱ��,0.1us */
    uint16 totalTaskTime;    /* ������ִ��ʱ��,0.1us */
    uint16 specificTaskMask; /* bit15 �����Ƿ�ʹ�ܣ� bit14--8 ������������ bit7--0 ���ڱ������ */
    uint16 specificTaskTime; /* ָ������ִ��ʱ��,0.1us */

    /* ��������� */
    strategy strgMask;
    uint16 taskNum;
    initTaskParam taskList[CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG]; /* ������Ϊ��������������2�� */

    /* �������״̬�� */
    hSchSmRec SchSmRec;
    hstaAct SchSm;

    /* �������������Ҫ�����ã� */
    void (*tick)(hCpnSch cthis);
    void (*run)(hCpnSch cthis);
    void (*addList)(hCpnSch cthis, taskLevel level, task t, uint16 prd, uint16 start, strategy strgMask);
    void (*delList)(hCpnSch cthis, task t);
    void (*addTask)(hCpnSch cthis, taskLevel level, task t, uint16 prd, uint16 start);
    void (*delTask)(hCpnSch cthis, taskLevel level, task t);
    void (*delay)(hCpnSch cthis, uint32 *tick);
    void (*setMonitor)(hCpnSch cthis, taskLevel level, task t);
    void (*getMonitor)(hCpnSch cthis, uint16 *point); /* 0.1us */
    void (*setStrategy)(hCpnSch cthis, strategy strgMask);
    void (*getStrategy)(hCpnSch cthis, strategy *strgMask);
    void (*getTaskNum)(hCpnSch cthis, uint16 *taskNum);

    /* ��������������������������� */
    void (*now)(hCpnSch cthis, uint16 *point); /* 0.1us */
    void (*err)(hCpnSch cthis, uint16 code);

    /* �ӿں��� */
    IMPL(iTime);
    IMPL(iErr);
    IMPL(iInitCpn);
};

#endif /*CPNSCH_H_*/

/**************************** Copyright(C) pxf ****************************/
