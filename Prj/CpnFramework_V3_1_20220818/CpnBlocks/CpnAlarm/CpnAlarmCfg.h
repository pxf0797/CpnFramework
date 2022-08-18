/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnAlarmCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/06/07 20:02:39
 * Description  :
 * Others       :
 * History      : 20210607 pxf Initially established.
 **************************************************************************/

#ifndef CPNALARMCFG_H_
#define CPNALARMCFG_H_

/* Include head files. */
#include "CpnErrCfg.h"
#include "StandType.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnAlarmCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNALARMCFG_ERR_ID                      0U    /* CpnAlarmCfg component error report ID. */
#define CPNALARMCFG_TASK_SLICE_PERIOD           2u /* ms */
#define CPNALARMCFG_ALARM_EXECUTE_PERIOD        10u /* ms */ /* it must be times of CPNALARMCFG_TASK_SLICE_PERIOD */

/* CpnAlarmCfg data type.
 **********************************************/
typedef enum {
    SERIOUS_HIGH,
    SERIOUS_MEDIUM,
    SERIOUS_LOW,
    SERIOUS_NO,

    SERIOUS_MAX_COUNT
} teSeriousLevel;
typedef enum {
    CLASS_COMMON,
    CLASS_SYS,
    CLASS_BLOCK,

    CLASS_MAX_COUNT
} teClassify;
typedef struct {
    uint16 eventNum;    /* all detected nums */
    uint16 *events;
    uint16 upgradeNum;  /* part of eventNum, only upgrade part */
    uint16 *upgrades;
} tsEvents, *htsEvents;


/* CpnAlarmCfg data type.
 **********************************************/
typedef uint32 alarmType; /* size should not bigger than 32, otherwise CPNSINK_TYPE_BITS need to be configured manually */
#define CPNALAEM_TYPE_BITS                    ((sizeof(alarmType)>>1u)+3u)//0x5u//0x4u//
#define CPNALAEM_TYPE_WIDTH                   (1u<<CPNALAEM_TYPE_BITS)
#define CPNALAEM_TYPE_MASK                    (CPNALAEM_TYPE_WIDTH-1u)

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNALARMCFG_FUNC,
} teCpnAlarmCfgErrClassify;
/* Error code.
 **********************************************************/
#define CPNALARMCFG_MEM_MALLOC_FAIL           (ERR_TYPE_BLOCK|ERR_SEVERITY_HIGH|(ERR_CPNALARMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|0u) /* memory malloc fail. */
#define CPNALARMCFG_REGIST_FAIL               (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNALARMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|1u) /* regist fail. */
#define CPNALARMCFG_REGIST_UP_FAIL            (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNALARMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|2u) /* regist alarm upgrade fail. */
#define CPNALARMCFG_ALARM_BUFF_LESS           (ERR_TYPE_BLOCK|ERR_SEVERITY_LOW|(ERR_CPNALARMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|3u) /* to get alarm event, alarm buffer not enough. */
#define CPNALARMCFG_ALARMUP_BUFF_LESS         (ERR_TYPE_BLOCK|ERR_SEVERITY_LOW|(ERR_CPNALARMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|4u) /* to get alarm upgrade event, alarm buffer not enough. */
#define CPNALARMCFG_ALARM_NUM_NOT_CORRESPOND  (ERR_TYPE_BLOCK|ERR_SEVERITY_LOW|(ERR_CPNALARMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|5u) /* alarm event num is not correspond to get. */
#define CPNALARMCFG_ALARMUP_NUM_NOT_CORRESPOND (ERR_TYPE_BLOCK|ERR_SEVERITY_LOW|(ERR_CPNALARMCFG_FUNC<<ERR_CLASSIFY_SHIFT)|6u) /* alarm upgrade event num is not correspond to get. */


#endif /*CPNALARMCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
