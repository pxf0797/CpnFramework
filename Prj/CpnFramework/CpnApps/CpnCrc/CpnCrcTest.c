/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCrcTest.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 19:28:48
* Description  :
* Others       :
* History      : 201202 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCrcTest.h"

#define  CRC_TYPE_NUM_T  6
Crc clCrcT[CRC_TYPE_NUM_T];

#define TEST_BYTE_NUM          8U
#define TEST_BYTE_NUM2         8U
uint8 ucCrcData[TEST_BYTE_NUM] = {0x12,0x23,0x34,0x45,0x56,0x78,0x89,0x90};
uint8 ucCrcData2[TEST_BYTE_NUM2] = {0x48,0xc4,0x2c,0xa2,0x6a,0x1e,0x91,0x09};

uint32 crcRestult[4][CRC_TYPE_NUM_T];

/*名称 : CpnCrcTest()
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
void CpnCrcTest(void){
    hCrc opRes = OOPC_NULL;
    CN(Crc, &clCrcT[0], crc_8, 0x07U, 0x00U, 0x00U, invert_yes);
    CN(Crc, &clCrcT[1], crc_8, 0x07U, 0x00U, 0x00U, invert_no);
    CN(Crc, &clCrcT[2], crc_16, 0x1021U, 0x0000U, 0x0000U, invert_yes);
    CN(Crc, &clCrcT[3], crc_16, 0x1021U, 0x0000U, 0x0000U, invert_no);
    CN(Crc, &clCrcT[4], crc_32, 0x04C11DB7UL, 0x0000UL, 0x0000UL, invert_yes);
    CN(Crc, &clCrcT[5], crc_32, 0x04C11DB7UL, 0x0000UL, 0x0000UL, invert_no);
    for(uint16 i = 0U; i < CRC_TYPE_NUM_T; i++){
        opRes = (OPRS(clCrcT[i]));
        if(opRes == OOPC_NULL){
            break;
        }
    }
    if(opRes != OOPC_NULL){
        ;
    }

    for(uint16 i = 0; i < CRC_TYPE_NUM_T; i++){
        crcRestult[0][i] = clCrcT[i].crcAlgorithm(clCrcT[i].self,ucCrcData,TEST_BYTE_NUM);
        crcRestult[1][i] = clCrcT[i].crc(clCrcT[i].self,ucCrcData,TEST_BYTE_NUM);
        crcRestult[2][i] = clCrcT[i].crcAlgorithm(clCrcT[i].self,ucCrcData2,TEST_BYTE_NUM2);
        crcRestult[3][i] = clCrcT[i].crc(clCrcT[i].self,ucCrcData2,TEST_BYTE_NUM2);
    }
}

/**************************** Copyright(C) pxf ****************************/
