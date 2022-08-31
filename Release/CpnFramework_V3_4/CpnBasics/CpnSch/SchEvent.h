/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SchEvent.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2022/04/10 11:11:02
 * Description  : SchEvent class and interface declaration file.
 * Others       :
 * History      : 20220410 pxf Initially established.
 **************************************************************************/

#ifndef SCHEVENT_H_
#define SCHEVENT_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "CpnSchCfg.h"
#include "FuncLib.h"


/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define SCHEVENT_MACRO_VERSION                  0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/

/* Data reference.
 **********************************************/
#define CPNEVENT_FIFO_MAX_LENGTH                32u /* fifo max length to store the event nums. */
#define CPNEVENT_DISPOSE_MAX_CFG                8u  /* event to dispose in one period. */
#define CPNEVENT_REFER_TASK_MAX_CFG             16u /* event reference task. when dispose event corresponding dispose task. */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
//INF(get){
//  uint16(*get)(void);
//};

/***********************************************************
 * SchEvent class definition.
 **********************************************************/
/* SchEvent class declaration.
 **********************************************/
CL(SchEvent){
    hSchEvent self;
    hSchEvent (*init)(hSchEvent cthis, hFifo fifo, uint8 *buff, uint16 maxNum, void *CpnSch);

    /* SchEvent class parameters. */
    hFifo fifo;
    uint8 *buff;
    uint16 maxNum;

    /* event refer tasks. */
    uint32 taskCount;
    htsRBNode nodes[CPNEVENT_REFER_TASK_MAX_CFG];

    /* SchEvent class functions. */
    void (*trig)(hSchEvent cthis, uint16 e);
    void (*run)(hSchEvent cthis);
    void (*err)(hSchEvent cthis, uint16 code);

    /* Inject Component class. */
    void *CpnSch;
};

#endif /*SCHEVENT_H_*/

/**************************** Copyright(C) pxf ****************************/
