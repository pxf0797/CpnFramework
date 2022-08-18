/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFuncLibTest.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/11/03 14:55:04
 * Description  : CpnFuncLibTest class and interface declaration file.
 * Others       : 
 * History      : 20211103 pxf Initially established.
 **************************************************************************/

#ifndef CPNFUNCLIBTEST_H_
#define CPNFUNCLIBTEST_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "FuncLib.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNFUNCLIBTEST_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
/* typedef struct{
    uint16 id;
    uint16 code;
} tsErrCode;
 */
/* TODO */
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
 * CpnFuncLibTest class definition.
 **********************************************************/
/* CpnFuncLibTest class declaration.
 **********************************************/
CL(CpnFuncLibTest){
    hCpnFuncLibTest self;
    hCpnFuncLibTest (*init)(hCpnFuncLibTest cthis);

    /* CpnFuncLibTest class parameters. */
    /* TODO */

    /* CpnFuncLibTest class functions. */
    void (*run)(hCpnFuncLibTest cthis);
    void (*rbTreeTest)(hCpnFuncLibTest cthis);
    void (*rbPrintTree)(hCpnFuncLibTest cthis);
    void (*skipListTest)(hCpnFuncLibTest cthis);
    void (*crcTest)(hCpnFuncLibTest cthis);

    IMPL(Fifo);
};

#endif /*CPNFUNCLIBTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
