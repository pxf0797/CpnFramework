/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSchSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 21:27:20
* Description  :
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnSchSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnSch.h"

/***********************************************************
* CpnSch�ඨ��
***********************************************************/
/*CpnSch��
***********************************************/
CpnSch clCpnSch;



/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*��ʼ���������
***********************************************/
void serv_CpnSch_initTask(void *buff){
    uint16 addIndex = 0u;

    if(clCpnSch.taskNum >= CPN_SCH_TASK_STRATEGY_LIST_NUM_CFG){
        clCpnSch.addList(clCpnSch.self, ((hinitTaskParam)buff)->level, ((hinitTaskParam)buff)->t, ((hinitTaskParam)buff)->prdTick, ((hinitTaskParam)buff)->startTick, ((hinitTaskParam)buff)->strgMask);
        return;
    }
    clCpnSch.addList(clCpnSch.self, ((hinitTaskParam)buff)->level, ((hinitTaskParam)buff)->t, ((hinitTaskParam)buff)->prdTick, ((hinitTaskParam)buff)->startTick, ((hinitTaskParam)buff)->strgMask);
    addIndex = (clCpnSch.taskNum-1u);
    if(clCpnSch.strgMask&clCpnSch.taskList[addIndex].strgMask){
        clCpnSch.addTask(clCpnSch.self, clCpnSch.taskList[addIndex].level, clCpnSch.taskList[addIndex].t, clCpnSch.taskList[addIndex].prdTick, clCpnSch.taskList[addIndex].startTick);
        clCpnSch.taskList[addIndex].strgMask |= TASK_STRATEGY_ACT_MASK;
    }
}
/*����������
***********************************************/
void serv_CpnSch_addTask(void *buff){
    clCpnSch.addTask(clCpnSch.self, ((hinitTaskParam)buff)->level, ((hinitTaskParam)buff)->t, ((hinitTaskParam)buff)->prdTick, ((hinitTaskParam)buff)->startTick);
}
/*ɾ���������
***********************************************/
void serv_CpnSch_delTask(void *buff){
    clCpnSch.delTask(clCpnSch.self, ((htaskParam)buff)->level, ((htaskParam)buff)->t);
}
/*��ʱ����
***********************************************/
void serv_CpnSch_delay(void *buff){
    clCpnSch.delay(clCpnSch.self, buff);
}
/*ʵʱ����
***********************************************/
void serv_CpnSch_now(void *buff){
    clCpnSch.now(clCpnSch.self, buff);
}
/*���ü���������
***********************************************/
void serv_CpnSch_setMonitor(void *buff){
    clCpnSch.setMonitor(clCpnSch.self, ((htaskParam)buff)->level, ((htaskParam)buff)->t);
}
/*��ȡ��������ʱ����
***********************************************/
void serv_CpnSch_getMonitor(void *buff){
    clCpnSch.getMonitor(clCpnSch.self, ((uint16*)buff));
}
/*���µ���������������
***********************************************/
void serv_CpnSch_updateStrategy(void *buff){
    strategy newStrgMask = *((strategy*)buff);
    //strategy strgMask;
    //uint16 taskNum;
    uint16 i = 0u;

    //clCpnSch.getStrategy(clCpnSch.self, &strgMask);
    //clCpnSch.getTaskNum(clCpnSch.self, &taskNum);
    if(newStrgMask != clCpnSch.strgMask){
        while(i < clCpnSch.taskNum){
            if((clCpnSch.taskList[i].strgMask&(~TASK_STRATEGY_ACT_MASK))&newStrgMask){
                /* ���µĲ������У�δ�����򼤻� */
                if(!(clCpnSch.taskList[i].strgMask&TASK_STRATEGY_ACT_MASK)){
                    clCpnSch.addTask(clCpnSch.self, clCpnSch.taskList[i].level, clCpnSch.taskList[i].t, clCpnSch.taskList[i].prdTick, clCpnSch.taskList[i].startTick);
                    clCpnSch.taskList[i].strgMask |= TASK_STRATEGY_ACT_MASK;
                }
            }else{
                /* �����µĲ������У��Ѽ�����ֹͣ */
                if(clCpnSch.taskList[i].strgMask&TASK_STRATEGY_ACT_MASK){
                    clCpnSch.delTask(clCpnSch.self, clCpnSch.taskList[i].level, clCpnSch.taskList[i].t);
                    clCpnSch.taskList[i].strgMask &= (~TASK_STRATEGY_ACT_MASK);
                }
            }
            i++;
        }
        clCpnSch.strgMask = newStrgMask;
    }
}
/*��ȡ����������������
***********************************************/
void serv_CpnSch_getStrategy(void *buff){
    clCpnSch.getStrategy(clCpnSch.self, ((strategy*)buff));
}
/*��ȡ���������ܸ�������
***********************************************/
void serv_CpnSch_getTaskNum(void *buff){
    clCpnSch.getTaskNum(clCpnSch.self, ((uint16*)buff));
}
/*��ʼ������
***********************************************/
void serv_CpnSch_init(void){
    CN(CpnSch, &clCpnSch, &SchSmRunRec, SchSm, trig_CpnSch_inf_getTime, trig_CpnSch_inf_setErr, trig_CpnSch_inf_initCpn);
    if(OPRS(clCpnSch) != NULL){}
}
/*���з���
***********************************************/
void serv_CpnSch_run(void){
    clCpnSch.run(clCpnSch.self);

    static tick sendDelay = 1000*MS_T;
    tDataSig sendStatus = {0};

    /* delay send */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_delay, (uint8*)&sendDelay);
    if(IS_TIMEOUT(sendDelay)){
        sendDelay = 3000*MS_T;
        sendStatus.id = 0x00;
        sendStatus.data = clCpnSch.usage;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
        sendStatus.id = 0x01;
        sendStatus.data = clCpnSch.currTaskTime;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
        sendStatus.id = 0x02;
        sendStatus.data = clCpnSch.totalTaskTime;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_sendSig, (uint8*)&sendStatus);
    }
}
/*��������
***********************************************/
void serv_CpnSch_tick(void){
    clCpnSch.tick(clCpnSch.self);
}


/*��ȡʵʱ�ӿڴ���
***********************************************/
void trig_CpnSch_inf_getTime(uint16 *point){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_inf_getTime, (uint8*)point);
}
/*������ӿڴ���
***********************************************/
void trig_CpnSch_inf_setErr(uint16 id, uint16 code){
    uint32 uwErrCode = (((uint32)id << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSch_inf_setErr, (uint8*)&uwErrCode);
}
/*��ʼ������ӿڴ���
***********************************************/
void trig_CpnSch_inf_initCpn(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMem_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMemTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCan_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFrameMatrix_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMap_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCrc_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_init, NULL);
//    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMem_init, NULL);
//    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMemTest_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCal_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_init, NULL);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskCtrl_init, NULL);
}

/**************************** Copyright(C) pxf ****************************/
