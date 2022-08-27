/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteAsyn.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:15:43
 * Description  : RteAsyn class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "RteAsyn.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * RteAsyn class definition.
 **********************************************************/
/* Function : RteAsyn_set(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   :
 * Others   : RteAsyn class function.
 **********************************************/
void RteAsyn_set(hRteAsyn cthis, asynType signal, uint8 *buff){
    uint8 *dest = OOPC_NULL;
    uint8 *source = buff;
    asynType i = 0u;
    if(signal){
        dest = ((uint8*)cthis->set_buff + cthis->set_index[signal-1u]);
        i = cthis->set_index[signal-1u];
    }else{
        dest = (uint8*)cthis->set_buff;
    }
    while(i++ < cthis->set_index[signal]){
        *dest++ = *source++;
    }
}

/* Function : RteAsyn_get(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   :
 * Others   : RteAsyn class function.
 **********************************************/
void RteAsyn_get(hRteAsyn cthis, asynType signal, uint8 *buff){
    uint8 *dest = buff;
    uint8 *source = OOPC_NULL;
    asynType i = 0u;
    if(cthis->get_index[signal]){
        source = ((uint8*)cthis->set_buff + cthis->set_index[cthis->get_index[signal]-1u]);
        i = cthis->set_index[cthis->get_index[signal]-1u];
    }else{
        source = (uint8*)cthis->set_buff;
    }
    while(i++ < cthis->set_index[signal]){
        *dest++ = *source++;
    }
}

/* Function : RteAsyn_getAddr(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   :
 * Others   : RteAsyn class function.
 **********************************************/
void RteAsyn_getAddr(hRteAsyn cthis, asynType signal, void **addr){
    if(cthis->get_index[signal]){
        (*(uint8**)addr) = ((uint8*)cthis->set_buff + cthis->set_index[cthis->get_index[signal]-1u]);
    }else{
        (*(uint8**)addr) = (uint8*)cthis->set_buff;
    }
}

/* Function : hRteAsyn RteAsyn_init(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   : hRteAsyn - cthis/OOPC_NULL
 * Others   : RteAsyn class initial function.
 **********************************************/
hRteAsyn RteAsyn_init(hRteAsyn cthis, uint8 *set_buff, asynType *set_index, asynType *get_index){
    /* Configure functions. */
    //cthis->set = RteAsyn_set;
    /* TODO */

    /* Configure parameters. */
    cthis->set_buff = set_buff;
    cthis->set_index = set_index;
    cthis->get_index = get_index;

    return cthis;
}

/* Function : hRteAsyn RteAsyn_ctor(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   : hRteAsyn - cthis/OOPC_NULL
 * Others   : RteAsyn class constructor.
 **********************************************/
CC(RteAsyn){
    cthis->init = RteAsyn_init;
    cthis->set = RteAsyn_set;
    cthis->get = RteAsyn_get;
    cthis->getAddr = RteAsyn_getAddr;

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hRteAsyn RteAsyn_dtor(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : RteAsyn class destructor.
 **********************************************/
CD(RteAsyn){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
