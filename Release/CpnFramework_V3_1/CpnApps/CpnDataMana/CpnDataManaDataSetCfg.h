/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaDataSetCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/26 20:09:36
 * Description  :
 * Others       :
 * History      : 20210926 pxf Initially established.
 **************************************************************************/

#ifndef CPNDATAMANADATASETCFG_H_
#define CPNDATAMANADATASETCFG_H_

/* Include head files. */
#include "CpnDataManaCfg.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* Signals initial.
 * DataSets configure.
 **********************************************/
// extern const tsDMDataSet dmDataSets[];
/* The receiving message cycle can be set without setting, the default value 0 can be used;
 * when the sending message cycle is set to 0, the message needs to be triggered before it can be sent. */
#define DATASET_CFG_LIST(_)                                                                                   \
    /*       pduId,             id,      rxtx,                format,  period,  dataSetLen,            ifx */ \
    _(   TxCanInfo,CPNINFOCFG_FRAME_ID, DM_TX,       DM_MOTOROLA_LSB,      0u,           8u,    DM_IFx_CAN )  \
    _(    TxCanAAB,        0xAABul,     DM_TX,     DM_INTEL_STANDARD,    110u,           8u,    DM_IFx_CAN )  \
    _(    TxCan100,        0x100ul,     DM_TX,       DM_MOTOROLA_LSB,     20u,           8u,    DM_IFx_CAN )  \
    _(    RxCan22F,        0x22Ful,     DM_RX,       DM_MOTOROLA_LSB,      0u,           8u,    DM_IFx_CAN )  \
    _(    TxCanF0A,        0xF0Aul,     DM_TX,       DM_MOTOROLA_MSB,    300u,           8u,    DM_IFx_CAN )  \
    _(   RxCan554E,   0x03AD554Eul,     DM_RX,     DM_INTEL_STANDARD,      0u,           8u,    DM_IFx_CAN )  \

/***********************************************************
 * Signals map.
 **********************************************************/
/* Send signals.
 **********************************************/
#define DATASET_SET_SIG_LIST(_,...)                                             \
    /*       pduId,       sig_name,  bit_start,  bit_len, dynamic parameters */ \
    _(   TxCanInfo,      ulInfoLow,        24u,      32u,        __VA_ARGS__ )  \
    _(   TxCanInfo,     ulInfoHigh,        56u,      32u,        __VA_ARGS__ )  \
    _(    TxCanAAB,        ulDataA,        20u,      16u,        __VA_ARGS__ )  \
    _(    TxCanAAB,        ulDataB,        54u,       4u,        __VA_ARGS__ )  \
    _(    TxCan100,        ulDataC,        20u,      16u,        __VA_ARGS__ )  \
    _(    TxCan100,        ulDataD,        54u,       4u,        __VA_ARGS__ )  \
    _(    TxCanF0A,        ulDataE,         3u,      16u,        __VA_ARGS__ )  \
    _(    TxCanF0A,        ulDataF,        27u,       7u,        __VA_ARGS__ )  \
    _(    TxCanF0A,        ulDataG,        44u,       5u,        __VA_ARGS__ )  \


/* Receive signals.
 **********************************************/
#define DATASET_GET_SIG_LIST(_,...)                                             \
    /*       pduId,       sig_name,  bit_start,  bit_len, dynamic parameters */ \
    _(    RxCan22F,        ulData1,        24u,      32u,        __VA_ARGS__ )  \
    _(    RxCan22F,        ulData2,        56u,      32u,        __VA_ARGS__ )  \
    _(    RxCan22F,        ulData3,        20u,      16u,        __VA_ARGS__ )  \
    _(    RxCan22F,        ulData4,        54u,       4u,        __VA_ARGS__ )  \
    _(   RxCan554E,        ulData5,        20u,      16u,        __VA_ARGS__ )  \
    _(   RxCan554E,        ulData6,        54u,       4u,        __VA_ARGS__ )  \
    _(   RxCan554E,        ulData7,        60u,       2u,        __VA_ARGS__ )  \
    _(   RxCan554E,        ulData8,        48u,       3u,        __VA_ARGS__ )  \


/***********************************************************
 * PduR map.
 **********************************************************/
/* PduId request and responce mapping.
 **********************************************/
#define PDUR_PDUID_REQ_RES_LIST(_,...) \
    /*    req  pduId,    res  pduId */ \
    _(      RxCan22F,      TxCan100 )  \
    _(     RxCan554E,      TxCan100 )  \


/***********************************************************
 * Function marcos.
 **********************************************************/
/* Signals index defination.
 **********************************************/
#define DATASET_SET_SIG_ENUM_COMBINE(pduId,sig_name,bit_start,bit_len,fill)  set_sig_##pduId##_##sig_name, /* Set signal enum index. */
#define DATASET_GET_SIG_ENUM_COMBINE(pduId,sig_name,bit_start,bit_len,fill)  get_sig_##pduId##_##sig_name, /* Get signal enum index. */
#define DATASET_SET_SIG_ENUM_EXPANTION(dataset_list)                         dataset_list(DATASET_SET_SIG_ENUM_COMBINE,fill)  /* Set signal enum extention. */
#define DATASET_GET_SIG_ENUM_EXPANTION(dataset_list)                         dataset_list(DATASET_GET_SIG_ENUM_COMBINE,fill)  /* Get signal enum extention. */
/* Signals mapping.
 **********************************************/
#define DATASET_SET_SIG_COMBINE(pduId,sig_name,bit_start,bit_len,fill)       {set_sig_##pduId##_##sig_name,pduId,bit_start,bit_len,sig_trig_CpnDataMana_setDataSig}, /* Set signal map array. */
#define DATASET_GET_SIG_COMBINE(pduId,sig_name,bit_start,bit_len,fill)       {get_sig_##pduId##_##sig_name,pduId,bit_start,bit_len,sig_trig_CpnDataMana_getDataSig}, /* Get signal map array. */
#define DATASET_SET_SIG_EXPANTION(dataset_list)                              dataset_list(DATASET_SET_SIG_COMBINE,fill)       /* Set signal enum extention. */
#define DATASET_GET_SIG_EXPANTION(dataset_list)                              dataset_list(DATASET_GET_SIG_COMBINE,fill)       /* Get signal enum extention. */
/* Signals service declaration.
 **********************************************/
#define DATASET_SET_SIG_SERV_DEC(pduId,sig_name,bit_start,bit_len,fill)      void serv_CpnDataMana_set_##pduId##_##sig_name(void *buff); /* set_sig serv declaration. */
#define DATASET_GET_SIG_SERV_DEC(pduId,sig_name,bit_start,bit_len,fill)      void serv_CpnDataMana_get_##pduId##_##sig_name(void *buff); /* get_sig serv declaration. */
#define DATASET_GET_SIG_SERV_DEC_EXPANTION(dataset_list)                     dataset_list(DATASET_GET_SIG_SERV_DEC,fill)      /* Set serv declaration extention. */
#define DATASET_SET_SIG_SERV_DEC_EXPANTION(dataset_list)                     dataset_list(DATASET_SET_SIG_SERV_DEC,fill)      /* Get serv declaration extention. */
/* Signals service definition.
 **********************************************/
// extern const tsDMMap dmMapSet[];
// extern const tsDMMap dmMapGet[];
// extern void serv_CpnDataMana_setDataSig_operation(uint16 set_sig, dataSigType *value);
// extern void serv_CpnDataMana_getDataSig_operation(uint16 get_sig, dataSigType *value);
#define DATASET_SET_SIG_SERV_DEF(pduId,sig_name,bit_start,bit_len,fill) /* set_sig serv definiton. */ \
void serv_CpnDataMana_set_##pduId##_##sig_name(void *buff){                                           \
    serv_CpnDataMana_setDataSig_operation(set_sig_##pduId##_##sig_name,((dataSigType*)buff));         \
}
#define DATASET_GET_SIG_SERV_DEF(pduId,sig_name,bit_start,bit_len,fill) /* get_sig serv definiton. */ \
void serv_CpnDataMana_get_##pduId##_##sig_name(void *buff){                                           \
    serv_CpnDataMana_getDataSig_operation(get_sig_##pduId##_##sig_name,((dataSigType*)buff));         \
}
#define DATASET_SET_SIG_SERV_DEF_EXPANTION(dataset_list)    dataset_list(DATASET_SET_SIG_SERV_DEF,fill)                 /* Set serv definition extention. */
#define DATASET_GET_SIG_SERV_DEF_EXPANTION(dataset_list)    dataset_list(DATASET_GET_SIG_SERV_DEF,fill)                 /* Get serv definition extention. */
/* Signals service RTE definition.
 **********************************************/
#define DATASET_SET_SIG_SERV_LIST_RTESYN(pduId,sig_name,bit_start,bit_len,X) X(sig_serv_CpnDataMana_set_##pduId##_##sig_name,serv_CpnDataMana_set_##pduId##_##sig_name) /* RTE set signal configure. */
#define DATASET_GET_SIG_SERV_LIST_RTESYN(pduId,sig_name,bit_start,bit_len,X) X(sig_serv_CpnDataMana_get_##pduId##_##sig_name,serv_CpnDataMana_get_##pduId##_##sig_name) /* RTE get signal configure. */
#define DATASET_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)       DATASET_SET_SIG_LIST(DATASET_SET_SIG_SERV_LIST_RTESYN,_)    /* RTE set signal extention. */ \
                                                            DATASET_SET_SIG_LIST(DATASET_GET_SIG_SERV_LIST_RTESYN,_)    /* RTE get signal extention. */
#define DATASET_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)       DATASET_GET_SIG_LIST(DATASET_GET_SIG_SERV_LIST_RTESYN,_)    /* RTE get signal extention. */
/* Signals trigger RTE definition.
 **********************************************/
#define DataSetMapSet(pduId,sig_name)                       sig_serv_CpnDataMana_set_##pduId##_##sig_name               /* Set signals map. */
#define DataSetMapGet(pduId,sig_name)                       sig_serv_CpnDataMana_get_##pduId##_##sig_name               /* Get signals map. */

/* PudR request and responce mapping.
 **********************************************/
#define PDUR_PDUID_REQ_RES_MAPPING(req,res)                 {req,res},                                                  /* set request and responce mapping. */
#define PDUR_PDUID_REQ_RES_EXPANTION(pduId_list)            pduId_list(PDUR_PDUID_REQ_RES_MAPPING)                      /* mapping expantion. */

#endif /*CPNDATAMANADATASETCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
