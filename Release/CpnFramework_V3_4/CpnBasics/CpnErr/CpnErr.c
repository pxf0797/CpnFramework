/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnErr.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 14:10:28
 * Description  : CpnErr class functions definition source files.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnErr.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/


/***********************************************************
 * CpnErr class definition.
 **********************************************************/
/* Function : CpnErr_setErr(hCpnErr cthis)
 * Input    : cthis - CpnErr class pointer
 * Output   :
 * Others   : CpnErr class function.
 **********************************************/
uint16 CpnErr_setErr(hCpnErr cthis, uint32 errCode){
    return cthis->clFifo->push(cthis->clFifo, &errCode);
}

/* Function : CpnErr_run(hCpnErr cthis)
 * Input    : cthis - CpnErr class pointer
 * Output   :
 * Others   : CpnErr class function.
 **********************************************/
void CpnErr_run(hCpnErr cthis){
    tsErrCode code;
    uint16 uwIndex = 0u;

    if(cthis->clFifo->fout(cthis->clFifo, &code)){
        uwIndex = ((code.code&ERR_TYPE_MASK)>>ERR_TYPE_SHIFT);
        cthis->uwErrNum[uwIndex]++;              /* Type error counters. */
        uwIndex = ((ERR_TYPE_MASK>>ERR_TYPE_SHIFT)+1u);
        uwIndex += ((code.code&ERR_SEVERITY_MASK)>>ERR_SEVERITY_SHIFT);
        cthis->uwErrNum[uwIndex]++;              /* Severity error counters. */
        uwIndex = (ERROR_TOTAL_TYPES-1u);
        cthis->uwErrNum[uwIndex]++;              /* Total error counters. */
    }
}

/* Function : hCpnErr CpnErr_init(hCpnErr cthis)
 * Input    : cthis - CpnErr class pointer
 * Output   : hCpnErr - cthis/OOPC_NULL
 * Others   : CpnErr class initial function.
 **********************************************/
hCpnErr CpnErr_init(hCpnErr cthis, hFifo clFifo, void *buff, uint16 buffSize, uint16 objectSize){
    uint16 i = 0u;

    /* Configure parameters. */
    for(i = 0u; i < ERROR_TOTAL_TYPES; i++){
        cthis->uwErrNum[i] = 0u;
    }
    cthis->clFifo = clFifo;
    CN(Fifo, cthis->clFifo, buff, buffSize, objectSize);
    if(OPRS(*cthis->clFifo) == OOPC_NULL){
        return OOPC_NULL;
    }

    return cthis;
}

/* Function : hCpnErr CpnErr_ctor(hCpnErr cthis)
 * Input    : cthis - CpnErr class pointer
 * Output   : hCpnErr - cthis/OOPC_NULL
 * Others   : CpnErr class constructor.
 **********************************************/
CC(CpnErr){
    /* Configure functions. */
    cthis->init = CpnErr_init;
    cthis->setErr = CpnErr_setErr;
    cthis->run = CpnErr_run;

    return cthis;
}

/* Function : hCpnErr CpnErr_dtor(hCpnErr cthis)
 * Input    : cthis - CpnErr class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnErr class destructor.
 **********************************************/
CD(CpnErr){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
