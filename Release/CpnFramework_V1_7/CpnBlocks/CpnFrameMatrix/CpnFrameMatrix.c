/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFrameMatrix.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:56:01
 * Description  : CpnFrameMatrix class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnFrameMatrix.h"
#include "./FrameBitLib.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnFrameMatrix class definition.
 **********************************************************/
/* Function : CpnFrameMatrix_getFrame(hCpnFrameMatrix cthis)
 * Input    : cthis - CpnFrameMatrix class pointer
 * Output   :
 * Others   : CpnFrameMatrix class function.
 **********************************************/
void CpnFrameMatrix_getFrame(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 *value){
    getFrameData(cthis->frame.data, cthis->format, bit_start, bit_len, value);
}

/* Function : CpnFrameMatrix_setFrame(hCpnFrameMatrix cthis)
 * Input    : cthis - CpnFrameMatrix class pointer
 * Output   :
 * Others   : CpnFrameMatrix class function.
 **********************************************/
void CpnFrameMatrix_setFrame(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 value){
    setFrameData(cthis->frame.data, cthis->format, bit_start, bit_len, value);
}

/* Function : hCpnFrameMatrix CpnFrameMatrix_init(hCpnFrameMatrix cthis)
 * Input    : cthis - CpnFrameMatrix class pointer
 * Output   : hCpnFrameMatrix - cthis/OOPC_NULL
 * Others   : CpnFrameMatrix class initial function.
 **********************************************/
hCpnFrameMatrix CpnFrameMatrix_init(hCpnFrameMatrix cthis, uint32 id, teRxTxType rxtx, teFrameFormat format, uint16 period){
    /* Configure functions. */
    //cthis->getFrame = CpnFrameMatrix_getFrame;
    /* TODO */

    /* Configure parameters. */
    cthis->id = id;
    cthis->rxtx = rxtx;
    cthis->format = format;
    cthis->period = period;

    return cthis;
}

/* Function : hCpnFrameMatrix CpnFrameMatrix_ctor(hCpnFrameMatrix cthis)
 * Input    : cthis - CpnFrameMatrix class pointer
 * Output   : hCpnFrameMatrix - cthis/OOPC_NULL
 * Others   : CpnFrameMatrix class constructor.
 **********************************************/
CC(CpnFrameMatrix){
    cthis->init = CpnFrameMatrix_init;
    cthis->getFrame = CpnFrameMatrix_getFrame;
    cthis->setFrame = CpnFrameMatrix_setFrame;
    /* TODO */

    /* Configure parameters. */
    cthis->counter = 0;
    memSet(cthis->frame.data, 0, sizeof(cthis->frame.data));
    return cthis;
}

/* Function : hCpnFrameMatrix CpnFrameMatrix_dtor(hCpnFrameMatrix cthis)
 * Input    : cthis - CpnFrameMatrix class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnFrameMatrix class destructor.
 **********************************************/
CD(CpnFrameMatrix){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
