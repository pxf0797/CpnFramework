/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SliceSch.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 09:37:05
 * Description  : SliceSch class functions definition source files.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "SliceSch.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * SliceSch class definition.
 **********************************************************/
/* Function : SliceSch_run(hSliceSch cthis)
 * Input    : cthis - SliceSch class pointer
 * Output   :
 * Others   : SliceSch class function.
 **********************************************/
void SliceSch_run(hSliceSch cthis){
    uint16 i = 0u, j = 0u;
    uint16 actGroupIndex = 0u;
    /*
    Sharding execution
    Periodic scheduling
    Multiple coincidence detection */
    /*
    |||||||||||||||||||||||||||                     slice
            |||||||||||||||||||||||||||
                    |||||||||||||||||||||||||||
    |period |
    */
    /* current execute slice = schPrd - sliceTable[timer]
     *                       = (schPrd - (timer + sliceTable[0]))         **
     *                       = ((schPrd << 1) - (timer + sliceTable[0]))  if (timer + sliceTable[0]) >= schPrd
     * */
    for(i = 0u; i < cthis->slicePrd; i++){
        actGroupIndex = (cthis->timer+cthis->sliceTable[i]);
        if(actGroupIndex >= cthis->schPrd){
            actGroupIndex = ((cthis->schPrd<<1) - actGroupIndex);
        }else{
            actGroupIndex = (cthis->schPrd - actGroupIndex);
        }
        if(actGroupIndex >= cthis->schPrd){
            actGroupIndex = (cthis->schPrd - actGroupIndex);
        }
        /* found group index and execute it. */
        j = 0u;
        while(j < cthis->slices){
            cthis->sliceFunc(j);
            j += cthis->schPrd;
        }
    }
    /* update for next slice. */
    if(++cthis->timer >= cthis->schPrd){
        cthis->timer = 0u;
    }
}

/* Function : hSliceSch SliceSch_init(hSliceSch cthis)
 * Input    : cthis - SliceSch class pointer
 * Output   : hSliceSch - cthis/OOPC_NULL
 * Others   : SliceSch class initial function.
 **********************************************/
hSliceSch SliceSch_init(hSliceSch cthis, uint16 slices, uint16 slicePrd, uint16 schPrd,
        uint16 *sliceTable, slice sliceFunc){
    uint16 i = 0u, index = 0u;
    hSliceSch retRes = cthis;

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
        cthis->sliceFunc = sliceFunc;

        /* Configure parameters. */
        if(!(slices&&slicePrd&&schPrd&&sliceTable)){
            retRes = OOPC_NULL;
            break;
        }
        cthis->slices = slices;
        cthis->slicePrd = slicePrd;
        cthis->schPrd = schPrd;
        cthis->sliceTable = sliceTable;
        /* initial for group[0] scheduler table. */
        for(i = 0u; i < cthis->schPrd; i++){
            if((cthis->slicePrd*i) >= (cthis->schPrd*index)){
                /* find sliceTable[index] correspond slice count. store it then find next. */
                cthis->sliceTable[index] = i;
                if(++index >= cthis->slicePrd){
                    break;
                }
            }
        }
    }while(0);
    return retRes;
}

/* Function : hSliceSch SliceSch_ctor(hSliceSch cthis)
 * Input    : cthis - SliceSch class pointer
 * Output   : hSliceSch - cthis/OOPC_NULL
 * Others   : SliceSch class constructor.
 **********************************************/
CC(SliceSch){
    hSliceSch retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        cthis->init = SliceSch_init;
        cthis->run = SliceSch_run;
        cthis->sliceFunc = OOPC_NULL;

        /* Configure parameters. */
        cthis->slices = 0u;
        cthis->slicePrd = 0u;
        cthis->schPrd = 0u;

    }while(0);
    return retRes;
}

/* Function : hSliceSch SliceSch_dtor(hSliceSch cthis)
 * Input    : cthis - SliceSch class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : SliceSch class destructor.
 **********************************************/
CD(SliceSch){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
