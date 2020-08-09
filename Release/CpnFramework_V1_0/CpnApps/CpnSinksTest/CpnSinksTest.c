/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksTest.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 19:07:35
* Description  : CpnSinksTest类各功能函数定义源文件
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./CpnSinksTest.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
extern tSinksParams sinkXy;
extern tStoreData outXy;
extern tSinksOut sinkXyOut;
extern tSinksSta sinkXySta;
extern uint16 buffFullFlg;

/***********************************************************
* CpnSinksTest类定义
***********************************************************/
/*名称 : CpnSinksTest_run(hCpnSinksTest cthis)
* 输入 : cthis - CpnSinksTest类指针
* 输出 : 无
* 其他 : CpnSinksTest类功能函数
***********************************************/
void CpnSinksTest_run(hCpnSinksTest cthis){
    cthis->testSinks(cthis);
}

/*名称 : CpnSinksTest_testSinks(hCpnSinksTest cthis)
* 输入 : cthis - CpnSinksTest类指针
* 输出 : 无
* 其他 : CpnSinksTest类功能函数
***********************************************/
void CpnSinksTest_testSinks(hCpnSinksTest cthis){
    tDataSig sendStatus = {0};
    static tick waitDelay = 10*S_T;

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_cacheSta, (uint8*)&sinkXySta);
    if(sinkXySta.sta == cacheNotStart){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_trigStart, (uint8*)&sinkXy);
    }else if(sinkXySta.sta == cacheFull){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_readData, (uint8*)&sinkXyOut);
        if(sinkXyOut.outOperation){
            sendStatus.id = 0x02;
            sendStatus.data = (int32)(((htStoreData)(sinkXyOut.buff))->data);
            clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_sendSig, (uint8*)&sendStatus);
        }
    }

    /* wait delay */
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_delay, (uint8*)&waitDelay);
    if(IS_TIMEOUT(waitDelay)){
        waitDelay = 13*S_T;

        // sinkXy.trig_getSig = sig_trig_CpnSinksTest_sGetData;
        // sinkXy.trig_endSig = sig_trig_CpnSinksTest_sIsFull;
        sinkXy.period = 5*MS_T;
        // sinkXy.data_size = sizeof(tStoreData);
        // sinkXy.buff_size = sizeof(sinkDataBuff);
        // sinkXy.buff = sinkDataBuff;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_reCache, (uint8*)&sinkXy);
    }
}

/*名称 : hCpnSinksTest CpnSinksTest_init(hCpnSinksTest cthis)
* 输入 : cthis - CpnSinksTest类指针
* 输出 : hCpnSinksTest - cthis/OOPC_NULL
* 其他 : CpnSinksTest类初始化函数
***********************************************/
hCpnSinksTest CpnSinksTest_init(hCpnSinksTest cthis){
    // 功能函数配置
    //cthis->run = CpnSinksTest_run;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*名称 : hCpnSinksTest CpnSinksTest_ctor(hCpnSinksTest cthis)
* 输入 : cthis - CpnSinksTest类指针
* 输出 : hCpnSinksTest - cthis/OOPC_NULL
* 其他 : CpnSinksTest类构造函数
***********************************************/
CC(CpnSinksTest){
    cthis->init = CpnSinksTest_init;
    cthis->run = CpnSinksTest_run;
    cthis->testSinks = CpnSinksTest_testSinks;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCpnSinksTest CpnSinksTest_dtor(hCpnSinksTest cthis)
* 输入 : cthis - CpnSinksTest类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : CpnSinksTest类析构函数
***********************************************/
CD(CpnSinksTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
