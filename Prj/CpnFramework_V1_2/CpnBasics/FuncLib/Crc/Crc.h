/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Crc.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/24 08:58:28
* Description  : Crc类及接口声明头文件
* Others       :
* History      : 201124 pxf 初次建立
***************************************************************************/

#ifndef CRC_H_
#define CRC_H_

/*头文件包含*/
#include "../../../cpnBasics/standType/standType.h"
#include "../../../cpnBasics/oopc/oopc.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CRC_MACRO_VERSION               0xC01D00    /* C代表V，D代表.，当前版本V1.00 */


/***********************************************************
* 数据类型定义
***********************************************************/
/*数据声明
***********************************************/
//typedef struct{
//    uint16 id;
//    uint16 code;
//} tErrCode;
typedef enum{
   crc_8=8,
   crc_16=16,
   crc_32=32
} TE_CRC_TYPE;
typedef enum{
   invert_no, /* bit low is low */
   invert_yes /* bit low is high */
} TE_INVERT_TYPE;
/*数据引用
***********************************************/
//TODO

/***********************************************************
* 接口定义
***********************************************************/
/*接口声明
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* Crc类定义
***********************************************************/
/*Crc类声明
***********************************************/
CL(Crc){
    hCrc self;
    hCrc (*init)(hCrc cthis, TE_CRC_TYPE crcType, uint32 poly, uint32 initial, uint32 final, TE_INVERT_TYPE invertType);

    // Crc类参数
    TE_CRC_TYPE crcType;
    uint32 highBit;
    uint32 mask;
    uint32 poly;
    uint32 invertPoly;
    uint32 initial;
    uint32 final;
    TE_INVERT_TYPE invertType;
    uint32 crcTable[256];

    // Crc类功能函数
    uint32 (*invert)(hCrc cthis, uint32 data, uint16 len);
    uint32 (*crcAlgorithm)(hCrc cthis, const uint8* s, uint32 len);
    uint32 (*crc)(hCrc cthis, const uint8* s, uint32 len);
    //TODO
};

#endif /*CRC_H_*/

/**************************** Copyright(C) pxf ****************************/
