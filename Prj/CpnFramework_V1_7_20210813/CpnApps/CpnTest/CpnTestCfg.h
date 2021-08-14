/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTestCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 17:06:41
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNTESTCFG_H_
#define CPNTESTCFG_H_

/* Include head files. */
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnTestCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNTESTCFG_ERR_ID                       0U    /* CpnTestCfg component error report ID. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNTESTCFG_FUNC,
} TE_CPNTESTCFG_ERR_CLASSIFY;
/* Error code.
 **********************************************************/
#define CPNTESTCFG_ERR_CODE                     (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNTESTCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNTESTCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
