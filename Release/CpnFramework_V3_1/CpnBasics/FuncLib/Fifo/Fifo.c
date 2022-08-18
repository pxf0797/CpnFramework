/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : Fifo.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 17:33:45
 * Description  : Fifo class functions definition source files.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "Fifo.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * Fifo class definition.
 **********************************************************/
/* Function : Fifo_push(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint8 Fifo_push(hFifo cthis, void *data){
    uint8 ucRet = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = NULL;
    uint16 i = 0u;

    do{
        if(cthis->currCnt >= cthis->saveObjMaxLen){
            ucRet = FALSE;
            break;
        }
        /* Calculate store position, and store it. */
        desPtr = (cthis->listBuffer + (cthis->top * cthis->fifoObjSize));
        for (i = 0u; i < cthis->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }
        /* Update flags. */
        cthis->currCnt++;
        cthis->top++;
        if (cthis->top >= cthis->saveObjMaxLen){
            cthis->top = 0u;
        }
    }while(0);
    return ucRet;
}

/* Function : Fifo_pop(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint8 Fifo_pop(hFifo cthis, void *data){
    uint8 ucRet = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0u;

    do{
        if (cthis->currCnt == 0u){
            ucRet = FALSE;
            break;
        }
        /* Update flags. */
        cthis->currCnt--;
        if (cthis->top == 0u){
            cthis->top = (cthis->saveObjMaxLen - 1u);
        }else{
            cthis->top--;
        }
        /* Calculate store position, and read out. */
        srcPtr = (cthis->listBuffer + (cthis->top * cthis->fifoObjSize));
        for (i = 0u; i < cthis->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }
    }while(0);
    return ucRet;
}

/* Function : Fifo_fout(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint8 Fifo_fout(hFifo cthis, void *data){
    uint8 ucRet = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0u;

    do{
        if (cthis->currCnt == 0u){
            ucRet = FALSE;
            break;
        }
        /* Calculate store position, and read out. */
        srcPtr = (cthis->listBuffer + (cthis->bottom * cthis->fifoObjSize));
        for (i = 0u; i < cthis->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }
        /* Update flags. */
        cthis->currCnt--;
        cthis->bottom++;
        if (cthis->bottom >= cthis->saveObjMaxLen){
            cthis->bottom = 0u;
        }
    }while(0);
    return ucRet;
}

/* Function : Fifo_del(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint8 Fifo_del(hFifo cthis, void *data, void *fifoObjTempBuff){
    uint8 ucRet = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = (uint8 *)fifoObjTempBuff;
    uint16 i = 0u;
    uint16 j = cthis->currCnt;
    uint16 lastMaxLen = cthis->currCnt;

    do{
        if (cthis->currCnt == 0u){
            ucRet = FALSE;
            break;
        }
        for (j = cthis->currCnt; j > 0u; j--){
            if (FALSE == cthis->fout(cthis, fifoObjTempBuff)){
                ucRet = FALSE;
                break;
            }
            /* Determine whether the data is the same, delete the same,
             * and save it back to the queue if the difference is different. */
            srcPtr = (uint8 *)data;
            desPtr = (uint8 *)fifoObjTempBuff;
            for (i = 0u; i < cthis->fifoObjSize; i++){
                if (*desPtr++ != *srcPtr++){
                    break;
                }
            }
            if (i < cthis->saveObjMaxLen){
                /* Store non-lookup data back to the queue. */
                if (FALSE == cthis->push(cthis, fifoObjTempBuff)){
                    ucRet = FALSE;
                    break;
                }
            }
        }
        /* Determine whether to find and delete data, and return the operation result. */
        if ((TRUE == ucRet) && (cthis->currCnt < lastMaxLen)){
            ucRet = TRUE;
        }else{
            ucRet = FALSE;
        }
    }while(0);
    return ucRet;
}

/* Function : Fifo_isFull(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint8 Fifo_isFull(hFifo cthis){
    uint8 ucRet = FALSE;
    if(cthis->currCnt == cthis->saveObjMaxLen){
        ucRet = TRUE;
    }
    return ucRet;
}

/* Function : Fifo_isEmpty(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint8 Fifo_isEmpty(hFifo cthis){
    uint8 ucRet = TRUE;
    if(cthis->currCnt){
        ucRet = FALSE;
    }
    return ucRet;
}

/* Function : Fifo_clearAll(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint8 Fifo_clearAll(hFifo cthis){
    uint8 ucRet = FALSE;
    if(cthis->currCnt){
        cthis->currCnt = 0u;
        cthis->bottom = cthis->top;
        ucRet = TRUE;
    }
    return ucRet;
}

/* Function : hFifo Fifo_init(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   : hFifo - cthis/OOPC_NULL
 * Others   : Fifo class initial function.
 **********************************************/
static hFifo Fifo_init(hFifo cthis, void *listBuffer, uint16 listBuffSize, uint16 fifoObjSize){
    /* Configure functions. */

    /* Configure parameters. */
    cthis->listBuffer = (uint8*)listBuffer;
    cthis->listBuffSize = listBuffSize;
    cthis->fifoObjSize = fifoObjSize;
    cthis->saveObjMaxLen = (cthis->listBuffSize / cthis->fifoObjSize);

    return cthis;
}

/* Function : hFifo Fifo_ctor(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   : hFifo - cthis/OOPC_NULL
 * Others   : Fifo class constructor.
 **********************************************/
CC(Fifo){
    cthis->init = Fifo_init;
    cthis->push = Fifo_push;
    cthis->pop = Fifo_pop;
    cthis->fout = Fifo_fout;
    cthis->del = Fifo_del;
    cthis->isFull = Fifo_isFull;
    cthis->isEmpty = Fifo_isEmpty;
    cthis->clearAll = Fifo_clearAll;

    /* Configure parameters. */
    cthis->listBuffer = NULL;
    cthis->listBuffSize = 0u;
    cthis->fifoObjSize = 0u;

    cthis->saveObjMaxLen = 0u;
    cthis->currCnt = 0u;
    cthis->top = 0u;
    cthis->bottom = 0u;

    return cthis;
}

/* Function : hFifo Fifo_dtor(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : Fifo class destructor.
 **********************************************/
CD(Fifo){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
