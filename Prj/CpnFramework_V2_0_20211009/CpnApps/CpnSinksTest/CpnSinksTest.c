/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSinksTest.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:53:35
 * Description  : CpnSinksTest class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnSinksTest.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
extern tSinksParams sinkXy;
//extern tStoreData outXy;
extern tSinksOut sinkXyOut;
extern tSinksSta sinkXySta;
//extern uint16 buffFullFlg;

/***********************************************************
 * CpnSinksTest class definition.
 **********************************************************/
/* Function : CpnSinksTest_run(hCpnSinksTest cthis)
 * Input    : cthis - CpnSinksTest class pointer
 * Output   :
 * Others   : CpnSinksTest class function.
 **********************************************/
void CpnSinksTest_run(hCpnSinksTest cthis){
    static tStoreData storeData = {0,0.0};
    clRteAsynSigs.get(clRteAsynSigs.self, sig_get_CpnSinksTest_wOutput, (uint8*)&storeData.data);
    storeData.index++;
    clRteAsynSigs.set(clRteAsynSigs.self, sig_set_CpnSinksTest_fetchData, (uint8*)&storeData);
    cthis->testSinks(cthis);
}

/* Function : CpnSinksTest_testSinks(hCpnSinksTest cthis)
 * Input    : cthis - CpnSinksTest class pointer
 * Output   :
 * Others   : CpnSinksTest class function.
 **********************************************/
void CpnSinksTest_testSinks(hCpnSinksTest cthis){
//    tDataSig sendStatus = {0};
    static tick waitDelay = 10*S_T;

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_cacheState, (uint8*)&sinkXySta);
    if(sinkXySta.sta == cacheNotStart){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_trigStart, (uint8*)&sinkXy);
    }else if(sinkXySta.sta == cacheFull){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_readData, (uint8*)&sinkXyOut);
        if(sinkXyOut.outOperation){
//            sendStatus.id = 0x02;
//            sendStatus.data = (int32)(((htStoreData)(sinkXyOut.buff))->data);
            //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSourceTest_sendSig, (uint8*)&sendStatus);
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
        // clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnSinksTest_reCache, (uint8*)&sinkXy);
    }
}

/* Function : hCpnSinksTest CpnSinksTest_init(hCpnSinksTest cthis)
 * Input    : cthis - CpnSinksTest class pointer
 * Output   : hCpnSinksTest - cthis/OOPC_NULL
 * Others   : CpnSinksTest class initial function.
 **********************************************/
hCpnSinksTest CpnSinksTest_init(hCpnSinksTest cthis){
    /* Configure functions. */
    //cthis->run = CpnSinksTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnSinksTest CpnSinksTest_ctor(hCpnSinksTest cthis)
 * Input    : cthis - CpnSinksTest class pointer
 * Output   : hCpnSinksTest - cthis/OOPC_NULL
 * Others   : CpnSinksTest class constructor.
 **********************************************/
CC(CpnSinksTest){
    cthis->init = CpnSinksTest_init;
    cthis->run = CpnSinksTest_run;
    cthis->testSinks = CpnSinksTest_testSinks;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCpnSinksTest CpnSinksTest_dtor(hCpnSinksTest cthis)
 * Input    : cthis - CpnSinksTest class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnSinksTest class destructor.
 **********************************************/
CD(CpnSinksTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
