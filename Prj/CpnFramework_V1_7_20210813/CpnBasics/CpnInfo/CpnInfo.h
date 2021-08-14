/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnInfo.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/05/26 16:35:22
 * Description  : CpnInfo class and interface declaration file.
 * Others       :
 * History      : 20210526 pxf Initially established.
 **************************************************************************/

#ifndef CPNINFO_H_
#define CPNINFO_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"
#include "./CpnInfoCfg.h"
#include "../FuncLib/FuncLib.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNINFO_MACRO_VERSION                   0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef struct{
    char *pBuff;
    char *pFifoBuff;
    uint16 uwUsedCnt;
} tsInfoFifoBuff, *htsInfoFifoBuff;
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
 * CpnInfo class definition.
 **********************************************************/
/* CpnInfo class declaration.
 **********************************************/
CL(CpnInfo){
    hCpnInfo self;
    hCpnInfo (*init)(hCpnInfo cthis, hBlockM hBlockM,
        uint8 *memSpace, uint16 blockSize, uint16 blockNum);

    /* CpnInfo class parameters. */
    hBlockM hBlockM;
    hFifo hFifo;

    /* CpnInfo class functions. */
    void (*run)(hCpnInfo cthis);
    void (*output)(hCpnInfo cthis, uint8 *buff, uint16 len);
    void (*setErr)(hCpnInfo cthis, uint16 code);
    void (*info)(hCpnInfo cthis, const char *file, const char *func,
        const uint16 line, const char *format, va_list args);
    /* TODO */
};

#endif /*CPNINFO_H_*/

/**************************** Copyright(C) pxf ****************************/
