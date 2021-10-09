/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSourceTest.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:59:39
 * Description  : CpnSourceTest class and interface declaration file.
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNSOURCETEST_H_
#define CPNSOURCETEST_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNSOURCETEST_MACRO_VERSION             0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
 * CpnSourceTest class definition.
 **********************************************************/
/* CpnSourceTest class declaration.
 **********************************************/
CL(CpnSourceTest){
    hCpnSourceTest self;
    hCpnSourceTest (*init)(hCpnSourceTest cthis);

    /* CpnSourceTest class parameters. */
    /* TODO */

    /* CpnSourceTest class functions. */
    void (*run)(hCpnSourceTest cthis);
    void (*testSource)(hCpnSourceTest cthis);
    /* TODO */
};

#endif /*CPNSOURCETEST_H_*/

/**************************** Copyright(C) pxf ****************************/
