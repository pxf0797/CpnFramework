/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  : CpnSinks����źŶ���Դ�ļ�
* Others       :
* History      : 200730 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnSinks.h"
#include "./CpnSinksSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnSinks�ඨ��
***********************************************************/
/*CpnSinks��
***********************************************/
CpnSinks clCpnSinks;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnSinks_init(void){
    CN(CpnSinks,&clCpnSinks,trig_CpnSinks_inf_setErr);
    if(OPRS(clCpnSinks) != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSinks;
        taskParam.prdTick = 1;//11*MS_T;
        taskParam.startTick = 5*MS_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_addTask, (uint8*)&taskParam);
    }
}

/*����
***********************************************/
void serv_CpnSinks_readData(void *buff){
    if(clCpnSinks.readData(clCpnSinks.self,((htSinksOut)buff)->sinks,((htSinksOut)buff)->buff)){
        ((htSinksOut)buff)->outOperation = TRUE;
    }else{
        ((htSinksOut)buff)->outOperation = FALSE;
    }
}
/*����
***********************************************/
void serv_CpnSinks_trigStart(void *buff){
    clCpnSinks.trigStart(clCpnSinks.self,(htSinksParams)buff);
}
/*����
***********************************************/
void serv_CpnSinks_cacheSta(void *buff){
    ((htSinksSta)buff)->sta= clCpnSinks.cacheSta(clCpnSinks.self,((htSinksSta)buff)->sinks);
}
/*����
***********************************************/
void serv_CpnSinks_registCache(void *buff){
    clCpnSinks.registCache(clCpnSinks.self,(htSinksParams)buff);
}
/*����
***********************************************/
void serv_CpnSinks_reCache(void *buff){
    clCpnSinks.reCache(clCpnSinks.self,(htSinksParams)buff);
}

/*�ӿڴ���
***********************************************/
//void trig_CpnSinks_inf_infFunc(void){}
/*������ӿڴ���
***********************************************/
void trig_CpnSinks_inf_setErr(uint16 id, uint16 code){
    uint32 uwErrCode = (((uint32)id << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_setErr, (uint8*)&uwErrCode);
}


/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnSinks(void){
    clCpnSinks.run(clCpnSinks.self);
}

/**************************** Copyright(C) pxf ****************************/
