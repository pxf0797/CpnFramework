/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapTestSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 20:32:16
* Description  : CpnMatrixMapTest����źŶ���Դ�ļ�
* Others       :
* History      : 201202 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnMatrixMapTest.h"
#include "./CpnMatrixMapTestSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnMatrixMapTest�ඨ��
***********************************************************/
/*CpnMatrixMapTest��
***********************************************/
CpnMatrixMapTest clCpnMatrixMapTest;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnMatrixMapTest_init(void){
    CNNP(CpnMatrixMapTest,&clCpnMatrixMapTest);
    if(OPRS(clCpnMatrixMapTest) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnMatrixMapTest;
        taskParam.prdTick = 101*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_matrix_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_initTask, (uint8*)&taskParam);
    }
}

/*����
***********************************************/
// void serv_CpnMatrixMapTest_setDataA(void){}
/*����
***********************************************/
// void serv_CpnMatrixMapTest_getData1(void){}

/*�ӿڴ���
***********************************************/
//void trig_CpnMatrixMapTest_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnMatrixMapTest(void){
    clCpnMatrixMapTest.run(clCpnMatrixMapTest.self);
}

/**************************** Copyright(C) pxf ****************************/
