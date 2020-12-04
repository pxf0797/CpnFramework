/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  : CpnSource����źŶ���Դ�ļ�
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnSource.h"
#include "./CpnSourceSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnSource�ඨ��
***********************************************************/
/*CpnSource��
***********************************************/
CpnSource clCpnSource;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnSource_init(void){
    CN(CpnSource,&clCpnSource,trig_CpnSource_inf_setErr);
    if(OPRS(clCpnSource) != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnSource;
        taskParam.prdTick = 1;//1*MS_T;
        taskParam.startTick = 5*MS_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_addTask, (uint8*)&taskParam);
    }
}

/*����
***********************************************/
void serv_CpnSource_registWaveSig(void *buff){
    clCpnSource.regist(clCpnSource.self, (htSourceParams)buff);
}
/*����
***********************************************/
void serv_CpnSource_changeWaveSig(void *buff){
    clCpnSource.change(clCpnSource.self, (htSourceParams)buff);
}

/*�ӿڴ���
***********************************************/
//void trig_CpnSource_inf_infFunc(void){}
/*������ӿڴ���
***********************************************/
void trig_CpnSource_inf_setErr(uint16 id, uint16 code){
    uint32 uwErrCode = (((uint32)id << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSource_setErr, (uint8*)&uwErrCode);
}


/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnSource(void){
    clCpnSource.run(clCpnSource.self);
}

/**************************** Copyright(C) pxf ****************************/
