/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : PduR.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 14:48:50
 * Description  : PduR class and interface declaration file.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

#ifndef PDUR_H_
#define PDUR_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "CpnDataManaDataSetCfg.h"
#include "RteSigs.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define PDUR_MACRO_VERSION                      0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef struct{
    uint32 id;
    pduIdType pduId;
} tsIFxPduId,*htsIFxPduId;
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
 * PduR class definition.
 **********************************************************/
/* PduR class declaration.
 **********************************************/
CL(PduR){
    hPduR self;
    hPduR (*init)(hPduR cthis, htsDMDataSet dataSet, uint8 *pduIdTable,
                uint16 pduRPduIdMapNums, htsPduRPudIdMap pduRPduIdMap);

    /* PduR class parameters. */
    htsDMDataSet dataSet;
    uint8 *pduIdTable;                    /* pudId Table. double size of the sizeof(tsIFxPduId)*PduIdMax. */
    uint16 rxIFxPudIdNums[DM_IFx_MAX];    /* receive ifx pduId count. */
    uint16 txIFxPudIdNums[DM_IFx_MAX];    /* sent ifx pduId count. */
    htsIFxPduId rxIFxPduId[DM_IFx_MAX];   /* receive ifx pduId start address. */
    htsIFxPduId txIFxPduId[DM_IFx_MAX];   /* sent ifx pduId start address. */

    /* pduId mapping. */
    uint16 pduRPduIdMapNums;              /* requset and responce pduId mapping counts. */
    htsPduRPudIdMap pduRPduIdMap;         /* requset and responce pduId mapping. */

    /* PduR class functions. */
    pduIdType (*getPduId)(hPduR cthis, teDMIFx ifx, teDMRxTx rxtx, uint32 id); /* if id not found, then pudId return PduIdMax. */
    pduIdType (*getRespondPduId)(hPduR cthis, pduIdType pduId);
    /* TODO */
};

#endif /*PDUR_H_*/

/**************************** Copyright(C) pxf ****************************/
