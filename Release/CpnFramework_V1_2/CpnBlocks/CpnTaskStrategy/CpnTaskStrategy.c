/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategy.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy类各功能函数定义源文件
* Others       :
* History      : 201218 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnTaskStrategy.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* CpnTaskStrategy类定义
***********************************************************/
/*名称 : CpnTaskStrategy_updateStrategy(hCpnTaskStrategy cthis)
* 输入 : cthis - CpnTaskStrategy类指针
* 输出 : 无
* 其他 : CpnTaskStrategy类功能函数
***********************************************/
void CpnTaskStrategy_updateStrategy(hCpnTaskStrategy cthis, strategy strgMask, uint16 addTime, uint16 delTime){
    cthis->strgMaskNew = strgMask;
    cthis->addTime = (addTime/CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD);
    cthis->delTime = (delTime/CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD);
    cthis->strgType = strategy_delay;
}

/*名称 : CpnTaskStrategy_updateStrategyCond(hCpnTaskStrategy cthis)
* 输入 : cthis - CpnTaskStrategy类指针
* 输出 : 无
* 其他 : CpnTaskStrategy类功能函数
***********************************************/
void CpnTaskStrategy_updateStrategyCond(hCpnTaskStrategy cthis, strategy strgMask, condition cond){
    cthis->strgMaskNew = strgMask;
    cthis->cond = cond;
    cthis->strgType = strategy_cond;
}

/*名称 : CpnTaskStrategy_run(hCpnTaskStrategy cthis)
* 输入 : cthis - CpnTaskStrategy类指针
* 输出 : 无
* 其他 : CpnTaskStrategy类功能函数
***********************************************/
void CpnTaskStrategy_run(hCpnTaskStrategy cthis){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_getStrategy, (uint8*)&cthis->strgMask);
    if(cthis->strgMask != cthis->strgMaskNew){
        if(cthis->strgType == strategy_delay){
            if(cthis->addTime > 0u){
                cthis->addTime--;
            }
            if(cthis->delTime > 0u){
                cthis->delTime--;
            }
            if((cthis->addTime == 0u) && ((cthis->strgMask&cthis->strgMaskNew) != cthis->strgMaskNew)){
                cthis->strgMask |= cthis->strgMaskNew;
                clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_updateStrategy, (uint8*)&cthis->strgMask);
            }
            if((cthis->delTime == 0u) && (cthis->strgMask != cthis->strgMaskNew)){
                clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_updateStrategy, (uint8*)&cthis->strgMaskNew);
            }
        }else{
            if((cthis->cond)&&(cthis->cond())){
                clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_updateStrategy, (uint8*)&cthis->strgMaskNew);
            }
        }
    }
}

/*名称 : hCpnTaskStrategy CpnTaskStrategy_init(hCpnTaskStrategy cthis)
* 输入 : cthis - CpnTaskStrategy类指针
* 输出 : hCpnTaskStrategy - cthis/OOPC_NULL
* 其他 : CpnTaskStrategy类初始化函数
***********************************************/
hCpnTaskStrategy CpnTaskStrategy_init(hCpnTaskStrategy cthis){
    // 功能函数配置
    //cthis->updateStrategy = CpnTaskStrategy_updateStrategy;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnTaskStrategy CpnTaskStrategy_ctor(hCpnTaskStrategy cthis)
* 输入 : cthis - CpnTaskStrategy类指针
* 输出 : hCpnTaskStrategy - cthis/OOPC_NULL
* 其他 : CpnTaskStrategy类构造函数
***********************************************/
CC(CpnTaskStrategy){
    cthis->init = CpnTaskStrategy_init;
    cthis->updateStrategy = CpnTaskStrategy_updateStrategy;
    cthis->updateStrategyCond = CpnTaskStrategy_updateStrategyCond;
    cthis->run = CpnTaskStrategy_run;
    //TODO

    // 参数配置
    cthis->strgMask = DEFAULT_STRATEGY_TASK_GROUPS;
    cthis->strgMaskNew = DEFAULT_STRATEGY_TASK_GROUPS;
    cthis->strgType = strategy_delay;
    cthis->addTime = 0u;
    cthis->delTime = 0u;
    cthis->cond = OOPC_NULL;

    return cthis;
}

/*名称 : hCpnTaskStrategy CpnTaskStrategy_dtor(hCpnTaskStrategy cthis)
* 输入 : cthis - CpnTaskStrategy类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnTaskStrategy类析构函数
***********************************************/
CD(CpnTaskStrategy){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
