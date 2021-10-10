/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 10:10:28
 * Description  :
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

#ifndef CPNDATAMANACFG_H_
#define CPNDATAMANACFG_H_

/* Include head files. */
#include "CpnErrCfg.h"
#include "StandType.h"
#include "FuncLib.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnDataManaCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNDATAMANACFG_ERR_ID                   0U    /* CpnDataManaCfg component error report ID. */
#define CPNDATAMANACFG_ALIGN_BYTES              4u    /* CpnDataManaUnitCfg data manage align bytes. */
#define CPNDATAMANACFG_TASK_SLICE_PERIOD        3u    /* ms */
#define CPNDATAMANACFG_DATAMANA_EXECUTE_PERIOD  5u    /* ms */
/* CpnDataManaCfg Data type define.
 **********************************************/
typedef uint32 dataSigType;
#define DATASIG_TYPE_BITS                       ((sizeof(dataSigType)>>1u)+3u)//0x5u//0x4u//
#define DATASIG_TYPE_WIDTH                      (1u<<DATASIG_TYPE_BITS)
#define DATASIG_TYPE_MASK                       (DATASIG_TYPE_WIDTH-1u)
typedef union{
    dataSigType data;
    uint8 byte[sizeof(dataSigType)];
} tuDataSig,*htuDataSig;
/* Basic types.
 **********************************************/
typedef uint16 pduIdType,*hpduIdType;
typedef enum{
    DM_INTEL_STANDARD,
    DM_INTEL_SEQUENTIAL,
    DM_MOTOROLA_LSB,
    DM_MOTOROLA_MSB,
    DM_MOTOROLA_SEQUENTIAL
} teDMFormat;
typedef enum{
    DM_RX,
    DM_TX
} teDMRxTx;
typedef enum{
    DM_IFx_CAN,
    DM_IFx_SPI,
    DM_IFx_SCI,
    DM_IFx_IIC,
    DM_IFx_MAX
} teDMIFx;
/* Const data types.
 **********************************************/
typedef struct{
    pduIdType pduId;
    uint32 id;
    teDMRxTx rxtx;
    teDMFormat format;
    uint16 period;       /* MS */
    uint16 dataSetLen;   /* bytes */
    teDMIFx ifx;
} tsDMDataSet, *htsDMDataSet;
typedef struct{
    uint16 sig_index;
    pduIdType pduId;
    uint16 bit_start;
    uint16 bit_len;
    uint16 sig_operation_name;
} tsDMMap, *htsDMMap;
/* PduR mapping types.
 **********************************************/
typedef struct{
    pduIdType pduIdReq;
    pduIdType pduIdRes;
} tsPduRPudIdMap, *htsPduRPudIdMap;

/***********************************************************
 * Signals initial.
 **********************************************************/
/* Signals.
 **********************************************/
//#include "./CpnDataManaDataSetCfg.h"

/***********************************************************
 * Function macros.
 **********************************************************/
/* Automatic expansion of DATASETS parameters.
 **********************************************/
#define DATASET_CFG(pduId,id,rxtx,format,period,dataSetLen,ifx)   {pduId,id,rxtx,format,period,dataSetLen,ifx}, /* DataSet contents. */
#define DATASETS_EXPANTION(dataset_list)                          dataset_list(DATASET_CFG)                     /* DataSet extention. */
#define PDUID_CFG(pduId,id,rxtx,format,period,dataSetLen,ifx)     pduId,                                        /* PduId. */
#define PDUIDS_EXPANTION(dataset_list)                            dataset_list(PDUID_CFG)                       /* PduId extention. */
#define DATASET_LEN_CFG(pduId,id,rxtx,format,period,dataSetLen,ifx) +ALIGN_SIZE(CPNDATAMANACFG_ALIGN_BYTES,dataSetLen) /* DataSet align length. */
#define DATASETS_LENGTH_EXPANTION(dataset_list)                   (0u dataset_list(DATASET_LEN_CFG))            /* DataSet length extention. */

/***********************************************************
 * Error classify.
 **********************************************************/
typedef enum{
    ERR_CPNDATAMANACFG_FUNC,
} teCpnDataManaCfgErrClassify;
/* Error code.
 **********************************************************/
#define CPNDATAMANACFG_ERR_CODE                 (ERR_TYPE_BLOCK|ERR_SEVERITY_MEDIUM|(ERR_CPNDATAMANACFG_FUNC<<ERR_CLASSIFY_SHIFT)|0) /* Error code. */

#endif /*CPNDATAMANACFG_H_*/

/**************************** Copyright(C) pxf ****************************/
