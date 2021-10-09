/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnDataManaTest.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/08 11:41:08
 * Description  : CpnDataManaTest class functions definition source files.
 * Others       :
 * History      : 20211008 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnDataManaTest.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
#define DATA_SET_ARRAY_NUM    7U
#define DATA_GET_ARRAY_NUM    8U
uint32 ulDataSet[DATA_SET_ARRAY_NUM];
uint32 ulDataSetGet[DATA_SET_ARRAY_NUM];
uint32 ulDataGet[DATA_GET_ARRAY_NUM];
uint16 uwTestCase = 0u;

/***********************************************************
 * CpnDataManaTest class definition.
 **********************************************************/
/* Function : CpnDataManaTest_run(hCpnDataManaTest cthis)
 * Input    : cthis - CpnDataManaTest class pointer
 * Output   :
 * Others   : CpnDataManaTest class function.
 **********************************************/
void CpnDataManaTest_run(hCpnDataManaTest cthis){
    static tick waitDelay = 1*S_T;
    static uint8 ucUpdateData = 0;
    uint32 ulTempData = 0;

    if(uwTestCase == 0U){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_delay, (uint8*)&waitDelay);
        if(IS_TIMEOUT(waitDelay)){
            waitDelay = 1*S_T;
            ucUpdateData++;
            ulTempData = ucUpdateData;
            ulTempData = ((SWAP32_BIT4(ulTempData)<<8U)|SWAP32_BIT2(SWAP32_BIT4(ulTempData)));
            for(uint16 i = 0; i < DATA_SET_ARRAY_NUM; i++){
                ulDataSet[i] = ulTempData;
            }
        }
    }else if(uwTestCase == 1U){
        ulDataSet[0] = ulDataGet[4];
        ulDataSet[1]++;// = ulDataGet[5];
        ulDataSet[2] = ulDataGet[0];
        ulDataSet[3] = ulDataGet[1];
        ulDataSet[4]++;// = ulDataGet[5];
        ulDataSet[5] = ulDataGet[5];
        ulDataSet[6] = ulDataGet[1];
    }

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_set_TxCanAAB_ulDataA, (uint8*)&ulDataSet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_set_TxCanAAB_ulDataB, (uint8*)&ulDataSet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_set_TxCan100_ulDataC, (uint8*)&ulDataSet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_set_TxCan100_ulDataD, (uint8*)&ulDataSet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataE, (uint8*)&ulDataSet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataF, (uint8*)&ulDataSet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataG, (uint8*)&ulDataSet[6]);

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan22F_ulData1, (uint8*)&ulDataGet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan22F_ulData2, (uint8*)&ulDataGet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan22F_ulData3, (uint8*)&ulDataGet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan22F_ulData4, (uint8*)&ulDataGet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan554E_ulData5, (uint8*)&ulDataGet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan554E_ulData6, (uint8*)&ulDataGet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan554E_ulData7, (uint8*)&ulDataGet[6]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_RxCan554E_ulData8, (uint8*)&ulDataGet[7]);

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_TxCanAAB_ulDataA, (uint8*)&ulDataSetGet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_TxCanAAB_ulDataB, (uint8*)&ulDataSetGet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_TxCan100_ulDataC, (uint8*)&ulDataSetGet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_TxCan100_ulDataD, (uint8*)&ulDataSetGet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataE, (uint8*)&ulDataSetGet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataF, (uint8*)&ulDataSetGet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataG, (uint8*)&ulDataSetGet[6]);
}

/* Function : hCpnDataManaTest CpnDataManaTest_init(hCpnDataManaTest cthis)
 * Input    : cthis - CpnDataManaTest class pointer
 * Output   : hCpnDataManaTest - cthis/OOPC_NULL
 * Others   : CpnDataManaTest class initial function.
 **********************************************/
hCpnDataManaTest CpnDataManaTest_init(hCpnDataManaTest cthis){
    hCpnDataManaTest retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        /* Configure functions. */
        //cthis->run = CpnDataManaTest_run;
        /* TODO */

        /* Configure parameters. */
        /* TODO */
    }while(0);
    return retRes;
}

/* Function : hCpnDataManaTest CpnDataManaTest_ctor(hCpnDataManaTest cthis)
 * Input    : cthis - CpnDataManaTest class pointer
 * Output   : hCpnDataManaTest - cthis/OOPC_NULL
 * Others   : CpnDataManaTest class constructor.
 **********************************************/
CC(CpnDataManaTest){
    hCpnDataManaTest retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        cthis->init = CpnDataManaTest_init;
        cthis->run = CpnDataManaTest_run;
        /* TODO */

        /* Configure parameters. */
        /* TODO */
    }while(0);
    return retRes;
}

/* Function : hCpnDataManaTest CpnDataManaTest_dtor(hCpnDataManaTest cthis)
 * Input    : cthis - CpnDataManaTest class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnDataManaTest class destructor.
 **********************************************/
CD(CpnDataManaTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
