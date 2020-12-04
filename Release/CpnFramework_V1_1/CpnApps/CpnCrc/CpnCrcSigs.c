/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCrcSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/26 15:14:48
* Description  : CpnCrc����źŶ���Դ�ļ�
* Others       :
* History      : 201126 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
//#include "./CpnCrc.h"
#include "./CpnCrcSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
// #include "./CpnCrcTest.h"

/***********************************************************
* CpnCrc�ඨ��
***********************************************************/
/*CpnCrc��
***********************************************/
// CpnCrc clCpnCrc;
#define CRC_TYPE_NUM    3
static Crc clCrc[CRC_TYPE_NUM];


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnCrc_init(void){
    hCrc opRes = OOPC_NULL;
    CN(Crc, &clCrc[0], crc_8, 0x07U, 0x00U, 0x00U, invert_yes);
    CN(Crc, &clCrc[1], crc_16, 0x1021U, 0x0000U, 0x0000U, invert_yes);
    CN(Crc, &clCrc[2], crc_32, 0x04C11DB7UL, 0x0000UL, 0x0000UL, invert_yes);
    for(uint16 i = 0U; i < CRC_TYPE_NUM; i++){
        opRes = (OPRS(clCrc[i]));
        if(opRes == OOPC_NULL){
            break;
        }
    }
    if(opRes != OOPC_NULL){
        ;
    }
    // CpnCrcTest();

    // CNNP(CpnCrc,&clCpnCrc);
    // if(OPRS(clCpnCrc) != NULL){
    //     addTaskParam taskParam;
    //     taskParam.level = level1;
    //     taskParam.t = taskCpnCrc;
    //     taskParam.prdTick = 11*MS_T;
    //     taskParam.startTick = 5*MS_T;
    //     clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCrc_addTask, (uint8*)&taskParam);
    // }
}

/*����
***********************************************/
void serv_CpnCrc_getCrc8(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[0].crc(clCrc[0].self,crcData->s,crcData->len);
}
/*����
***********************************************/
void serv_CpnCrc_getCrc16(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[1].crc(clCrc[1].self,crcData->s,crcData->len);
}
/*����
***********************************************/
void serv_CpnCrc_getCrc32(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[2].crc(clCrc[2].self,crcData->s,crcData->len);
}

/*�ӿڴ���
***********************************************/
//void trig_CpnCrc_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnCrc(void){}

/**************************** Copyright(C) pxf ****************************/
