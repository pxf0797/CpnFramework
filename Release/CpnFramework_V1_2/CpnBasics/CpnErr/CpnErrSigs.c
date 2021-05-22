/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErrSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  : CpnErr����źŶ���Դ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnErr.h"
#include "./CpnErrSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnErr�ඨ��
***********************************************************/
/*CpnErr��
***********************************************/
CpnErr clCpnErr;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnErr_init(void){
    CN(CpnErr,&clCpnErr, &clFifoCpnErr);
    if(OPRS(clCpnErr) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnErr;
        taskParam.prdTick = 2*MS_T;
        taskParam.startTick = 1*MS_T;
        taskParam.strgMask = task_strategy_basic_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_initTask, (uint8*)&taskParam);
    }
}

/*����
***********************************************/
void serv_CpnErr_setErr(void *buff){
    uint32 ulErrCode = *(uint32*)buff;
    clCpnErr.setErr(clCpnErr.self, ulErrCode);
}

/*�ӿڴ���
***********************************************/
//void trig_CpnErr_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnErr(void){
    static tick sendDelay = 1000*MS_T;
//    tDataSig sendErrNum = {0u};
//
//    sendErrNum.id = 0x10u;
//    sendErrNum.data = clCpnErr.uwTotalErrNum;

    clCpnErr.run(clCpnErr.self);

    /* delay send */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_delay, (uint8*)&sendDelay);
    if(IS_TIMEOUT(sendDelay)){
        sendDelay = 5000*MS_T;
        //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnErr_sendSig, (uint8*)&sendErrNum);
    }
}

/**************************** Copyright(C) pxf ****************************/
