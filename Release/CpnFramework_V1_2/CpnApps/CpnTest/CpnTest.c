/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTest.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/23 17:26:23
* Description  : CpnTest类各功能函数定义源文件
* Others       : 
* History      : 200723 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnTest.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* CpnTest类定义
***********************************************************/
/*名称 : CpnTest_run(hCpnTest cthis)
* 输入 : cthis - CpnTest类指针
* 输出 : 无
* 其他 : CpnTest类功能函数
***********************************************/
void CpnTest_run(hCpnTest cthis){
    //TODO
}

/*名称 : hCpnTest CpnTest_init(hCpnTest cthis)
* 输入 : cthis - CpnTest类指针
* 输出 : hCpnTest - cthis/OOPC_NULL
* 其他 : CpnTest类初始化函数
***********************************************/
hCpnTest CpnTest_init(hCpnTest cthis){
    // 功能函数配置
    //cthis->run = CpnTest_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnTest CpnTest_ctor(hCpnTest cthis)
* 输入 : cthis - CpnTest类指针
* 输出 : hCpnTest - cthis/OOPC_NULL
* 其他 : CpnTest类构造函数
***********************************************/
CC(CpnTest){
    cthis->init = CpnTest_init;
    cthis->run = CpnTest_run;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnTest CpnTest_dtor(hCpnTest cthis)
* 输入 : cthis - CpnTest类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnTest类析构函数
***********************************************/
CD(CpnTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
