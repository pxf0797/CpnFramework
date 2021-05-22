/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnErrCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 14:10:28
 * Description  :
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CPNERRCFG_H_
#define CPNERRCFG_H_

/* Include head files. */


/***********************************************************
 * Configure parameters.
 **********************************************************/
 #define CPNERR_FIFO_BUFF_LENGTH            64U   /* Number of queue storage failures */
/* Error reporting ID, all modules need to be registered in this file.
 **********************************************/
typedef enum {
    CPNSCHCFG_ERR_ID,
    CPNSOURCECFG_ERR_ID,
    CPNSINKSCFG_ERR_ID,
} TE_ERR_ID;

/* Error classify.
 **********************************************/
typedef enum{
    /* Error type. */
    ERR_TYPE_MASK = 0xF000u,
    ERR_TYPE_SHIFT = 0x0000Cu,
    ERR_TYPE_SYS = 0x0000u,
    ERR_TYPE_BLOCK = 0x1000u,
    ERR_TYPE_FUNC = 0x2000u,
    /* Severity type. */
    ERR_SEVERITY_MASK = 0x0C00u,
    ERR_SEVERITY_SHIFT = 0x0000Au,
    ERR_SEVERITY_NO = 0x0000u,
    ERR_SEVERITY_LOW = 0x0400u,
    ERR_SEVERITY_MEDIUM = 0x0800u,
    ERR_SEVERITY_HIGH = 0x0C00u,
    /* Classify type. */
    ERR_CLASSIFY_MASK = 0x03F0u,
    ERR_CLASSIFY_SHIFT = 0x0004u,
    /* Index type. */
    ERR_INDEX_MASK = 0x000Fu,
    ERR_INDEX_SHIFT = 0x0000u,
} TE_ERR_CLASSIFY;
/* Error total type = Error type + Severity type + total counts 1.
 **********************************************/
#define ERROR_TOTAL_TYPES        (16u+4u+1u)


#endif /*CPNERRCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
