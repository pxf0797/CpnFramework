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
#include "./RteAsyn.h"

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
void RteAsyn_set(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len){
    uint8 *dest = ((uint8*)cthis->set_buff + cthis->set_index[signal]);
    uint8 *source = buff + len;
    uint16 i = len;
    while(i-- > 0u){
        dest--;
        source--;
        *dest = *source;
    }
}

/* Function : RteAsyn_get(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   :
 * Others   : RteAsyn class function.
 **********************************************/
void RteAsyn_get(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len){
    uint8 *dest = buff + len;
    uint8 *source = ((uint8*)cthis->set_buff + cthis->set_index[cthis->get_index[signal]]);
    uint16 i = len;
    while(i-- > 0u){
        dest--;
        source--;
        *dest = *source;
    }
}

/* Function : hRteAsyn RteAsyn_init(hRteAsyn cthis)
 * Input    : cthis - RteAsyn class pointer
 * Output   : hRteAsyn - cthis/OOPC_NULL
 * Others   : RteAsyn class initial function.
 **********************************************/
hRteAsyn RteAsyn_init(hRteAsyn cthis, uint8 *set_buff, uint16 *set_index, uint16 *get_index){
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
    /* TODO */

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
