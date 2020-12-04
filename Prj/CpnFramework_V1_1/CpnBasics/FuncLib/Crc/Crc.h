/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Crc.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/24 08:58:28
* Description  : Crc�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 201124 pxf ���ν���
***************************************************************************/

#ifndef CRC_H_
#define CRC_H_

/*ͷ�ļ�����*/
#include "../../../cpnBasics/standType/standType.h"
#include "../../../cpnBasics/oopc/oopc.h"

/***********************************************************
* �汾����
***********************************************************/
#define CRC_MACRO_VERSION               0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */


/***********************************************************
* �������Ͷ���
***********************************************************/
/*��������
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
/*��������
***********************************************/
//TODO

/***********************************************************
* �ӿڶ���
***********************************************************/
/*�ӿ�����
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* Crc�ඨ��
***********************************************************/
/*Crc������
***********************************************/
CL(Crc){
    hCrc self;
    hCrc (*init)(hCrc cthis, TE_CRC_TYPE crcType, uint32 poly, uint32 initial, uint32 final, TE_INVERT_TYPE invertType);

    // Crc�����
    TE_CRC_TYPE crcType;
    uint32 highBit;
    uint32 mask;
    uint32 poly;
    uint32 invertPoly;
    uint32 initial;
    uint32 final;
    TE_INVERT_TYPE invertType;
    uint32 crcTable[256];

    // Crc�๦�ܺ���
    uint32 (*invert)(hCrc cthis, uint32 data, uint16 len);
    uint32 (*crcAlgorithm)(hCrc cthis, const uint8* s, uint32 len);
    uint32 (*crc)(hCrc cthis, const uint8* s, uint32 len);
    //TODO
};

#endif /*CRC_H_*/

/**************************** Copyright(C) pxf ****************************/
