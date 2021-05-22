/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSm.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/17 10:12:15
* Description  : 状态机CpnCalSm定义及各状态动作定义源文件
* Others       : 
* History      : 201217 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnCalSm.h"

/*状态机CpnCalSm定义
* 配置状态机相关处理状态
***********************************************/
SMDF(CpnCalSm, CPNCALSM_LIST);

/*名称 : CpnCalSm_act_init()
* 输入 : CpnCalSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 初始状态操作函数
***********************************************/
void CpnCalSm_act_init(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_init;
}

/*名称 : CpnCalSm_act_idle()
* 输入 : CpnCalSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态idle操作函数
***********************************************/
void CpnCalSm_act_idle(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_idle;
}

/*名称 : CpnCalSm_act_wait()
* 输入 : CpnCalSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态wait操作函数
***********************************************/
void CpnCalSm_act_wait(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_wait;
}

/*名称 : CpnCalSm_act_dispose()
* 输入 : CpnCalSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态dispose操作函数
***********************************************/
void CpnCalSm_act_dispose(void *CpnCalSmRec){
    hCpnCalSmRec hRec = (hCpnCalSmRec)CpnCalSmRec;

    // TODO

    hRec->next = CpnCalSm_sta_init;
    hRec->last = CpnCalSm_sta_dispose;
}

/**************************** Copyright(C) pxf ****************************/
