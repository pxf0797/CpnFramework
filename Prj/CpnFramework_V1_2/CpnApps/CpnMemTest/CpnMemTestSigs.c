/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMemTestSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/09 11:41:03
* Description  : CpnMemTest����źŶ���Դ�ļ�
* Others       :
* History      : 201209 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnMemTest.h"
#include "./CpnMemTestSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnMemTest�ඨ��
***********************************************************/
/*CpnMemTest��
***********************************************/
CpnMemTest clCpnMemTest;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnMemTest_init(void){
    CNNP(CpnMemTest,&clCpnMemTest);
    if(OPRS(clCpnMemTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnMemTest;
        taskParam.prdTick = 19*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_test_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMemTest_initTask, (uint8*)&taskParam);
    }
}


/*�ӿڴ���
***********************************************/
//void trig_CpnMemTest_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnMemTest(void){
    clCpnMemTest.run(clCpnMemTest.self);
}

/**************************** Copyright(C) pxf ****************************/
