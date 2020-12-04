/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSynSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:24
* Description  :
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./RteSigs.h"

/***********************************************************
* trig serv����
***********************************************************/
/*������񴥷��źŻ���
***********************************************/
BUFF_SERVTRIG_DEFINE(RteSynSigs,SIGNAL_SERV_LIST_RTESYN,SIGNAL_TRIG_MAP_LIST_RTESYN);
/*������񴥷���
***********************************************/
RteSyn clRteSynSigs;

/***********************************************************
* trig serv��ʼ��
***********************************************************/
/*ע���źż���ʼ�����񴥷���
***********************************************/
void RetSynServTrigInit(void)
{
    /*���źŽ���ע��
    ***********************************************/
    SIGNALS_SERVTRIG_REGISTER(SIGNAL_SERV_LIST_RTESYN,SYN_SERV_SIGNAL_REGISTER);
    SIGNALS_SERVTRIG_REGISTER(SIGNAL_TRIG_MAP_LIST_RTESYN,SYN_TRIG_SIGNAL_REGISTER);

    /*��ʼ��������
    ***********************************************/
    CN(RteSyn,&clRteSynSigs,RteSynSigsSigServBuff,RteSynSigsSigTrigIndex);
    if(OPRS(clRteSynSigs) != NULL){}
}

/**************************** Copyright(C) pxf ****************************/
