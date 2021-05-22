/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCalSm.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/17 10:12:15
* Description  : 状态机CpnCalSm声明及状态机使用示例头文件
* Others       : 
* History      : 201217 pxf 初次建立
***************************************************************************/

#ifndef CPNCALSM_H_
#define CPNCALSM_H_

/*头文件包含*/
#include "../../cpnBasics/sm/sm.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNCALSM_MACRO_VERSION          0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/*状态机CpnCalSm使用示例：
* 当前状态机已在SMDF中定义出实体CpnCalSm，需要做的只是让其运行起来
* 状态机运行方式有两种直接给时钟驱动的SMR和使用自定义记录状态后进驱动的SMRE
***********************************************
* SMR方式
***********************************************
void test(void){
    while(1){SMR(CpnCalSm);};
}
***********************************************
* SMRE方式
***********************************************
void test2(void){
    static CpnCalSmRec CpnCalSmRunRec = {CpnCalSm_sta_init};
    while(1){SMRE(CpnCalSm, CpnCalSmRunRec);};
}
***********************************************/


/*状态机CpnCalSm状态序列定义
* 注意其中CpnCalSm_init,CpnCalSm_default未在此定义，默认会给出
***********************************************/
#define CPNCALSM_LIST(_)    \
    _(CpnCalSm, idle)       \
    _(CpnCalSm, wait)       \
    _(CpnCalSm, dispose)    \


/*状态机CpnCalSm声明
* 已给出状态记录next,及上一状态last，其他参数需自行添加
***********************************************/
SMDC(CpnCalSm, CPNCALSM_LIST){
    sta next; // 运行状态记录
    sta last; // 上一状态记录
    // TODO
};

#endif /*CPNCALSM_H_*/

/**************************** Copyright(C) pxf ****************************/
