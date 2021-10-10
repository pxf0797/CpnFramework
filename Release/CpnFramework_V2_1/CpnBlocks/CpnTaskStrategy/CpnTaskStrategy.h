/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTaskStrategy.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 09:53:54
 * Description  : CpnTaskStrategy class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNTASKSTRATEGY_H_
#define CPNTASKSTRATEGY_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "CpnTaskStrategyCfg.h"
#include "CpnSch.h"
#include "CpnTaskStrategyCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNTASKSTRATEGY_MACRO_VERSION   0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
// typedef uint16 (*condition)(void); /* true/false */
typedef enum{
    strategy_delay,
    strategy_cond
} strategy_type;

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
 * CpnTaskStrategy class definition.
 **********************************************************/
/* CpnTaskStrategy class declaration.
 **********************************************/
CL(CpnTaskStrategy){
    hCpnTaskStrategy self;
    hCpnTaskStrategy (*init)(hCpnTaskStrategy cthis);

    /* CpnTaskStrategy class parameters. */
    strategy strgMask;
    strategy strgMaskNew;
    strategy_type strgType;
    uint16 addTime;
    uint16 delTime;
    condition cond;

    /* CpnTaskStrategy class functions. */
    void (*updateStrategy)(hCpnTaskStrategy cthis, strategy strgMask, uint16 addTime, uint16 delTime);
    void (*updateStrategyCond)(hCpnTaskStrategy cthis, strategy strgMask, condition cond);
    void (*run)(hCpnTaskStrategy cthis);
    /* TODO */
};

#endif /*CPNTASKSTRATEGY_H_*/

/**************************** Copyright(C) pxf ****************************/
