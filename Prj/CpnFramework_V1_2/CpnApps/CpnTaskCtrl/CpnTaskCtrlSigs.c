/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskCtrlSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/21 11:24:55
* Description  : CpnTaskCtrl����źŶ���Դ�ļ�
* Others       :
* History      : 201221 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
// #include "./CpnTaskCtrl.h"
#include "./CpnTaskCtrlSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnTaskCtrl�ඨ��
***********************************************************/
/*CpnTaskCtrl��
***********************************************/
// CpnTaskCtrl clCpnTaskCtrl;
typedef enum{
    task_ctrl_basic,
    task_ctrl_sink,
    task_ctrl_source,
    task_ctrl_test,
    task_ctrl_cal,

    task_ctrl_max_num
} task_ctrl_group;
static const strategy strgGroups[task_ctrl_max_num] = {
    (task_strategy_basic_mask|task_strategy_matrix_mask),
    (task_strategy_basic_mask|task_strategy_matrix_mask|task_strategy_sink_mask),
    (task_strategy_basic_mask|task_strategy_matrix_mask|task_strategy_source_mask),
    (task_strategy_basic_mask|task_strategy_matrix_mask|task_strategy_sink_mask|task_strategy_source_mask|task_strategy_test_mask),
    (task_strategy_basic_mask|task_strategy_matrix_mask|task_strategy_cal_mask),
};


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnTaskCtrl_init(void){
    // CNNP(CpnTaskCtrl,&clCpnTaskCtrl);
    // if(OPRS(clCpnTaskCtrl) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnTaskCtrl;
        taskParam.prdTick = 10*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskCtrl_initTask, (uint8*)&taskParam);
    // }
}


/*�ӿڴ���
***********************************************/
//void trig_CpnTaskCtrl_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
uint16 testTaskGroup = 1u;//0u;
tick condDelay = 100*MS_T;
uint16 conditionUpdate(void){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskCtrl_delay, (uint8*)&condDelay);
    if(IS_TIMEOUT(condDelay)){
        return 1u;
    }
    return 0u;
}
void conditionReset(void){
    condDelay = 100*MS_T;
}

/*����������
***********************************************/
void taskCpnTaskCtrl(void){
    static tick waitDelay = 5000*MS_T;
    static uint16 taskIndex = 0u;
    strgDelayUpdate strgDelayMask = {0};
    strgCondUpdate strgCondMask = {0};

    /* wait delay */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskCtrl_delay, (uint8*)&waitDelay);
    if(IS_TIMEOUT(waitDelay)){
        waitDelay = 5000*MS_T;

        if(testTaskGroup == 1u){
            strgDelayMask.strgMask = strgGroups[task_ctrl_test];//strgGroups[taskIndex];
            strgDelayMask.addTime = 50*MS_T;
            strgDelayMask.delTime = 200*MS_T;
            clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskCtrl_delayUpdate, (uint8*)&strgDelayMask);
        }else if(testTaskGroup == 2u){
            conditionReset();
            strgCondMask.strgMask = strgGroups[taskIndex];
            strgCondMask.cond = conditionUpdate;
            clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskCtrl_condUpdate, (uint8*)&strgCondMask);
        }
        if(++taskIndex >= task_ctrl_max_num){
            taskIndex = 0u;
        }
    }
}

/**************************** Copyright(C) pxf ****************************/
