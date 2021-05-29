/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinks.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:09:52
 * Description  : CpnSinks class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnSinks.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnSinks class definition.
 **********************************************************/
/* Function : CpnSinks_run(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
void CpnSinks_run(hCpnSinks cthis){
    uint16 i = 0u;
    sinkType groupMask = 0u;
    sinkType curMask = 0u;
    uint16 curIndex = 0u;

    for(i = 0u; i < CPNSINKSCFG_CACHE_TYPE_GROUPS; i++){
        groupMask = cthis->cacheGroups[i].cacheMask;
        while(groupMask){
            /* Get current channel. */
            curMask = MASK_FIRST_BIT(groupMask);
            groupMask &= (~curMask);
            curIndex = log_2n((uint32)curMask);
            curMask &= cthis->cacheGroups[i].startMask;
            if((curMask) /* Judge whether current channel started. */
            && (++cthis->cacheGroups[i].cacheCounter[curIndex] >= cthis->cacheGroups[i].sinksParams[curIndex].period)){ /* Increase counter. */
                cthis->cacheGroups[i].cacheCounter[curIndex] = 0;
                /* Fetch datas. */
                clRteAsynSigs.get(clRteAsynSigs.self, cthis->cacheGroups[i].sinksParams->get_getSig,
                (cthis->cacheGroups[i].cacheFifo[curIndex].listBuffer+cthis->cacheGroups[i].cacheFifo[curIndex].listBuffSize),
                cthis->cacheGroups[i].cacheFifo[curIndex].fifoObjSize); /* Get data, and save it in temporay buffer. */
                cthis->cacheGroups[i].cacheFifo[curIndex].push(cthis->cacheGroups[i].cacheFifo[curIndex].self,
                (void*)(cthis->cacheGroups[i].cacheFifo[curIndex].listBuffer+cthis->cacheGroups[i].cacheFifo[curIndex].listBuffSize));
                /* Cache queue is full, then stop cache. */
                if(cthis->cacheGroups[i].cacheFifo[curIndex].isFull(cthis->cacheGroups[i].cacheFifo[curIndex].self)){
                    cthis->cacheGroups[i].startMask &= (~curMask);
                    cthis->cacheEnd(cthis,&cthis->cacheGroups[i].sinksParams[curIndex]);
                }
            }
        }
    }
}

/* Function : CpnSinks_readData(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
uint16 CpnSinks_readData(hCpnSinks cthis, htSinksParams sinks, void *buff){
    uint16 retSta = FALSE;
    uint16 curGroup = 0u;
    uint16 curIndex = 0u;
    sinkType curMask = 0u;

    /* Get current channel. */
    curGroup = (sinks->type_index>>CPNSINK_TYPE_BITS);
    curIndex = (sinks->type_index&CPNSINK_TYPE_MASK);
    curMask = ((sinkType)0x1u << curIndex);
    curMask &= cthis->cacheGroups[curGroup].cacheMask;
    /* Judge whether current channel exist. */
    if(curMask){
        if(cthis->cacheGroups[curGroup].cacheFifo[curIndex].isEmpty(cthis->cacheGroups[curGroup].cacheFifo[curIndex].self)){
            retSta = FALSE;
        }else{
            cthis->cacheGroups[curGroup].cacheFifo[curIndex].fout(cthis->cacheGroups[curGroup].cacheFifo[curIndex].self,buff);
            retSta = TRUE;
        }
    }else{
        cthis->err(cthis, CPNSINKSCFG_CACHE_NO_SUCH_KIND);
        retSta = FALSE;
    }
    return retSta;
}

/* Function : CpnSinks_trigStart(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
void CpnSinks_trigStart(hCpnSinks cthis, htSinksParams sinks){
    uint16 curGroup = 0u;
    uint16 curIndex = 0u;
    sinkType curMask = 0u;

    /* Get current channel. */
    curGroup = (sinks->type_index>>CPNSINK_TYPE_BITS);
    curIndex = (sinks->type_index&CPNSINK_TYPE_MASK);
    curMask = ((sinkType)0x1u << curIndex);
    curMask &= cthis->cacheGroups[curGroup].cacheMask;
    /* Judge whether current channel exist. */
    if(curMask){
        cthis->cacheGroups[curGroup].startMask |= curMask;
    }else{
        cthis->err(cthis, CPNSINKSCFG_CACHE_NO_SUCH_KIND);
    }
}

/* Function : CpnSinks_cacheState(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
tCacheProcessSta CpnSinks_cacheState(hCpnSinks cthis, htSinksParams sinks){
    tCacheProcessSta cachSta = cacheNotStart;
    uint16 curGroup = 0u;
    uint16 curIndex = 0u;
    sinkType curMask = 0u;

    /* Get current channel. */
    curGroup = (sinks->type_index>>CPNSINK_TYPE_BITS);
    curIndex = (sinks->type_index&CPNSINK_TYPE_MASK);
    curMask = ((sinkType)0x1u << curIndex);
    curMask &= cthis->cacheGroups[curGroup].startMask;
    /* Judge current channel state. */
    if(curMask){
        cachSta = cacheCaching;
    }else{
        if(!cthis->cacheGroups[curGroup].cacheFifo[curIndex].isEmpty(cthis->cacheGroups[curGroup].cacheFifo[curIndex].self)){
            cachSta = cacheFull;
        }
    }
    return cachSta;
}

/* Function : CpnSinks_cacheEnd(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
void CpnSinks_cacheEnd(hCpnSinks cthis, htSinksParams sinks){
    clRteSynSigs.trig(clRteSynSigs.self, sinks->trig_endSig,NULL);
}

/* Function : CpnSinks_registerCache(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
void CpnSinks_registerCache(hCpnSinks cthis, htSinksParams sinks){
    uint16 i = 0u;
    uint16 curIndex = 0u;
    sinkType curMask = 0u;

    /* Judge whether cache group full. */
    curMask = cthis->cacheGroups[CPNSINKSCFG_CACHE_TYPE_GROUPS-1u].cacheMask;
    if((curMask+1u)==0u){
        cthis->err(cthis, CPNSINKSCFG_CACHE_GROUP_FULL);
        return;
    }

    /* Find one channel. */
    for(i = 0u; i < CPNSINKSCFG_CACHE_TYPE_GROUPS; i++){
        curMask = cthis->cacheGroups[i].cacheMask;
        if((curMask+1u)!=0u){
            /* Calculate parameters. */
            curMask = (~curMask);
            curMask = MASK_FIRST_BIT(curMask);
            cthis->cacheGroups[i].cacheMask |= curMask;
            cthis->cacheGroups[i].startMask &= (~curMask);
            curIndex = log_2n((uint32)curMask);
            sinks->type_index = (16*i+curIndex);

            /* Configure paramters. */
            cthis->cacheGroups[i].sinksParams[curIndex].get_getSig = sinks->get_getSig;
            cthis->cacheGroups[i].sinksParams[curIndex].trig_endSig = sinks->trig_endSig;
            cthis->cacheGroups[i].sinksParams[curIndex].type_index = sinks->type_index;
            cthis->cacheGroups[i].sinksParams[curIndex].period = sinks->period;

            if(sinks->data_size > 0u){
                cthis->cacheGroups[i].sinksParams[curIndex].data_size = sinks->data_size;
            }else{
                cthis->err(cthis, CPNSINKSCFG_CACHE_DATA_SIZE_ERR);
            }
            if(sinks->buff){
                cthis->cacheGroups[i].sinksParams[curIndex].buff = sinks->buff;
            }else{
                cthis->err(cthis, CPNSINKSCFG_CACHE_DATA_BUFF_ERR);
            }
            cthis->cacheGroups[i].cacheCounter[curIndex] = 0u;

            /* Use the last data in the buff queue as a temporary buffer. */
            CN(Fifo,&cthis->cacheGroups[i].cacheFifo[curIndex],sinks->buff,(sinks->buff_size-sinks->data_size),sinks->data_size);
            if(OPRS(cthis->cacheGroups[i].cacheFifo[curIndex]) == OOPC_NULL){
                cthis->cacheGroups[i].cacheMask &= (~curMask);
                cthis->err(cthis, CPNSINKSCFG_CACHE_FIFO_INIT_ERR);
            }
        }
    }
}

/* Function : CpnSinks_reCache(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
void CpnSinks_reCache(hCpnSinks cthis, htSinksParams sinks){
    uint16 curGroup = 0u;
    uint16 curIndex = 0u;
    sinkType curMask = 0u;

    /* Get current channel. */
    curGroup = (sinks->type_index>>CPNSINK_TYPE_BITS);
    curIndex = (sinks->type_index&CPNSINK_TYPE_MASK);
    curMask = ((sinkType)0x1u<<curIndex);
    curMask &= cthis->cacheGroups[curGroup].cacheMask;
    /* Judge whether current channel exist. */
    if(curGroup >= CPNSINKSCFG_CACHE_INDEX_OUT_RANGE){
        cthis->err(cthis, CPNSINKSCFG_CACHE_INDEX_OUT_RANGE);
        return;
    }
    if(!curMask){
        cthis->err(cthis, CPNSINKSCFG_CACHE_INDEX_NOT_EXIST);
        return;
    }

    /* Modify paramters. */
    cthis->cacheGroups[curGroup].startMask &= (~curMask);
    // cthis->cacheGroups[curGroup].sinksParams[curIndex].get_getSig = sinks->get_getSig;
    // cthis->cacheGroups[curGroup].sinksParams[curIndex].trig_endSig = sinks->trig_endSig;
    // cthis->cacheGroups[curGroup].sinksParams[curIndex].type_index = sinks->type_index;
    cthis->cacheGroups[curGroup].sinksParams[curIndex].period = sinks->period;
    cthis->cacheGroups[curGroup].cacheCounter[curIndex] = 0;

    /* clear all buffer */
    if(!cthis->cacheGroups[curGroup].cacheFifo[curIndex].isEmpty(cthis->cacheGroups[curGroup].cacheFifo[curIndex].self)){
        cthis->cacheGroups[curGroup].cacheFifo[curIndex].clearAll(cthis->cacheGroups[curGroup].cacheFifo[curIndex].self);
    }
}

/* Function : CpnSinks_err(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
void CpnSinks_err(hCpnSinks cthis, uint16 code){
    uint32 uwErrCode = (((uint32)CPNSINKSCFG_ERR_ID << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinks_setErr, (uint8*)&uwErrCode);
}

/* Function : hCpnSinks CpnSinks_init(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   : hCpnSinks - cthis/OOPC_NULL
 * Others   : CpnSinks class initial function.
 **********************************************/
hCpnSinks CpnSinks_init(hCpnSinks cthis){
    /* Configure functions. */
    // cthis->iErr.setErr = setErr;

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnSinks CpnSinks_ctor(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   : hCpnSinks - cthis/OOPC_NULL
 * Others   : CpnSinks class constructor.
 **********************************************/
CC(CpnSinks){
    cthis->init = CpnSinks_init;
    cthis->run = CpnSinks_run;
    cthis->readData = CpnSinks_readData;
    cthis->trigStart = CpnSinks_trigStart;
    cthis->cacheState = CpnSinks_cacheState;
    cthis->cacheEnd = CpnSinks_cacheEnd;
    cthis->registerCache = CpnSinks_registerCache;
    cthis->reCache = CpnSinks_reCache;
    cthis->err = CpnSinks_err;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCpnSinks CpnSinks_dtor(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnSinks class destructor.
 **********************************************/
CD(CpnSinks){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
