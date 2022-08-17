/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksTestCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:53:35
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSINKSTESTCFG_H_
#define CPNSINKSTESTCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnSinksTestCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNSINKSTESTCFG_ERR_ID                  0U    /* CpnSinksTestCfg component error report ID. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNSINKSTESTCFG_FUNC,
} TE_CPNSINKSTESTCFG_ERR_CLASSIFY;
/* Error code.
 **********************************************************/
#define CPNSINKSTESTCFG_ERR_CODE                (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKSTESTCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNSINKSTESTCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
