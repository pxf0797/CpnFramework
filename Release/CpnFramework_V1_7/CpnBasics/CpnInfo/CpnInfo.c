/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnInfo.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/05/26 16:35:22
 * Description  : CpnInfo class functions definition source files.
 * Others       :
 * History      : 20210526 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnInfo.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnInfo class definition.
 **********************************************************/
/* Function : CpnInfo_run(hCpnInfo cthis)
 * Input    : cthis - CpnInfo class pointer
 * Output   :
 * Others   : CpnInfo class function.
 **********************************************/
typedef enum {
    INFO_IDLE,
    INFO_SENDING,
    INFO_FREE_MEM
} teInfoSendStep;
void CpnInfo_run(hCpnInfo cthis){
    static teInfoSendStep teStep = INFO_IDLE;
    static tsInfoFifoBuff tsInfo;
    static char *pInfoBuffFree = NULL;

    switch (teStep){
    case INFO_IDLE:
        if(!cthis->hFifo->isEmpty(cthis->hFifo)){
            cthis->hFifo->fout(cthis->hFifo, &tsInfo);
            pInfoBuffFree = tsInfo.pBuff;
            teStep = INFO_SENDING;
        }
        break;

    case INFO_SENDING:
        if(tsInfo.uwUsedCnt > CPNINFOCFG_OUTPUT_FRAME_SIZE){
            cthis->output(cthis, (uint8*)tsInfo.pBuff, CPNINFOCFG_OUTPUT_FRAME_SIZE);
            tsInfo.uwUsedCnt -= CPNINFOCFG_OUTPUT_FRAME_SIZE;
            tsInfo.pBuff += CPNINFOCFG_OUTPUT_FRAME_SIZE;
            teStep = INFO_SENDING;
        }else{
            cthis->output(cthis, (uint8*)tsInfo.pBuff, tsInfo.uwUsedCnt);
            tsInfo.uwUsedCnt = 0;
            tsInfo.pBuff = NULL;
            teStep = INFO_FREE_MEM;
        }
        break;

    case INFO_FREE_MEM:
        if(pInfoBuffFree){
            cthis->hBlockM->free(cthis->hBlockM, pInfoBuffFree);
            cthis->hBlockM->free(cthis->hBlockM, tsInfo.pFifoBuff);
        }
        pInfoBuffFree = NULL;
        teStep = INFO_IDLE;
        break;

    default:
        teStep = INFO_IDLE;
        break;
    }
}

/* Function : CpnInfo_output(hCpnInfo cthis)
 * Input    : cthis - CpnInfo class pointer
 * Output   :
 * Others   : CpnInfo class function.
 **********************************************/
void CpnInfo_output(hCpnInfo cthis, uint8 *buff, uint16 len){
    tuBytesData tuFrameData;
    tsFrameTrans tsFrame = {CPNINFOCFG_FRAME_ID, &tuFrameData};

    if(!buff){
        return;
    }
    if(len >= CPNINFOCFG_OUTPUT_FRAME_SIZE){
        memCopy(tsFrame.frame->byte, buff, CPNINFOCFG_OUTPUT_FRAME_SIZE);
    }else{
        memCopy(tsFrame.frame->byte, buff, len);
        memSet(&tsFrame.frame->byte[len], 0, (CPNINFOCFG_OUTPUT_FRAME_SIZE-len));
    }

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnInfo_updateFrame, (uint8*)&tsFrame);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnInfo_sendFrame, (uint8*)&tsFrame.id);
}

/* Function : CpnInfo_setErr(hCpnInfo cthis)
 * Input    : cthis - CpnInfo class pointer
 * Output   :
 * Others   : CpnInfo class function.
 **********************************************/
void CpnInfo_setErr(hCpnInfo cthis, uint16 code){
    uint32 uwErrCode = (((uint32)CPNINFOCFG_ERR_ID << 16) + code);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnInfo_setErr, (uint8*)&uwErrCode);
}

/* Function : CpnInfo_info(hCpnInfo cthis)
 * Input    : cthis - CpnInfo class pointer
 * Output   :
 * Others   : CpnInfo class function.
 **********************************************/
void CpnInfo_info(hCpnInfo cthis, const char *file, const char *func,
    const uint16 line, const char *format, va_list args){
    //va_list args;
    htsInfoFifoBuff htsInfo = NULL;
    uint16 uwNow = 0u;
    char *pFile = (char*)file, *pTempFile = (char*)file;

    if(cthis->hFifo->isFull(cthis->hFifo)){
        cthis->setErr(cthis, CPNINFOCFG_FIFO_IS_FULL);
        return;
    }

    htsInfo = (htsInfoFifoBuff)cthis->hBlockM->malloc(cthis->hBlockM, sizeof(tsInfoFifoBuff));
    if(!htsInfo){
        cthis->setErr(cthis, CPNINFOCFG_MEMORY_NOT_ENOUGH);
        return;
    }
    htsInfo->pFifoBuff = (char*)htsInfo;
    htsInfo->pBuff = (char*)cthis->hBlockM->malloc(cthis->hBlockM, CPNINFOCFG_INFO_BUFF_SIZE);
    if(!htsInfo->pBuff){
        cthis->hBlockM->free(cthis->hBlockM, htsInfo);
        cthis->setErr(cthis, CPNINFOCFG_MEMORY_NOT_ENOUGH);
        return;
    }
    htsInfo->uwUsedCnt = 0u;

    while(*pTempFile){
        if(*pTempFile == '\\'){
            pFile = (pTempFile+1u);
        }
        pTempFile++;
    }

    //va_start(args, format);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnInfo_now, (uint8*)&uwNow);
    htsInfo->uwUsedCnt += (uint16)snprintf((char*)&htsInfo->pBuff[htsInfo->uwUsedCnt], (CPNINFOCFG_INFO_BUFF_SIZE-htsInfo->uwUsedCnt), "[%05u] ", uwNow);
    htsInfo->uwUsedCnt += (uint16)vsnprintf((char*)&htsInfo->pBuff[htsInfo->uwUsedCnt], (CPNINFOCFG_INFO_BUFF_SIZE-htsInfo->uwUsedCnt), format, args);

    htsInfo->uwUsedCnt += strCopy(&htsInfo->pBuff[htsInfo->uwUsedCnt], " <");
    htsInfo->uwUsedCnt += strCopy(&htsInfo->pBuff[htsInfo->uwUsedCnt], pFile);
    htsInfo->uwUsedCnt += strCopy(&htsInfo->pBuff[htsInfo->uwUsedCnt], " - ");
    htsInfo->uwUsedCnt += strCopy(&htsInfo->pBuff[htsInfo->uwUsedCnt], (char*)func);
    htsInfo->uwUsedCnt += (uint16)snprintf((char*)&htsInfo->pBuff[htsInfo->uwUsedCnt], (CPNINFOCFG_INFO_BUFF_SIZE-htsInfo->uwUsedCnt), ":%u ", line);
    htsInfo->uwUsedCnt += strCopy(&htsInfo->pBuff[htsInfo->uwUsedCnt], ">\n");
    //va_end(args);

    cthis->hFifo->push(cthis->hFifo, htsInfo);
}

/* Function : hCpnInfo CpnInfo_init(hCpnInfo cthis)
 * Input    : cthis - CpnInfo class pointer
 * Output   : hCpnInfo - cthis/OOPC_NULL
 * Others   : CpnInfo class initial function.
 **********************************************/
hCpnInfo CpnInfo_init(hCpnInfo cthis, hBlockM hBlockM,
    uint8 *memSpace, uint16 blockSize, uint16 blockNum){
    uint8 *pucBuffer = NULL;
    hCpnInfo hCpnInfoRet = cthis;

    /* Configure functions. */
    cthis->hBlockM = hBlockM;

    /* Configure parameters. */
    CN(BlockM,cthis->hBlockM,memSpace,blockSize,blockNum);
    if(OPRS(*cthis->hBlockM) != OOPC_NULL){
        cthis->hFifo = (hFifo)cthis->hBlockM->malloc(cthis->hBlockM, sizeof(Fifo));
        if(cthis->hFifo == NULL){
            hCpnInfoRet = OOPC_NULL;
        }
    }else{
        hCpnInfoRet = OOPC_NULL;
    }
    if(hCpnInfoRet != OOPC_NULL){
        pucBuffer = (uint8*)cthis->hBlockM->malloc(cthis->hBlockM, sizeof(tsInfoFifoBuff)*CPNINFOCFG_FIFO_OBJECT_NUM);
        if(pucBuffer == NULL){
            cthis->hBlockM->free(cthis->hBlockM, cthis->hFifo);
            hCpnInfoRet = OOPC_NULL;
        }else{
            CN(Fifo, cthis->hFifo,pucBuffer, sizeof(tsInfoFifoBuff)*CPNINFOCFG_FIFO_OBJECT_NUM, sizeof(tsInfoFifoBuff));
            if(OPRS(*cthis->hFifo) == OOPC_NULL){
                hCpnInfoRet = OOPC_NULL;
            }
        }
    }

    return hCpnInfoRet;
}

/* Function : hCpnInfo CpnInfo_ctor(hCpnInfo cthis)
 * Input    : cthis - CpnInfo class pointer
 * Output   : hCpnInfo - cthis/OOPC_NULL
 * Others   : CpnInfo class constructor.
 **********************************************/
CC(CpnInfo){
    cthis->init = CpnInfo_init;
    cthis->run = CpnInfo_run;
    cthis->output = CpnInfo_output;
    cthis->setErr = CpnInfo_setErr;
    cthis->info = CpnInfo_info;
    /* TODO */

    /* Configure parameters. */
    cthis->hBlockM = NULL;
    cthis->hFifo = NULL;

    return cthis;
}

/* Function : hCpnInfo CpnInfo_dtor(hCpnInfo cthis)
 * Input    : cthis - CpnInfo class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnInfo class destructor.
 **********************************************/
CD(CpnInfo){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
