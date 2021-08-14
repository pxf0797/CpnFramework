/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteAsynSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:48:45
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./RteSigs.h"

/***********************************************************
 * set get definition.
 **********************************************************/
/* get set signals buffer definition.
 **********************************************/
BUFF_SETGET_DEFINE(RteAsynSigs,SIGNAL_SET_LIST_RTEASYN,SIGNAL_GET_MAP_LIST_RTEASYN);
/* Asynchronize class definition.
 **********************************************/
RteAsyn clRteAsynSigs;

/***********************************************************
 * get set initialization.
 **********************************************************/
/* Register signals and initial Asynchronize class.
***********************************************/
void RteAsynSetGetInit(void)
{
    /* Register signals.
     **********************************************/
    SIGNALS_GETSET_REGISTER(SIGNAL_SET_LIST_RTEASYN,ASYN_SET_SIGNAL_REGISTER);
    SIGNALS_GETSET_REGISTER(SIGNAL_GET_MAP_LIST_RTEASYN,ASYN_GET_SIGNAL_REGISTER);

    /* Initial class.
     **********************************************/
    CN(RteAsyn,&clRteAsynSigs,RteAsynSigsSigSetBuff,RteAsynSigsSigSetIndex,RteAsynSigsSigGetIndex);
    if(OPRS(clRteAsynSigs) != NULL){}
}

/**************************** Copyright(C) pxf ****************************/
