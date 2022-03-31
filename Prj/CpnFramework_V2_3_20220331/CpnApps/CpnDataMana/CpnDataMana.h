/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataMana.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 10:10:28
 * Description  : CpnDataMana class and interface declaration file.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

#ifndef CPNDATAMANA_H_
#define CPNDATAMANA_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "CpnDataManaDataSetCfg.h"
#include "RteSigs.h"
#include "FuncLib.h"
#include "PduR.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNDATAMANA_MACRO_VERSION               0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
void groupAct(uint16 index);
INF(sentDrv){
    void(*sentDrv)(teDMIFx ifx, uint32 id, uint8 *start, uint16 len);
};

/***********************************************************
 * CpnDataMana class definition.
 **********************************************************/
/* CpnDataMana class declaration.
 **********************************************/
#define DATASETS_ALIGN_MASK_SIZE       (ALIGN_SIZE(DATASIG_TYPE_WIDTH,PduIdMax)/DATASIG_TYPE_WIDTH)
CL(CpnDataMana){
    hCpnDataMana self;
    hCpnDataMana (*init)(hCpnDataMana cthis,
                        const htsDMDataSet dataSet, uint8 *space, uint16 *start,
                        slice sliceFunc,
                        void(*sentDrv)(teDMIFx ifx, uint32 id, uint8 *start, uint16 len),
                        uint16 pduRPduIdMapNums, htsPduRPudIdMap pduRPduIdMap);

    /* CpnDataMana class parameters. */
    htsDMDataSet dataSet;
    uint8 *space;          /* dataSet memory space. */
    uint16 *start;         /* dataSet memory correspond start offset. */
    /* CpnDataMana scheduler parameters. */
    uint16 timer;                   /* basic CPNDATAMANACFG_TASK_SLICE_PERIOD recorder */
    uint16 dataSetGroups;
    dataSigType txDataSetMask[DATASETS_ALIGN_MASK_SIZE];
    dataSigType txDataSetActMask[DATASETS_ALIGN_MASK_SIZE];
    uint16 dataSetPeriodCounter[PduIdMax];  /* current execute record */
    /* slice scheduler */
    uint16 sliceTable[CPNDATAMANACFG_TASK_SLICE_PERIOD];
    SliceSch slicSch;

    /* PduR */
    tsIFxPduId ifxPduIdTable[PduIdMax<<1];  /* used to store id correspond pduId table. */
    PduR pduR;

    /* CpnDataMana class functions. */
    void (*run)(hCpnDataMana cthis);
    void (*setDataSig)(hCpnDataMana cthis, pduIdType pduId, uint16 bit_start, uint16 bit_len, dataSigType value);
    void (*getDataSig)(hCpnDataMana cthis, pduIdType pduId, uint16 bit_start, uint16 bit_len, dataSigType *value);
    void (*executeGroup)(hCpnDataMana cthis, uint16 index);
    uint16 (*triggerSent)(hCpnDataMana cthis, pduIdType pduId); /* set sent successful return TRUE, else return FALSE. */
    uint16 (*clearSent)(hCpnDataMana cthis, pduIdType pduId);  /* if sent set, then clear it return TRUE. else return FALSE. */

    /* Interface */
    IMPL(sentDrv);
};

#endif /*CPNDATAMANA_H_*/

/**************************** Copyright(C) pxf ****************************/
