/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 10:10:28
 * Description  : CpnDataMana component signals definition source file.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnDataMana.h"
// #include "CpnDataManaSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnDataMana class definition.
 **********************************************************/
/* CpnDataMana class.
 **********************************************/
/*static */CpnDataMana clCpnDataMana;

/* Const datas.
 **********************************************/
static const tsDMDataSet dmDataSets[] = {DATASETS_EXPANTION(DATASET_CFG_LIST)};
static const tsDMMap dmMapSet[] = {
    DATASET_SET_SIG_EXPANTION(DATASET_SET_SIG_LIST)
};
static const tsDMMap dmMapGet[] = {
    DATASET_GET_SIG_EXPANTION(DATASET_GET_SIG_LIST)
    DATASET_GET_SIG_EXPANTION(DATASET_SET_SIG_LIST)
};
/* Space definiton.
 **********************************************/
static uint8 dmDataSetsSpace[DATASETS_LENGTH_EXPANTION(DATASET_CFG_LIST)];
static uint16 dmDataSetsStartAddr[PduIdMax];
/* PduR pduId request ans responce mapping.
 **********************************************/
static tsPduRPudIdMap pduRPduIdMap[] = {PDUR_PDUID_REQ_RES_EXPANTION(PDUR_PDUID_REQ_RES_LIST)};
/* Interface.
 **********************************************/
void dataSet_sentDrv(teDMIFx ifx, uint32 id, uint8 *start, uint16 len);

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnDataMana_init(void){
    uint16 i = 0u;

    dmDataSetsStartAddr[0] = 0u;
    for(i = 0u; i < (PduIdMax-1u); i++){
        dmDataSetsStartAddr[i+1] = (dmDataSetsStartAddr[i] + ALIGN_SIZE(CPNDATAMANACFG_ALIGN_BYTES,dmDataSets[i].dataSetLen));
    }
    CN(CpnDataMana,&clCpnDataMana,(const htsDMDataSet)dmDataSets,dmDataSetsSpace,dmDataSetsStartAddr,
    groupAct,dataSet_sentDrv,
    (sizeof(pduRPduIdMap)/sizeof(tsPduRPudIdMap)),pduRPduIdMap);
    if(OPRS(clCpnDataMana) != NULL){
        // tsInitTask taskParam;
        // taskParam.level = level1;
        // taskParam.t = taskCpnDataMana;
        // taskParam.prdTick = 11*MS_T;
        // taskParam.startTick = 5*MS_T;
        // taskParam.e.all = e_basic;
        // clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataMana_initTask, (uint8*)&taskParam);
    }
}

/* triggerTransmit Service.
 **********************************************/
void serv_CpnDataMana_triggerTransmit(void *buff){
    hpduIdType pduId = (hpduIdType)buff;
    clCpnDataMana.triggerSent(clCpnDataMana.self, *pduId);
}
/* cancelTransmit Service.
 **********************************************/
void serv_CpnDataMana_cancelTransmit(void *buff){
    hpduIdType pduId = (hpduIdType)buff;
    clCpnDataMana.clearSent(clCpnDataMana.self, *pduId);
}
/* txConfirmation Service.
 **********************************************/
void serv_CpnDataMana_txConfirmation(void *buff){
    // hpduIdType pduId = (hpduIdType)buff;
}
/* rxIndication Service.
 **********************************************/
void serv_CpnDataMana_rxIndication(void *buff){
    /* inform other component that dataset is received. */
    // hpduIdType pduId = (hpduIdType)buff;
}
/* rxConfirmation Service.
 **********************************************/
void serv_CpnDataMana_rxConfirmation(void *buff){
    /* usually used to receive multi-datas as one. */
    // hpduIdType pduId = (hpduIdType)buff;
}
/* getDataSetLen Service.
 **********************************************/
void serv_CpnDataMana_getDataSetLen(void *buff){
    htsDataSetLen dataSetLen = (htsDataSetLen)buff;
    dataSetLen->len = dmDataSets[dataSetLen->pduId].dataSetLen;
}
/* getDataSet Service.
 **********************************************/
void serv_CpnDataMana_getDataSet(void *buff){
    htsDataSet dataSet = (htsDataSet)buff;
    dataSet->dataSet = &dmDataSetsSpace[dmDataSetsStartAddr[dataSet->pduId]];
}
/* getDataSig Service.
 **********************************************/
void serv_CpnDataMana_getDataSig(void *buff){
    htsDataSig dataSig = (htsDataSig)buff;
    htsDMMap getMap = (htsDMMap)&dmMapGet[dataSig->sig];
    clCpnDataMana.getDataSig(clCpnDataMana.self,getMap->pduId,getMap->bit_start,getMap->bit_len,dataSig->value);
}
/* getDataByte Service.
 **********************************************/
void serv_CpnDataMana_getDataByte(void *buff){
    htsDataByte dataByte = (htsDataByte)buff;
    /* if index out of range retrun 0. */
    if(dataByte->index < dmDataSets[dataByte->pduId].dataSetLen){
        dataByte->byte = dmDataSetsSpace[dmDataSetsStartAddr[dataByte->pduId]+dataByte->index];
    }else{
        dataByte->byte = 0u;
    }
}
/* getDataLen Service.
 **********************************************/
void serv_CpnDataMana_getDataLen(void *buff){
    htsDataLen dataLen = (htsDataLen)buff;
    uint16 len = dataLen->len;
    if((dataLen->len+dataLen->index) > dmDataSets[dataLen->pduId].dataSetLen){
        if(dataLen->index >= dmDataSets[dataLen->pduId].dataSetLen){
            len = 0u;
        }else{
            len = (dmDataSets[dataLen->pduId].dataSetLen-dataLen->index);
        }
    }
    /* if length is abnormal stop copy datas. */
    if(len){
        appMemCopy(&dmDataSetsSpace[dmDataSetsStartAddr[dataLen->pduId]+dataLen->index],dataLen->buff,len);
    }
}
/* setDataSet Service.
 **********************************************/
void serv_CpnDataMana_setDataSet(void *buff){
    htsDataSet dataSet = (htsDataSet)buff;
    appMemCopy(&dmDataSetsSpace[dmDataSetsStartAddr[dataSet->pduId]],dataSet->dataSet,dmDataSets[dataSet->pduId].dataSetLen);
    /* indicate DataSet is received. */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataMana_rxIndication, (uint8*)&dataSet->pduId);
}
/* setDataSig Service.
 **********************************************/
void serv_CpnDataMana_setDataSig(void *buff){
    htsDataSig dataSig = (htsDataSig)buff;
    htsDMMap setMap = (htsDMMap)&dmMapSet[dataSig->sig];
    clCpnDataMana.setDataSig(clCpnDataMana.self,setMap->pduId,setMap->bit_start,setMap->bit_len,*dataSig->value);
}
/* setDataByte Service.
 **********************************************/
void serv_CpnDataMana_setDataByte(void *buff){
    htsDataByte dataByte = (htsDataByte)buff;
    dmDataSetsSpace[dmDataSetsStartAddr[dataByte->pduId]+dataByte->index] = dataByte->byte;
}
/* setDataLen Service.
 **********************************************/
void serv_CpnDataMana_setDataLen(void *buff){
    htsDataLen dataLen = (htsDataLen)buff;
    uint16 len = dataLen->len;
    if((dataLen->len+dataLen->index) > dmDataSets[dataLen->pduId].dataSetLen){
        if(dataLen->index >= dmDataSets[dataLen->pduId].dataSetLen){
            len = 0u;
        }else{
            len = (dmDataSets[dataLen->pduId].dataSetLen-dataLen->index);
        }
    }
    /* if length is abnormal stop copy datas. */
    if(len){
        appMemCopy(dataLen->buff,&dmDataSetsSpace[dmDataSetsStartAddr[dataLen->pduId]+dataLen->index],len);
    }
}


/* set signals serv.
 **********************************************/
void serv_CpnDataMana_setDataSig_operation(uint16 set_sig, dataSigType *value){
    tsDataSig dataSigSet;
    dataSigSet.sig = set_sig;
    dataSigSet.value = value;
    clRteSynSigs.trig(clRteSynSigs.self, dmMapSet[set_sig].sig_operation_name, (uint8*)&dataSigSet);
}
/*void serv_CpnDataMana_set_TxCanAAB_ulDataA(void *buff){
    serv_CpnDataMana_setDataSig_operation(set_sig_TxCanAAB_ulDataA,((dataSigType*)buff));
}*/
 DATASET_SET_SIG_SERV_DEF_EXPANTION(DATASET_SET_SIG_LIST)

/* get signals serv.
 **********************************************/
void serv_CpnDataMana_getDataSig_operation(uint16 get_sig, dataSigType *value){
    tsDataSig dataSigGet;
    dataSigGet.sig = get_sig;
    dataSigGet.value = value;
    clRteSynSigs.trig(clRteSynSigs.self, dmMapGet[get_sig].sig_operation_name, (uint8*)&dataSigGet);
}
/*void serv_CpnDataMana_get_RxCan22F_ulData1(void *buff){
    serv_CpnDataMana_getDataSig_operation(get_sig_RxCan22F_ulData1,((dataSigType*)buff));
}*/
 DATASET_GET_SIG_SERV_DEF_EXPANTION(DATASET_GET_SIG_LIST)
 DATASET_GET_SIG_SERV_DEF_EXPANTION(DATASET_SET_SIG_LIST)


/* Interface trigger.
 **********************************************/
//void trig_CpnDataMana_inf_infFunc(void){}
 /* Interface.
  **********************************************/
 void dataSet_sentDrv(teDMIFx ifx, uint32 id, uint8 *start, uint16 len){
    pduIdType pduId = 0u;

    switch(ifx){
    case DM_IFx_CAN:
        break;
    case DM_IFx_SPI:
        break;
    case DM_IFx_SCI:
        break;
    case DM_IFx_IIC:
        break;
    default:
        break;
    }
    /* indicate DataSet is transmitted. */
    pduId = clCpnDataMana.pduR.getPduId(clCpnDataMana.pduR.self,ifx,DM_TX,id);
    if(pduId < PduIdMax){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataMana_txConfirmation, (uint8*)&pduId);
    }
 }


/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnDataMana(void){}

/**************************** Copyright(C) pxf ****************************/
