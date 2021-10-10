/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksTest.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:53:35
 * Description  : CpnSinksTest class and interface declaration file.
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSINKSTEST_H_
#define CPNSINKSTEST_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSINKSTEST_MACRO_VERSION              0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
 * CpnSinksTest class definition.
 **********************************************************/
/* CpnSinksTest class declaration.
 **********************************************/
CL(CpnSinksTest){
    hCpnSinksTest self;
    hCpnSinksTest (*init)(hCpnSinksTest cthis);

    /* CpnSinksTest class parameters. */
    /* TODO */

    /* CpnSinksTest class functions. */
    void (*run)(hCpnSinksTest cthis);
    void (*testSinks)(hCpnSinksTest cthis);
    /* TODO */
};

#endif /*CPNSINKSTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
