/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : Fifo.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 17:33:45
 * Description  : Fifo class and interface declaration file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define FIFO_MACRO_VERSION              0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
/* typedef struct{
    uint16 id;
    uint16 code;
} tErrCode;
 */
/* TODO */
/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
//INF(get){
//  uint16(*get)(void);
//};
/* TODO */

/***********************************************************
 * Fifo class definition.
 **********************************************************/
/* Fifo class declaration.
 **********************************************/
CL(Fifo){
    hFifo self;
    hFifo (*init)(hFifo cthis, void *listBuffer, uint16 listBuffSize, uint16 fifoObjSize);

    /* Fifo class parameters. */
    uint8 *listBuffer;                                         /* Cache queue start address. */
    uint16 listBuffSize;                                       /* Cache queue total size. */
    uint16 fifoObjSize;                                        /* Cache queue object size. */

    uint16 saveObjMaxLen;                                      /* Cache queue maximum counters. */
    uint16 currLen;                                            /* Cache queue cached counters. */
    uint16 top;                                                /* Cache queue new cache position. */
    uint16 bottom;                                             /* Cache queue first cache position. */

    /* Fifo class functions. */
    uint16 (*push)(hFifo cthis, void *data);                       /* Object cache in cache queue. */
    uint16 (*pop)(hFifo cthis, void *data);                        /* Last object out cache queue. */
    uint16 (*fout)(hFifo cthis, void *data);                       /* First object out cache queue. */
    uint16 (*del)(hFifo cthis, void *data, void *fifoObjTempBuff); /* Delete a certain data in the queue; in order to delete the data,
                                                                      an object temporary buffer area FifoObjTempBuff needs to be provided. */
    uint16 (*isFull)(hFifo cthis);                                 /* Cache queue is full. TRUE/FALSE */
    uint16 (*isEmpty)(hFifo cthis);                                /* Cache queue is empty. TRUE/FALSE */
    uint16 (*clearAll)(hFifo cthis);                               /* Clear all cache queue objects. TRUE/FALSE */
};

#endif /*FIFO_H_*/

/**************************** Copyright(C) pxf ****************************/
