/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErr.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  : CpnErr类各功能函数定义源文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnErr.h"
//#include "../RteSigs/RteSigs.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
Fifo clFifoCpnErr;
static uint32 ulErrCodeBuff[CPNERR_FIFO_BUFF_LENGTH];

/***********************************************************
* CpnErr类定义
***********************************************************/
/*名称 : CpnErr_run(hCpnErr cthis)
* 输入 : cthis - CpnErr类指针
* 输出 : 无
* 其他 : CpnErr类功能函数
***********************************************/
void CpnErr_run(hCpnErr cthis){
    tErrCode code;
    if(cthis->clFifo->fout(cthis->clFifo, &code)){
        cthis->uwTotalErrNum++;
    }
}

/*名称 : CpnErr_setErr(hCpnErr cthis)
* 输入 : cthis - CpnErr类指针
* 输出 : 无
* 其他 : CpnErr类功能函数
***********************************************/
uint16 CpnErr_setErr(hCpnErr cthis, uint32 errCode){
    return cthis->clFifo->push(cthis->clFifo, &errCode);
}

/*名称 : hCpnErr CpnErr_init(hCpnErr cthis)
* 输入 : cthis - CpnErr类指针
* 输出 : hCpnErr - cthis/OOPC_NULL
* 其他 : CpnErr类初始化函数
***********************************************/
hCpnErr CpnErr_init(hCpnErr cthis, hFifo clFifo){
    // 功能函数配置
    //cthis->run = CpnErr_run;
    //TODO

    // 参数配置
    cthis->uwTotalErrNum = 0;
    cthis->clFifo = clFifo;

    return cthis;
}

/*名称 : hCpnErr CpnErr_ctor(hCpnErr cthis)
* 输入 : cthis - CpnErr类指针
* 输出 : hCpnErr - cthis/OOPC_NULL
* 其他 : CpnErr类构造函数
***********************************************/
CC(CpnErr){
    cthis->init = CpnErr_init;
    cthis->run = CpnErr_run;
    cthis->setErr = CpnErr_setErr;
    //TODO

    // 参数配置
    //TODO

    CN(Fifo, &clFifoCpnErr, ulErrCodeBuff, sizeof(ulErrCodeBuff), sizeof(uint32));
    if(OPRS(clFifoCpnErr) == OOPC_NULL){
        return OOPC_NULL;
    }

    return cthis;
}

/*名称 : hCpnErr CpnErr_dtor(hCpnErr cthis)
* 输入 : cthis - CpnErr类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnErr类析构函数
***********************************************/
CD(CpnErr){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
