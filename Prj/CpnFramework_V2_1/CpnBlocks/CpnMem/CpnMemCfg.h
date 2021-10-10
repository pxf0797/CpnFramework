/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:39:10
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMEMCFG_H_
#define CPNMEMCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnMemCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNMEMCFG_ERR_ID                        0U    /* CpnMemCfg component error report ID. */
#define CPNMEMCFG_MEM_SPACE_SIZE          (8U*1024U) /* Manage memory space size. */

#define CPNMEMCFG_DBG_INFO_PRINT_FILE     1U  /* Print to file, 0no, 1yes. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNMEMCFG_FUNC,
} TE_CPNMEMCFG_ERR_CLASSIFY;
/* Error code.
 **********************************************************/
#define CPNMEMCFG_ERR_CODE                      (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNMEMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNMEMCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
