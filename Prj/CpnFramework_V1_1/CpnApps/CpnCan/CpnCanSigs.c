/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCanSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 16:09:24
* Description  : CpnCan����źŶ���Դ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCan.h"
#include "./CpnCanSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnCan�ඨ��
***********************************************************/
/*CpnCan��
***********************************************/
CpnCan clCpnCan;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnCan_init(void){
    CN(CpnCan,&clCpnCan, &clFifoCpnCan);
    if(OPRS(clCpnCan) != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnCan;
        taskParam.prdTick = 19*MS_T;//201*MS_T;
        taskParam.startTick = 5*S_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCan_addTask, (uint8*)&taskParam);
    }
}

/*����
***********************************************/
void serv_CpnCan_sendSig(void *sig){
    //clCpnCan.send(clCpnCan.self, (tDataSig*)sig);
    clCpnCan.clFifoSend->push(clCpnCan.clFifoSend, sig);
}
/*����
***********************************************/
void serv_CpnCan_receiveSig(void *sig){}

/*�ӿڴ���
***********************************************/
//void trig_CpnCan_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnCan(void){
    clCpnCan.run(clCpnCan.self);
}

/**************************** Copyright(C) pxf ****************************/
