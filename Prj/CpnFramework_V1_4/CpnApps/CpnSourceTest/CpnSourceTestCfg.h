/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceTestCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:59:39
 * Description  : 
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSOURCETESTCFG_H_
#define CPNSOURCETESTCFG_H_

/* Include head files. */
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnSourceTestCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNSOURCETESTCFG_ERR_ID                 0U    /* CpnSourceTestCfg component error report ID. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNSOURCETESTCFG_FUNC,
} TE_CPNSOURCETESTCFG_ERR_CLASSIFY;
 * Error code.
 **********************************************************/
#define CPNSOURCETESTCFG_ERR_CODE               (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSOURCETESTCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNSOURCETESTCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
