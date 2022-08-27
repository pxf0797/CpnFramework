/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnErr.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 14:10:28
 * Description  : CpnErr class and interface declaration file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CPNERR_H_
#define CPNERR_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "FuncLib.h"
#include "CpnErrCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNERR_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
// typedef struct{
//     uint16 id;
//     uint16 code;
// } tErrCode;

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
 * CpnErr class definition.
 **********************************************************/
/* CpnErr class declaration.
 **********************************************/
CL(CpnErr){
    hCpnErr self;
    hCpnErr (*init)(hCpnErr cthis, hFifo clFifo, void *buff, uint16 buffSize, uint16 objectSize);

    /* CpnErr class parameters. */
    uint16 uwErrNum[ERROR_TOTAL_TYPES];

    /* CpnErr class functions. */
    uint16 (*setErr)(hCpnErr cthis, uint32 errCode);
    void (*run)(hCpnErr cthis);

    INJ(Fifo, clFifo);
};

#endif /*CPNERR_H_*/

/**************************** Copyright(C) pxf ****************************/
