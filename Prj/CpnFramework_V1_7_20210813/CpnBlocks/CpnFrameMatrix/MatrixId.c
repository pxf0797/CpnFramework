/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : MatrixId.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:57:50
 * Description  : MatrixId class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./MatrixId.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * MatrixId class definition.
 **********************************************************/
/* Function : MatrixId_getIdIndex(hMatrixId cthis)
 * Input    : cthis - MatrixId class pointer
 * Output   :
 * Others   : MatrixId class function.
 **********************************************/
uint16 MatrixId_getIdIndex(hMatrixId cthis, uint32 ulMatrixId){
    /* bin search id index */
    uint16 low = 0, mid = 0, high = 0;
    uint16 idIndex = cthis->ulMatrixIdNum;

    high = cthis->ulMatrixIdNum-1;
    while(low <= high){
        mid = ((low+high)>>1U);    /* Odd number, no matter even or odd, just have a value. */
        if(ulMatrixId < cthis->ulMatrixId[mid]){
            if(mid == 0){
                break;
            }
            high = (mid-1U);       /* Is mid-1, because mid has been compared. */
        }else if(ulMatrixId > cthis->ulMatrixId[mid]){
            low = (mid+1U);
        }else{
            idIndex = cthis->uwMatrixIdIndex[mid];
            break;
        }
    }

    return idIndex;
}

/* Function : hMatrixId MatrixId_init(hMatrixId cthis)
 * Input    : cthis - MatrixId class pointer
 * Output   : hMatrixId - cthis/OOPC_NULL
 * Others   : MatrixId class initial function.
 **********************************************/
hMatrixId MatrixId_init(hMatrixId cthis, const FrameMatrix matrixDatas[], uint32 ulMatrixId[], uint16 uwMatrixIdIndex[], uint16 ulMatrixIdNum){
    uint16 i = 0;
    uint16 j = 0;
    /* Configure functions. */
    //cthis->getIdIndex = MatrixId_getIdIndex;
    /* TODO */

    /* Configure parameters. */
    cthis->ulMatrixId = ulMatrixId;
    cthis->uwMatrixIdIndex = uwMatrixIdIndex;
    cthis->ulMatrixIdNum = ulMatrixIdNum;

    /* insert sort ids */
    cthis->ulMatrixId[0] = matrixDatas[0].id;
    cthis->uwMatrixIdIndex[0] = 0U;
    for(i = 1U; i < cthis->ulMatrixIdNum; i++){
        j = i;
        while(j>0U){
            if(matrixDatas[i].id < cthis->ulMatrixId[j-1U]){
                cthis->ulMatrixId[j] = cthis->ulMatrixId[j-1U];
                cthis->uwMatrixIdIndex[j] = cthis->uwMatrixIdIndex[j-1U];
                cthis->ulMatrixId[j-1U] = matrixDatas[i].id;
                cthis->uwMatrixIdIndex[j-1U] = i;
            }else{
                cthis->ulMatrixId[j] = matrixDatas[i].id;
                cthis->uwMatrixIdIndex[j] = i;
                break;
            }
            j--;
        }
    }

    return cthis;
}

/* Function : hMatrixId MatrixId_ctor(hMatrixId cthis)
 * Input    : cthis - MatrixId class pointer
 * Output   : hMatrixId - cthis/OOPC_NULL
 * Others   : MatrixId class constructor.
 **********************************************/
CC(MatrixId){
    cthis->init = MatrixId_init;
    cthis->getIdIndex = MatrixId_getIdIndex;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hMatrixId MatrixId_dtor(hMatrixId cthis)
 * Input    : cthis - MatrixId class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : MatrixId class destructor.
 **********************************************/
CD(MatrixId){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
