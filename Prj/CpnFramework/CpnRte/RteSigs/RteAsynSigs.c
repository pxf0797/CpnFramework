/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsynSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:12
* Description  :
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./RteSigs.h"

/***********************************************************
* set get����
***********************************************************/
/*�����շ��źŻ���
***********************************************/
BUFF_SETGET_DEFINE(RteAsynSigs,SIGNAL_SET_LIST_RTEASYN,SIGNAL_GET_MAP_LIST_RTEASYN);
/*�����շ���
***********************************************/
RteAsyn clRteAsynSigs;

/***********************************************************
* get set��ʼ��
***********************************************************/
/*ע���źż���ʼ�����ͽ�����
***********************************************/
void RteAsynSetGetInit(void)
{
    /*���źŽ���ע��
    ***********************************************/
    SIGNALS_GETSET_REGISTER(SIGNAL_SET_LIST_RTEASYN,ASYN_SET_SIGNAL_REGISTER);
    SIGNALS_GETSET_REGISTER(SIGNAL_GET_MAP_LIST_RTEASYN,ASYN_GET_SIGNAL_REGISTER);

    /*��ʼ��������
    ***********************************************/
    CN(RteAsyn,&clRteAsynSigs,RteAsynSigsSigSetBuff,RteAsynSigsSigSetIndex,RteAsynSigsSigGetIndex);
    if(OPRS(clRteAsynSigs) != NULL){}
}

/**************************** Copyright(C) pxf ****************************/
