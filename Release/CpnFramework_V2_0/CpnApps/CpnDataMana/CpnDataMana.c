/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataMana.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 10:10:28
 * Description  : CpnDataMana class functions definition source files.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnDataMana.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
extern CpnDataMana clCpnDataMana;

/***********************************************************
 * CpnDataMana class definition.
 **********************************************************/
/* Function : CpnDataMana_run(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   :
 * Others   : CpnDataMana class function.
 **********************************************/
void CpnDataMana_run(hCpnDataMana cthis){
    cthis->slicSch.run(cthis->slicSch.self);
    cthis->timer++;
}

/* Function : groupAct()
 * Input    : index - group index
 * Output   :
 * Others   :
 **********************************************/
void groupAct(uint16 index){
    hCpnDataMana cthis = &clCpnDataMana;
    cthis->executeGroup(cthis, index);
}

/* Function : CpnDataMana_setDataSig(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   :
 * Others   : CpnDataMana class function.
 **********************************************/
void CpnDataMana_setDataSig(hCpnDataMana cthis, pduIdType pduId, uint16 bit_start, uint16 bit_len, dataSigType value){
#if 0
    volatile uint16 leftShift, long_data_index, long_data_bit_index;
    volatile dataSigType mask, dataL, dataH, dataL_mask, dataH_mask;
    htsDMDataSet dataSet = &cthis->dataSet[pduId];
    uint8 *dataSetAddr = &cthis->space[cthis->start[pduId]];

    if(dataSet->format == DM_INTEL_STANDARD){
        leftShift = bit_start;
    }else if(dataSet->format == DM_INTEL_SEQUENTIAL){
        leftShift = bit_start^0x7U;
    }else if(dataSet->format == DM_MOTOROLA_LSB){
        leftShift = bit_start^0x38U;
    }else if(dataSet->format == DM_MOTOROLA_MSB){
        leftShift = ((bit_start^0x7U)+bit_len-1U)^0x3FU;
    }else if(dataSet->format == DM_MOTOROLA_SEQUENTIAL){
        leftShift = ((dataSet->dataSetLen<<3U)-bit_len-bit_start);
    }else{
        /* default intel standard */
        leftShift = bit_start;
    }

    long_data_index = (uint16)(leftShift>>DATASIG_TYPE_BITS);
    long_data_bit_index = (uint16)(leftShift&DATASIG_TYPE_MASK);
    mask = (dataSigType)((0x1UL << bit_len)-1U);

    dataL_mask = (~(mask<<long_data_bit_index));
    dataH_mask = (~(mask>>(DATASIG_TYPE_WIDTH-long_data_bit_index)));
    dataL = (value<<long_data_bit_index);
    dataH = (value>>(DATASIG_TYPE_WIDTH-long_data_bit_index));

    if(dataSet->format > DM_INTEL_SEQUENTIAL){
        dataL_mask = SWAP32_BIT8(SWAP32_BIT16(dataL_mask));
        dataH_mask = SWAP32_BIT8(SWAP32_BIT16(dataH_mask));
        dataL = SWAP32_BIT8(SWAP32_BIT16(dataL));
        dataH = SWAP32_BIT8(SWAP32_BIT16(dataH));

        long_data_index = (((dataSet->dataSetLen>>2U)-1U)-long_data_index);
        dataSetAddr[long_data_index] &= dataL_mask;
        dataSetAddr[long_data_index] |= dataL;
        if(long_data_index > 0U){
            dataSetAddr[long_data_index-1U] &= dataH_mask;
            dataSetAddr[long_data_index-1U] |= dataH;
        }
    }else{
        dataSetAddr[long_data_index] &= dataL_mask;
        dataSetAddr[long_data_index] |= dataL;
        if(long_data_index < ((dataSet->dataSetLen>>2U)-1U)){
            dataSetAddr[long_data_index+1U] &= dataH_mask;
            dataSetAddr[long_data_index+1U] |= dataH;
        }
    }
#else
    volatile uint16 leftShift, dataSigType_index, dataSigType_bit_index, total_bits;
    dataSigType mask;
    htsDMDataSet dataSet = &cthis->dataSet[pduId];
    uint8 *dataSetAddr = &cthis->space[cthis->start[pduId]];
    volatile tuDataSig dataL, dataH, dataL_mask, dataH_mask;
    uint16 i = 0u, startIndex = 0u;

    /* calculate shift bit. */
    total_bits = (dataSet->dataSetLen<<3u);
    switch(dataSet->format){
    case DM_INTEL_STANDARD:
        leftShift = bit_start;
    break;
    case DM_INTEL_SEQUENTIAL:
        leftShift = bit_start^0x7u;
    break;
    case DM_MOTOROLA_LSB:
        //leftShift = bit_start^0x38u;
        leftShift = (total_bits-((bit_start^7u)+1u));
    break;
    case DM_MOTOROLA_MSB:
        leftShift = (total_bits-((bit_start^7u)+bit_len));
    break;
    case DM_MOTOROLA_SEQUENTIAL:
        leftShift = (total_bits-(bit_start+bit_len));
    break;
    default:
        return;
    break;
    }
    /* get bit index in dataSigType range. */
    mask = ((bit_len>=DATASIG_TYPE_WIDTH)?((dataSigType)0u-1u):(((dataSigType)1u<<bit_len)-1u));
    dataSigType_index = (leftShift>>DATASIG_TYPE_BITS);
    dataSigType_bit_index = (leftShift&DATASIG_TYPE_MASK);
    /* calculate data fill dataSet. */
    dataL.data = (value<<dataSigType_bit_index);
    dataL_mask.data = (mask<<dataSigType_bit_index);
    dataH_mask.data = 0u;
    if((dataSigType_bit_index+bit_len) > DATASIG_TYPE_WIDTH){
        dataH.data = (value>>(DATASIG_TYPE_WIDTH-dataSigType_bit_index));
        dataH_mask.data = (mask>>(DATASIG_TYPE_WIDTH-dataSigType_bit_index));
    }
    /* fill dataSet. */
    if(dataSet->format > DM_INTEL_SEQUENTIAL){
        /* fill low bytes. */
        startIndex = (dataSigType_index*sizeof(dataSigType));
        for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
            dataSetAddr[dataSet->dataSetLen-i-1u] &= (~dataL_mask.byte[i-startIndex]);
            dataSetAddr[dataSet->dataSetLen-i-1u] |= dataL.byte[i-startIndex];
        }
        /* fill high bytes. */
        if(dataH_mask.data){
            startIndex = ((dataSigType_index+1u)*sizeof(dataSigType));
            for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
                dataSetAddr[dataSet->dataSetLen-i-1u] &= (~dataH_mask.byte[i-startIndex]);
                dataSetAddr[dataSet->dataSetLen-i-1u] |= dataH.byte[i-startIndex];
            }
        }
    }else{
        /* fill low bytes. */
        startIndex = (dataSigType_index*sizeof(dataSigType));
        for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
            dataSetAddr[i] &= (~dataL_mask.byte[i-startIndex]);
            dataSetAddr[i] |= dataL.byte[i-startIndex];
        }
        /* fill high bytes. */
        if(dataH_mask.data){
            startIndex = ((dataSigType_index+1u)*sizeof(dataSigType));
            for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
                dataSetAddr[i] &= (~dataH_mask.byte[i-startIndex]);
                dataSetAddr[i] |= dataH.byte[i-startIndex];
            }
        }
    }
#endif
}

/* Function : CpnDataMana_getDataSig(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   :
 * Others   : CpnDataMana class function.
 **********************************************/
void CpnDataMana_getDataSig(hCpnDataMana cthis, pduIdType pduId, uint16 bit_start, uint16 bit_len, dataSigType *value){
#if 0
    volatile uint16 leftShift, long_data_index, long_data_bit_index;
    volatile uint32 mask, dataL, dataH/*, dataL_mask, dataH_mask*/;
    htsDMDataSet dataSet = &cthis->dataSet[pduId];
    uint8 *dataSetAddr = &cthis->space[cthis->start[pduId]];

    if(dataSet->format == DM_INTEL_STANDARD){
        leftShift = bit_start;
    }else if(dataSet->format == DM_INTEL_SEQUENTIAL){
        leftShift = bit_start^0x7U;
    }else if(dataSet->format == DM_MOTOROLA_LSB){
        leftShift = bit_start^0x38U;
    }else if(dataSet->format == DM_MOTOROLA_MSB){
        leftShift = ((bit_start^0x7U)+bit_len-1U)^0x3FU;
    }else if(dataSet->format == DM_MOTOROLA_SEQUENTIAL){
        leftShift = ((dataSet->dataSetLen<<3U)-bit_len-bit_start);
    }else{
        /* default intel standard */
        leftShift = bit_start;
    }

    long_data_index = (uint16)(leftShift>>DATASIG_TYPE_BITS);
    long_data_bit_index = (uint16)(leftShift&DATASIG_TYPE_MASK);
    mask = (dataSigType)((0x1UL << bit_len)-1U);

    //dataL_mask = (~(mask<<long_data_bit_index));
    //dataH_mask = (~(mask>>(DATASIG_TYPE_WIDTH-long_data_bit_index)));
    if(dataSet->format > DM_INTEL_SEQUENTIAL){
        long_data_index = (((dataSet->dataSetLen>>2U)-1U)-long_data_index);
        dataL = dataSetAddr[long_data_index];
        if(long_data_index > 0U){
            dataH = dataSetAddr[long_data_index-1U];
        }
        dataL = SWAP32_BIT8(SWAP32_BIT16(dataL));
        dataH = SWAP32_BIT8(SWAP32_BIT16(dataH));
    }else{
        dataL = dataSetAddr[long_data_index];
        if(long_data_index < ((dataSet->dataSetLen>>2U)-1U)){
            dataH = dataSetAddr[long_data_index+1U];
        }
    }
    *value = (((dataH<<(DATASIG_TYPE_WIDTH-long_data_bit_index))|(dataL>>long_data_bit_index))&mask);
#else
    volatile uint16 leftShift, dataSigType_index, dataSigType_bit_index, total_bits;
    dataSigType mask;
    htsDMDataSet dataSet = &cthis->dataSet[pduId];
    uint8 *dataSetAddr = &cthis->space[cthis->start[pduId]];
    volatile tuDataSig dataL, dataH/*, dataL_mask, dataH_mask*/;
    uint16 i = 0u, startIndex = 0u;

    /* calculate shift bit. */
    total_bits = (dataSet->dataSetLen<<3u);
    switch(dataSet->format){
    case DM_INTEL_STANDARD:
        leftShift = bit_start;
    break;
    case DM_INTEL_SEQUENTIAL:
        leftShift = bit_start^0x7u;
    break;
    case DM_MOTOROLA_LSB:
        //leftShift = bit_start^0x38u;
        leftShift = (total_bits-((bit_start^7u)+1u));
    break;
    case DM_MOTOROLA_MSB:
        leftShift = (total_bits-((bit_start^7u)+bit_len));
    break;
    case DM_MOTOROLA_SEQUENTIAL:
        leftShift = (total_bits-(bit_start+bit_len));
    break;
    default:
        return;
    break;
    }
    /* get bit index in dataSigType range. */
    mask = ((bit_len>=DATASIG_TYPE_WIDTH)?((dataSigType)0u-1u):(((dataSigType)1u<<bit_len)-1u));
    dataSigType_index = (leftShift>>DATASIG_TYPE_BITS);
    dataSigType_bit_index = (leftShift&DATASIG_TYPE_MASK);
    /* fill tuDataSig. */
    if(dataSet->format > DM_INTEL_SEQUENTIAL){
        /* fill low bytes. */
        startIndex = (dataSigType_index*sizeof(dataSigType));
        for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
            dataL.byte[i-startIndex] = dataSetAddr[dataSet->dataSetLen-i-1u];
        }
        /* fill high bytes. */
        if((dataSigType_bit_index+bit_len) > DATASIG_TYPE_WIDTH){
            startIndex = ((dataSigType_index+1u)*sizeof(dataSigType));
            for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
                dataH.byte[i-startIndex] = dataSetAddr[dataSet->dataSetLen-i-1u];
            }
        }
    }else{
        /* fill low bytes. */
        startIndex = (dataSigType_index*sizeof(dataSigType));
        for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
            dataL.byte[i-startIndex] = dataSetAddr[i];
        }
        /* fill high bytes. */
        if((dataSigType_bit_index+bit_len) > DATASIG_TYPE_WIDTH){
            startIndex = ((dataSigType_index+1u)*sizeof(dataSigType));
            for(i = startIndex; ((i < dataSet->dataSetLen) && (i < (startIndex+sizeof(dataSigType)))); i++){
                dataH.byte[i-startIndex] = dataSetAddr[i];
            }
        }
    }
    /* shift data, and set output value. */
    dataL.data >>= dataSigType_bit_index;
    if((dataSigType_bit_index+bit_len) > DATASIG_TYPE_WIDTH){
        dataL.data |= (dataH.data<<(DATASIG_TYPE_WIDTH-dataSigType_bit_index));
    }
    dataL.data &= mask;
    *value = dataL.data;
#endif
}

/* Function : CpnDataMana_executeGroup(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   :
 * Others   : CpnDataMana class function.
 **********************************************/
void CpnDataMana_executeGroup(hCpnDataMana cthis, uint16 index){
    uint16 i = 0u;
    dataSigType mask = 0u, actMask = 0u;
    pduIdType pduId = 0u;
    uint16 periodTimes = 0u;

    if(index >= cthis->dataSetGroups){
        return;
    }
    mask = (cthis->txDataSetMask[index]&cthis->txDataSetActMask[index]);
    for(i = 0u; i < DATASIG_TYPE_WIDTH; i++){
        actMask = ((dataSigType)1u << i);
        pduId = ((index*DATASIG_TYPE_WIDTH)+i);
        /* dispose abnormal */
        if(pduId >= PduIdMax){
            break;
        }
        if(cthis->dataSet[pduId].rxtx == DM_RX){
            continue;
        }
        /* set actMask, wait for execute. */
        if(cthis->txDataSetMask[index]){
            //pduId = ((index*DATASIG_TYPE_WIDTH)+i);
            /* set actMask */
            if((cthis->dataSet[pduId].rxtx == DM_TX)
            &&(cthis->dataSet[pduId].period != 0u)){
                /* times of CPNDATAMANACFG_DATAMANA_EXECUTE_PERIOD active actMask one time.
                 * so, it is act at the period of ((period/CPNDATAMANACFG_DATAMANA_EXECUTE_PERIOD)-1u).
                 * */
                periodTimes = (cthis->dataSet[pduId].period/CPNDATAMANACFG_DATAMANA_EXECUTE_PERIOD);
                if(periodTimes != cthis->dataSetPeriodCounter[pduId]){
                    /* update for next time, and set actMask. */
                    if(++cthis->dataSetPeriodCounter[pduId] >= periodTimes){
                        cthis->dataSetPeriodCounter[pduId] = 0u;
                        cthis->txDataSetActMask[index] |= actMask;
                    }
                }
            }
            /* sent actMask dataSet. */
            if((cthis->txDataSetActMask[index]&actMask)   /* period task */
            ||(mask&actMask)){                            /* one time task */
                pduId = ((index*DATASIG_TYPE_WIDTH)+i);
                cthis->sentDrv.sentDrv(cthis->dataSet[pduId].ifx,
                        cthis->dataSet[pduId].id,
                        &cthis->space[cthis->start[pduId]],
                        cthis->dataSet[pduId].dataSetLen);
                /* clear current actMask. wait for next time active. */
                cthis->txDataSetActMask[index] &= (~actMask);
            }
        }
    }
}

/* Function : CpnDataMana_triggerSent(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   :
 * Others   : CpnDataMana class function.
 **********************************************/
uint16 CpnDataMana_triggerSent(hCpnDataMana cthis, pduIdType pduId){
    uint16 retRes = FALSE;
    dataSigType actMask = 0u;
    uint16 index = 0u;

    actMask = ((dataSigType)1u<<(pduId&DATASIG_TYPE_MASK));
    index = (pduId>>DATASIG_TYPE_BITS);
    if(pduId < PduIdMax){
        /* find setMask, then set setActMask */
        if(cthis->txDataSetMask[index]&actMask){
            cthis->txDataSetActMask[index] |= actMask;
            retRes = TRUE;
        }
    }
    return retRes;
}

/* Function : CpnDataMana_clearSent(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   :
 * Others   : CpnDataMana class function.
 **********************************************/
uint16 CpnDataMana_clearSent(hCpnDataMana cthis, pduIdType pduId){
    uint16 retRes = FALSE;
    dataSigType actMask = 0u;
    uint16 index = 0u;

    actMask = ((dataSigType)1u<<(pduId&DATASIG_TYPE_MASK));
    index = (pduId>>DATASIG_TYPE_BITS);
    if(pduId < PduIdMax){
        /* find setActMask, then clear setActMask */
        if(cthis->txDataSetActMask[index]&actMask){
            cthis->txDataSetActMask[index] &= (~actMask);
            retRes = TRUE;
        }
    }
    return retRes;
}

/* Function : hCpnDataMana CpnDataMana_init(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   : hCpnDataMana - cthis/OOPC_NULL
 * Others   : CpnDataMana class initial function.
 **********************************************/
hCpnDataMana CpnDataMana_init(hCpnDataMana cthis,
                        const htsDMDataSet dataSet, uint8 *space, uint16 *start,
                        slice sliceFunc,
                        void(*sentDrv)(teDMIFx ifx, uint32 id, uint8 *start, uint16 len),
                        uint16 pduRPduIdMapNums, htsPduRPudIdMap pduRPduIdMap){
    hCpnDataMana retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        /* Configure functions. */
        if(!sliceFunc){
            retRes = OOPC_NULL;
            break;
        }
        CN(SliceSch,&cthis->slicSch,cthis->dataSetGroups,
                CPNDATAMANACFG_TASK_SLICE_PERIOD,CPNDATAMANACFG_DATAMANA_EXECUTE_PERIOD,
                cthis->sliceTable,sliceFunc);
        if(!OPRS(cthis->slicSch)){
            break;
        }
        /* Interface */
        if(!sentDrv){
            retRes = OOPC_NULL;
            break;
        }
        cthis->sentDrv.sentDrv = sentDrv;

        /* Configure parameters. */
        if(!(dataSet&&space&&start)){
            retRes = OOPC_NULL;
            break;
        }
        cthis->dataSet = dataSet;
        cthis->space = space;
        cthis->start = start;

        /* PduR */
        CN(PduR, &cthis->pduR,cthis->dataSet,(uint8*)cthis->ifxPduIdTable,pduRPduIdMapNums,pduRPduIdMap);
        if(!OPRS(cthis->pduR)){
            retRes = OOPC_NULL;
        }
    }while(0);
    return retRes;
}

/* Function : hCpnDataMana CpnDataMana_ctor(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   : hCpnDataMana - cthis/OOPC_NULL
 * Others   : CpnDataMana class constructor.
 **********************************************/
CC(CpnDataMana){
    hCpnDataMana retRes = cthis;
    uint16 i = 0u;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        cthis->init = CpnDataMana_init;
        cthis->run = CpnDataMana_run;
        cthis->setDataSig = CpnDataMana_setDataSig;
        cthis->getDataSig = CpnDataMana_getDataSig;
        cthis->executeGroup = CpnDataMana_executeGroup;
        cthis->triggerSent = CpnDataMana_triggerSent;
        cthis->clearSent = CpnDataMana_clearSent;

        /* Configure parameters. */
        cthis->timer = 0u;
        cthis->dataSetGroups = DATASETS_ALIGN_MASK_SIZE;
        for(i = 0u; i < DATASETS_ALIGN_MASK_SIZE; i++){
            cthis->txDataSetMask[i] = 0u;
            cthis->txDataSetActMask[i] = 0u;
        }
        for(i = 0u; i < PduIdMax; i++){
            cthis->dataSetPeriodCounter[i] = 0u;
        }
        /* slice scheduler */
        for(i = 0u; i < CPNDATAMANACFG_TASK_SLICE_PERIOD; i++){
            cthis->sliceTable[i] = 0u;
        }
        /* PduR */
        for(i = 0u; i < (PduIdMax<<1); i++){
            cthis->ifxPduIdTable[i].id = 0u;
            cthis->ifxPduIdTable[i].pduId = 0u;
        }
    }while(0);
    return retRes;
}

/* Function : hCpnDataMana CpnDataMana_dtor(hCpnDataMana cthis)
 * Input    : cthis - CpnDataMana class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnDataMana class destructor.
 **********************************************/
CD(CpnDataMana){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
