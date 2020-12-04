/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCrcSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/26 15:14:48
* Description  : CpnCrc组件信号定义源文件
* Others       :
* History      : 201126 pxf 初次建立
***************************************************************************/

/*头文件包含*/
//#include "./CpnCrc.h"
#include "./CpnCrcSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
// #include "./CpnCrcTest.h"

/***********************************************************
* CpnCrc类定义
***********************************************************/
/*CpnCrc类
***********************************************/
// CpnCrc clCpnCrc;
#define CRC_TYPE_NUM    3
static Crc clCrc[CRC_TYPE_NUM];


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
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

/*服务
***********************************************/
void serv_CpnCrc_getCrc8(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[0].crc(clCrc[0].self,crcData->s,crcData->len);
}
/*服务
***********************************************/
void serv_CpnCrc_getCrc16(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[1].crc(clCrc[1].self,crcData->s,crcData->len);
}
/*服务
***********************************************/
void serv_CpnCrc_getCrc32(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[2].crc(clCrc[2].self,crcData->s,crcData->len);
}

/*接口触发
***********************************************/
//void trig_CpnCrc_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
void taskCpnCrc(void){}

/**************************** Copyright(C) pxf ****************************/
