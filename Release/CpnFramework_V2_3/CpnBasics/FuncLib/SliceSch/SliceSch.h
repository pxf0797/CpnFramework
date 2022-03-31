/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SliceSch.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/09/30 09:37:05
 * Description  : SliceSch class and interface declaration file.
 * Others       :
 * History      : 20210930 pxf Initially established.
 **************************************************************************/

#ifndef SLICESCH_H_
#define SLICESCH_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define SLICESCH_MACRO_VERSION                  0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef void (*slice)(uint16 index);
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
 * SliceSch class definition.
 **********************************************************/
/* SliceSch class declaration.
 **********************************************/
CL(SliceSch){
    hSliceSch self;
    hSliceSch (*init)(hSliceSch cthis, uint16 slices, uint16 slicePrd, uint16 schPrd,
            uint16 *sliceTable, slice sliceFunc);

    /* SliceSch class parameters. */
    uint16 slices;       /* total slices for execute. */
    /* period execute task time is slicePrd*schPrd.
     * so, task slice execute has a index table, it is counts is slicePrd, and count range is [0,schPrd).
     * only need to do is generate group[0] scheduler table,
     * other slices shift one index.
     */
    uint16 timer;
    uint16 slicePrd;     /* current slice execute period. */
    uint16 schPrd;       /* task minimum execute period. */
    /* correspond slice scheduler table.
     * sliceTable[x] - timer = sliceTable[0],
     * so, sliceTable[x] = (timer + sliceTable[0])           **
     *                   = (timer + sliceTable[0] - schPrd)  if (timer + sliceTable[0]) >= schPrd
     *         |    Timer | sliceTable
     * ____________________________________________
     *         |        0 | sliceTable[0]
     *         |        1 | 1+sliceTable[0]
     *         |      ... | ...
     *         | schPrd-1 | schPrd-1+sliceTable[0]
     * */
    uint16 *sliceTable;  /* table used to specify group[0] execute time. it's length is slicePrd. */
    slice sliceFunc;     /* slice function act correspond group. */

    /* SliceSch class functions. */
    void (*run)(hSliceSch cthis);
};

#endif /*SLICESCH_H_*/

/**************************** Copyright(C) pxf ****************************/
