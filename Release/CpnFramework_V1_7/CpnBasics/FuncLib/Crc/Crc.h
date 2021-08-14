/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : Crc.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 17:59:42
 * Description  : Crc class and interface declaration file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef CRC_H_
#define CRC_H_

/* Include head files. */
#include "../../../CpnBasics/StandType/StandType.h"
#include "../../../CpnBasics/Oopc/Oopc.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CRC_MACRO_VERSION               0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef enum{
   crc_8=8,
   crc_16=16,
   crc_32=32
} TE_CRC_TYPE;
typedef enum{
   invert_no, /* bit low is low */
   invert_yes /* bit low is high */
} TE_INVERT_TYPE;

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
 * Crc class definition.
 **********************************************************/
/* Crc class declaration.
 **********************************************/
CL(Crc){
    hCrc self;
    hCrc (*init)(hCrc cthis, TE_CRC_TYPE crcType, uint32 poly, uint32 initial, uint32 final, TE_INVERT_TYPE invertType);

    /* Crc class parameters. */
    TE_CRC_TYPE crcType;
    uint32 highBit;
    uint32 mask;
    uint32 poly;
    uint32 invertPoly;
    uint32 initial;
    uint32 final;
    TE_INVERT_TYPE invertType;
    uint32 crcTable[256];

    /* Crc class functions. */
    uint32 (*invert)(hCrc cthis, uint32 data, uint16 len);
    uint32 (*crcAlgorithm)(hCrc cthis, const uint8* s, uint32 len);
    uint32 (*crc)(hCrc cthis, const uint8* s, uint32 len);
};

#endif /*CRC_H_*/

/**************************** Copyright(C) pxf ****************************/
