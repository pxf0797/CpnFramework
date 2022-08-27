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
#include "CpnDataManaTest.h"
#include "RteSigs.h"
#include "FuncLib.h"

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
        SYN_TRIG(sig_trig_CpnDataManaTest_delay, &waitDelay);
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

    SYN_TRIG(sig_trig_CpnDataManaTest_set_TxCanAAB_ulDataA, &ulDataSet[0]);
    SYN_TRIG(sig_trig_CpnDataManaTest_set_TxCanAAB_ulDataB, &ulDataSet[1]);
    SYN_TRIG(sig_trig_CpnDataManaTest_set_TxCan100_ulDataC, &ulDataSet[2]);
    SYN_TRIG(sig_trig_CpnDataManaTest_set_TxCan100_ulDataD, &ulDataSet[3]);
    SYN_TRIG(sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataE, &ulDataSet[4]);
    SYN_TRIG(sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataF, &ulDataSet[5]);
    SYN_TRIG(sig_trig_CpnDataManaTest_set_TxCanF0A_ulDataG, &ulDataSet[6]);

    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan22F_ulData1, &ulDataGet[0]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan22F_ulData2, &ulDataGet[1]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan22F_ulData3, &ulDataGet[2]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan22F_ulData4, &ulDataGet[3]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan554E_ulData5, &ulDataGet[4]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan554E_ulData6, &ulDataGet[5]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan554E_ulData7, &ulDataGet[6]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_RxCan554E_ulData8, &ulDataGet[7]);

    SYN_TRIG(sig_trig_CpnDataManaTest_get_TxCanAAB_ulDataA, &ulDataSetGet[0]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_TxCanAAB_ulDataB, &ulDataSetGet[1]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_TxCan100_ulDataC, &ulDataSetGet[2]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_TxCan100_ulDataD, &ulDataSetGet[3]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataE, &ulDataSetGet[4]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataF, &ulDataSetGet[5]);
    SYN_TRIG(sig_trig_CpnDataManaTest_get_TxCanF0A_ulDataG, &ulDataSetGet[6]);
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
