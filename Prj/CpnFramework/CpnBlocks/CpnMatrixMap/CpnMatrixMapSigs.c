/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/21 10:36:48
* Description  : CpnMatrixMap����źŶ���Դ�ļ�
* Others       :
* History      : 201121 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
// #include "./CpnMatrixMap.h"
#include "./CpnMatrixMapSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* CpnMatrixMap�ඨ��
***********************************************************/
/*CpnMatrixMap��
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
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
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

/*����
***********************************************/

/*����
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
/*����
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


/*�ӿڴ���
***********************************************/
//void trig_CpnMatrixMap_inf_infFunc(void){}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
// void taskCpnMatrixMap(void){}

/**************************** Copyright(C) pxf ****************************/
