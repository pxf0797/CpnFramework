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
static uint16 Fifo_push(hFifo cthis, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = NULL;
    uint16 i = 0;

    if(cthis->currLen < cthis->saveObjMaxLen){
        /* Calculate store position, and store it. */
        desPtr = (cthis->listBuffer + (cthis->top * cthis->fifoObjSize));
        for (i = 0; i < cthis->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }
        /* Update flags. */
        cthis->currLen++;
        cthis->top++;
        if (cthis->top >= cthis->saveObjMaxLen){
            cthis->top = 0;
        }
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/* Function : Fifo_pop(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint16 Fifo_pop(hFifo cthis, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0;

    if (cthis->currLen > 0){
        /* Update flags. */
        cthis->currLen--;
        cthis->top--;
        if (cthis->top <= 0){
            cthis->top = (cthis->saveObjMaxLen - 1);
        }
        /* Calculate store position, and read out. */
        srcPtr = (cthis->listBuffer + (cthis->top * cthis->fifoObjSize));
        for (i = 0; i < cthis->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/* Function : Fifo_fout(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint16 Fifo_fout(hFifo cthis, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0;

    if (cthis->currLen > 0){
        /* Calculate store position, and read out. */
        srcPtr = (cthis->listBuffer + (cthis->bottom * cthis->fifoObjSize));
        for (i = 0; i < cthis->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }
        /* Update flags. */
        cthis->currLen--;
        cthis->bottom++;
        if (cthis->bottom >= cthis->saveObjMaxLen){
            cthis->bottom = 0;
        }
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/* Function : Fifo_del(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint16 Fifo_del(hFifo cthis, void *data, void *fifoObjTempBuff){
    uint16 rtv = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = (uint8 *)fifoObjTempBuff;
    uint16 i = 0;
    uint16 j = cthis->currLen;
    uint16 lastMaxLen = cthis->currLen;

    if (cthis->currLen > 0){
        for (j = cthis->currLen; j > 0u; j--){
            if (TRUE == cthis->fout(cthis, fifoObjTempBuff)){
                /* Determine whether the data is the same, delete the same,
                 * and save it back to the queue if the difference is different. */
                srcPtr = (uint8 *)data;
                desPtr = (uint8 *)fifoObjTempBuff;
                for (i = 0; i < cthis->fifoObjSize; i++){
                    if (*desPtr++ != *srcPtr++){
                        break;
                    }
                }
                if (i < cthis->saveObjMaxLen){
                    /* Store non-lookup data back to the queue. */
                    if (TRUE != cthis->push(cthis, fifoObjTempBuff)){
                        rtv = FALSE;
                    }
                }
            }else{
                rtv = FALSE;
            }
            if (FALSE == rtv){
                break;
            }
        }
        /* Determine whether to find and delete data, and return the operation result. */
        if ((TRUE == rtv) && (cthis->currLen < lastMaxLen)){
            rtv = TRUE;
        }else{
            rtv = FALSE;
        }
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/* Function : Fifo_isFull(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint16 Fifo_isFull(hFifo cthis){
    uint16 retType = FALSE;

    if(cthis->currLen == cthis->saveObjMaxLen){
        retType = TRUE;
    }
    return retType;
}

/* Function : Fifo_isEmpty(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint16 Fifo_isEmpty(hFifo cthis){
    uint16 retType = TRUE;

    if(cthis->currLen){
        retType = FALSE;
    }
    return retType;
}

/* Function : Fifo_clearAll(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   :
 * Others   : Fifo class function.
 **********************************************/
static uint16 Fifo_clearAll(hFifo cthis){
    uint16 retType = FALSE;

    if(cthis->currLen){
        cthis->currLen = 0;
        cthis->bottom = cthis->top;
        retType = TRUE;
    }
    return retType;
}

/* Function : hFifo Fifo_init(hFifo cthis)
 * Input    : cthis - Fifo class pointer
 * Output   : hFifo - cthis/OOPC_NULL
 * Others   : Fifo class initial function.
 **********************************************/
static hFifo Fifo_init(hFifo cthis, void *listBuffer, uint16 listBuffSize, uint16 fifoObjSize){
    /* Configure functions. */
    //cthis->push = Fifo_push;
    /* TODO */

    /* Configure parameters. */
    cthis->listBuffer = (uint8 *)listBuffer;
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
    cthis->listBuffSize = 0;
    cthis->fifoObjSize = 0;

    cthis->saveObjMaxLen = 0;
    cthis->currLen = 0;
    cthis->top = 0;
    cthis->bottom = 0;

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
