/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteAsyn.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:15:43
 * Description  : RteAsyn class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef RTEASYN_H_
#define RTEASYN_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define RTEASYN_MACRO_VERSION           0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef uint16 asynType;
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
 * RteAsyn class definition.
 **********************************************************/
/* RteAsyn class declaration.
 **********************************************/
CL(RteAsyn){
    hRteAsyn self;
    hRteAsyn (*init)(hRteAsyn cthis, uint8 *set_buff, asynType *set_index, asynType *get_index);

    /* RteAsyn class parameters. */
    uint8 *set_buff;
    asynType *set_index;
    asynType *get_index;

    /* RteAsyn class functions. */
    void (*set)(hRteAsyn cthis, asynType signal, uint8 *buff);
    void (*get)(hRteAsyn cthis, asynType signal, uint8 *buff);
    void (*getAddr)(hRteAsyn cthis, asynType signal, void **addr);
};

#endif /*RTEASYN_H_*/

/**************************** Copyright(C) pxf ****************************/
