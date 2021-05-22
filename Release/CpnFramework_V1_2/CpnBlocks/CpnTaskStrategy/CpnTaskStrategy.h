/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategy.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy类及接口声明头文件
* Others       :
* History      : 201218 pxf 初次建立
***************************************************************************/

#ifndef CPNTASKSTRATEGY_H_
#define CPNTASKSTRATEGY_H_

/*头文件包含*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"
#include "./CpnTaskStrategyCfg.h"
#include "../../cpnBasics/CpnSch/CpnSch.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNTASKSTRATEGY_MACRO_VERSION   0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据声明
***********************************************/
//typedef struct{
//    uint16 id;
//    uint16 code;
//} tErrCode;
//TODO
/*数据引用
***********************************************/
// typedef uint16 (*condition)(void); /* true/false */
typedef enum{
    strategy_delay,
    strategy_cond
} strategy_type;

/***********************************************************
* 接口定义
***********************************************************/
/*接口声明
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* CpnTaskStrategy类定义
***********************************************************/
/*CpnTaskStrategy类声明
***********************************************/
CL(CpnTaskStrategy){
    hCpnTaskStrategy self;
    hCpnTaskStrategy (*init)(hCpnTaskStrategy cthis);

    // CpnTaskStrategy类参数
    strategy strgMask;
    strategy strgMaskNew;
    strategy_type strgType;
    uint16 addTime;
    uint16 delTime;
    condition cond;

    // CpnTaskStrategy类功能函数
    void (*updateStrategy)(hCpnTaskStrategy cthis, strategy strgMask, uint16 addTime, uint16 delTime);
    void (*updateStrategyCond)(hCpnTaskStrategy cthis, strategy strgMask, condition cond);
    void (*run)(hCpnTaskStrategy cthis);
    //TODO
};

#endif /*CPNTASKSTRATEGY_H_*/

/**************************** Copyright(C) pxf ****************************/
