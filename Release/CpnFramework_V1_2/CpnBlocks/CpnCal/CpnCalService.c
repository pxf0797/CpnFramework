/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalService.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:39:49
* Description  : CpnCalService类各功能函数定义源文件
* Others       : 
* History      : 201212 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCalService.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* CpnCalService类定义
***********************************************************/
/*名称 : CpnCalService_run(hCpnCalService cthis)
* 输入 : cthis - CpnCalService类指针
* 输出 : 无
* 其他 : CpnCalService类功能函数
***********************************************/
void CpnCalService_run(hCpnCalService cthis){
    //TODO
}

/*名称 : hCpnCalService CpnCalService_init(hCpnCalService cthis)
* 输入 : cthis - CpnCalService类指针
* 输出 : hCpnCalService - cthis/OOPC_NULL
* 其他 : CpnCalService类初始化函数
***********************************************/
hCpnCalService CpnCalService_init(hCpnCalService cthis){
    // 功能函数配置
    //cthis->run = CpnCalService_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnCalService CpnCalService_ctor(hCpnCalService cthis)
* 输入 : cthis - CpnCalService类指针
* 输出 : hCpnCalService - cthis/OOPC_NULL
* 其他 : CpnCalService类构造函数
***********************************************/
CC(CpnCalService){
    cthis->init = CpnCalService_init;
    cthis->run = CpnCalService_run;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnCalService CpnCalService_dtor(hCpnCalService cthis)
* 输入 : cthis - CpnCalService类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnCalService类析构函数
***********************************************/
CD(CpnCalService){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
