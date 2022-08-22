/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteSynSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:48:34
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "RteSigs.h"

/***********************************************************
 * trig serv definition.
 **********************************************************/
/* trig serv signals buffer definition.
 **********************************************/
BUFF_SERVTRIG_DEFINE(RteSynSigs,SIGNAL_SERV_LIST_RTESYN,SIGNAL_TRIG_MAP_LIST_RTESYN);
/* Synchronize class definition.
 **********************************************/
static RteSyn clRteSynSigs;

/***********************************************************
 * trig serv initialization.
 **********************************************************/
/* Register signals and initial Synchronize class.
***********************************************/
void RetSynServTrigInit(void)
{
    /* Register signals.
     **********************************************/
    SIGNALS_SERVTRIG_REGISTER(SIGNAL_SERV_LIST_RTESYN,SYN_SERV_SIGNAL_REGISTER);
    SIGNALS_SERVTRIG_REGISTER(SIGNAL_TRIG_MAP_LIST_RTESYN,SYN_TRIG_SIGNAL_REGISTER);

    /* Initial class.
     **********************************************/
    CN(RteSyn,&clRteSynSigs,RteSynSigsSigServBuff,RteSynSigsSigTrigIndex);
    if(OPRS(clRteSynSigs) != NULL){}
}

/* Interface trigger signal.
***********************************************/
void if_trig(synType signal, uint8 *buff){
    clRteSynSigs.trig(clRteSynSigs.self, signal, buff);
}

/**************************** Copyright(C) pxf ****************************/
