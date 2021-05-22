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
    uint16 i = 0;
    uint16 groupMask = 0;
    uint16 curMask = 0;
    uint16 curIndex = 0;

    for(i = 0; i < CPNSINKSCFG_CACHE_TYPE_GROUPS; i++){
        groupMask = cthis->cacheGroups[i].cacheMask;
        while(groupMask){
            curMask = (groupMask & (-groupMask));
            groupMask &= (~curMask);
            curIndex = log_2n((uint32)curMask);
            curMask &= cthis->cacheGroups[i].startMask;
            if(curMask){
                if(++cthis->cacheGroups[i].cacheCounter[curIndex] >= cthis->cacheGroups[i].sinksParams[curIndex].period){
                    cthis->cacheGroups[i].cacheCounter[curIndex] = 0;
                    cthis->cacheData(cthis,&cthis->cacheGroups[i].sinksParams[curIndex]);
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
}

/* Function : CpnSinks_readData(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
uint16 CpnSinks_readData(hCpnSinks cthis, htSinksParams sinks, void *buff){
    uint16 retSta = FALSE;
    uint16 curGroup = 0;
    uint16 curIndex = 0;
    uint16 curMask = 0;

    curGroup = sinks->type_index>>4;
    curIndex = sinks->type_index&0x000FU;
    curMask = ((uint16)0x1 << curIndex);
    curMask &= cthis->cacheGroups[curGroup].cacheMask;
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
    uint16 curGroup = 0;
    uint16 curIndex = 0;
    uint16 curMask = 0;

    curGroup = sinks->type_index>>4;
    curIndex = sinks->type_index&0x000FU;
    curMask = ((uint16)0x1 << curIndex);
    curMask &= cthis->cacheGroups[curGroup].cacheMask;
    if(curMask){
        cthis->cacheGroups[curGroup].startMask |= curMask;
    }else{
        cthis->err(cthis, CPNSINKSCFG_CACHE_NO_SUCH_KIND);
    }
}

/* Function : CpnSinks_cacheData(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
void CpnSinks_cacheData(hCpnSinks cthis, htSinksParams sinks){
    uint16 curGroup = 0;
    uint16 curIndex = 0;

    curGroup = sinks->type_index>>4;
    curIndex = sinks->type_index&0x000FU;
    clRteSynSigs.trig(clRteSynSigs.self, sinks->trig_getSig,
    (cthis->cacheGroups[curGroup].cacheFifo[curIndex].listBuffer+cthis->cacheGroups[curGroup].cacheFifo[curIndex].listBuffSize));
}

/* Function : CpnSinks_cacheState(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   :
 * Others   : CpnSinks class function.
 **********************************************/
tCacheProcessSta CpnSinks_cacheState(hCpnSinks cthis, htSinksParams sinks){
    tCacheProcessSta cachSta = cacheNotStart;
    uint16 curGroup = 0;
    uint16 curIndex = 0;
    uint16 curMask = 0;

    curGroup = sinks->type_index>>4;
    curIndex = sinks->type_index&0x000FU;
    curMask = ((uint16)0x1 << curIndex);
    curMask &= cthis->cacheGroups[curGroup].startMask;
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
    uint16 i = 0;
    uint16 curMask = 0;
    uint16 curIndex = 0;

    curMask = cthis->cacheGroups[CPNSINKSCFG_CACHE_TYPE_GROUPS-1].cacheMask;
    if((curMask+1)==0){
        cthis->err(cthis, CPNSINKSCFG_CACHE_GROUP_FULL);
        return;
    }

    for(i = 0; i < CPNSINKSCFG_CACHE_TYPE_GROUPS; i++){
        curMask = cthis->cacheGroups[i].cacheMask;
        if((curMask+1)!=0){
            curMask = (~curMask);
            curMask = (curMask & (-curMask));
            cthis->cacheGroups[i].cacheMask |= curMask;
            cthis->cacheGroups[i].startMask &= (~curMask);
            curIndex = log_2n((uint32)curMask);
            sinks->type_index = (16*i+curIndex);

            cthis->cacheGroups[i].sinksParams[curIndex].trig_getSig = sinks->trig_getSig;
            cthis->cacheGroups[i].sinksParams[curIndex].trig_endSig = sinks->trig_endSig;
            cthis->cacheGroups[i].sinksParams[curIndex].type_index = sinks->type_index;
            cthis->cacheGroups[i].sinksParams[curIndex].period = sinks->period;

            if(sinks->data_size > 0){
                cthis->cacheGroups[i].sinksParams[curIndex].data_size = sinks->data_size;
            }else{
                cthis->err(cthis, CPNSINKSCFG_CACHE_DATA_SIZE_ERR);
            }
            if(sinks->buff){
                cthis->cacheGroups[i].sinksParams[curIndex].buff = sinks->buff;
            }else{
                cthis->err(cthis, CPNSINKSCFG_CACHE_DATA_BUFF_ERR);
            }
            cthis->cacheGroups[i].cacheCounter[curIndex] = 0;

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
    uint16 curGroup = 0;
    uint16 curIndex = 0;
    uint16 curMask = 0;

    curGroup = sinks->type_index>>4;
    curIndex = sinks->type_index&0x000FU;
    curMask = ((uint16)0x1 << curIndex);
    if(curGroup >= CPNSINKSCFG_CACHE_INDEX_OUT_RANGE){
        cthis->err(cthis, CPNSINKSCFG_CACHE_INDEX_OUT_RANGE);
        return;
    }
    if(!(((cthis->cacheGroups[curGroup].cacheMask)>>curIndex)&0x0001U)){
        cthis->err(cthis, CPNSINKSCFG_CACHE_INDEX_NOT_EXIST);
        return;
    }

    cthis->cacheGroups[curGroup].startMask &= (~curMask);
    // cthis->cacheGroups[curGroup].sinksParams[curIndex].trig_getSig = sinks->trig_getSig;
    // cthis->cacheGroups[curGroup].sinksParams[curIndex].trig_endSig = sinks->trig_endSig;
    // cthis->cacheGroups[curGroup].sinksParams[curIndex].type_index = sinks->type_index;
    cthis->cacheGroups[curGroup].sinksParams[curIndex].period = sinks->period;

    // if(sinks->data_size > 0){
    //     cthis->cacheGroups[curGroup].sinksParams[curIndex].data_size = sinks->data_size;
    // }else{
    //     cthis->err(cthis, CPNSINKSCFG_CACHE_DATA_SIZE_ERR);
    // }
    // if(sinks->buff){
    //     cthis->cacheGroups[curGroup].sinksParams[curIndex].buff = sinks->buff;
    // }else{
    //     cthis->err(cthis, CPNSINKSCFG_CACHE_DATA_BUFF_ERR);
    // }
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
    cthis->iErr.setErr(CPNSINKSCFG_ERR_ID, code);
}

/* Function : hCpnSinks CpnSinks_init(hCpnSinks cthis)
 * Input    : cthis - CpnSinks class pointer
 * Output   : hCpnSinks - cthis/OOPC_NULL
 * Others   : CpnSinks class initial function.
 **********************************************/
hCpnSinks CpnSinks_init(hCpnSinks cthis, void (*setErr)(uint16 id, uint16 code)){
    /* Configure functions. */
    cthis->iErr.setErr = setErr;

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
    cthis->cacheData = CpnSinks_cacheData;
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
