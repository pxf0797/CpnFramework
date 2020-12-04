/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsyn.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/21 11:57:29
* Description  : RteAsyn类各功能函数定义源文件
* Others       : 
* History      : 191221 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./RteAsyn.h"

/***********************************************************
* RteAsyn类定义
***********************************************************/
/*名称 : RteAsyn_set(hRteAsyn cthis)
* 输入 : cthis - RteAsyn类指针
* 输出 : 无
* 其他 : RteAsyn类功能函数
***********************************************/
void RteAsyn_set(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len){
    uint8 *dest = ((uint8*)cthis->set_buff + cthis->set_index[signal]);
    uint8 *source = buff + len;
    uint16 i = len;
    while(i-- > 0){
        dest--;
        source--;
        *dest = *source;
    }
}

/*名称 : RteAsyn_get(hRteAsyn cthis)
* 输入 : cthis - RteAsyn类指针
* 输出 : 无
* 其他 : RteAsyn类功能函数
***********************************************/
void RteAsyn_get(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len){
    uint8 *dest = buff + len;
    uint8 *source = ((uint8*)cthis->set_buff + cthis->set_index[cthis->get_index[signal]]);
    uint16 i = len;
    while(i-- > 0){
        dest--;
        source--;
        *dest = *source;
    }
}

/*名称 : hRteAsyn RteAsyn_init(hRteAsyn cthis)
* 输入 : cthis - RteAsyn类指针
* 输出 : hRteAsyn - cthis/OOPC_NULL
* 其他 : RteAsyn类初始化函数
***********************************************/
hRteAsyn RteAsyn_init(hRteAsyn cthis, uint8 *set_buff, uint16 *set_index, uint16 *get_index){
    // 功能函数配置
    //cthis->set_data = RteAsyn_set_data;
    //TODO

    // 参数配置
    cthis->set_buff = set_buff;
    cthis->set_index = set_index;
    cthis->get_index = get_index;

    return cthis;
}

/*名称 : hRteAsyn RteAsyn_ctor(hRteAsyn cthis)
* 输入 : cthis - RteAsyn类指针
* 输出 : hRteAsyn - cthis/OOPC_NULL
* 其他 : RteAsyn类构造函数
***********************************************/
CC(RteAsyn){
    cthis->init = RteAsyn_init;
    cthis->set = RteAsyn_set;
    cthis->get = RteAsyn_get;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hRteAsyn RteAsyn_dtor(hRteAsyn cthis)
* 输入 : cthis - RteAsyn类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : RteAsyn类析构函数
***********************************************/
CD(RteAsyn){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
