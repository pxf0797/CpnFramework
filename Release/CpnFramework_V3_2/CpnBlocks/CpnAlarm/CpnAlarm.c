/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnAlarm.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/06/07 20:02:39
 * Description  : CpnAlarm class functions definition source files.
 * Others       :
 * History      : 20210607 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnAlarm.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnAlarm class definition.
 **********************************************************/
/* Function : CpnAlarm_getAlarmCount(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
uint16 CpnAlarm_getAlarmMax(hCpnAlarm cthis, teClassify classify, teSeriousLevel serious){
    uint16 uwCount = 0u;
    uint16 uwStartIndex = (classify*(SERIOUS_MAX_COUNT+1u));

    if(classify >= CLASS_MAX_COUNT){
        if(serious >= SERIOUS_MAX_COUNT){
            uwCount = cthis->alarmEventMax[SERIOUS_MAX_COUNT];
        }else{
            uwCount = cthis->alarmEventMax[serious];
        }
    }else{
        if(serious >= SERIOUS_MAX_COUNT){
            uwCount = cthis->alarmClassifyEventMax[uwStartIndex+SERIOUS_MAX_COUNT];
        }else{
            uwCount = cthis->alarmClassifyEventMax[uwStartIndex+serious];
        }
    }
    return uwCount;
}

/* Function : CpnAlarm_getAlarmCount(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
uint16 CpnAlarm_getAlarmCount(hCpnAlarm cthis, teClassify classify, teSeriousLevel serious){
    uint16 uwCount = 0u;
    uint16 uwStartIndex = (classify*(SERIOUS_MAX_COUNT+1u));

    if(classify >= CLASS_MAX_COUNT){
        if(serious >= SERIOUS_MAX_COUNT){
            uwCount = cthis->alarmCount[SERIOUS_MAX_COUNT];
        }else{
            uwCount = cthis->alarmCount[serious];
        }
    }else{
        if(serious >= SERIOUS_MAX_COUNT){
            uwCount = cthis->alarmClassifyCount[uwStartIndex+SERIOUS_MAX_COUNT];
        }else{
            uwCount = cthis->alarmClassifyCount[uwStartIndex+serious];
        }
    }
    return uwCount;
}

/* Function : CpnAlarm_getAlarmEvents(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
htsEvents CpnAlarm_getAlarmEvents(hCpnAlarm cthis, teClassify classify, teSeriousLevel serious){
    uint16 uwCount = 0u, uwUpCount = 0u, uwEvent = 0u;
    tsMemPointer tsMem;
    uint16 uwGroupIndex = 0u, uwGroupIndexMax = 0u, uwMaskIndex = 0u;
    alarmType aGroupMask = 0u, aMask = 0u;

    /* free previous space. */
    if(cthis->alarmedEvents.eventNum){
        cthis->alarmedEvents.eventNum = 0u;
    }
    if(cthis->alarmedEvents.events){
        SYN_TRIG(sig_trig_CpnAlarm_memFree, &cthis->alarmedEvents.events);
    }
    if(cthis->alarmedEvents.upgradeNum){
        cthis->alarmedEvents.upgradeNum = 0u;
    }
    if(cthis->alarmedEvents.upgrades){
        SYN_TRIG(sig_trig_CpnAlarm_memFree, &cthis->alarmedEvents.upgrades);
    }

    do{
        /* set current nums. */
        cthis->alarmedEvents.eventNum = cthis->getAlarmCount(cthis,classify,serious);
        /* cthis->alarmedEvents.events */
        tsMem.indication = (cthis->alarmedEvents.eventNum*sizeof(uint16));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            break;
        }
        cthis->alarmedEvents.events = tsMem.pointer;

        /* find specific class alarms. */
        uwGroupIndexMax = (cthis->buffEventMax>>CPNALAEM_TYPE_BITS);
        uwGroupIndex = 0u;
        uwCount = 0u;
        while((uwCount<cthis->alarmedEvents.eventNum)
        &&(uwGroupIndex<uwGroupIndexMax)){
            aGroupMask = cthis->alarmFlag[uwGroupIndex];
            while(aGroupMask){
                /* get alarmed event. */
                aMask = MASK_FIRST_BIT(aGroupMask);
                uwMaskIndex = log_2n(aMask);
                uwEvent = (uwMaskIndex+(uwGroupIndex<<CPNALAEM_TYPE_BITS));
                /* Judge type and store event. */
                if(classify >= CLASS_MAX_COUNT){
                    if(serious >= SERIOUS_MAX_COUNT){
                        /* store all events. */
                        if(uwCount<cthis->alarmedEvents.eventNum){
                            cthis->alarmedEvents.events[uwCount++] = uwEvent;
                        }else{
                            cthis->err(cthis,CPNALARMCFG_ALARM_BUFF_LESS);
                        }
                    }else{
                        /* store correspond serious events. */
                        if(cthis->alarms[uwEvent].serious==serious){
                            if(uwCount<cthis->alarmedEvents.eventNum){
                                cthis->alarmedEvents.events[uwCount++] = uwEvent;
                            }else{
                                cthis->err(cthis,CPNALARMCFG_ALARM_BUFF_LESS);
                            }
                        }
                    }
                }else{
                    /* Judge class, if not, continue. */
                    if(cthis->alarms[uwEvent].classify!=classify){
                        aGroupMask &= (~aMask);
                        continue;
                    }
                    if(serious >= SERIOUS_MAX_COUNT){
                        /* store all events. */
                        if(uwCount<cthis->alarmedEvents.eventNum){
                            cthis->alarmedEvents.events[uwCount++] = uwEvent;
                        }else{
                            cthis->err(cthis,CPNALARMCFG_ALARM_BUFF_LESS);
                        }
                    }else{
                        /* store correspond serious events. */
                        if(cthis->alarms[uwEvent].serious==serious){
                            if(uwCount<cthis->alarmedEvents.eventNum){
                                cthis->alarmedEvents.events[uwCount++] = uwEvent;
                            }else{
                                cthis->err(cthis,CPNALARMCFG_ALARM_BUFF_LESS);
                            }
                        }
                    }
                }
                aGroupMask &= (~aMask);
            }
            uwGroupIndex++;
        }

        /* if find event num uwCount less than cthis->alarmedEvents.eventNum,
        then find upgrade events. */
        if(uwCount<cthis->alarmedEvents.eventNum){
            cthis->alarmedEvents.upgradeNum = (cthis->alarmedEvents.eventNum-uwCount);
            /* cthis->alarmedEvents.upgrades */
            tsMem.indication = (cthis->alarmedEvents.upgradeNum*sizeof(uint16));
            SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
            if(!tsMem.pointer){
                cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
                break;
            }
            cthis->alarmedEvents.upgrades = tsMem.pointer;
        }else{
            break;
        }

        /* find specific class alarms. */
        uwGroupIndexMax = (cthis->buffUpEventMax>>CPNALAEM_TYPE_BITS);
        uwGroupIndex = 0u;
        uwUpCount = 0u;
        while((uwUpCount<cthis->alarmedEvents.upgradeNum)
        &&(uwCount<cthis->alarmedEvents.eventNum)
        &&(uwGroupIndex<uwGroupIndexMax)){
            aGroupMask = cthis->alarmUpFlag[uwGroupIndex];
            while(aGroupMask){
                /* get alarmed event. */
                aMask = MASK_FIRST_BIT(aGroupMask);
                uwMaskIndex = log_2n(aMask);
                uwMaskIndex = (uwMaskIndex+(uwGroupIndex<<CPNALAEM_TYPE_BITS));
                uwEvent = cthis->alarmUps[uwMaskIndex].event;
                /* Judge type and store event. */
                if(classify >= CLASS_MAX_COUNT){
                    if(serious >= SERIOUS_MAX_COUNT){
                        /* store all events. */
                        if(uwUpCount<cthis->alarmedEvents.upgradeNum){
                            cthis->alarmedEvents.events[uwCount++] = uwEvent;
                            cthis->alarmedEvents.upgrades[uwUpCount++] = uwMaskIndex;
                        }else{
                            cthis->err(cthis,CPNALARMCFG_ALARMUP_BUFF_LESS);
                        }
                    }else{
                        /* store correspond serious events. */
                        if(cthis->alarmUps[uwMaskIndex].serious==serious){
                            if(uwUpCount<cthis->alarmedEvents.upgradeNum){
                                cthis->alarmedEvents.events[uwCount++] = uwEvent;
                                cthis->alarmedEvents.upgrades[uwUpCount++] = uwMaskIndex;
                            }else{
                                cthis->err(cthis,CPNALARMCFG_ALARMUP_BUFF_LESS);
                            }
                        }
                    }
                }else{
                    /* Judge class, if not, continue. */
                    if(cthis->alarms[uwEvent].classify!=classify){
                        aGroupMask &= (~aMask);
                        continue;
                    }
                    if(serious >= SERIOUS_MAX_COUNT){
                        /* store all events. */
                        if(uwUpCount<cthis->alarmedEvents.upgradeNum){
                            cthis->alarmedEvents.events[uwCount++] = uwEvent;
                            cthis->alarmedEvents.upgrades[uwUpCount++] = uwMaskIndex;
                        }else{
                            cthis->err(cthis,CPNALARMCFG_ALARMUP_BUFF_LESS);
                        }
                    }else{
                        /* store correspond serious events. */
                        if(cthis->alarmUps[uwMaskIndex].serious==serious){
                            if(uwUpCount<cthis->alarmedEvents.upgradeNum){
                                cthis->alarmedEvents.events[uwCount++] = uwEvent;
                                cthis->alarmedEvents.upgrades[uwUpCount++] = uwMaskIndex;
                            }else{
                                cthis->err(cthis,CPNALARMCFG_ALARMUP_BUFF_LESS);
                            }
                        }
                    }
                }
                aGroupMask &= (~aMask);
            }
            uwGroupIndex++;
        }
    }while(0);
    /* judge result. */
    if(uwUpCount<cthis->alarmedEvents.upgradeNum){
        cthis->alarmedEvents.upgradeNum = uwUpCount;
        cthis->err(cthis,CPNALARMCFG_ALARMUP_NUM_NOT_CORRESPOND);
    }
    if(uwCount<cthis->alarmedEvents.eventNum){
        cthis->alarmedEvents.eventNum = uwCount;
        cthis->err(cthis,CPNALARMCFG_ALARM_NUM_NOT_CORRESPOND);
    }

    return &cthis->alarmedEvents;
}

/* Function : CpnAlarm_isAlarmed(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
uint8 CpnAlarm_isAlarmed(hCpnAlarm cthis, uint16 event){
    uint16 uwGroupIndex = (event>>CPNALAEM_TYPE_BITS);
    alarmType aGroupMask = ((alarmType)1u<<(event&CPNALAEM_TYPE_MASK));
    uint8 ucRet = FALSE;

    if((event<cthis->alarmEventMax[SERIOUS_MAX_COUNT])
    &&(cthis->alarmFlag[uwGroupIndex]&aGroupMask)){
        ucRet = TRUE;
    }
    return ucRet;
}

/* Function : CpnAlarm_isUpgraded(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
uint8 CpnAlarm_isUpgraded(hCpnAlarm cthis, uint16 alarmUpIndex){
    uint16 uwUpGroupIndex = (alarmUpIndex>>CPNALAEM_TYPE_BITS);
    alarmType aUpGroupMask = ((alarmType)1u<<(alarmUpIndex&CPNALAEM_TYPE_MASK));
    uint8 ucRet = FALSE;

    if((alarmUpIndex<cthis->alarmUpEventMax)
    &&(cthis->alarmUpFlag[uwUpGroupIndex]&aUpGroupMask)){
        ucRet = TRUE;
    }
    return ucRet;
}

/* Function : CpnAlarm_alarmSrcCheck(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
teAlarmCheckSta CpnAlarm_alarmSrcCheck(hCpnAlarm cthis, htsAlarm alarm){
    uint32 *pGetData = OOPC_NULL;
    teAlarmCheckSta alramChecking = ALRAM_CHECKING;

    ASYN_ADDR(alarm->get_sig, &pGetData); /* get read data address */
    if(!pGetData){
        return alramChecking;
    }

    switch (alarm->alarmType){
    case ALRAM_UP:
        if(*pGetData >= alarm->setPoint){
            alramChecking = ALARM_CHECK_UP;
        }else if(*pGetData <= alarm->resetPoint){
            alramChecking = ALARM_CHECK_DOWN;
        }else{}
        break;

    case ALARM_DOWN:
        if(*pGetData <= alarm->setPoint){
            alramChecking = ALARM_CHECK_UP;
        }else if(*pGetData >= alarm->resetPoint){
            alramChecking = ALARM_CHECK_DOWN;
        }else{}
        break;

    case ALARM_FLAG:
        if(*pGetData){
            alramChecking = ALARM_CHECK_UP;
        }else{
            alramChecking = ALARM_CHECK_DOWN;
        }
        break;

    default:
        break;
    }

    return alramChecking;
}

/* Function : CpnAlarm_alarmCheckUpdate(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_alarmCheckUpdate(hCpnAlarm cthis, htsAlarm alarm){
    uint16 uwGroupIndex = (alarm->event>>CPNALAEM_TYPE_BITS);
    alarmType aGroupMask = ((alarmType)1u<<(alarm->event&CPNALAEM_TYPE_MASK));
    uint8 ucCond = FALSE;

    SYN_TRIG(alarm->trig_sig, &ucCond); /* read precondition */
    if(!ucCond){
        /* precondition do not satisfy, return directly. */
        cthis->alarmTimer[alarm->event] = cthis->timer;
        return;
    }

    switch (alarm->serious){
    case SERIOUS_HIGH:
        if(cthis->alarmSrcCheck(cthis, alarm)==ALARM_CHECK_UP){
             if(cthis->alarmFlag[uwGroupIndex]&aGroupMask){
             }else{
                if((cthis->timer-cthis->alarmTimer[alarm->event]) >= alarm->setLast){
                    cthis->alarmFlag[uwGroupIndex] |= aGroupMask;           /* setup flag */
                    cthis->alarmUpdateCount(cthis, alarm, ALRAM_COUNT_INC); /* update counter */
                }
             }
        /*}else if(cthis->alarmSrcCheck(cthis, alarm)==ALARM_CHECK_DOWN){*/
        }else{
            cthis->alarmTimer[alarm->event] = cthis->timer;
        }
        break;

    case SERIOUS_MEDIUM:
    case SERIOUS_LOW:
    case SERIOUS_NO:
        if(cthis->alarmSrcCheck(cthis, alarm)==ALARM_CHECK_UP){
            if(cthis->alarmFlag[uwGroupIndex]&aGroupMask){
                cthis->alarmTimer[alarm->event] = cthis->timer;
            }else{
                if((cthis->timer-cthis->alarmTimer[alarm->event]) >= alarm->setLast){
                    cthis->alarmFlag[uwGroupIndex] |= aGroupMask;           /* setup flag */
                    cthis->alarmUpdateCount(cthis, alarm, ALRAM_COUNT_INC); /* update counter */
                }
            }
        }else if(cthis->alarmSrcCheck(cthis, alarm)==ALARM_CHECK_DOWN){
            if(cthis->alarmFlag[uwGroupIndex]&aGroupMask){
                if((cthis->timer-cthis->alarmTimer[alarm->event]) >= alarm->clearLast){
                    cthis->alarmFlag[uwGroupIndex] &= (~aGroupMask);        /* clear flag */
                    cthis->alarmUpdateCount(cthis, alarm, ALRAM_COUNT_DEC); /* update counter */
                }
            }else{
                cthis->alarmTimer[alarm->event] = cthis->timer;
            }
        }else{
            cthis->alarmTimer[alarm->event] = cthis->timer;
        }
        break;

    default:
        break;
    }
}

/* Function : CpnAlarm_alarmUpdateCount(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_alarmUpdateCount(hCpnAlarm cthis, htsAlarm alarm, teAlarmCountUpdate countType){
    uint16 uwStartIndex = (alarm->classify*(SERIOUS_MAX_COUNT+1u));

    if(countType){
        /* Increase */
        /* For all event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        cthis->alarmCount[alarm->serious]++;
        cthis->alarmCount[SERIOUS_MAX_COUNT]++;

        /* For classify event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        cthis->alarmClassifyCount[uwStartIndex+alarm->serious]++;
        cthis->alarmClassifyCount[uwStartIndex+SERIOUS_MAX_COUNT]++;
    }else{
        /* Decrease */
        /* For all event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        if(cthis->alarmCount[alarm->serious]){
            cthis->alarmCount[alarm->serious]--;
        }
        if(cthis->alarmCount[SERIOUS_MAX_COUNT]){
            cthis->alarmCount[SERIOUS_MAX_COUNT]--;
        }

        /* For classify event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        if(cthis->alarmClassifyCount[uwStartIndex+alarm->serious]){
            cthis->alarmClassifyCount[uwStartIndex+alarm->serious]--;
        }
        if(cthis->alarmClassifyCount[uwStartIndex+SERIOUS_MAX_COUNT]){
            cthis->alarmClassifyCount[uwStartIndex+SERIOUS_MAX_COUNT]--;
        }
    }
}

/* Function : CpnAlarm_alarmUpUpdateCount(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_alarmUpUpdateCount(hCpnAlarm cthis, htsAlarmUp alarmUp, teAlarmCountUpdate countType){
    uint16 uwStartIndex = (cthis->alarms[alarmUp->event].classify*(SERIOUS_MAX_COUNT+1u));

    if(countType){
        /* Increase */
        /* For all event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        cthis->alarmCount[alarmUp->serious]++;
        cthis->alarmCount[SERIOUS_MAX_COUNT]++;

        /* For classify event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        cthis->alarmClassifyCount[uwStartIndex+alarmUp->serious]++;
        cthis->alarmClassifyCount[uwStartIndex+SERIOUS_MAX_COUNT]++;
    }else{
        /* Decrease */
        /* For all event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        if(cthis->alarmCount[alarmUp->serious]){
            cthis->alarmCount[alarmUp->serious]--;
        }
        if(cthis->alarmCount[SERIOUS_MAX_COUNT]){
            cthis->alarmCount[SERIOUS_MAX_COUNT]--;
        }

        /* For classify event update counter. SERIOUS_HIGH,SERIOUS_MEDIUM,SERIOUS_LOW,SERIOUS_NO,total */
        if(cthis->alarmClassifyCount[uwStartIndex+alarmUp->serious]){
            cthis->alarmClassifyCount[uwStartIndex+alarmUp->serious]--;
        }
        if(cthis->alarmClassifyCount[uwStartIndex+SERIOUS_MAX_COUNT]){
            cthis->alarmClassifyCount[uwStartIndex+SERIOUS_MAX_COUNT]--;
        }
    }
}

/* Function : CpnAlarm_run(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_run(hCpnAlarm cthis){
    static uint16 uwGroupIndex = 0u;
    static uint16 uwUpGroupIndex = 0u;
    uint16 uwGroupIndexMax = 0u;
    uint16 uwMultiGroups = 0u, uwStartIndex = 0u, uwStartGroup = 0u;
    uint16 i = 0u, j = 0u;
    htsAlarm alarm = OOPC_NULL;
    htsAlarmUp alarmUp = OOPC_NULL;

    /*
    Sharding execution
    Periodic scheduling
    Multiple coincidence detection */
    /*
    |||||||||||||||||||||||||||                     slice
            |||||||||||||||||||||||||||
                    |||||||||||||||||||||||||||
    |preiod |
    */

    cthis->timer++; /* Update basic timer. */
    /* alarms schedule */
    uwGroupIndexMax = (cthis->buffEventMax>>CPNALAEM_TYPE_BITS);
    if(uwGroupIndex >= (CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD)){
        uwGroupIndex = 0u;
    }
    /* find multiple groups */
    if(uwGroupIndexMax <= (CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD))
    {
        uwStartIndex = (uwGroupIndex<<CPNALAEM_TYPE_BITS);        /* get start index */
        for(i = uwStartIndex; i < (uwStartIndex+CPNALAEM_TYPE_WIDTH); i++){
            if(i >= cthis->alarmEventMax[SERIOUS_MAX_COUNT]){
                break;
            }
            alarm = &cthis->alarms[i];
            cthis->alarmCheckUpdate(cthis, alarm);
        }
    }else{
        uwMultiGroups = ALIGN_SIZE((CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD),uwGroupIndexMax)/ \
                (CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD);
        for(j = 0u; j < uwMultiGroups; j++){
            /* get start group */
            uwStartGroup = (uwGroupIndex+j*(CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD));
            uwStartIndex = (uwStartGroup<<CPNALAEM_TYPE_BITS);        /* get start index */
            for(i = uwStartIndex; i < (uwStartIndex+CPNALAEM_TYPE_WIDTH); i++){
                if(i >= cthis->alarmEventMax[SERIOUS_MAX_COUNT]){
                    break;
                }
                alarm = &cthis->alarms[i];
                cthis->alarmCheckUpdate(cthis, alarm);
            }
        }
    }
    uwGroupIndex++;
    /* alarmUps schedule */
    uwGroupIndexMax = (cthis->buffUpEventMax>>CPNALAEM_TYPE_BITS);
    if(uwUpGroupIndex >= (CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD)){
        uwUpGroupIndex = 0u;
    }
    /* find multiple groups */
    if(uwGroupIndexMax <= (CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD))
    {
        uwStartIndex = (uwUpGroupIndex<<CPNALAEM_TYPE_BITS);        /* get start index */
        for(i = uwStartIndex; i < (uwStartIndex+CPNALAEM_TYPE_WIDTH); i++){
            if(i >= cthis->alarmUpEventMax){
                break;
            }
            alarmUp = &cthis->alarmUps[i];
            cthis->alarmUpCheckUpdate(cthis, alarmUp);
        }
    }else{
        uwMultiGroups = ALIGN_SIZE((CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD),uwGroupIndexMax)/ \
                (CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD);
        for(j = 0u; j < uwMultiGroups; j++){
            /* get start group */
            uwStartGroup = (uwUpGroupIndex+j*(CPNALARMCFG_ALARM_EXECUTE_PERIOD/CPNALARMCFG_TASK_SLICE_PERIOD));
            uwStartIndex = (uwStartGroup<<CPNALAEM_TYPE_BITS);        /* get start index */
            for(i = uwStartIndex; i < (uwStartIndex+CPNALAEM_TYPE_WIDTH); i++){
                if(i >= cthis->alarmUpEventMax){
                    break;
                }
                alarmUp = &cthis->alarmUps[i];
                cthis->alarmUpCheckUpdate(cthis, alarmUp);
            }
        }
    }
    uwUpGroupIndex++;
}

/* Function : CpnAlarm_err(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_err(hCpnAlarm cthis, uint16 code){
    tsErrCode errCode;
    errCode.code = code;
    errCode.id = CPNALARMCFG_ERR_ID;
    SYN_TRIG(sig_trig_CpnAlarm_setErr, &errCode);
}

/* Function : CpnAlarm_regist(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_regist(hCpnAlarm cthis, htsAlarm alarm){
    uint16 uwStartIndex = (alarm->classify*(SERIOUS_MAX_COUNT+1u));
    if(cthis->alarmEventMax[SERIOUS_MAX_COUNT] >= cthis->buffEventMax){
        if(FALSE == cthis->dilatation(cthis)){
            cthis->err(cthis,CPNALARMCFG_REGIST_FAIL);
            return;
        }
    }
    alarm->event = cthis->alarmEventMax[SERIOUS_MAX_COUNT];                                             /* regist event */
    appMemCopy(&cthis->alarms[cthis->alarmEventMax[SERIOUS_MAX_COUNT]], alarm, sizeof(tsAlarm));           /* regist */
    cthis->alarms[cthis->alarmEventMax[SERIOUS_MAX_COUNT]].setLast /= CPNALARMCFG_TASK_SLICE_PERIOD;    /* update slice time */
    cthis->alarms[cthis->alarmEventMax[SERIOUS_MAX_COUNT]].clearLast /= CPNALARMCFG_TASK_SLICE_PERIOD;  /* update slice time */
    cthis->alarmTimer[cthis->alarmEventMax[SERIOUS_MAX_COUNT]] = cthis->timer;                          /* set timer */
    cthis->alarmEventMax[SERIOUS_MAX_COUNT]++; /* total count. */
    cthis->alarmEventMax[alarm->serious]++;
    cthis->alarmClassifyEventMax[uwStartIndex+SERIOUS_MAX_COUNT]++; /* class total count. */
    cthis->alarmClassifyEventMax[uwStartIndex+alarm->serious]++;
}

/* Function : CpnAlarm_registUp(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_registUp(hCpnAlarm cthis, htsAlarmUp alarmUp){
    if(cthis->alarmUpEventMax >= cthis->buffUpEventMax){
        if(FALSE == cthis->dilatationUp(cthis)){
            cthis->err(cthis,CPNALARMCFG_REGIST_UP_FAIL);
            return;
        }
    }
    alarmUp->alarmUpIndex = cthis->alarmUpEventMax;                                         /* regist alarm upgrade index */
    appMemCopy(&cthis->alarmUps[cthis->alarmUpEventMax], alarmUp, sizeof(tsAlarmUp));
    cthis->alarmUps[cthis->alarmUpEventMax].time /= CPNALARMCFG_TASK_SLICE_PERIOD;          /* update slice time */
    cthis->alarmUps[cthis->alarmUpEventMax].decreaseTime /= CPNALARMCFG_TASK_SLICE_PERIOD;  /* update slice time */
    cthis->alarmUpTimer[cthis->alarmUpEventMax] = cthis->timer;                             /* set timer */
    cthis->alarmUpMask[(alarmUp->event>>CPNALAEM_TYPE_BITS)] |= ((alarmType)1u<<(alarmUp->event&CPNALAEM_TYPE_MASK)); /* set alarm upgrade mask */
    cthis->alarmUpEventMax++;
}

/* Function : CpnAlarm_dilatation(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
uint16 CpnAlarm_dilatation(hCpnAlarm cthis){
    tsMemPointer tsMem;
    uint16 uwRetVal = TRUE;

    do{
        cthis->buffEventMax += CPNALAEM_TYPE_WIDTH;
        /* cthis->alarms */
        tsMem.indication = (cthis->buffEventMax*sizeof(tsAlarm));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarms){
            appMemCopy(tsMem.pointer,cthis->alarms,((cthis->buffEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(tsAlarm)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarms);
        }
        cthis->alarms = tsMem.pointer;
        /* cthis->alarmFlag */
        tsMem.indication = (cthis->buffEventMax*sizeof(alarmType));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarmFlag){
            appMemCopy(tsMem.pointer,cthis->alarmFlag,((cthis->buffEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(alarmType)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarmFlag);
        }
        cthis->alarmFlag = tsMem.pointer;
        /* cthis->alarmUpMask */
        // tsMem.indication = (cthis->buffEventMax*sizeof(alarmType));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarmUpMask){
            appMemCopy(tsMem.pointer,cthis->alarmUpMask,((cthis->buffEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(alarmType)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarmUpMask);
        }
        cthis->alarmUpMask = tsMem.pointer;
        /* cthis->alarmTimer */
        tsMem.indication = (cthis->buffEventMax*sizeof(uint32));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarmTimer){
            appMemCopy(tsMem.pointer,cthis->alarmTimer,((cthis->buffEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(uint32)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarmTimer);
        }
        cthis->alarmTimer = tsMem.pointer;
    }while(0);

    return uwRetVal;
}

/* Function : CpnAlarm_dilatationUp(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
uint16 CpnAlarm_dilatationUp(hCpnAlarm cthis){
    tsMemPointer tsMem;
    uint16 uwRetVal = TRUE;

    do{
        cthis->buffUpEventMax += CPNALAEM_TYPE_WIDTH;
        /* cthis->alarmUps */
        tsMem.indication = (cthis->buffUpEventMax*sizeof(tsAlarmUp));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffUpEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarmUps){
            appMemCopy(tsMem.pointer,cthis->alarmUps,((cthis->buffUpEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(tsAlarmUp)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarmUps);
        }
        cthis->alarmUps = tsMem.pointer;
        /* cthis->alarmUpFlag */
        tsMem.indication = (cthis->buffUpEventMax*sizeof(alarmType));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffUpEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarmUpFlag){
            appMemCopy(tsMem.pointer,cthis->alarmUpFlag,((cthis->buffUpEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(alarmType)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarmUpFlag);
        }
        cthis->alarmUpFlag = tsMem.pointer;
        /* cthis->alarmUpTimer */
        tsMem.indication = (cthis->buffUpEventMax*sizeof(uint32));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffUpEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarmUpTimer){
            appMemCopy(tsMem.pointer,cthis->alarmUpTimer,((cthis->buffUpEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(uint32)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarmUpTimer);
        }
        cthis->alarmUpTimer = tsMem.pointer;
        /* cthis->alarmUpCounter */
        tsMem.indication = (cthis->buffUpEventMax*sizeof(uint16));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->buffUpEventMax -= CPNALAEM_TYPE_WIDTH;
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            uwRetVal = FALSE;
            break;
        }
        if(cthis->alarmUpCounter){
            appMemCopy(tsMem.pointer,cthis->alarmUpCounter,((cthis->buffUpEventMax-CPNALAEM_TYPE_WIDTH)*sizeof(uint16)));
            SYN_TRIG(sig_trig_CpnAlarm_memFree, cthis->alarmUpCounter);
        }
        cthis->alarmUpCounter = tsMem.pointer;
    }while(0);

    return uwRetVal;
}

/* Function : CpnAlarm_alarmUpCheckUpdate(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   :
 * Others   : CpnAlarm class function.
 **********************************************/
void CpnAlarm_alarmUpCheckUpdate(hCpnAlarm cthis, htsAlarmUp alramUp){
    uint16 uwGroupIndex = (alramUp->alarmUpIndex>>CPNALAEM_TYPE_BITS);
    alarmType aGroupMask = ((alarmType)1u<<(alramUp->alarmUpIndex&CPNALAEM_TYPE_MASK));

    if(!(cthis->alarmUpMask[(alramUp->event>>CPNALAEM_TYPE_BITS)]&((alarmType)1u<<(alramUp->event&CPNALAEM_TYPE_MASK)))
    ||(cthis->alarmUpFlag[uwGroupIndex]&aGroupMask)){
        return;
    }
    if(cthis->isAlarmed(cthis,alramUp->event)
    ||cthis->alarmUpCounter[alramUp->alarmUpIndex]){
        if(cthis->isAlarmed(cthis,alramUp->event)){
            if(!IS_ALARMUP_COUNTING(alramUp->count)){
                alramUp->count = SET_ALARMUP_COUNTING(alramUp->count);
                cthis->alarmUpTimer[alramUp->alarmUpIndex] = cthis->timer;      /* update timer for time out setup flag */
                cthis->alarmUpCounter[alramUp->alarmUpIndex]++;                 /* increase counter */
                if(cthis->alarmUpCounter[alramUp->alarmUpIndex]>=CLEAR_ALARMUP_COUNTING(alramUp->count)){
                    alramUp->count = CLEAR_ALARMUP_COUNTING(alramUp->count);
                    cthis->alarmUpFlag[uwGroupIndex] |= aGroupMask;             /* setup flag */
                    cthis->alarmUpUpdateCount(cthis, alramUp, ALRAM_COUNT_INC); /* update counter */
                }
            }
            if((cthis->timer-cthis->alarmUpTimer[alramUp->alarmUpIndex]) >= alramUp->time){
                cthis->alarmUpFlag[uwGroupIndex] |= aGroupMask;                 /* setup flag */
                cthis->alarmUpUpdateCount(cthis, alramUp, ALRAM_COUNT_INC);     /* update counter */
            }
        }else{
            if(IS_ALARMUP_COUNTING(alramUp->count)){
                alramUp->count = CLEAR_ALARMUP_COUNTING(alramUp->count);
                cthis->alarmUpTimer[alramUp->alarmUpIndex] = cthis->timer;      /* update timer for reset counter */
            }
            if(alramUp->decreaseTime                                            /* if decreaseTime is 0, do not decrease counter */
            &&(cthis->timer-cthis->alarmUpTimer[alramUp->alarmUpIndex]) >= alramUp->decreaseTime){
                if(cthis->alarmUpCounter[alramUp->alarmUpIndex]){
                    cthis->alarmUpTimer[alramUp->alarmUpIndex] = cthis->timer;  /* decrease for residue */
                    cthis->alarmUpCounter[alramUp->alarmUpIndex]--;             /* decrease counter */
                }
            }
        }
    }
}

/* Function : hCpnAlarm CpnAlarm_init(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   : hCpnAlarm - cthis/OOPC_NULL
 * Others   : CpnAlarm class initial function.
 **********************************************/
hCpnAlarm CpnAlarm_init(hCpnAlarm cthis){
    tsMemPointer tsMem;
    hCpnAlarm retVal = cthis;
    uint16 i = 0u, j = 0u;

    /* Configure functions. */
    //cthis->getAlarmCount = CpnAlarm_getAlarmCount;
    /* TODO */

    /* Configure parameters. */
    do{
        /* cthis->alarmClassifyEventMax */
        tsMem.indication = (cthis->alarmClassifyMax*(SERIOUS_MAX_COUNT+1u)*sizeof(uint16));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            retVal = OOPC_NULL;
            break;
        }
        cthis->alarmClassifyEventMax = tsMem.pointer;
        /* cthis->alarmClassifyCount */
        tsMem.indication = (cthis->alarmClassifyMax*(SERIOUS_MAX_COUNT+1u)*sizeof(uint16));
        SYN_TRIG(sig_trig_CpnAlarm_memMalloc, &tsMem);
        if(!tsMem.pointer){
            cthis->err(cthis,CPNALARMCFG_MEM_MALLOC_FAIL);
            retVal = OOPC_NULL;
            break;
        }
        cthis->alarmClassifyCount = tsMem.pointer;

        /* cthis->alarms */
        if(FALSE == cthis->dilatation(cthis)){
            retVal = OOPC_NULL;
            break;
        }
        /* cthis->alarmUps */
        if(FALSE == cthis->dilatationUp(cthis)){
            retVal = OOPC_NULL;
            break;
        }

        /* Initial paramters */
        /*for(i = 0; i < cthis->alarmClassifyMax; i++){
            cthis->alarmClassifyEventMax[i] = 0u;
            for(j = (i*(SERIOUS_MAX_COUNT+1u)); j < ((i+1u)*(SERIOUS_MAX_COUNT+1u)); j++){
                cthis->alarmClassifyCount[j] = 0u;
            }
        }*/
        for(i = 0; i < cthis->alarmClassifyMax; i++){
            for(j = (i*(SERIOUS_MAX_COUNT+1u)); j < ((i+1u)*(SERIOUS_MAX_COUNT+1u)); j++){
                cthis->alarmClassifyEventMax[j] = 0u;
                cthis->alarmClassifyCount[j] = 0u;
            }
        }
    }while(0);

    return retVal;
}

/* Function : hCpnAlarm CpnAlarm_ctor(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   : hCpnAlarm - cthis/OOPC_NULL
 * Others   : CpnAlarm class constructor.
 **********************************************/
CC(CpnAlarm){
    uint16 i = 0u;

    cthis->init = CpnAlarm_init;
    cthis->getAlarmMax = CpnAlarm_getAlarmMax;
    cthis->getAlarmCount = CpnAlarm_getAlarmCount;
    cthis->getAlarmEvents = CpnAlarm_getAlarmEvents;
    cthis->isAlarmed = CpnAlarm_isAlarmed;
    cthis->isUpgraded = CpnAlarm_isUpgraded;
    cthis->run = CpnAlarm_run;
    cthis->err = CpnAlarm_err;
    cthis->regist = CpnAlarm_regist;
    cthis->registUp = CpnAlarm_registUp;
    cthis->dilatation = CpnAlarm_dilatation;
    cthis->dilatationUp = CpnAlarm_dilatationUp;
    cthis->alarmSrcCheck = CpnAlarm_alarmSrcCheck;
    cthis->alarmCheckUpdate = CpnAlarm_alarmCheckUpdate;
    cthis->alarmUpdateCount = CpnAlarm_alarmUpdateCount;
    cthis->alarmUpCheckUpdate = CpnAlarm_alarmUpCheckUpdate;
    cthis->alarmUpUpdateCount = CpnAlarm_alarmUpUpdateCount;

    /* Configure parameters. */
    cthis->alarms = OOPC_NULL;
    cthis->alarmUps = OOPC_NULL;
    cthis->alarmFlag = OOPC_NULL;
    cthis->alarmUpMask = OOPC_NULL;
    cthis->alarmUpFlag = OOPC_NULL;
    cthis->buffEventMax = 0u;
    cthis->alarmClassifyMax = CLASS_MAX_COUNT;
    for(i = 0u; i < (SERIOUS_MAX_COUNT+1u); i++){
        cthis->alarmEventMax[i] = 0u;
    }
    cthis->alarmUpEventMax = 0u;
    for(i = 0u; i < (SERIOUS_MAX_COUNT+1u); i++){
        cthis->alarmCount[i] = 0u;
    }
    cthis->alarmClassifyEventMax = OOPC_NULL;
    cthis->alarmClassifyCount = OOPC_NULL;
    /* schedular parameters. */
    cthis->timer = 0u;
    cthis->alarmTimer = OOPC_NULL;
    cthis->alarmUpTimer = OOPC_NULL;
    cthis->alarmUpCounter = OOPC_NULL;
    /* alarmed events. */
    cthis->alarmedEvents.eventNum = 0u;
    cthis->alarmedEvents.events = OOPC_NULL;
    cthis->alarmedEvents.upgradeNum = 0u;
    cthis->alarmedEvents.upgrades = OOPC_NULL;

    return cthis;
}

/* Function : hCpnAlarm CpnAlarm_dtor(hCpnAlarm cthis)
 * Input    : cthis - CpnAlarm class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnAlarm class destructor.
 **********************************************/
CD(CpnAlarm){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
