/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnAlarmSourceSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/06/26 09:54:34
 * Description  : CpnAlarmSource component signals definition source file.
 * Others       :
 * History      : 20210626 pxf Initially established.
 **************************************************************************/

/* Include head files. */
// #include "CpnAlarmSource.h"
#include "CpnAlarmSourceSigs.h"
#include "RteSigs.h"

/***********************************************************
 * CpnAlarmSource class definition.
 **********************************************************/
/* CpnAlarmSource class.
 **********************************************/
// static CpnAlarmSource clCpnAlarmSource;
typedef enum{
    S_SINE,
    S_PLUSE,
    S_UPDOWN,
    S_UP,
    S_DOWN,

    S_MAX_COUNT
} teSourceTag;
static tSourceParams sSource[S_MAX_COUNT];
static float32 fOutput[S_MAX_COUNT];
static uint32 ulOutput[S_MAX_COUNT];

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnAlarmSource_init(void){
    // CNNP(CpnAlarmSource,&clCpnAlarmSource);
    // if(OPRS(clCpnAlarmSource) != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnAlarmSource;
        taskParam.prdTick = 11*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_source_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnAlarmSource_initTask, (uint8*)&taskParam);

        sSource[S_SINE].type = w_sine;
        sSource[S_SINE].trig_sig = sig_trig_CpnAlarmSource_sSine;
        sSource[S_SINE].amplitude = 1000.0;
        sSource[S_SINE].step = 2*MS_T;
        sSource[S_SINE].period = 2*S_T;
        sSource[S_SINE].duty = 0u;
        sSource[S_SINE].phase = 900u;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnAlarmSource_registWaveSig, (uint8*)&sSource[S_SINE]);

        sSource[S_PLUSE].type = w_pluse;
        sSource[S_PLUSE].trig_sig = sig_trig_CpnAlarmSource_sPluse;
        sSource[S_PLUSE].amplitude = 1000.0;
        sSource[S_PLUSE].step = 5*MS_T;
        sSource[S_PLUSE].period = 5*S_T;
        sSource[S_PLUSE].duty = 500u;
        sSource[S_PLUSE].phase = 900u;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnAlarmSource_registWaveSig, (uint8*)&sSource[S_PLUSE]);

        sSource[S_UPDOWN].type = w_countUpDown;
        sSource[S_UPDOWN].trig_sig = sig_trig_CpnAlarmSource_sUpDown;
        sSource[S_UPDOWN].amplitude = 1000.0;
        sSource[S_UPDOWN].step = 10*MS_T;
        sSource[S_UPDOWN].period = 8*S_T;
        sSource[S_UPDOWN].duty = 0u;
        sSource[S_UPDOWN].phase = 900u;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnAlarmSource_registWaveSig, (uint8*)&sSource[S_UPDOWN]);

        sSource[S_UP].type = w_countUp;
        sSource[S_UP].trig_sig = sig_trig_CpnAlarmSource_sUp;
        sSource[S_UP].amplitude = 1000.0;
        sSource[S_UP].step = 5*MS_T;
        sSource[S_UP].period = 4*S_T;
        sSource[S_UP].duty = 0u;
        sSource[S_UP].phase = 900u;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnAlarmSource_registWaveSig, (uint8*)&sSource[S_UP]);

        sSource[S_DOWN].type = w_countDown;
        sSource[S_DOWN].trig_sig = sig_trig_CpnAlarmSource_sDown;
        sSource[S_DOWN].amplitude = 1000.0;
        sSource[S_DOWN].step = 5*MS_T;
        sSource[S_DOWN].period = 2*S_T;
        sSource[S_DOWN].duty = 0u;
        sSource[S_DOWN].phase = 900u;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnAlarmSource_registWaveSig, (uint8*)&sSource[S_DOWN]);

        clRteAsynSigs.set(clRteAsynSigs.self,sig_set_CpnAlarmSource_sSine,(uint8*)&ulOutput[S_SINE]);
        clRteAsynSigs.set(clRteAsynSigs.self,sig_set_CpnAlarmSource_sPluse,(uint8*)&ulOutput[S_PLUSE]);
        clRteAsynSigs.set(clRteAsynSigs.self,sig_set_CpnAlarmSource_sUpDown,(uint8*)&ulOutput[S_UPDOWN]);
        clRteAsynSigs.set(clRteAsynSigs.self,sig_set_CpnAlarmSource_sUp,(uint8*)&ulOutput[S_UP]);
        clRteAsynSigs.set(clRteAsynSigs.self,sig_set_CpnAlarmSource_sDown,(uint8*)&ulOutput[S_DOWN]);
    // }
}

/* getSine Service.
 **********************************************/
void serv_CpnAlarmSource_sSine(void *buff){
    fOutput[S_SINE] = *((float32*)buff);
    ulOutput[S_SINE] = (uint32)(fOutput[S_SINE]+1000);
}
/* getPluse Service.
 **********************************************/
void serv_CpnAlarmSource_sPluse(void *buff){
    fOutput[S_PLUSE] = *((float32*)buff);
    ulOutput[S_PLUSE] = (uint32)fOutput[S_PLUSE];
}
/* getUpDown Service.
 **********************************************/
void serv_CpnAlarmSource_sUpDown(void *buff){
    fOutput[S_UPDOWN] = *((float32*)buff);
    ulOutput[S_UPDOWN] = (uint32)fOutput[S_UPDOWN];
}
/* getUp Service.
 **********************************************/
void serv_CpnAlarmSource_sUp(void *buff){
    fOutput[S_UP] = *((float32*)buff);
    ulOutput[S_UP] = (uint32)fOutput[S_UP];
}
/* getDown Service.
 **********************************************/
void serv_CpnAlarmSource_sDown(void *buff){
    fOutput[S_DOWN] = *((float32*)buff);
    ulOutput[S_DOWN] = (uint32)fOutput[S_DOWN];
}
/* sSineUpCOnd Service.
 **********************************************/
void serv_CpnAlarmSource_sSineUpCOnd(void *buff){
    if(fOutput[S_SINE]>700.0){
        *((uint8*)buff) = TRUE;
    }else{
        *((uint8*)buff) = FALSE;
    }
}
/* sUpCOnd Service.
 **********************************************/
void serv_CpnAlarmSource_sUpCOnd(void *buff){
    if(fOutput[S_UPDOWN]>500.0){
        *((uint8*)buff) = TRUE;
    }else{
        *((uint8*)buff) = FALSE;
    }
}

/* Interface trigger.
 **********************************************/
//void trig_CpnAlarmSource_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnAlarmSource(void){
    // clCpnAlarmSource.run(clCpnAlarmSource.self);
}

/**************************** Copyright(C) pxf ****************************/
