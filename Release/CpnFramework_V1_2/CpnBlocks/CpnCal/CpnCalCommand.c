/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalCommand.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/12 10:39:13
* Description  : CpnCalCommand类各功能函数定义源文件
* Others       : 
* History      : 201212 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCalCommand.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* CpnCalCommand类定义
***********************************************************/
/*名称 : CpnCalCommand_run(hCpnCalCommand cthis)
* 输入 : cthis - CpnCalCommand类指针
* 输出 : 无
* 其他 : CpnCalCommand类功能函数
***********************************************/
void CpnCalCommand_run(hCpnCalCommand cthis){
    //TODO
}

/*名称 : hCpnCalCommand CpnCalCommand_init(hCpnCalCommand cthis)
* 输入 : cthis - CpnCalCommand类指针
* 输出 : hCpnCalCommand - cthis/OOPC_NULL
* 其他 : CpnCalCommand类初始化函数
***********************************************/
hCpnCalCommand CpnCalCommand_init(hCpnCalCommand cthis){
    // 功能函数配置
    //cthis->run = CpnCalCommand_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnCalCommand CpnCalCommand_ctor(hCpnCalCommand cthis)
* 输入 : cthis - CpnCalCommand类指针
* 输出 : hCpnCalCommand - cthis/OOPC_NULL
* 其他 : CpnCalCommand类构造函数
***********************************************/
CC(CpnCalCommand){
    cthis->init = CpnCalCommand_init;
    cthis->run = CpnCalCommand_run;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnCalCommand CpnCalCommand_dtor(hCpnCalCommand cthis)
* 输入 : cthis - CpnCalCommand类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnCalCommand类析构函数
***********************************************/
CD(CpnCalCommand){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
