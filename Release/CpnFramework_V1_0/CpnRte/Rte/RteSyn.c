/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSyn.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 10:05:34
* Description  : RteSyn类各功能函数定义源文件
* Others       : 
* History      : 191222 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./RteSyn.h"
#include "./TriggerService.h"

/***********************************************************
* RteSyn类定义
***********************************************************/
/*名称 : RteSyn_serv(hRteSyn cthis)
* 输入 : cthis - RteSyn类指针
* 输出 : 无
* 其他 : RteSyn类功能函数
***********************************************/
void RteSyn_serv(hRteSyn cthis, uint16 signal, uint8 *buff){
    void *func = cthis->serv_ServBuff[signal];
    if(func){
        if(buff){
            ((serv_param)func)(buff);
        }else{
            ((serv_void)func)();
        }
    }
}

/*名称 : RteSyn_trig(hRteSyn cthis)
* 输入 : cthis - RteSyn类指针
* 输出 : 无
* 其他 : RteSyn类功能函数
***********************************************/
void RteSyn_trig(hRteSyn cthis, uint16 signal, uint8 *buff){
    cthis->serv(cthis, cthis->trig_index[signal], buff);
}

/*名称 : hRteSyn RteSyn_init(hRteSyn cthis)
* 输入 : cthis - RteSyn类指针
* 输出 : hRteSyn - cthis/OOPC_NULL
* 其他 : RteSyn类初始化函数
***********************************************/
hRteSyn RteSyn_init(hRteSyn cthis, void **serv_ServBuff, uint16 *trig_index){
    // 功能函数配置
    //cthis->serv = RteSyn_serv;
    //TODO

    // 参数配置
    cthis->serv_ServBuff = serv_ServBuff;
    cthis->trig_index = trig_index;

    return cthis;
}

/*名称 : hRteSyn RteSyn_ctor(hRteSyn cthis)
* 输入 : cthis - RteSyn类指针
* 输出 : hRteSyn - cthis/OOPC_NULL
* 其他 : RteSyn类构造函数
***********************************************/
CC(RteSyn){
    cthis->init = RteSyn_init;
    cthis->serv = RteSyn_serv;
    cthis->trig = RteSyn_trig;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hRteSyn RteSyn_dtor(hRteSyn cthis)
* 输入 : cthis - RteSyn类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : RteSyn类析构函数
***********************************************/
CD(RteSyn){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
