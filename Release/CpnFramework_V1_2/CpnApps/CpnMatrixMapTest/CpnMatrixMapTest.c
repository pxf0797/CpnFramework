/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapTest.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/02 20:32:16
* Description  : CpnMatrixMapTest类各功能函数定义源文件
* Others       :
* History      : 201202 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnMatrixMapTest.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO
#define DATA_SET_ARRAY_NUM    7U
#define DATA_GET_ARRAY_NUM    8U
uint32 ulDataSet[DATA_SET_ARRAY_NUM];
uint32 ulDataSetGet[DATA_SET_ARRAY_NUM];
uint32 ulDataGet[DATA_GET_ARRAY_NUM];
uint16 uwTestCase = 1U;


/***********************************************************
* CpnMatrixMapTest类定义
***********************************************************/
/*名称 : CpnMatrixMapTest_run(hCpnMatrixMapTest cthis)
* 输入 : cthis - CpnMatrixMapTest类指针
* 输出 : 无
* 其他 : CpnMatrixMapTest类功能函数
***********************************************/
void CpnMatrixMapTest_run(hCpnMatrixMapTest cthis){
    static tick waitDelay = 1*S_T;
    static uint8 ucUpdateData = 0;
    uint32 ulTempData = 0;

    if(uwTestCase == 0U){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_delay, (uint8*)&waitDelay);
        if(IS_TIMEOUT(waitDelay)){
            waitDelay = 1*S_T;
            ucUpdateData++;
            ulTempData = ucUpdateData;
            ulTempData = ((SWAP32_BIT4(ulTempData)<<8U)|SWAP32_BIT2(SWAP32_BIT4(ulTempData)));
            for(uint16 i = 0; i < DATA_SET_ARRAY_NUM; i++){
                ulDataSet[i] = ulTempData;
            }
        }
    }else if(uwTestCase == 1U){
        ulDataSet[0] = ulDataGet[4];
        ulDataSet[1]++;// = ulDataGet[5];
        ulDataSet[2] = ulDataGet[0];
        ulDataSet[3] = ulDataGet[1];
        ulDataSet[4]++;// = ulDataGet[5];
        ulDataSet[5] = ulDataGet[5];
        ulDataSet[6] = ulDataGet[1];
    }

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataA, (uint8*)&ulDataSet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataB, (uint8*)&ulDataSet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataC, (uint8*)&ulDataSet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataD, (uint8*)&ulDataSet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataE, (uint8*)&ulDataSet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataF, (uint8*)&ulDataSet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataG, (uint8*)&ulDataSet[6]);

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData1, (uint8*)&ulDataGet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData2, (uint8*)&ulDataGet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData3, (uint8*)&ulDataGet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData4, (uint8*)&ulDataGet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData5, (uint8*)&ulDataGet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData6, (uint8*)&ulDataGet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData7, (uint8*)&ulDataGet[6]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData8, (uint8*)&ulDataGet[7]);

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataA, (uint8*)&ulDataSetGet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataB, (uint8*)&ulDataSetGet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataC, (uint8*)&ulDataSetGet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataD, (uint8*)&ulDataSetGet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataE, (uint8*)&ulDataSetGet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataF, (uint8*)&ulDataSetGet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataG, (uint8*)&ulDataSetGet[6]);
}

/*名称 : hCpnMatrixMapTest CpnMatrixMapTest_init(hCpnMatrixMapTest cthis)
* 输入 : cthis - CpnMatrixMapTest类指针
* 输出 : hCpnMatrixMapTest - cthis/OOPC_NULL
* 其他 : CpnMatrixMapTest类初始化函数
***********************************************/
hCpnMatrixMapTest CpnMatrixMapTest_init(hCpnMatrixMapTest cthis){
    // 功能函数配置
    //cthis->run = CpnMatrixMapTest_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnMatrixMapTest CpnMatrixMapTest_ctor(hCpnMatrixMapTest cthis)
* 输入 : cthis - CpnMatrixMapTest类指针
* 输出 : hCpnMatrixMapTest - cthis/OOPC_NULL
* 其他 : CpnMatrixMapTest类构造函数
***********************************************/
CC(CpnMatrixMapTest){
    cthis->init = CpnMatrixMapTest_init;
    cthis->run = CpnMatrixMapTest_run;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnMatrixMapTest CpnMatrixMapTest_dtor(hCpnMatrixMapTest cthis)
* 输入 : cthis - CpnMatrixMapTest类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnMatrixMapTest类析构函数
***********************************************/
CD(CpnMatrixMapTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
