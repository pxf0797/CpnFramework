/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemTestCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:45:13
 * Description  : 
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMEMTESTCFG_H_
#define CPNMEMTESTCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnMemTestCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNMEMTESTCFG_ERR_ID                    0U    /* CpnMemTestCfg component error report ID. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNMEMTESTCFG_FUNC,
} TE_CPNMEMTESTCFG_ERR_CLASSIFY;
/* Error code.
 **********************************************************/
#define CPNMEMTESTCFG_ERR_CODE                  (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNMEMTESTCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNMEMTESTCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
