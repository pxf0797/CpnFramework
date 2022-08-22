/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSchSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  : CpnSch component signals definition source file.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnSch.h"
#include "CpnSchSigs.h"
#include "RteSigs.h"
#include "FuncLib.h"

/***********************************************************
 * CpnSch class definition.
 **********************************************************/
/* CpnSch class.
 **********************************************/
static CpnSch clCpnSch;
#define GROUP_SIZE(basic,period,num) +ALIGN_SIZE(sizeof(uint32),sizeof(task))*te_task_##period##ms_num
#define GROUPS_SIZE(slice_list) slice_list(GROUP_SIZE)
#define CPNSCH_MEM_SPACE_SIZE       ALIGN_SIZE(sizeof(uint32),sizeof(CpnSch)) \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(BlockM)) \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(RBTree)) \
                                    +ALIGN_SIZE(sizeof(uint32),RED_BLACK_MANA_SIZE(CPNSCH_INIT_TASK_MAX_NUM)) \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(tsTask)*CPNSCH_INIT_TASK_MAX_NUM) \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(SchTask)) \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(sliceParam))*te_task_period_index_max \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(taskGroupType))*te_task_period_index_max \
                                    GROUPS_SIZE(SLICE_LIST) \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(SchEvent)) \
                                    +ALIGN_SIZE(sizeof(uint32),sizeof(Fifo)) \
                                    +ALIGN_SIZE(sizeof(uint32),(sizeof(event)*CPNEVENT_FIFO_MAX_LENGTH)) \

static uint8 memSpace[BLOCKMCFG_CAL_MANAGE_SIZE(uint32,(CPNSCH_MEM_SPACE_SIZE+CPNSCH_EXTRA_MEM_SPACE_SIZE))];

/* Internal interface definition.
 **********************************************/
rbType get_eventOrder(void *block);
void task_event(void);

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnSch_initTask(void *buff){
    clCpnSch.regist(clCpnSch.self,(htsInitTask)buff);
}
/* Delay Service.
 **********************************************/
void serv_CpnSch_delay(void *buff){
    clCpnSch.taskM->delay(clCpnSch.taskM, buff);
}
/* Real time Service.
 **********************************************/
void serv_CpnSch_now(void *buff){
    clCpnSch.taskM->now(clCpnSch.taskM, buff);
}
/* Set monitor Service.
 **********************************************/
void serv_CpnSch_setMonitor(void *buff){
    clCpnSch.taskM->setMonitor(clCpnSch.taskM, ((htsTask)buff));
}
/* Get monitor Service.
 **********************************************/
void serv_CpnSch_getMonitor(void *buff){
    clCpnSch.taskM->getMonitor(clCpnSch.taskM, ((uint16*)buff));
}

/* Get all schduler task counters Service.
 **********************************************/
void serv_CpnSch_getTaskNum(void *buff){
    uint16 counter = sig_clear;
    uint16 i = sig_clear;

    for(i = 0u; i < level_max; i++){
        counter += clCpnSch.taskM->smRec.taskLevelCounter[i];
    }
    for(i = 0u; i < te_task_period_index_max; i++){
        counter += clCpnSch.taskM->slices[i].taskCounter;
    }
    *((uint16*)buff) = counter;
}

/* trigger event.
 **********************************************/
void serv_CpnSch_event(void *buff){
    clCpnSch.event->trig(clCpnSch.event, *(uint16*)buff);
}

/* Component initial Service.
 **********************************************/
void serv_CpnSch_init(void){
    CN(CpnSch, &clCpnSch, memSpace, sizeof(memSpace), SchSm,
    trig_CpnSch_inf_getTime, trig_CpnSch_inf_initCpn, get_eventOrder, task_event);
    if(OPRS(clCpnSch) != NULL){}
}
/* Component run Service.
 **********************************************/
void serv_CpnSch_run(void){
    clCpnSch.taskM->run(clCpnSch.taskM);
}
/* Step Service.
 **********************************************/
void serv_CpnSch_tick(void){
    clCpnSch.taskM->tick(clCpnSch.taskM);
}

/* Real time Interface trigger.
 **********************************************/
void trig_CpnSch_inf_getTime(uint16 *point){
    SYN_TRIG(sig_trig_CpnSch_inf_getTime, point);
}

/* Interface definition
 **********************************************/
rbType get_eventOrder(void *block){
    rbType order = 0u;
    //return (rbType)(((htuEventTask)block)->order);
    order = ((htsTask)block)->init.e.all;
    order = (order<<16u);
    order |= ((htsTask)block)->sta.registIndex;
    return order;
}
/* event run interface.
 **********************************************/
void task_event(void){
    clCpnSch.event->run(clCpnSch.event);
}

/* Initial component Interface trigger.
 **********************************************/
void trig_CpnSch_inf_initCpn(void){
    /* regist every component. */
    SYN_TRIG(sig_trig_CpnMem_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnErr_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnSource_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnSinks_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnTest_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnSourceTest_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnSinksTest_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnCrc_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnMemTest_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnInfo_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnAlarm_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnAlarmSource_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnDataMana_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnDataManaTest_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnFuncLibTest_init, OOPC_NULL);
    SYN_TRIG(sig_trig_CpnSimple_init, OOPC_NULL);

    /* set start evnet. */
    SYN_EVENT(E_ADD(e_start_event));
}

/**************************** Copyright(C) pxf ****************************/
