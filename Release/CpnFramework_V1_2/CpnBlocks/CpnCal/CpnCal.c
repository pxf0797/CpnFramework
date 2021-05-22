/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCal.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:06:36
* Description  : CpnCal类各功能函数定义源文件
* Others       : 
* History      : 201212 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCal.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* CpnCal类定义
***********************************************************/
/*名称 : CpnCal_run(hCpnCal cthis)
* 输入 : cthis - CpnCal类指针
* 输出 : 无
* 其他 : CpnCal类功能函数
***********************************************/
void CpnCal_run(hCpnCal cthis){
    //TODO
}

/*名称 : hCpnCal CpnCal_init(hCpnCal cthis)
* 输入 : cthis - CpnCal类指针
* 输出 : hCpnCal - cthis/OOPC_NULL
* 其他 : CpnCal类初始化函数
***********************************************/
hCpnCal CpnCal_init(hCpnCal cthis){
    // 功能函数配置
    //cthis->run = CpnCal_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnCal CpnCal_ctor(hCpnCal cthis)
* 输入 : cthis - CpnCal类指针
* 输出 : hCpnCal - cthis/OOPC_NULL
* 其他 : CpnCal类构造函数
***********************************************/
CC(CpnCal){
    cthis->init = CpnCal_init;
    cthis->run = CpnCal_run;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnCal CpnCal_dtor(hCpnCal cthis)
* 输入 : cthis - CpnCal类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnCal类析构函数
***********************************************/
CD(CpnCal){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
