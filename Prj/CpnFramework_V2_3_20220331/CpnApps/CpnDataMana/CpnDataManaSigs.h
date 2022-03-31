/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 10:10:28
 * Description  : CpnDataMana component signals declaration head file.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

#ifndef CPNDATAMANASIGS_H_
#define CPNDATAMANASIGS_H_

/* Include head files. */
#include "Rte.h"
#include "CpnDataManaDataSetCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNDATAMANASIGS_MACRO_VERSION           0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Get Set data type definition.
 * Generally, only the set data is defined, and the get type refers to the current header file.
 * Only need to define the data send, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Send data type.
 **********************************************/



/***********************************************************
 * Serv Trig data type definition.
 * Generally, only the serv data is defined, and the trig type refers to the current header file.
 * Only need to define the data send, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* signals definiton.
 **********************************************/
typedef enum {
    PDUIDS_EXPANTION(DATASET_CFG_LIST)
    PduIdMax
} tePduIds;
typedef enum{
    DATASET_SET_SIG_ENUM_EXPANTION(DATASET_SET_SIG_LIST)
    set_sig_num_max
} teDMSetSig;
typedef enum{
    DATASET_GET_SIG_ENUM_EXPANTION(DATASET_GET_SIG_LIST)
    DATASET_GET_SIG_ENUM_EXPANTION(DATASET_SET_SIG_LIST)
    get_sig_num_max
} teDMGetSig;
/* Serv data type.
 **********************************************/
typedef struct{
    pduIdType pduId;
    uint16 len;          /* DataSet length */
} tsDataSetLen, *htsDataSetLen;
typedef struct{
    pduIdType pduId;
    uint8 *dataSet;      /* DataSet pointer */
} tsDataSet, *htsDataSet;
typedef struct{
    uint16 sig;          /* set_sig or get_sig */
    dataSigType *value;  /* data value pointer */
} tsDataSig, *htsDataSig;
typedef struct{
    pduIdType pduId;
    uint16 index;        /* byte index */
    uint8 byte;          /* byte value */
} tsDataByte, *htsDataByte;
typedef struct{
    pduIdType pduId;
    uint16 index;        /* byte index */
    uint16 len;          /* byte nums */
    uint8 *buff;         /* data values */
} tsDataLen, *htsDataLen;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnDataMana_init(void);
/* triggerTransmit Service.
 **********************************************/
void serv_CpnDataMana_triggerTransmit(void *buff);
/* cancelTransmit Service.
 **********************************************/
void serv_CpnDataMana_cancelTransmit(void *buff);
/* txConfirmation Service.
 **********************************************/
void serv_CpnDataMana_txConfirmation(void *buff);
/* rxIndication Service.
 **********************************************/
void serv_CpnDataMana_rxIndication(void *buff);
/* rxConfirmation Service.
 **********************************************/
void serv_CpnDataMana_rxConfirmation(void *buff);
/* getDataSetLen Service.
 **********************************************/
void serv_CpnDataMana_getDataSetLen(void *buff);
/* getDataSet Service.
 **********************************************/
void serv_CpnDataMana_getDataSet(void *buff);
/* getDataSig Service.
 **********************************************/
void serv_CpnDataMana_getDataSig(void *buff);
/* getDataByte Service.
 **********************************************/
void serv_CpnDataMana_getDataByte(void *buff);
/* getDataLen Service.
 **********************************************/
void serv_CpnDataMana_getDataLen(void *buff);
/* setDataSet Service.
 **********************************************/
void serv_CpnDataMana_setDataSet(void *buff);
/* setDataSig Service.
 **********************************************/
void serv_CpnDataMana_setDataSig(void *buff);
/* setDataByte Service.
 **********************************************/
void serv_CpnDataMana_setDataByte(void *buff);
/* setDataLen Service.
 **********************************************/
void serv_CpnDataMana_setDataLen(void *buff);

/* Set serv.
 * serv_CpnMatrixMap_set_ulDataA
 **********************************************/
DATASET_SET_SIG_SERV_DEC_EXPANTION(DATASET_SET_SIG_LIST)

/* Get serv.
 * serv_CpnMatrixMap_get_ulData1
 **********************************************/
DATASET_GET_SIG_SERV_DEC_EXPANTION(DATASET_GET_SIG_LIST)
DATASET_GET_SIG_SERV_DEC_EXPANTION(DATASET_SET_SIG_LIST)

/* Trigger interface.
 **********************************************/
//void trig_CpnDataMana_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNDATAMANA(_)                                  \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNDATAMANA(_)                              \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNDATAMANA(_)                                  \
    _(sig_serv_CpnDataMana_init,serv_CpnDataMana_init)                          \
    _(sig_serv_CpnDataMana_triggerTransmit,serv_CpnDataMana_triggerTransmit)    \
    _(sig_serv_CpnDataMana_cancelTransmit,serv_CpnDataMana_cancelTransmit)      \
    _(sig_serv_CpnDataMana_txConfirmation,serv_CpnDataMana_txConfirmation)      \
    _(sig_serv_CpnDataMana_rxIndication,serv_CpnDataMana_rxIndication)          \
    _(sig_serv_CpnDataMana_rxConfirmation,serv_CpnDataMana_rxConfirmation)      \
    _(sig_serv_CpnDataMana_getDataSet,serv_CpnDataMana_getDataSet)              \
    _(sig_serv_CpnDataMana_getDataSig,serv_CpnDataMana_getDataSig)              \
    _(sig_serv_CpnDataMana_getDataByte,serv_CpnDataMana_getDataByte)            \
    _(sig_serv_CpnDataMana_getDataLen,serv_CpnDataMana_getDataLen)              \
    _(sig_serv_CpnDataMana_setDataSet,serv_CpnDataMana_setDataSet)              \
    _(sig_serv_CpnDataMana_setDataSig,serv_CpnDataMana_setDataSig)              \
    _(sig_serv_CpnDataMana_setDataByte,serv_CpnDataMana_setDataByte)            \
    _(sig_serv_CpnDataMana_setDataLen,serv_CpnDataMana_setDataLen)              \
     /*_(sig_serv_CpnDataMana_set_TxCanAAB_ulDataA,serv_CpnDataMana_set_TxCanAAB_ulDataA)*/ \
     /*_(sig_serv_CpnDataMana_get_RxCan22F_ulData1,serv_CpnDataMana_get_RxCan22F_ulData1)*/ \
     DATASET_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)                              \
     DATASET_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)                              \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNDATAMANA(_)                              \
    _(sig_trig_CpnDataMana_initTask,sig_serv_CpnSch_initTask)                   \
    _(sig_trig_CpnDataMana_addTask,sig_serv_CpnSch_addTask)                     \
    _(sig_trig_CpnDataMana_delTask,sig_serv_CpnSch_delTask)                     \
    _(sig_trig_CpnDataMana_delay,sig_serv_CpnSch_delay)                         \
    _(sig_trig_CpnDataMana_now,sig_serv_CpnSch_now)                             \
    _(sig_trig_CpnDataMana_setErr,sig_serv_CpnErr_setErr)                       \
    _(sig_trig_CpnDataMana_triggerTransmit,sig_serv_CpnDataMana_triggerTransmit) \
    _(sig_trig_CpnDataMana_cancelTransmit,sig_serv_CpnDataMana_cancelTransmit)  \
    _(sig_trig_CpnDataMana_txConfirmation,sig_serv_CpnDataMana_txConfirmation)  \
    _(sig_trig_CpnDataMana_rxIndication,sig_serv_CpnDataMana_rxIndication)      \
    _(sig_trig_CpnDataMana_rxConfirmation,sig_serv_CpnDataMana_rxConfirmation)  \
    _(sig_trig_CpnDataMana_getDataSet,sig_serv_CpnDataMana_getDataSet)          \
    _(sig_trig_CpnDataMana_getDataSig,sig_serv_CpnDataMana_getDataSig)          \
    _(sig_trig_CpnDataMana_getDataByte,sig_serv_CpnDataMana_getDataByte)        \
    _(sig_trig_CpnDataMana_getDataLen,sig_serv_CpnDataMana_getDataLen)          \
    _(sig_trig_CpnDataMana_setDataSet,sig_serv_CpnDataMana_setDataSet)          \
    _(sig_trig_CpnDataMana_setDataSig,sig_serv_CpnDataMana_setDataSig)          \
    _(sig_trig_CpnDataMana_setDataByte,sig_serv_CpnDataMana_setDataByte)        \
    _(sig_trig_CpnDataMana_setDataLen,sig_serv_CpnDataMana_setDataLen)          \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
void taskCpnDataMana(void);

#endif /*CPNDATAMANASIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
