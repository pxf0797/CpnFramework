/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSch.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 15:10:52
 * Description  : CpnSch class functions definition source files.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnSch.h"
#include "FuncLib.h"
#include "RteSigs.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/

/***********************************************************
 * CpnSch class definition.
 **********************************************************/
/* Function : CpnSch_addTask(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_regist(hCpnSch cthis, htsInitTask t){
    if(cthis->taskCount >= CPNSCH_INIT_TASK_MAX_NUM){
        cthis->err(cthis, CPN_SCH_REGIST_BUFF_IS_FULL);
        return;
    }
    appMemCopy(&cthis->tasks[cthis->taskCount].init,t,sizeof(tsInitTask));
    cthis->tasks[cthis->taskCount].sta.registIndex = cthis->taskCount;
    cthis->rbTree->add(cthis->rbTree, &cthis->tasks[cthis->taskCount]);
    cthis->taskCount++;
}

/* Function : CpnSch_err(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   :
 * Others   : CpnSch class function.
 **********************************************/
void CpnSch_err(hCpnSch cthis, uint16 code){
    tsErrCode errCode;
    errCode.code = code;
    errCode.id = CPNSCHCFG_ERR_ID;
    SYN_TRIG(sig_trig_CpnSch_setErr, &errCode);
}

/* Function : hCpnSch CpnSch_init(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   : hCpnSch - cthis/OOPC_NULL
 * Others   : CpnSch class initial function.
 **********************************************/
hCpnSch CpnSch_init(hCpnSch cthis, uint8 *space, uint32 size,
        hstaAct sm,
        void (*getTime)(uint16 *point),
        void (*initCpn)(void),
        rbType (*rbOrder)(void *block),
        void (*eventTask)(void)){
    BlockM clBlockM;
    uint8 *rbSpace = OOPC_NULL;
    hCpnSch retRes = OOPC_NULL;
    uint16 i = 0u;
    uint8 *pointer = OOPC_NULL;
    uint8 *pointer2 = OOPC_NULL;
    tsInitTask eventParam;

    do{
        /* Set basic BlockM. */
        CN(BlockM,&clBlockM,space,sizeof(uint32),size);
        if(OPRS(clBlockM) == OOPC_NULL){
            break;
        }
        cthis->mem = OOPC_NULL;
        cthis->mem = clBlockM.malloc(clBlockM.self,sizeof(BlockM));
        if(cthis->mem == OOPC_NULL){
            break;
        }
        /* set block memory manage in the block. */
        appMemCopy(cthis->mem, &clBlockM ,sizeof(BlockM));
        cthis->mem->self = cthis->mem;


        /* Tasks and event search tree. */
        cthis->tasks =  cthis->mem->malloc(cthis->mem,sizeof(tsTask)*CPNSCH_INIT_TASK_MAX_NUM);
        if(cthis->tasks == OOPC_NULL){
            break;
        }
        cthis->rbTree = cthis->mem->malloc(cthis->mem,sizeof(RBTree));
        rbSpace = cthis->mem->malloc(cthis->mem,RED_BLACK_MANA_SIZE(CPNSCH_INIT_TASK_MAX_NUM));
        if((cthis->rbTree == OOPC_NULL) || (rbSpace == OOPC_NULL)){
            break;
        }
        CN(RBTree, cthis->rbTree, rbSpace, CPNSCH_INIT_TASK_MAX_NUM, rbOrder);
        if(OPRS(*cthis->rbTree) == OOPC_NULL){
            break;
        }

        /* Set lowest task */
        cthis->taskM =  cthis->mem->malloc(cthis->mem,sizeof(SchTask));
        if(cthis->taskM == OOPC_NULL){
            break;
        }
        cthis->taskM->slices =  cthis->mem->malloc(cthis->mem,sizeof(sliceParam)*te_task_period_index_max);
        if(cthis->taskM->slices == OOPC_NULL){
            break;
        }
        //appMemSet(cthis->taskM->slices, 0u, sizeof(sliceParam)*te_task_period_index_max);

        /* configure the mask and slice task */
        #define SLICESCH_INIT_PARAM(basic,period,num) do{ \
            cthis->taskM->slices[te_task_##period##ms_index].taskMask = cthis->mem->malloc(cthis->mem,sizeof(taskGroupType)*(te_task_##period##ms_num>>GROUP_TYPE_BITS));\
            cthis->taskM->slices[te_task_##period##ms_index].sliceTask = cthis->mem->malloc(cthis->mem,sizeof(task)*te_task_##period##ms_num);\
        }while(0);
        #define SLICESCH_INIT_PARAMS(slice_list) do{slice_list(SLICESCH_INIT_PARAM)}while(0)
        SLICESCH_INIT_PARAMS(SLICE_LIST);
        for(i = 0u; i < te_task_period_index_max; i++){
            if(!(cthis->taskM->slices[i].taskMask&&cthis->taskM->slices[i].sliceTask)){
                break;
            }
        }
        if(i < te_task_period_index_max){
            break;
        }
        /* init SchTask */
        CN(SchTask, cthis->taskM, SchSm, cthis->taskM->slices, cthis);
        if(OPRS(*cthis->taskM) == OOPC_NULL){
            break;
        }

        /* set event manage. */
        cthis->event =  cthis->mem->malloc(cthis->mem,sizeof(SchEvent));
        pointer = cthis->mem->malloc(cthis->mem,sizeof(Fifo));
        pointer2 = cthis->mem->malloc(cthis->mem,sizeof(event)*CPNEVENT_FIFO_MAX_LENGTH);
        if((cthis->event == OOPC_NULL) || (pointer == OOPC_NULL) || (pointer2 == OOPC_NULL)){
            break;
        }
        CN(SchEvent, cthis->event, (hFifo)pointer, pointer2, CPNEVENT_FIFO_MAX_LENGTH, cthis);
        if(OPRS(*cthis->event) == OOPC_NULL){
            break;
        }
        /* add event task. */
        eventParam.t = eventTask;
        eventParam.level = level1;
        eventParam.prdTick = 1*MS_T;
        eventParam.startTick = 0*MS_T;
        eventParam.e.all = e_event_task;
        cthis->regist(cthis, &eventParam);
        cthis->taskM->addTask(cthis->taskM, &cthis->tasks[cthis->taskCount-1u]);

        /* configure interface. */
        cthis->taskM->iTime.getTime = getTime;
        cthis->iInitCpn.initCpn = initCpn;

        /* Initial component. */
        cthis->iInitCpn.initCpn();

        retRes = cthis;
    }while(0);

    return retRes;
}

/* Function : hCpnSch CpnSch_ctor(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   : hCpnSch - cthis/OOPC_NULL
 * Others   : CpnSch class constructor.
 **********************************************/
CC(CpnSch){
    cthis->init = CpnSch_init;
    cthis->regist = CpnSch_regist;
    cthis->err = CpnSch_err;
    /* TODO */

    /* Configure parameters. */
    cthis->mem = OOPC_NULL;
    cthis->taskCount = 0u;
    cthis->tasks = OOPC_NULL;
    cthis->rbTree = OOPC_NULL;

    cthis->taskM = OOPC_NULL;
    cthis->event = OOPC_NULL;

    return cthis;
}

/* Function : hCpnSch CpnSch_dtor(hCpnSch cthis)
 * Input    : cthis - CpnSch class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnSch class destructor.
 **********************************************/
CD(CpnSch){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
