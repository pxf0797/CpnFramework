/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMatrixMapTest.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:00:03
 * Description  : CpnMatrixMapTest class and interface declaration file.
 * Others       : 
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMATRIXMAPTEST_H_
#define CPNMATRIXMAPTEST_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNMATRIXMAPTEST_MACRO_VERSION  0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
 * CpnMatrixMapTest class definition.
 **********************************************************/
/* CpnMatrixMapTest class declaration.
 **********************************************/
CL(CpnMatrixMapTest){
    hCpnMatrixMapTest self;
    hCpnMatrixMapTest (*init)(hCpnMatrixMapTest cthis);

    /* CpnMatrixMapTest class parameters. */
    /* TODO */

    /* CpnMatrixMapTest class functions. */
    void (*run)(hCpnMatrixMapTest cthis);
    /* TODO */
};

#endif /*CPNMATRIXMAPTEST_H_*/

/**************************** Copyright(C) pxf ****************************/
