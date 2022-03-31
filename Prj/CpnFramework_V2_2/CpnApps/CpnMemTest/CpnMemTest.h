/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemTest.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:45:13
 * Description  : CpnMemTest class and interface declaration file.
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMEMTEST_H_
#define CPNMEMTEST_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNMEMTEST_MACRO_VERSION                0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
/* typedef struct{
    uint16 id;
    uint16 code;
} tErrCode;
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
 * CpnMemTest class definition.
 **********************************************************/
/* CpnMemTest class declaration.
 **********************************************/
CL(CpnMemTest){
    hCpnMemTest self;
    hCpnMemTest (*init)(hCpnMemTest cthis);

    /* CpnMemTest class parameters. */
    /* TODO */

    /* CpnMemTest class functions. */
    void (*run)(hCpnMemTest cthis);
    /* TODO */
};

#endif /*CPNMEMTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
