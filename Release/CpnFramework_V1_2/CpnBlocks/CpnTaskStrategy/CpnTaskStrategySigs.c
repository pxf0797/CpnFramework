/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategySigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy����źŶ���Դ�ļ�
* Others       :
* History      : 201218 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnTaskStrategy.h"
#include "./CpnTaskStrategySigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
* CpnTaskStrategy�ඨ��
***********************************************************/
/*CpnTaskStrategy��
***********************************************/
CpnTaskStrategy clCpnTaskStrategy;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnTaskStrategy_init(void){
    CNNP(CpnTaskStrategy,&clCpnTaskStrategy);
    if(OPRS(clCpnTaskStrategy) != NULL){
        initTaskParam taskParam;
        taskParam.level = level2;
        taskParam.t = taskCpnTaskStrategy;
        taskParam.prdTick = CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD;
        taskParam.startTick = 3*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_initTask, (uint8*)&taskParam);
    }
}

/*��ʱ�������������
***********************************************/
void serv_CpnTaskStrategy_delayUpdate(void *buff){
    clCpnTaskStrategy.updateStrategy(clCpnTaskStrategy.self, ((hstrgDelayUpdate)buff)->strgMask, ((hstrgDelayUpdate)buff)->addTime, ((hstrgDelayUpdate)buff)->delTime);
}
/*�����������������
***********************************************/
void serv_CpnTaskStrategy_condUpdate(void *buff){
    clCpnTaskStrategy.updateStrategyCond(clCpnTaskStrategy.self, ((hstrgCondUpdate)buff)->strgMask, ((hstrgCondUpdate)buff)->cond);
}

/*�ӿڴ���
***********************************************/
//void trig_CpnTaskStrategy_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnTaskStrategy(void){
    clCpnTaskStrategy.run(clCpnTaskStrategy.self);
}

/**************************** Copyright(C) pxf ****************************/
