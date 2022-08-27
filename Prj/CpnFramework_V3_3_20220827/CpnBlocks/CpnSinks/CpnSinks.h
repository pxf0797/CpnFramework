/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinks.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:09:52
 * Description  : CpnSinks class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSINKS_H_
#define CPNSINKS_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "CpnSinksCfg.h"
#include "FuncLib.h"
#include "RteSigs.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSINKS_MACRO_VERSION          0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef struct{
    sinkType cacheMask;                /* signal register */
    sinkType startMask;                /* start to cache mask */
    tSinksParams sinksParams[CPNSINK_TYPE_WIDTH]; /* signal run params */
    uint16 cacheCounter[CPNSINK_TYPE_WIDTH]; /* signal drive counter */
    Fifo cacheFifo[CPNSINK_TYPE_WIDTH]; /* fifo cache data */
} tCacheGroup, *htCacheGroup;
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
 * CpnSinks class definition.
 **********************************************************/
/* CpnSinks class declaration.
 **********************************************/
CL(CpnSinks){
    hCpnSinks self;
    hCpnSinks (*init)(hCpnSinks cthis);

    /* CpnSinks class parameters. */
    tCacheGroup cacheGroups[CPNSINKSCFG_CACHE_TYPE_GROUPS];

    /* CpnSinks class functions. */
    void (*run)(hCpnSinks cthis);
    uint16 (*readData)(hCpnSinks cthis, htSinksParams sinks, void *buff);
    void (*trigStart)(hCpnSinks cthis, htSinksParams sinks);
    tCacheProcessSta (*cacheState)(hCpnSinks cthis, htSinksParams sinks);
    void (*cacheEnd)(hCpnSinks cthis, htSinksParams sinks);
    void (*registerCache)(hCpnSinks cthis, htSinksParams sinks);
    void (*reCache)(hCpnSinks cthis, htSinksParams sinks);
    void (*err)(hCpnSinks cthis, uint16 code);
};

#endif /*CPNSINKS_H_*/

/**************************** Copyright(C) pxf ****************************/
