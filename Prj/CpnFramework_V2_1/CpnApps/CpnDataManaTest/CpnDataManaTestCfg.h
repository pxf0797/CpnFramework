/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaTestCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/08 11:41:08
 * Description  : 
 * Others       : 
 * History      : 20211008 pxf Initially established.
 **************************************************************************/

#ifndef CPNDATAMANATESTCFG_H_
#define CPNDATAMANATESTCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnDataManaTestCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNDATAMANATESTCFG_ERR_ID               0U    /* CpnDataManaTestCfg component error report ID. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNDATAMANATESTCFG_FUNC,
} teCpnDataManaTestCfgErrClassify;
/* Error code.
 **********************************************************/
#define CPNDATAMANATESTCFG_ERR_CODE             (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNDATAMANATESTCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNDATAMANATESTCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
