/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMatrixMapTest.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:00:03
 * Description  : CpnMatrixMapTest class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnMatrixMapTest.h"
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
uint16 uwTestCase = 1U;

/***********************************************************
 * CpnMatrixMapTest class definition.
 **********************************************************/
/* Function : CpnMatrixMapTest_run(hCpnMatrixMapTest cthis)
 * Input    : cthis - CpnMatrixMapTest class pointer
 * Output   :
 * Others   : CpnMatrixMapTest class function.
 **********************************************/
void CpnMatrixMapTest_run(hCpnMatrixMapTest cthis){
    static tick waitDelay = 1*S_T;
    static uint8 ucUpdateData = 0;
    uint32 ulTempData = 0;

    if(uwTestCase == 0U){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_delay, (uint8*)&waitDelay);
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

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataA, (uint8*)&ulDataSet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataB, (uint8*)&ulDataSet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataC, (uint8*)&ulDataSet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataD, (uint8*)&ulDataSet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataE, (uint8*)&ulDataSet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataF, (uint8*)&ulDataSet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_set_ulDataG, (uint8*)&ulDataSet[6]);

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData1, (uint8*)&ulDataGet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData2, (uint8*)&ulDataGet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData3, (uint8*)&ulDataGet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData4, (uint8*)&ulDataGet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData5, (uint8*)&ulDataGet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData6, (uint8*)&ulDataGet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData7, (uint8*)&ulDataGet[6]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulData8, (uint8*)&ulDataGet[7]);

    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataA, (uint8*)&ulDataSetGet[0]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataB, (uint8*)&ulDataSetGet[1]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataC, (uint8*)&ulDataSetGet[2]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataD, (uint8*)&ulDataSetGet[3]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataE, (uint8*)&ulDataSetGet[4]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataF, (uint8*)&ulDataSetGet[5]);
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMatrixMapTest_get_ulDataG, (uint8*)&ulDataSetGet[6]);
}

/* Function : hCpnMatrixMapTest CpnMatrixMapTest_init(hCpnMatrixMapTest cthis)
 * Input    : cthis - CpnMatrixMapTest class pointer
 * Output   : hCpnMatrixMapTest - cthis/OOPC_NULL
 * Others   : CpnMatrixMapTest class initial function.
 **********************************************/
hCpnMatrixMapTest CpnMatrixMapTest_init(hCpnMatrixMapTest cthis){
    /* Configure functions. */
    //cthis->run = CpnMatrixMapTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnMatrixMapTest CpnMatrixMapTest_ctor(hCpnMatrixMapTest cthis)
 * Input    : cthis - CpnMatrixMapTest class pointer
 * Output   : hCpnMatrixMapTest - cthis/OOPC_NULL
 * Others   : CpnMatrixMapTest class constructor.
 **********************************************/
CC(CpnMatrixMapTest){
    cthis->init = CpnMatrixMapTest_init;
    cthis->run = CpnMatrixMapTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCpnMatrixMapTest CpnMatrixMapTest_dtor(hCpnMatrixMapTest cthis)
 * Input    : cthis - CpnMatrixMapTest class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnMatrixMapTest class destructor.
 **********************************************/
CD(CpnMatrixMapTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
