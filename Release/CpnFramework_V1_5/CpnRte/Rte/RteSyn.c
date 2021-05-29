/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteSyn.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:15:23
 * Description  : RteSyn class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./RteSyn.h"
#include "./TriggerService.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * RteSyn class definition.
 **********************************************************/
/* Function : RteSyn_serv(hRteSyn cthis)
 * Input    : cthis - RteSyn class pointer
 * Output   :
 * Others   : RteSyn class function.
 **********************************************/
void RteSyn_serv(hRteSyn cthis, uint16 signal, uint8 *buff){
    void *func = cthis->serv_ServBuff[signal];
    if(func){
        if(buff){
            ((serv_param)func)(buff);
        }else{
            ((serv_void)func)();
        }
    }
}

/* Function : RteSyn_trig(hRteSyn cthis)
 * Input    : cthis - RteSyn class pointer
 * Output   :
 * Others   : RteSyn class function.
 **********************************************/
void RteSyn_trig(hRteSyn cthis, uint16 signal, uint8 *buff){
    cthis->serv(cthis, cthis->trig_index[signal], buff);
}

/* Function : hRteSyn RteSyn_init(hRteSyn cthis)
 * Input    : cthis - RteSyn class pointer
 * Output   : hRteSyn - cthis/OOPC_NULL
 * Others   : RteSyn class initial function.
 **********************************************/
hRteSyn RteSyn_init(hRteSyn cthis, void **serv_ServBuff, uint16 *trig_index){
    /* Configure functions. */
    //cthis->serv = RteSyn_serv;
    /* TODO */

    /* Configure parameters. */
    cthis->serv_ServBuff = serv_ServBuff;
    cthis->trig_index = trig_index;

    return cthis;
}

/* Function : hRteSyn RteSyn_ctor(hRteSyn cthis)
 * Input    : cthis - RteSyn class pointer
 * Output   : hRteSyn - cthis/OOPC_NULL
 * Others   : RteSyn class constructor.
 **********************************************/
CC(RteSyn){
    cthis->init = RteSyn_init;
    cthis->serv = RteSyn_serv;
    cthis->trig = RteSyn_trig;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hRteSyn RteSyn_dtor(hRteSyn cthis)
 * Input    : cthis - RteSyn class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : RteSyn class destructor.
 **********************************************/
CD(RteSyn){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
