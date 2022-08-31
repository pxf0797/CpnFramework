/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SchEvent.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2022/04/10 11:11:02
 * Description  : SchEvent class functions definition source file.
 * Others       :
 * History      : 20220410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "SchEvent.h"
#include "CpnSch.h"
#include "RteSigs.h"
#include "FuncLib.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface definition
 **********************************************/

/***********************************************************
 * SchEvent class definition.
 **********************************************************/
/* Function : SchEvent_trig(hSchEvent cthis)
 * Input    : cthis - SchEvent class pointer
 * Output   :
 * Others   : SchEvent class function.
 **********************************************/
void SchEvent_trig(hSchEvent cthis, uint16 e){
    cthis->fifo->push(cthis->fifo, &e);
}

/* Function : SchEvent_run(hSchEvent cthis)
 * Input    : cthis - SchEvent class pointer
 * Output   :
 * Others   : SchEvent class function.
 **********************************************/
void SchEvent_run(hSchEvent cthis){
    uint16 i = 0u;
    uint16 limit = 0u;
    event e;
    hRBTree rbTree = ((hCpnSch)cthis->CpnSch)->rbTree;
    rbType orderEqual = 0u, orderLess = 0u;
    htsTask taskParam;
    hSchTask task = ((hCpnSch)(cthis->CpnSch))->taskM;

    do{
        if(cthis->fifo->isEmpty(cthis->fifo)){
            break;
        }
        /* dispose every event */
        limit = cthis->fifo->currCnt;
        if(cthis->fifo->currCnt > CPNEVENT_DISPOSE_MAX_CFG){
            limit = CPNEVENT_DISPOSE_MAX_CFG;
        }
        for(i = 0u; i < limit; i++){
            /* get each task index and task status. */
            cthis->fifo->fout(cthis->fifo, &e.all);
            orderEqual = (((rbType)(e.bit.e))<<16);
            orderLess = (((rbType)(e.bit.e+1u))<<16);
            rbTree->getNode(rbTree, orderEqual, orderLess, (hhtsRBNode)&cthis->nodes, &cthis->taskCount);
            if(!cthis->taskCount){continue;}
            if(cthis->taskCount  > CPNEVENT_REFER_TASK_MAX_CFG){
                cthis->err(cthis, CPN_SCH_EVENT_EVENT_REFERTASK_OVERFLOW);
                continue;
            }
            /* add or delete the tasks. */
            while(cthis->taskCount){
                cthis->taskCount--;
                taskParam = (htsTask)(cthis->nodes[cthis->taskCount]->block);
                if(e.bit.dele){
                    if(taskParam->init.level){
                        task->delTask(task, taskParam);
                    }else{
                        task->delLowestTask(task, taskParam);
                    }
                }else{
                    if(taskParam->init.level){
                        task->addTask(task, taskParam);
                    }else{
                        task->addLowestTask(task, taskParam);
                    }
                }
            }
        }
    }while(0);
}

/* Function : SchEvent_err(hSchEvent cthis)
 * Input    : cthis - SchTask class pointer
 * Output   :
 * Others   : SchTask class function.
 **********************************************/
void SchEvent_err(hSchEvent cthis, uint16 code){
    tsErrCode errCode;
    errCode.code = code;
    errCode.id = CPNSCHCFG_ERR_ID;
    SYN_TRIG(sig_trig_CpnSch_setErr, &errCode);
}

/* Function : hSchEvent SchEvent_init(hSchEvent cthis)
 * Input    : cthis - SchEvent class pointer
 * Output   : hSchEvent - cthis/OOPC_NULL
 * Others   : SchEvent class initial function.
 **********************************************/
hSchEvent SchEvent_init(hSchEvent cthis, hFifo fifo, uint8 *buff, uint16 maxNum, void *CpnSch){
    hSchEvent retRes = cthis;

    do{
        /* specific failure detected */
        if(!(fifo&&buff&&maxNum)){
            retRes = OOPC_NULL;
            break;
        }
        /* Configure parameters. */
        cthis->buff = buff;
        cthis->maxNum = maxNum;
        CN(Fifo, fifo, cthis->buff, sizeof(event)*cthis->maxNum, sizeof(event));
        if(OPRS(*fifo) == OOPC_NULL){
            retRes = OOPC_NULL;
            break;
        }
        cthis->fifo = fifo;
        cthis->CpnSch = CpnSch;
    }while(0);
    return retRes;
}

/* Function : hSchEvent SchEvent_ctor(hSchEvent cthis)
 * Input    : cthis - SchEvent class pointer
 * Output   : hSchEvent - cthis/OOPC_NULL
 * Others   : SchEvent class constructor.
 **********************************************/
CC(SchEvent){
    hSchEvent retRes = cthis;

    do{
        /* Configure functions. */
        cthis->init = SchEvent_init;
        cthis->trig = SchEvent_trig;
        cthis->run = SchEvent_run;
        cthis->err = SchEvent_err;
    }while(0);
    return retRes;
}

/* Function : hSchEvent SchEvent_dtor(hSchEvent cthis)
 * Input    : cthis - SchEvent class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : SchEvent class destructor.
 **********************************************/
CD(SchEvent){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
