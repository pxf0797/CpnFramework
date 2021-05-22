/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalTimer.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:45:32
* Description  : CpnCalTimer类各功能函数定义源文件
* Others       : 
* History      : 201212 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCalTimer.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* CpnCalTimer类定义
***********************************************************/
/*名称 : CpnCalTimer_run(hCpnCalTimer cthis)
* 输入 : cthis - CpnCalTimer类指针
* 输出 : 无
* 其他 : CpnCalTimer类功能函数
***********************************************/
void CpnCalTimer_run(hCpnCalTimer cthis){
    //TODO
}

/*名称 : hCpnCalTimer CpnCalTimer_init(hCpnCalTimer cthis)
* 输入 : cthis - CpnCalTimer类指针
* 输出 : hCpnCalTimer - cthis/OOPC_NULL
* 其他 : CpnCalTimer类初始化函数
***********************************************/
hCpnCalTimer CpnCalTimer_init(hCpnCalTimer cthis){
    // 功能函数配置
    //cthis->run = CpnCalTimer_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnCalTimer CpnCalTimer_ctor(hCpnCalTimer cthis)
* 输入 : cthis - CpnCalTimer类指针
* 输出 : hCpnCalTimer - cthis/OOPC_NULL
* 其他 : CpnCalTimer类构造函数
***********************************************/
CC(CpnCalTimer){
    cthis->init = CpnCalTimer_init;
    cthis->run = CpnCalTimer_run;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnCalTimer CpnCalTimer_dtor(hCpnCalTimer cthis)
* 输入 : cthis - CpnCalTimer类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnCalTimer类析构函数
***********************************************/
CD(CpnCalTimer){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
