/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RteSyn.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:15:23
 * Description  : RteSyn class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef RTESYN_H_
#define RTESYN_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define RTESYN_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef uint16 synType;
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
 * RteSyn class definition.
 **********************************************************/
/* RteSyn class declaration.
 **********************************************/
CL(RteSyn){
    hRteSyn self;
    hRteSyn (*init)(hRteSyn cthis, void **serv_ServBuff, synType *trig_index);

    /* RteSyn class parameters. */
    void **serv_ServBuff;
    synType *trig_index;

    /* RteSyn class functions. */
    void (*serv)(hRteSyn cthis, synType signal, uint8 *buff);
    void (*trig)(hRteSyn cthis, synType signal, uint8 *buff);
};

#endif /*RTESYN_H_*/

/**************************** Copyright(C) pxf ****************************/
