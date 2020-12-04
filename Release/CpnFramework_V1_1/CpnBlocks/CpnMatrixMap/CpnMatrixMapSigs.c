/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/21 10:36:48
* Description  : CpnMatrixMap组件信号定义源文件
* Others       :
* History      : 201121 pxf 初次建立
***************************************************************************/

/*头文件包含*/
// #include "./CpnMatrixMap.h"
#include "./CpnMatrixMapSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnMatrixMap类定义
***********************************************************/
/*CpnMatrixMap类
***********************************************/
// CpnMatrixMap clCpnMatrixMap;

const TS_FRAME_MAP frameMapDatasSet[set_sig_num_max] = {
    FRAME_SET_SIG_EXPANTION(FRAME_SET_SIG_LIST)
};
const TS_FRAME_MAP frameMapDatasGet[get_sig_num_max] = {
    FRAME_GET_SIG_EXPANTION(FRAME_GET_SIG_LIST)
    FRAME_GET_SIG_EXPANTION(FRAME_SET_SIG_LIST)
};

/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnMatrixMap_init(void){
    // CNNP(CpnMatrixMap,&clCpnMatrixMap);
    // if(OPRS(clCpnMatrixMap) != NULL){
    //     addTaskParam taskParam;
    //     taskParam.level = level1;
    //     taskParam.t = taskCpnMatrixMap;
    //     taskParam.prdTick = 11*MS_T;
    //     taskParam.startTick = 5*MS_T;
    //     clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMap_addTask, (uint8*)&taskParam);
    // }
}

/*服务
***********************************************/

/*服务
***********************************************/
 FRAME_SET_SIG_SERV_DEF_EXPANTION(FRAME_SET_SIG_LIST)
/*void serv_CpnMatrixMap_set_ulDataA(void *buff){
    TS_FRAME_SET setData;
    setData.id = frameMapDatasSet[set_sig_ulDataA].id;
    setData.bit_start = frameMapDatasSet[set_sig_ulDataA].bit_start;
    setData.bit_len = frameMapDatasSet[set_sig_ulDataA].bit_len;
    setData.value = *((uint32*)buff);
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasSet[set_sig_ulDataA].sig_operation_name, (uint8*)&setData);
}*/
/*服务
***********************************************/
 FRAME_GET_SIG_SERV_DEF_EXPANTION(FRAME_GET_SIG_LIST)
 FRAME_GET_SIG_SERV_DEF_EXPANTION(FRAME_SET_SIG_LIST)
/*void serv_CpnMatrixMap_get_ulData1(void *buff){
    TS_FRAME_GET getData;
    getData.id = frameMapDatasGet[get_sig_ulData1].id;
    getData.bit_start = frameMapDatasGet[get_sig_ulData1].bit_start;
    getData.bit_len = frameMapDatasGet[get_sig_ulData1].bit_len;
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasGet[get_sig_ulData1].sig_operation_name, (uint8*)&getData);
    *((uint32*)buff) = *(getData.value);
}*/


/*接口触发
***********************************************/
//void trig_CpnMatrixMap_inf_infFunc(void){}



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务定义
***********************************************/
// void taskCpnMatrixMap(void){}

/**************************** Copyright(C) pxf ****************************/
