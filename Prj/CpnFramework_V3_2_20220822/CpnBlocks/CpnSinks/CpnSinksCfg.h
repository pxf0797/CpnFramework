/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:09:52
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSINKSCFG_H_
#define CPNSINKSCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnSinksCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNSINKSCFG_ERR_ID              0U    /* CpnSinksCfg component error report ID. */
#define CPNSINKSCFG_CACHE_TYPE_GROUPS       1U    /* Signal wave array counters. */

/* CpnSinkCfg data type.
 **********************************************/
typedef uint16 sinkType; /* size should not bigger than 32, otherwise CPNSINK_TYPE_BITS need to be configured manually */
#define CPNSINK_TYPE_BITS                     ((sizeof(sinkType)>>1u)+3u)//0x5u//0x4u//
#define CPNSINK_TYPE_WIDTH                    (1u<<CPNSINK_TYPE_BITS)
#define CPNSINK_TYPE_MASK                     (CPNSINK_TYPE_WIDTH-1u)

/* CpnSinkCfg error classify.
 **********************************************/
typedef enum{
    ERR_CPNSINKS_CACHE,
} TE_CPNSINKS_ERR_CLASSIFY;
/*errDefine
***********************************************************************************************************************/
#define CPNSINKSCFG_CACHE_GROUP_FULL              (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKS_CACHE<<ERR_CLASSIFY_SHIFT)|0) /* Signals group is full. */
#define CPNSINKSCFG_CACHE_INDEX_OUT_RANGE         (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKS_CACHE<<ERR_CLASSIFY_SHIFT)|1) /* Signals index out of range. */
#define CPNSINKSCFG_CACHE_INDEX_NOT_EXIST         (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKS_CACHE<<ERR_CLASSIFY_SHIFT)|2) /* Signals index not exist. */
#define CPNSINKSCFG_CACHE_NO_SUCH_KIND            (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKS_CACHE<<ERR_CLASSIFY_SHIFT)|3) /* Signal type not exist. */
#define CPNSINKSCFG_CACHE_DATA_SIZE_ERR           (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKS_CACHE<<ERR_CLASSIFY_SHIFT)|4) /* Signal data size error. */
#define CPNSINKSCFG_CACHE_DATA_BUFF_ERR           (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKS_CACHE<<ERR_CLASSIFY_SHIFT)|5) /* Signal data address error. */
#define CPNSINKSCFG_CACHE_FIFO_INIT_ERR           (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSINKS_CACHE<<ERR_CLASSIFY_SHIFT)|6) /* Cache buffer initial fail. */

#endif /*CPNSINKSCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
