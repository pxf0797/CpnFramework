/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SchSm.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:12:12
 * Description  : State machine SchSm declaration and state machine use cases.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef SCHSM_H_
#define SCHSM_H_

/* Include head files. */
#include "StandType.h"
#include "CpnSchCfg.h"
#include "Sm.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define SCHSM_MACRO_VERSION             0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/* State machine SchSm use example:
 * State machine SchSm has been defined in SMDF, all you need to do is let it running.
* There are two operation modes of the state machine:
 * SMR directly driven by the clock and SMRE driven by the custom recording state.
 **********************************************
 * type SMR
 **********************************************
void test(void){
    while(1){SMR(SchSm);};
}
 **********************************************
 * type SMRE
 **********************************************
void test2(void){
    static SchSmRec SchSmRunRec = {SchSm_sta_init};
    while(1){SMRE(SchSm, SchSmRunRec);};
}
 **********************************************/

/* Interface declaration.
 **********************************************/
typedef void(*task)(void);                        /* Task definition. */

/* Task group declaration.
***********************************************/
typedef struct{
    uint16 startTick[sizeof(taskGroupType)<<3U];  /* Schedule period start tick. */
    uint16 prdTick[sizeof(taskGroupType)<<3U];    /* Schedule period tick. */
    taskGroupType unstartMask;                    /* Task deactivate mask. */
    taskGroupType actMask;                        /* Task activate mask. */
    taskGroupType taskMask;                       /* Task allocate mask. */
    task taskGroup[sizeof(taskGroupType)<<3U];    /* Task group. */
} taskGroupSm;

/* State machine SchSm state list definition.
 * Note: SchSm_init undefined in this list, it will be given by default.
***********************************************/
#define SCHSM_LIST(_)         \
    _(SchSm, update)          \
    _(SchSm, execute)         \


#define TASK_EXECUTE_DEVIATION_STEPS              2u /* steps deviation. */
/* State machine SchSm declaration.
 * It is given state record next, and last state record last. You can added other parameters.
 **********************************************/
SMDC(SchSm, SCHSM_LIST){
    sta next;               /* Running state record. */
    sta last;               /* Last state record. */
    uint16 ticker;          /* Counter. */
    uint16 tickerLast;      /* Last counter. */
    uint16 taskMeasureEn;   /* task measure enable. */
    uint16 taskGroupNum;    /* Task group counters. */
    uint16 taskLevelGroupIndex[level_max];             /* Task level max nums. */
    uint16 taskLevelMaxNum[level_max];                 /* Task level max nums. */
    uint16 taskLevelCounter[level_max];                /* Task level counter. */
    taskGroupSm taskGroups[CPN_SCH_GROUP_TOTAL_NUMS];  /* Task groups. */
    void *SchTask;          /* Inject Component class. */
};

#endif /*SCHSM_H_*/

/**************************** Copyright(C) pxf ****************************/
