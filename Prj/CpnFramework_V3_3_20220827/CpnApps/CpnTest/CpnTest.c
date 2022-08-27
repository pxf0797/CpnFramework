/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTest.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 17:06:41
 * Description  : CpnTest class functions definition source files.
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnTest.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnTest class definition.
 **********************************************************/
/* Function : CpnTest_run(hCpnTest cthis)
 * Input    : cthis - CpnTest class pointer
 * Output   :  
 * Others   : CpnTest class function.
 **********************************************/
void CpnTest_run(hCpnTest cthis){
    /* TODO */
}

/* Function : hCpnTest CpnTest_init(hCpnTest cthis)
 * Input    : cthis - CpnTest class pointer
 * Output   : hCpnTest - cthis/OOPC_NULL
 * Others   : CpnTest class initial function.
 **********************************************/
hCpnTest CpnTest_init(hCpnTest cthis){
    /* Configure functions. */
    //cthis->run = CpnTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnTest CpnTest_ctor(hCpnTest cthis)
 * Input    : cthis - CpnTest class pointer
 * Output   : hCpnTest - cthis/OOPC_NULL
 * Others   : CpnTest class constructor.
 **********************************************/
CC(CpnTest){
    cthis->init = CpnTest_init;
    cthis->run = CpnTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCpnTest CpnTest_dtor(hCpnTest cthis)
 * Input    : cthis - CpnTest class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnTest class destructor.
 **********************************************/
CD(CpnTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
