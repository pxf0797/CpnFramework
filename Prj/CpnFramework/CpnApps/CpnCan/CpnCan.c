/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCan.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 16:09:24
* Description  : CpnCan类各功能函数定义源文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCan.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
Fifo clFifoCpnCan;
static tDataSig dataBUff[CPNCAN_FIFO_BUFF_LENGTH];

/***********************************************************
* CpnCan类定义
***********************************************************/
/*名称 : CpnCan_run(hCpnCan cthis)
* 输入 : cthis - CpnCan类指针
* 输出 : 无
* 其他 : CpnCan类功能函数
***********************************************/
void CpnCan_run(hCpnCan cthis){
    cthis->send(cthis);
}

/*名称 : CpnCan_send(hCpnCan cthis)
* 输入 : cthis - CpnCan类指针
* 输出 : 无
* 其他 : CpnCan类功能函数
***********************************************/
void CpnCan_send(hCpnCan cthis){
    tDataSig sendData;
    if(cthis->clFifoSend->fout(cthis->clFifoSend,&sendData)){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCan_sendSig, (uint8*)&sendData);
    }
}

/*名称 : CpnCan_receive(hCpnCan cthis)
* 输入 : cthis - CpnCan类指针
* 输出 : 无
* 其他 : CpnCan类功能函数
***********************************************/
void CpnCan_receive(hCpnCan cthis){
    //TODO
}

/*名称 : hCpnCan CpnCan_init(hCpnCan cthis)
* 输入 : cthis - CpnCan类指针
* 输出 : hCpnCan - cthis/OOPC_NULL
* 其他 : CpnCan类初始化函数
***********************************************/
hCpnCan CpnCan_init(hCpnCan cthis, hFifo clFifoSend){
    // 功能函数配置
    //cthis->run = CpnCan_run;
    //TODO

    // 参数配置
    cthis->clFifoSend = clFifoSend;

    return cthis;
}

/*名称 : hCpnCan CpnCan_ctor(hCpnCan cthis)
* 输入 : cthis - CpnCan类指针
* 输出 : hCpnCan - cthis/OOPC_NULL
* 其他 : CpnCan类构造函数
***********************************************/
CC(CpnCan){
    cthis->init = CpnCan_init;
    cthis->run = CpnCan_run;
    cthis->send = CpnCan_send;
    cthis->receive = CpnCan_receive;
    //TODO

    // 参数配置
    //TODO

    CN(Fifo, &clFifoCpnCan, dataBUff, sizeof(dataBUff), sizeof(tDataSig));
    if(OPRS(clFifoCpnCan) == OOPC_NULL){
        return OOPC_NULL;
    }

    return cthis;
}

/*名称 : hCpnCan CpnCan_dtor(hCpnCan cthis)
* 输入 : cthis - CpnCan类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnCan类析构函数
***********************************************/
CD(CpnCan){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
