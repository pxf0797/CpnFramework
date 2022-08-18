/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFuncLibTestCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/11/03 14:55:04
 * Description  : 
 * Others       : 
 * History      : 20211103 pxf Initially established.
 **************************************************************************/

#ifndef CPNFUNCLIBTESTCFG_H_
#define CPNFUNCLIBTESTCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnFuncLibTestCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNFUNCLIBTESTCFG_ERR_ID                0U    /* CpnFuncLibTestCfg component error report ID. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNFUNCLIBTESTCFG_FUNC,
} teCpnFuncLibTestCfgErrClassify;
/* Error code.
 **********************************************************/
#define CPNFUNCLIBTESTCFG_ERR_CODE              (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNFUNCLIBTESTCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNFUNCLIBTESTCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
