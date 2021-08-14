/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSource.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:32:56
 * Description  : CpnSource class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSOURCE_H_
#define CPNSOURCE_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnSourceCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSOURCE_MACRO_VERSION         0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef struct{
    sourceType sourceMask;              /* signal register */
    tSourceParams sourceParams[CPNSOURCE_TYPE_WIDTH]; /* signal run params */
    uint16 sourceCounter[CPNSOURCE_TYPE_WIDTH]; /* signal drive counter */
} tWaveGroup, *htWaveGroup;
/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
//INF(get){
//  uint16(*get)(void);
//};
/* TODO */

/***********************************************************
 * CpnSource class definition.
 **********************************************************/
/* CpnSource class declaration.
 **********************************************/
CL(CpnSource){
    hCpnSource self;
    hCpnSource (*init)(hCpnSource cthis);

    /* CpnSource class parameters. */
    tWaveGroup waveGroups[CPNSOURCECFG_WAVE_TYPE_GROUPS];

    /* CpnSource class functions. */
    void (*regist)(hCpnSource cthis, htSourceParams source);
    void (*change)(hCpnSource cthis, htSourceParams source);
    void (*free)(hCpnSource cthis, htSourceParams source);
    void (*sine)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*pulse)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countUp)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countDown)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*countUpDown)(hCpnSource cthis, htSourceParams source, uint16 counter);
    void (*wave)(hCpnSource cthis, htSourceParams source, float32 *output);
    void (*run)(hCpnSource cthis);
    void (*err)(hCpnSource cthis, uint16 code);
};

#endif /*CPNSOURCE_H_*/

/**************************** Copyright(C) pxf ****************************/
