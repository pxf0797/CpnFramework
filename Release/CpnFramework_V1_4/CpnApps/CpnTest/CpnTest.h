/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTest.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 17:06:41
 * Description  : CpnTest class and interface declaration file.
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNTEST_H_
#define CPNTEST_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNTEST_MACRO_VERSION                   0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
 * CpnTest class definition.
 **********************************************************/
/* CpnTest class declaration.
 **********************************************/
CL(CpnTest){
    hCpnTest self;
    hCpnTest (*init)(hCpnTest cthis);

    /* CpnTest class parameters. */
    /* TODO */

    /* CpnTest class functions. */
    void (*run)(hCpnTest cthis);
    /* TODO */
};

#endif /*CPNTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
