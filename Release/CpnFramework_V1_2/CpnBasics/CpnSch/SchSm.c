/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SchSm.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:24:20
* Description  : ״̬��SchSm���弰��״̬��������Դ�ļ�
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./SchSm.h"
#include "./CpnSch.h"
#include "../FuncLib/FuncLib.h"

/*״̬��SchSm����
* ����״̬����ش���״̬
***********************************************/
SMDF(SchSm, SCHSM_LIST);
SchSmRec SchSmRunRec;
extern CpnSch clCpnSch;

/*���� : SchSm_act_init()
* ���� : SchSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ��ʼ״̬��������
***********************************************/
void SchSm_act_init(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    uint16 i = 0u;
    uint16 j = 0u;

    hRec->ticker = 0u;
    hRec->taskGroupNum = CPN_SCH_GROUP_TOTAL_NUMS;
    hRec->CpnSch = &clCpnSch;
    for(i = 0u; i < CPN_SCH_GROUP_TOTAL_NUMS; i++){
        for(j = 0u; j < (sizeof(taskGroupType)<<3U); j++){
            hRec->taskGroups[i].startTick[j] = 0u;
            hRec->taskGroups[i].prdTick[j] = 0u;
            hRec->taskGroups[i].taskGroup[j] = NULL;
        }
        hRec->taskGroups[i].unstartMask = 0u;
        hRec->taskGroups[i].actMask = 0u;
        hRec->taskGroups[i].taskMask = 0u;
    }

    hRec->next = SchSm_sta_execute;
    hRec->last = SchSm_sta_init;
}

/*���� : SchSm_act_update()
* ���� : SchSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ״̬update��������
***********************************************/
void SchSm_act_update(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 i = 0u;
    uint16 diffTick = 0u;

    // �޳������������ִ�б�־
    for(i = 0u; i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG); i++){
        /* ���¸��鼤������ */
        taskMask = hRec->taskGroups[i].taskMask;
        while(taskMask != 0u){
            //curTask = (taskMask&(taskMask^(taskMask-1u)));
            curTask = (taskMask&(-taskMask));
            //taskMask ^= curTask;
            taskMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            if(hRec->taskGroups[i].unstartMask){
                /* ��鵱ǰ�����Ƿ��������ִ�� */
                if(hRec->taskGroups[i].unstartMask&curTask){
                    /* С��2������ƫ��Ҳ���������������������������û��ƫ��� */
                    diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                    if(diffTick <= 5U/*2U*/){
                        hRec->taskGroups[i].unstartMask &= (~curTask);
                        /* ���¼���״̬�Լ���һ������ʼ���� */
                        hRec->taskGroups[i].actMask |= curTask;
                        //hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                    }
                }else{
                    diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                    if(diffTick >= hRec->taskGroups[i].prdTick[taskIndex]){
                        /* ���¼���״̬�Լ���һ������ʼ���� */
                        hRec->taskGroups[i].actMask |= curTask;
                        hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                    }
                }
            }else{
                /* ȫ����������ִ�� */
                diffTick = (hRec->ticker-hRec->taskGroups[i].startTick[taskIndex]);
                if(diffTick >= hRec->taskGroups[i].prdTick[taskIndex]){
                    /* ���¼���״̬�Լ���һ������ʼ���� */
                    hRec->taskGroups[i].actMask |= curTask;
                    hRec->taskGroups[i].startTick[taskIndex] += hRec->taskGroups[i].prdTick[taskIndex];
                }
            }
        }
    }

    hRec->next = SchSm_sta_execute;
    hRec->last = SchSm_sta_update;
}

/*���� : SchSm_act_execute()
* ���� : SchSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ״̬execute��������
***********************************************/
void SchSm_act_execute(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    taskGroupType taskMask = 0u;
    taskGroupType curTask = 0u;
    uint16 taskIndex = 0u;
    uint16 i = 0u;
    uint16 specificFlg = 0u;
#if (CPN_SCH_TASK_MEASURE_ENABLE == TRUE)
    static uint16 taskTimePot = 0u;
    uint16 currUsage = 0u;
    ((hCpnSch)(hRec->CpnSch))->now(hRec->CpnSch, &taskTimePot);
#endif

    for(i = 0u; i < hRec->taskGroupNum; i++){
        /* �鿴�������񣬲�ִ��������ȼ����� */
        taskMask = hRec->taskGroups[i].actMask;
        if(taskMask != 0u){
            //curTask = (taskMask&(taskMask^(taskMask-1u)));
            curTask = (taskMask&(-taskMask));
            //hRec->taskGroups[i].actMask ^= curTask; // �����������ɿؽ��
            hRec->taskGroups[i].actMask &= (~curTask);
            taskIndex = log_2n((uint32)curTask);

            /* �ж��Ƿ�Ϊһ�������������level0�������������������ȥ�� */
            if((hRec->taskGroups[i].prdTick[taskIndex] == 0u) && (i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG))){
                hRec->taskGroups[i].taskMask &= (~curTask);
            }

            /* ����ָ��������λ��־ */
            if((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x8000u)
            &&(((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x7F00u)>>8u)==i)
            &&((((hCpnSch)(hRec->CpnSch))->specificTaskMask&0x00FFu)==taskIndex)){
                specificFlg = 1u;
            }

            /* ִ������ */
            ((hCpnSch)(hRec->CpnSch))->currTaskIndex = ((i<<8u)|taskIndex);
            if(hRec->taskGroups[i].taskGroup[taskIndex]){
                hRec->taskGroups[i].taskGroup[taskIndex]();
            }
            break;
        }
    }

#if (CPN_SCH_TASK_MEASURE_ENABLE == TRUE)
    ((hCpnSch)(hRec->CpnSch))->currTaskTime = taskTimePot;
    ((hCpnSch)(hRec->CpnSch))->now(hRec->CpnSch, &taskTimePot);
    ((hCpnSch)(hRec->CpnSch))->currTaskTime = (taskTimePot-((hCpnSch)(hRec->CpnSch))->currTaskTime);
    /* ����ָ������ִ��ʱ�� */
    if(specificFlg){
        ((hCpnSch)(hRec->CpnSch))->specificTaskTime = ((hCpnSch)(hRec->CpnSch))->currTaskTime;
    }
    /* Ŀǰʱ�������ȷ��0.1us��ʹ���ʾ�ȷ��0.1% */
    if(i < (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG)){
        ((hCpnSch)(hRec->CpnSch))->totalTaskTime += ((hCpnSch)(hRec->CpnSch))->currTaskTime;
    }else{
        if(((hCpnSch)(hRec->CpnSch))->totalTaskTime){
            currUsage = ((uint32)((hCpnSch)(hRec->CpnSch))->totalTaskTime*100U/CPN_SCH_TASK_TICK_TIME_US);
            ((hCpnSch)(hRec->CpnSch))->usage = (uint16)lowpassFilter(currUsage, (uint32)((hCpnSch)(hRec->CpnSch))->usage, 4U);
            ((hCpnSch)(hRec->CpnSch))->totalTaskTime = 0U;
        }
    }
#endif

    if(hRec->ticker != hRec->tickerLast){
        hRec->tickerLast = hRec->ticker;
        hRec->next = SchSm_sta_update;
    }else if((i >= hRec->taskGroupNum) && (!hRec->taskGroups[hRec->taskGroupNum-1u].actMask)){
        hRec->next = SchSm_sta_updateBgTask;
    }else{
        hRec->next = SchSm_sta_execute;
    }
    hRec->last = SchSm_sta_execute;
}

/*���� : SchSm_act_updateBgTask()
* ���� : SchSmRec - ״̬��¼����ָ��
* ��� : ��
* ���� : ״̬updateBgTask��������
***********************************************/
void SchSm_act_updateBgTask(void *SchSmRec){
    hSchSmRec hRec = (hSchSmRec)SchSmRec;
    uint16 i = 0u;

    for(i = (hRec->taskGroupNum-CPN_SCH_LEVEL0_GROUP_NUM_CFG); i < hRec->taskGroupNum; i++){
        hRec->taskGroups[i].actMask = hRec->taskGroups[i].taskMask;
    }

    if(hRec->ticker != hRec->tickerLast){
        hRec->tickerLast = hRec->ticker;
        hRec->next = SchSm_sta_update;
    }else{
        hRec->next = SchSm_sta_execute;
    }
    hRec->last = SchSm_sta_updateBgTask;
}

/**************************** Copyright(C) pxf ****************************/
