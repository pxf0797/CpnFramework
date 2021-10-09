/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaTest.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/08 11:41:08
 * Description  : CpnDataManaTest class and interface declaration file.
 * Others       : 
 * History      : 20211008 pxf Initially established.
 **************************************************************************/

#ifndef CPNDATAMANATEST_H_
#define CPNDATAMANATEST_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNDATAMANATEST_MACRO_VERSION           0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
 * CpnDataManaTest class definition.
 **********************************************************/
/* CpnDataManaTest class declaration.
 **********************************************/
CL(CpnDataManaTest){
    hCpnDataManaTest self;
    hCpnDataManaTest (*init)(hCpnDataManaTest cthis);

    /* CpnDataManaTest class parameters. */
    /* TODO */

    /* CpnDataManaTest class functions. */
    void (*run)(hCpnDataManaTest cthis);
    /* TODO */
};

#endif /*CPNDATAMANATEST_H_*/

/**************************** Copyright(C) pxf ****************************/
