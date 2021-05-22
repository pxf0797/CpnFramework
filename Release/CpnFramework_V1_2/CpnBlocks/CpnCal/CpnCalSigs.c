/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:06:36
* Description  : CpnCal����źŶ���Դ�ļ�
* Others       :
* History      : 201212 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCal.h"
#include "./CpnCalSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnCal�ඨ��
***********************************************************/
/*CpnCal��
***********************************************/
CpnCal clCpnCal;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnCal_init(void){
    CNNP(CpnCal,&clCpnCal);
    if(OPRS(clCpnCal) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnCal;
        taskParam.prdTick = 11*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_cal_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCal_initTask, (uint8*)&taskParam);
    }
}

/*����
***********************************************/
void serv_CpnCal_getCtrlBits(void){}
/*����
***********************************************/
void serv_CpnCal_getCmdBits(void){}
/*����
***********************************************/
void serv_CpnCal_getFrameLen(void){}
/*����
***********************************************/
void serv_CpnCal_getByte(void){}
/*����
***********************************************/
void serv_CpnCal_setCtrlBits(void){}
/*����
***********************************************/
void serv_CpnCal_setCmdBits(void){}
/*����
***********************************************/
void serv_CpnCal_setFrameLen(void){}
/*����
***********************************************/
void serv_CpnCal_setByte(void){}

/*�ӿڴ���
***********************************************/
//void trig_CpnCal_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnCal(void){}

/**************************** Copyright(C) pxf ****************************/
