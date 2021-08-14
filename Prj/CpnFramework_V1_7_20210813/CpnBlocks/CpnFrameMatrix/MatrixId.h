/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : MatrixId.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:57:50
 * Description  : MatrixId class and interface declaration file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef MATRIXID_H_
#define MATRIXID_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"
#include "../../CpnBasics/Oopc/Oopc.h"
#include "./CpnFrameMatrix.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define MATRIXID_MACRO_VERSION          0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

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
 * MatrixId class definition.
 **********************************************************/
/* MatrixId class declaration.
 **********************************************/
CL(MatrixId){
    hMatrixId self;
    hMatrixId (*init)(hMatrixId cthis, const FrameMatrix matrixDatas[], uint32 ulMatrixId[], uint16 uwMatrixIdIndex[], uint16 ulMatrixIdNum);

    /* MatrixId class parameters. */
    uint32 *ulMatrixId;
    uint16 *uwMatrixIdIndex;
    uint16 ulMatrixIdNum;

    /* MatrixId class functions. */
    uint16 (*getIdIndex)(hMatrixId cthis, uint32 ulMatrixId); /* id not exist, return CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS */
};

#endif /*MATRIXID_H_*/

/**************************** Copyright(C) pxf ****************************/
