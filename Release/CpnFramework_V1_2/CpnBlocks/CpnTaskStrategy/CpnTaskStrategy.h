/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategy.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 201218 pxf ���ν���
***************************************************************************/

#ifndef CPNTASKSTRATEGY_H_
#define CPNTASKSTRATEGY_H_

/*ͷ�ļ�����*/
#include "../../cpnBasics/standType/standType.h"
#include "../../cpnBasics/oopc/oopc.h"
#include "./CpnTaskStrategyCfg.h"
#include "../../cpnBasics/CpnSch/CpnSch.h"
#include "./CpnTaskStrategyCfg.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNTASKSTRATEGY_MACRO_VERSION   0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
***********************************************/
//typedef struct{
//    uint16 id;
//    uint16 code;
//} tErrCode;
//TODO
/*��������
***********************************************/
// typedef uint16 (*condition)(void); /* true/false */
typedef enum{
    strategy_delay,
    strategy_cond
} strategy_type;

/***********************************************************
* �ӿڶ���
***********************************************************/
/*�ӿ�����
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* CpnTaskStrategy�ඨ��
***********************************************************/
/*CpnTaskStrategy������
***********************************************/
CL(CpnTaskStrategy){
    hCpnTaskStrategy self;
    hCpnTaskStrategy (*init)(hCpnTaskStrategy cthis);

    // CpnTaskStrategy�����
    strategy strgMask;
    strategy strgMaskNew;
    strategy_type strgType;
    uint16 addTime;
    uint16 delTime;
    condition cond;

    // CpnTaskStrategy�๦�ܺ���
    void (*updateStrategy)(hCpnTaskStrategy cthis, strategy strgMask, uint16 addTime, uint16 delTime);
    void (*updateStrategyCond)(hCpnTaskStrategy cthis, strategy strgMask, condition cond);
    void (*run)(hCpnTaskStrategy cthis);
    //TODO
};

#endif /*CPNTASKSTRATEGY_H_*/

/**************************** Copyright(C) pxf ****************************/
