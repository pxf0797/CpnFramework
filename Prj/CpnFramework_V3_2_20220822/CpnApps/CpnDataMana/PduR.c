/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : PduR.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 14:48:50
 * Description  : PduR class functions definition source files.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "PduR.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * PduR class definition.
 **********************************************************/
/* Function : PduR_getPduId(hPduR cthis)
 * Input    : cthis - PduR class pointer
 * Output   :
 * Others   : PduR class function.
 **********************************************/
pduIdType PduR_getPduId(hPduR cthis, teDMIFx ifx, teDMRxTx rxtx, uint32 id){
    pduIdType pudId = PduIdMax;
    uint16 low = 0u, mid = 0u, high = 0u;
    htsIFxPduId ifxPduId = OOPC_NULL;
    /* bin search id index */
    do{
        /* dispose abnormal. */
        if((rxtx == DM_RX)
        &&(!cthis->rxIFxPudIdNums[ifx])){
            break;
        }
        if((rxtx == DM_TX)
        &&(!cthis->txIFxPudIdNums[ifx])){
            break;
        }
        if(rxtx == DM_RX){
            high = cthis->rxIFxPudIdNums[ifx];
            ifxPduId = cthis->rxIFxPduId[ifx];
        }else{
            high = cthis->txIFxPudIdNums[ifx];
            ifxPduId = cthis->txIFxPduId[ifx];
        }
        while(ifxPduId[low].id <= ifxPduId[high].id){
            /* Odd number, no matter even or odd, just have a value. */
            mid = ((low+high)>>1u);
            if(id < ifxPduId[mid].id){
                if(mid == 0u){
                    break;
                    /* Is mid-1, because mid has been compared. */
                    high = (mid-1u);
                }
            }else if(id > ifxPduId[mid].id){
                low = (mid+1u);
            }else{
                pudId = ifxPduId[mid].pduId;
                break;
            }
        }
    }while(0);
    return pudId;
}

/* Function : PduR_getRespondPduId(hPduR cthis)
 * Input    : cthis - PduR class pointer
 * Output   :
 * Others   : PduR class function.
 **********************************************/
pduIdType PduR_getRespondPduId(hPduR cthis, pduIdType pduId){
    pduIdType pudId = PduIdMax;
    uint16 low = 0u, mid = 0u, high = 0u;
    /* bin search id index */
    do{
        /* dispose abnormal. */
        if(!cthis->pduRPduIdMapNums){
            break;
        }
        if(pduId > cthis->pduRPduIdMap[cthis->pduRPduIdMapNums-1].pduIdReq){
            break;
        }
        high = (cthis->pduRPduIdMapNums-1u);
        while(cthis->pduRPduIdMap[low].pduIdReq <= cthis->pduRPduIdMap[high].pduIdReq){
            /* Odd number, no matter even or odd, just have a value. */
            mid = ((low+high)>>1u);
            if(pduId < cthis->pduRPduIdMap[mid].pduIdReq){
                if(mid == 0u){
                    break;
                }
                /* Is mid-1, because mid has been compared. */
                high = (mid-1u);
            }else if(pduId > cthis->pduRPduIdMap[mid].pduIdReq){
                low = (mid+1u);
            }else{
                pudId = cthis->pduRPduIdMap[mid].pduIdRes;
                break;
            }
        }
    }while(0);
    return pudId;
}

/* Function : hPduR PduR_init(hPduR cthis)
 * Input    : cthis - PduR class pointer
 * Output   : hPduR - cthis/OOPC_NULL
 * Others   : PduR class initial function.
 **********************************************/
hPduR PduR_init(hPduR cthis, htsDMDataSet dataSet, uint8 *pduIdTable,
                uint16 pduRPduIdMapNums, htsPduRPudIdMap pduRPduIdMap){
    hPduR retRes = cthis;
    uint16 i = 0u, j = 0u;
    uint16 initCount[2][DM_IFx_MAX] = {0};
    teDMIFx ifx = DM_IFx_MAX;
    teDMRxTx rxtx = DM_RX;
    htsIFxPduId ifxPduId = OOPC_NULL;
    pduIdType pduId = 0u;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        if(!(dataSet&&pduIdTable&&pduRPduIdMapNums&&pduRPduIdMap)){
            retRes = OOPC_NULL;
            break;
        }
        /* Configure functions. */
        //cthis->getPduId = PduR_getPduId;
        /* TODO */

        /* Configure parameters. */
        cthis->dataSet = dataSet;
        cthis->pduIdTable = pduIdTable;
        cthis->pduRPduIdMapNums = pduRPduIdMapNums;
        cthis->pduRPduIdMap = pduRPduIdMap;
        /* bubble sort pduRPduIdMap, increase. */
        for(i = 0u; i < (cthis->pduRPduIdMapNums-1u); i++){
            for(j = 0u; j < (cthis->pduRPduIdMapNums-1u-i); j++){
                if(cthis->pduRPduIdMap[j].pduIdReq > cthis->pduRPduIdMap[j+1].pduIdReq){
                    pduId = cthis->pduRPduIdMap[j].pduIdReq;
                    cthis->pduRPduIdMap[j].pduIdReq = cthis->pduRPduIdMap[j+1].pduIdReq;
                    cthis->pduRPduIdMap[j+1].pduIdReq = pduId;
                }
            }
        }
        /* count rx and tx pduIdNums. */
        for(i = 0u; i < PduIdMax; i++){
            ifx = cthis->dataSet[i].ifx;
            if(ifx >= DM_IFx_MAX){
                continue;
            }
            if(cthis->dataSet[i].rxtx == DM_RX){
                cthis->rxIFxPudIdNums[ifx]++;
            }else{
                cthis->txIFxPudIdNums[ifx]++;
            }
        }
        /* set pduId table addr. */
        cthis->rxIFxPduId[0] = (htsIFxPduId)cthis->pduIdTable;
        cthis->txIFxPduId[0] = (htsIFxPduId)(cthis->pduIdTable+(sizeof(tsIFxPduId)*DM_IFx_MAX));
        for(i = 0u; i < (DM_IFx_MAX-1u); i++){
            cthis->rxIFxPduId[i+1] = (cthis->rxIFxPduId[i]+(sizeof(tsIFxPduId)*cthis->rxIFxPudIdNums[i]));
            cthis->txIFxPduId[i+1] = (cthis->txIFxPduId[i]+(sizeof(tsIFxPduId)*cthis->txIFxPudIdNums[i]));
        }
        /* initial pduId table. */
        for(i = 0u; i < PduIdMax; i++){
            ifx = cthis->dataSet[i].ifx;
            if(ifx >= DM_IFx_MAX){
                continue;
            }
            rxtx = cthis->dataSet[i].rxtx;
            if(rxtx == DM_RX){
                ifxPduId = cthis->rxIFxPduId[ifx];
            }else{
                ifxPduId = cthis->txIFxPduId[ifx];
            }
            /* insert sort. */
            do{
                /* if current count is 0, direct save pduId map. */
                if(initCount[rxtx][ifx] == 0u){
                    ifxPduId[0].id = cthis->dataSet[i].id;
                    ifxPduId[0].pduId = cthis->dataSet[i].pduId;
                    break;
                }
                for(j = initCount[rxtx][ifx]; j > 0u; j--){
                    if(ifxPduId[j-1].id > cthis->dataSet[i].id){
                        ifxPduId[j].id = ifxPduId[j-1].id;
                        ifxPduId[j].pduId = ifxPduId[j-1].pduId;
                        if(j==1u){
                            ifxPduId[0].id = cthis->dataSet[i].id;
                            ifxPduId[0].pduId = cthis->dataSet[i].pduId;
                            break;
                        }
                    }else{
                        ifxPduId[j].id = cthis->dataSet[i].id;
                        ifxPduId[j].pduId = cthis->dataSet[i].pduId;
                        break;
                    }
                }
            }while(0);
            /* increase count. */
            initCount[rxtx][ifx]++;
        }
        /* judge initial result */
        for(i = 0u; i < DM_IFx_MAX; i++){
            if((cthis->rxIFxPudIdNums[i] != initCount[DM_RX][i])
            || (cthis->txIFxPudIdNums[i] != initCount[DM_TX][i])){
                retRes = OOPC_NULL;
                break;
            }
        }
    }while(0);
    return retRes;
}

/* Function : hPduR PduR_ctor(hPduR cthis)
 * Input    : cthis - PduR class pointer
 * Output   : hPduR - cthis/OOPC_NULL
 * Others   : PduR class constructor.
 **********************************************/
CC(PduR){
    hPduR retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        cthis->init = PduR_init;
        cthis->getPduId = PduR_getPduId;
        cthis->getRespondPduId = PduR_getRespondPduId;
        /* TODO */

        /* Configure parameters. */
        cthis->pduRPduIdMapNums = 0u;
        cthis->pduRPduIdMap = OOPC_NULL;
    }while(0);
    return retRes;
}

/* Function : hPduR PduR_dtor(hPduR cthis)
 * Input    : cthis - PduR class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : PduR class destructor.
 **********************************************/
CD(PduR){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
