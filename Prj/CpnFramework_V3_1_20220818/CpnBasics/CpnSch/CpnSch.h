/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSch.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  : CpnSch class and interface declaration file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CPNSCH_H_
#define CPNSCH_H_

/* Include head files. */
#include "Oopc.h"
#include "StandType.h"
#include "CpnSchCfg.h"
#include "SchTask.h"
#include "SchEvent.h"
#include "FuncLib.h"
#include "CpnSchSigs.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSCH_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Delay service data type declaration.
 **********************************************/
typedef uint32 tick;
/* Real time service data type declaration.
 **********************************************/
typedef uint16 point;
/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
INF(iInitCpn){
    void (*initCpn)(void);
};

/***********************************************************
 * CpnSch class definition.
 **********************************************************/

/* CpnSch class declaration.
 **********************************************/
CL(CpnSch){
    hCpnSch self;
    hCpnSch (*init)(hCpnSch cthis, uint8 *space, uint32 size,
        hstaAct SchSm,
        void (*getTime)(uint16 *point),
        void (*initCpn)(void),
        rbType (*rbOrder)(void *block),
        void (*eventTask)(void));

    /* CpnSch dynamic memory. */
    hBlockM mem;

    /* Tasks and event search tree. */
    uint16 taskCount;
    htsTask tasks;
    hRBTree rbTree;
    /* task management. */
    hSchTask taskM;
    /* event management. */
    hSchEvent event;

    /* CpnSch class functions. */
    void (*regist)(hCpnSch cthis, htsInitTask t);
    void (*err)(hCpnSch cthis, uint16 code);
    /* Interfaces */
    IMPL(iInitCpn);
};

#endif /*CPNSCH_H_*/

/**************************** Copyright(C) pxf ****************************/
