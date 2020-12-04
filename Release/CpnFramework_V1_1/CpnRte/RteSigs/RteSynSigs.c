/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSynSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:08:24
* Description  :
* Others       :
* History      : 191228 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./RteSigs.h"

/***********************************************************
* trig serv定义
***********************************************************/
/*定义服务触发信号缓存
***********************************************/
BUFF_SERVTRIG_DEFINE(RteSynSigs,SIGNAL_SERV_LIST_RTESYN,SIGNAL_TRIG_MAP_LIST_RTESYN);
/*定义服务触发类
***********************************************/
RteSyn clRteSynSigs;

/***********************************************************
* trig serv初始化
***********************************************************/
/*注册信号及初始化服务触发类
***********************************************/
void RetSynServTrigInit(void)
{
    /*对信号进行注册
    ***********************************************/
    SIGNALS_SERVTRIG_REGISTER(SIGNAL_SERV_LIST_RTESYN,SYN_SERV_SIGNAL_REGISTER);
    SIGNALS_SERVTRIG_REGISTER(SIGNAL_TRIG_MAP_LIST_RTESYN,SYN_TRIG_SIGNAL_REGISTER);

    /*初始化调用类
    ***********************************************/
    CN(RteSyn,&clRteSynSigs,RteSynSigsSigServBuff,RteSynSigsSigTrigIndex);
    if(OPRS(clRteSynSigs) != NULL){}
}

/**************************** Copyright(C) pxf ****************************/
