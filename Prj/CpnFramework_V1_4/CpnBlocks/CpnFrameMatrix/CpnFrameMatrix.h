/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFrameMatrix.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:56:01
 * Description  : CpnFrameMatrix class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNFRAMEMATRIX_H_
#define CPNFRAMEMATRIX_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"
#include "./CpnFrameMatrixCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNFRAMEMATRIX_MACRO_VERSION    0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef union
{
   uint8 byte[CPNFRAMEMATRIXCFG_FRAME_BYTES];
   uint32 data[CPNFRAMEMATRIXCFG_FRAME_BYTES>>2];
} TU_BYTES_DATA, *hTU_BYTES_DATA;

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
 * CpnFrameMatrix class definition.
 **********************************************************/
/* CpnFrameMatrix class declaration.
 **********************************************/
CL(CpnFrameMatrix){
    hCpnFrameMatrix self;
    hCpnFrameMatrix (*init)(hCpnFrameMatrix cthis, uint32 id, TE_RXTX_TYPE rxtx, TE_FRAME_FORMAT format, uint16 period);

    /* CpnFrameMatrix class parameters. */
    uint32 id;
    TE_RXTX_TYPE rxtx;
    TE_FRAME_FORMAT format;
    TU_BYTES_DATA frame;
    uint16 period; /* MS */
    uint16 counter; /* MS */

    /* CpnFrameMatrix class functions. */
    void (*getFrame)(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 *value);
    void (*setFrame)(hCpnFrameMatrix cthis, uint16 bit_start, uint16 bit_len, uint32 value);
    /* TODO */
};

#endif /*CPNFRAMEMATRIX_H_*/

/**************************** Copyright(C) pxf ****************************/
