/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTestSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 17:06:41
 * Description  : CpnTest component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnTest.h"
#include "CpnTestSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnTest class definition.
 **********************************************************/
/* CpnTest class.
 **********************************************/
CpnTest clCpnTest;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnTest_init(void){
    CNNP(CpnTest,&clCpnTest);
    if(OPRS(clCpnTest) != NULL){
        tsInitTask taskParam;
        taskParam.level = level0;
        taskParam.t = taskCpnTest;
        taskParam.prdTick = 13*MS_T;
        taskParam.startTick = 8000*MS_T;
        taskParam.e.all = e_CpnTest;
        SYN_TRIG(sig_trig_CpnTest_initTask, &taskParam);
    }
}

/* servSig1 Service.
 **********************************************/
uint16 uwServCnt1 = 0;
void serv_CpnTest_servSig1(void){
    uwServCnt1++;
}
/* servSig2_uint16 Service.
 **********************************************/
uint16 uwGetData = 0;
uint16 uwServCnt2 = 0;
void serv_CpnTest_servSig2_uint16(void *buff){
    uwGetData = *(uint16*)buff;
    uwServCnt2++;
}

/* Interface trigger.
 **********************************************/
//void trig_CpnTest_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
uint16 uwTrigData = 0;
void taskCpnTest(void){
    static tick waitDelay = 50*MS_T;
    static tick waitDelay2 = 10*MS_T;
    //tDataSig sendServTrig = {0};

    uwTrigData++;

    /* wait delay */
    SYN_TRIG(sig_trig_CpnTest_delay, &waitDelay);
    if(IS_TIMEOUT(waitDelay)){
        waitDelay = 300*MS_T;

        SYN_TRIG(sig_trig_CpnTest_trigSig1_uint16, &uwTrigData);
        SYN_TRIG(sig_trig_CpnTest_trigSig2, OOPC_NULL);
    }

    /* wait delay */
    SYN_TRIG(sig_trig_CpnTest_delay, &waitDelay2);
    if(IS_TIMEOUT(waitDelay2)){
        waitDelay2 = 2000*MS_T;

#define U8SHIFT_U32_BIT(value,bit) (((uint32)((value)&0xFFU))<<(bit))
        //sendServTrig.id = 0x20;
        //sendServTrig.data = (((uint32)uwServCnt1<<24)|((uint32)uwServCnt2<<16)|((uint32)uwTrigData<<8)|((uint32)uwGetData<<0));
        //sendServTrig.data = U8SHIFT_U32_BIT(uwServCnt1,24)|U8SHIFT_U32_BIT(uwServCnt2,16)|U8SHIFT_U32_BIT(uwTrigData,8)|U8SHIFT_U32_BIT(uwGetData,0);
        // SYN_TRIG(sig_trig_CpnTest_sendSig, &sendServTrig);
    }
}

/**************************** Copyright(C) pxf ****************************/
