/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnTaskStrategy.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 09:53:54
 * Description  : CpnTaskStrategy class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnTaskStrategy.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnTaskStrategy class definition.
 **********************************************************/
/* Function : CpnTaskStrategy_updateStrategy(hCpnTaskStrategy cthis)
 * Input    : cthis - CpnTaskStrategy class pointer
 * Output   :
 * Others   : CpnTaskStrategy class function.
 **********************************************/
void CpnTaskStrategy_updateStrategy(hCpnTaskStrategy cthis, strategy strgMask, uint16 addTime, uint16 delTime){
    cthis->strgMaskNew = strgMask;
    cthis->addTime = (addTime/CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD);
    cthis->delTime = (delTime/CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD);
    cthis->strgType = strategy_delay;
}

/* Function : CpnTaskStrategy_updateStrategyCond(hCpnTaskStrategy cthis)
 * Input    : cthis - CpnTaskStrategy class pointer
 * Output   :
 * Others   : CpnTaskStrategy class function.
 **********************************************/
void CpnTaskStrategy_updateStrategyCond(hCpnTaskStrategy cthis, strategy strgMask, condition cond){
    cthis->strgMaskNew = strgMask;
    cthis->cond = cond;
    cthis->strgType = strategy_cond;
}

/* Function : CpnTaskStrategy_run(hCpnTaskStrategy cthis)
 * Input    : cthis - CpnTaskStrategy class pointer
 * Output   :
 * Others   : CpnTaskStrategy class function.
 **********************************************/
void CpnTaskStrategy_run(hCpnTaskStrategy cthis){
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_getStrategy, (uint8*)&cthis->strgMask);
    if(cthis->strgMask != cthis->strgMaskNew){
        if(cthis->strgType == strategy_delay){
            if(cthis->addTime > 0u){
                cthis->addTime--;
            }
            if(cthis->delTime > 0u){
                cthis->delTime--;
            }
            if((cthis->addTime == 0u) && ((cthis->strgMask&cthis->strgMaskNew) != cthis->strgMaskNew)){
                cthis->strgMask |= cthis->strgMaskNew;
                clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_updateStrategy, (uint8*)&cthis->strgMask);
            }
            if((cthis->delTime == 0u) && (cthis->strgMask != cthis->strgMaskNew)){
                clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_updateStrategy, (uint8*)&cthis->strgMaskNew);
            }
        }else{
            if((cthis->cond)&&(cthis->cond())){
                clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnTaskStrategy_updateStrategy, (uint8*)&cthis->strgMaskNew);
            }
        }
    }
}

/* Function : hCpnTaskStrategy CpnTaskStrategy_init(hCpnTaskStrategy cthis)
 * Input    : cthis - CpnTaskStrategy class pointer
 * Output   : hCpnTaskStrategy - cthis/OOPC_NULL
 * Others   : CpnTaskStrategy class initial function.
 **********************************************/
hCpnTaskStrategy CpnTaskStrategy_init(hCpnTaskStrategy cthis){
    /* Configure functions. */
    //cthis->updateStrategy = CpnTaskStrategy_updateStrategy;
    /* TODO */

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnTaskStrategy CpnTaskStrategy_ctor(hCpnTaskStrategy cthis)
 * Input    : cthis - CpnTaskStrategy class pointer
 * Output   : hCpnTaskStrategy - cthis/OOPC_NULL
 * Others   : CpnTaskStrategy class constructor.
 **********************************************/
CC(CpnTaskStrategy){
    cthis->init = CpnTaskStrategy_init;
    cthis->updateStrategy = CpnTaskStrategy_updateStrategy;
    cthis->updateStrategyCond = CpnTaskStrategy_updateStrategyCond;
    cthis->run = CpnTaskStrategy_run;
    /* TODO */

    /* Configure parameters. */
    cthis->strgMask = DEFAULT_STRATEGY_TASK_GROUPS;
    cthis->strgMaskNew = DEFAULT_STRATEGY_TASK_GROUPS;
    cthis->strgType = strategy_delay;
    cthis->addTime = 0u;
    cthis->delTime = 0u;
    cthis->cond = OOPC_NULL;
    return cthis;
}

/* Function : hCpnTaskStrategy CpnTaskStrategy_dtor(hCpnTaskStrategy cthis)
 * Input    : cthis - CpnTaskStrategy class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnTaskStrategy class destructor.
 **********************************************/
CD(CpnTaskStrategy){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
