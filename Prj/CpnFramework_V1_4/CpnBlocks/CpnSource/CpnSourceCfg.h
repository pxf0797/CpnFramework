/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:32:56
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSOURCECFG_H_
#define CPNSOURCECFG_H_

/* Include head files. */
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnSourceCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNSOURCECFG_ERR_ID             0U    /* CpnSourceCfg component error report ID. */
#define CPNSOURCECFG_WAVE_TYPE_GROUPS       1U    /* Signal wave array counters. */

typedef enum{
    ERR_CPNSOURCE_WAVE,
    ERR_CPNSOURCE_PARAM,
} TE_CPNSOURCE_ERR_CLASSIFY;
/*errDefine
***********************************************************************************************************************/
#define CPNSOURCECFG_WAVE_GROUP_FULL          (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSOURCE_WAVE<<ERR_CLASSIFY_SHIFT)|0) /* Signals group is full. */
#define CPNSOURCECFG_WAVE_INDEX_OUT_RANGE     (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSOURCE_WAVE<<ERR_CLASSIFY_SHIFT)|1) /* Signals index out of range. */
#define CPNSOURCECFG_WAVE_INDEX_NOT_EXIST     (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSOURCE_WAVE<<ERR_CLASSIFY_SHIFT)|2) /* Signals index not exist. */
#define CPNSOURCECFG_WAVE_NO_SUCH_KIND        (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSOURCE_WAVE<<ERR_CLASSIFY_SHIFT)|3) /* Signal type not exist. */

#define CPNSOURCECFG_WAVE_DUTY_OUT_RANGE      (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSOURCE_PARAM<<ERR_CLASSIFY_SHIFT)|4) /* Parameter, duty out of range. */
#define CPNSOURCECFG_WAVE_PHASE_OUT_RANGE     (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNSOURCE_PARAM<<ERR_CLASSIFY_SHIFT)|5) /* Parameter, phase out of range. */

#endif /*CPNSOURCECFG_H_*/

/**************************** Copyright(C) pxf ****************************/
