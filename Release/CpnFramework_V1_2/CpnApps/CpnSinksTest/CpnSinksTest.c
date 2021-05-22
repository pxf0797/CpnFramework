/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksTest.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 19:07:35
* Description  : CpnSinksTest������ܺ�������Դ�ļ�
* Others       :
* History      : 200730 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnSinksTest.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
extern tSinksParams sinkXy;
extern tStoreData outXy;
extern tSinksOut sinkXyOut;
extern tSinksSta sinkXySta;
extern uint16 buffFullFlg;

/***********************************************************
* CpnSinksTest�ඨ��
***********************************************************/
/*���� : CpnSinksTest_run(hCpnSinksTest cthis)
* ���� : cthis - CpnSinksTest��ָ��
* ��� : ��
* ���� : CpnSinksTest�๦�ܺ���
***********************************************/
void CpnSinksTest_run(hCpnSinksTest cthis){
    cthis->testSinks(cthis);
}

/*���� : CpnSinksTest_testSinks(hCpnSinksTest cthis)
* ���� : cthis - CpnSinksTest��ָ��
* ��� : ��
* ���� : CpnSinksTest�๦�ܺ���
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

/*���� : hCpnSinksTest CpnSinksTest_init(hCpnSinksTest cthis)
* ���� : cthis - CpnSinksTest��ָ��
* ��� : hCpnSinksTest - cthis/OOPC_NULL
* ���� : CpnSinksTest���ʼ������
***********************************************/
hCpnSinksTest CpnSinksTest_init(hCpnSinksTest cthis){
    // ���ܺ�������
    //cthis->run = CpnSinksTest_run;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnSinksTest CpnSinksTest_ctor(hCpnSinksTest cthis)
* ���� : cthis - CpnSinksTest��ָ��
* ��� : hCpnSinksTest - cthis/OOPC_NULL
* ���� : CpnSinksTest�๹�캯��
***********************************************/
CC(CpnSinksTest){
    cthis->init = CpnSinksTest_init;
    cthis->run = CpnSinksTest_run;
    cthis->testSinks = CpnSinksTest_testSinks;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCpnSinksTest CpnSinksTest_dtor(hCpnSinksTest cthis)
* ���� : cthis - CpnSinksTest��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnSinksTest����������
***********************************************/
CD(CpnSinksTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
