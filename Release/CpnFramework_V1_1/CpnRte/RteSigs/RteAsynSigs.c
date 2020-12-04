/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsynSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:12
* Description  :
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./RteSigs.h"

/***********************************************************
* set get定义
***********************************************************/
/*定义收发信号缓存
***********************************************/
BUFF_SETGET_DEFINE(RteAsynSigs,SIGNAL_SET_LIST_RTEASYN,SIGNAL_GET_MAP_LIST_RTEASYN);
/*定义收发类
***********************************************/
RteAsyn clRteAsynSigs;

/***********************************************************
* get set初始化
***********************************************************/
/*注册信号及初始化发送接收类
***********************************************/
void RteAsynSetGetInit(void)
{
    /*对信号进行注册
    ***********************************************/
    SIGNALS_GETSET_REGISTER(SIGNAL_SET_LIST_RTEASYN,ASYN_SET_SIGNAL_REGISTER);
    SIGNALS_GETSET_REGISTER(SIGNAL_GET_MAP_LIST_RTEASYN,ASYN_GET_SIGNAL_REGISTER);

    /*初始化调用类
    ***********************************************/
    CN(RteAsyn,&clRteAsynSigs,RteAsynSigsSigSetBuff,RteAsynSigsSigSetIndex,RteAsynSigsSigGetIndex);
    if(OPRS(clRteAsynSigs) != NULL){}
}

/**************************** Copyright(C) pxf ****************************/
