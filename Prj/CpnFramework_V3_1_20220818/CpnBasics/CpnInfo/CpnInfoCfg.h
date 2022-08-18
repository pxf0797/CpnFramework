/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnInfoCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/05/26 16:35:22
 * Description  :
 * Others       :
 * History      : 20210526 pxf Initially established.
 **************************************************************************/

#ifndef CPNINFOCFG_H_
#define CPNINFOCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnInfoCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNINFOCFG_ERR_ID                       0U    /* CpnInfoCfg component error report ID. */
#define CPNINFOCFG_REPORT_ENABLE                TRUE /* TRUE/FALSE */
#define CPNINFOCFG_INFO_BUFF_SIZE               256u /* byte */
#define CPNINFOCFG_FIFO_OBJECT_NUM              8u /* counter */

#define CPNINFOCFG_OUTPUT_FRAME_SIZE            8u /* output frame buffer size. unit byte. */
#define CPNINFOCFG_FRAME_ID                     0x6AAul /* frame send id. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNINFOCFG_FUNC,
} TE_CPNINFOCFG_ERR_CLASSIFY;
/* Error code.
 **********************************************************/
#define CPNINFOCFG_MEMORY_NOT_ENOUGH            (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNINFOCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Memory not enough. */
#define CPNINFOCFG_FIFO_IS_FULL                 (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNINFOCFG_FUNC<<ERR_CLASSIFY_SHIFT)|1) /* Fifo is full. */

#endif /*CPNINFOCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
