/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnSource.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:32:56
 * Description  : CpnSource class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnSource.h"
#include "RteSigs.h"
#include "FuncLib.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * CpnSource class definition.
 **********************************************************/
/* Function : CpnSource_register(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_regist(hCpnSource cthis, htSourceParams source){
    uint16 i = 0u;
    sourceType curMask = 0u;
    uint16 curIndex = 0u;

    /* Judge whether wave goroup is full. */
    curMask = cthis->waveGroups[CPNSOURCECFG_WAVE_TYPE_GROUPS-1].sourceMask;
    if((curMask+1u)==0u){
        cthis->err(cthis, CPNSOURCECFG_WAVE_GROUP_FULL);
        return;
    }
    /* Regist wave group. */
    for(i = 0u; i < CPNSOURCECFG_WAVE_TYPE_GROUPS; i++){
        curMask = cthis->waveGroups[i].sourceMask;
        if((curMask+1u)!=0u){
            curMask = (~curMask);
            curMask = MASK_FIRST_BIT(curMask);
            cthis->waveGroups[i].sourceMask |= curMask;
            curIndex = log_2n((uint32)curMask);
            source->type_index = (CPNSOURCE_TYPE_WIDTH*i+curIndex);

            /* Config parameters. */
            cthis->waveGroups[i].sourceParams[curIndex].type = source->type;
            cthis->waveGroups[i].sourceParams[curIndex].trig_sig = source->trig_sig;
            cthis->waveGroups[i].sourceParams[curIndex].type_index = source->type_index;
            cthis->waveGroups[i].sourceParams[curIndex].amplitude = source->amplitude;
            cthis->waveGroups[i].sourceParams[curIndex].step = source->step;
            cthis->waveGroups[i].sourceParams[curIndex].period = source->period;
            if(source->duty <= 1000u){
                cthis->waveGroups[i].sourceParams[curIndex].duty = source->duty;
            }else{
                cthis->waveGroups[i].sourceParams[curIndex].duty = 0u;
                cthis->err(cthis, CPNSOURCECFG_WAVE_DUTY_OUT_RANGE);
            }
            if(source->phase <= 3600u){
                cthis->waveGroups[i].sourceParams[curIndex].phase = source->phase;
            }else{
                cthis->waveGroups[i].sourceParams[curIndex].phase = 0u;
                cthis->err(cthis, CPNSOURCECFG_WAVE_PHASE_OUT_RANGE);
            }
            cthis->waveGroups[i].sourceCounter[curIndex] = (uint16)(((uint32)source->phase)*source->period/3600u);
        }
    }
}

/* Function : CpnSource_change(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_change(hCpnSource cthis, htSourceParams source){
    uint16 curGroup = 0u;
    uint16 curIndex = 0u;

    curGroup = (source->type_index>>CPNSOURCE_TYPE_BITS);
    curIndex = (source->type_index&CPNSOURCE_TYPE_MASK);
    /* Out of range, report error. */
    if(curGroup >= CPNSOURCECFG_WAVE_TYPE_GROUPS){
        cthis->err(cthis, CPNSOURCECFG_WAVE_INDEX_OUT_RANGE);
        return;
    }
    /* Not exist, report error. */
    if(!(((cthis->waveGroups[curGroup].sourceMask)>>curIndex)&0x0001u)){
        cthis->err(cthis, CPNSOURCECFG_WAVE_INDEX_NOT_EXIST);
        return;
    }

    /* Modify parameters. */
    //cthis->waveGroups[curGroup].sourceParams[curIndex].type = source->type;
    //cthis->waveGroups[curGroup].sourceParams[curIndex].serv_sig = source->serv_sig;
    //cthis->waveGroups[curGroup].sourceParams[curIndex].type_index = source->type_index;
    cthis->waveGroups[curGroup].sourceParams[curIndex].amplitude = source->amplitude;
    cthis->waveGroups[curGroup].sourceParams[curIndex].step = source->step;
    cthis->waveGroups[curGroup].sourceParams[curIndex].period = source->period;
    if(source->duty <= 1000u){
        cthis->waveGroups[curGroup].sourceParams[curIndex].duty = source->duty;
    }else{
        cthis->waveGroups[curGroup].sourceParams[curIndex].duty = 0u;
        cthis->err(cthis, CPNSOURCECFG_WAVE_DUTY_OUT_RANGE);
    }
    if(source->phase <= 3600u){
        cthis->waveGroups[curGroup].sourceParams[curIndex].phase = source->phase;
    }else{
        cthis->waveGroups[curGroup].sourceParams[curIndex].phase = 0u;
        cthis->err(cthis, CPNSOURCECFG_WAVE_PHASE_OUT_RANGE);
    }
    cthis->waveGroups[curGroup].sourceCounter[curIndex] = (uint16)(((uint32)source->phase)*source->period/3600u);
}

/* Function : CpnSource_free(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_free(hCpnSource cthis, htSourceParams source){
    uint16 curGroup = 0u;
    uint16 curIndex = 0u;
    sourceType curMask = 0u;

    curGroup = (source->type_index>>CPNSOURCE_TYPE_BITS);
    curIndex = (source->type_index&CPNSOURCE_TYPE_MASK);
    curMask = ((sourceType)1u<<curIndex);
    /* Out of range, report error. */
    if(curGroup >= CPNSOURCECFG_WAVE_TYPE_GROUPS){
        cthis->err(cthis, CPNSOURCECFG_WAVE_INDEX_OUT_RANGE);
        return;
    }
    /* Not exist, report error. */
    curMask &= cthis->waveGroups[curGroup].sourceMask;
    if(!curMask){
        cthis->err(cthis, CPNSOURCECFG_WAVE_INDEX_NOT_EXIST);
        return;
    }

    /* Free group mask. */
    cthis->waveGroups[curGroup].sourceMask &= (~curMask);
}


/* Function : CpnSource_sine(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_sine(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 input = 0u;
    float32 output = 0u;

    input = counter*2*PI/source->period;
    output = SineTable(input);
    output *= source->amplitude;
    cthis->wave(cthis, source, &output);
}

/* Function : CpnSource_pulse(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_pulse(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0u;
    uint16 high = 0u;

    high = (uint16)(((uint32)source->duty * source->period)/1000u);
    if(counter < high){
        output = source->amplitude;
    }
    cthis->wave(cthis, source, &output);
}

/* Function : CpnSource_countUp(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_countUp(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0u;

    output = (source->amplitude*counter/source->period);
    cthis->wave(cthis, source, &output);
}

/* Function : CpnSource_countDown(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_countDown(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0u;

    output = (source->amplitude*(source->period-counter)/source->period);
    cthis->wave(cthis, source, &output);
}

/* Function : CpnSource_countUpDown(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_countUpDown(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0u;

    if(counter < (source->period>>1u)){
        output = (source->amplitude*counter*2/source->period);
    }else{
        output = (source->amplitude*(source->period-counter)*2/source->period);
    }
    cthis->wave(cthis, source, &output);
}

/* Function : CpnSource_wave(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_wave(hCpnSource cthis, htSourceParams source, float32 *output){
    SYN_TRIG(source->trig_sig, output);
}

/* Function : CpnSource_run(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_run(hCpnSource cthis){
    uint16 i = 0u;
    sourceType groupMask = 0u;
    sourceType curMask = 0u;
    uint16 curIndex = 0u;

    for(i = 0u; i < CPNSOURCECFG_WAVE_TYPE_GROUPS; i++){
        groupMask = cthis->waveGroups[i].sourceMask;
        while(groupMask){
            curMask = MASK_FIRST_BIT(groupMask);
            groupMask &= (~curMask);
            curIndex = log_2n((uint32)curMask);
            /* update counter. */
            if(++cthis->waveGroups[i].sourceCounter[curIndex] >= cthis->waveGroups[i].sourceParams[curIndex].period){
                cthis->waveGroups[i].sourceCounter[curIndex] = 0u;
            }
            if((cthis->waveGroups[i].sourceParams[curIndex].step)&&(cthis->waveGroups[i].sourceCounter[curIndex])){
                if((cthis->waveGroups[i].sourceCounter[curIndex]%cthis->waveGroups[i].sourceParams[curIndex].step)){
                    continue;
                }
            }

            /* output wave. */
            switch (cthis->waveGroups[i].sourceParams[curIndex].type)
            {
            case w_sine:
                cthis->sine(cthis, &cthis->waveGroups[i].sourceParams[curIndex], cthis->waveGroups[i].sourceCounter[curIndex]);
                break;
            case w_pluse:
                cthis->pulse(cthis, &cthis->waveGroups[i].sourceParams[curIndex], cthis->waveGroups[i].sourceCounter[curIndex]);
                break;
            case w_countUp:
                cthis->countUp(cthis, &cthis->waveGroups[i].sourceParams[curIndex], cthis->waveGroups[i].sourceCounter[curIndex]);
                break;
            case w_countDown:
                cthis->countDown(cthis, &cthis->waveGroups[i].sourceParams[curIndex], cthis->waveGroups[i].sourceCounter[curIndex]);
                break;
            case w_countUpDown:
                cthis->countUpDown(cthis, &cthis->waveGroups[i].sourceParams[curIndex], cthis->waveGroups[i].sourceCounter[curIndex]);
                break;
            default:
                cthis->err(cthis, CPNSOURCECFG_WAVE_NO_SUCH_KIND);
                break;
            }
        }
    }
}

/* Function : CpnSource_err(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   :
 * Others   : CpnSource class function.
 **********************************************/
void CpnSource_err(hCpnSource cthis, uint16 code){
    tsErrCode errCode;
    errCode.code = code;
    errCode.id = CPNSOURCECFG_ERR_ID;
    SYN_TRIG(sig_trig_CpnSource_setErr, &errCode);
}

/* Function : hCpnSource CpnSource_init(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   : hCpnSource - cthis/OOPC_NULL
 * Others   : CpnSource class initial function.
 **********************************************/
hCpnSource CpnSource_init(hCpnSource cthis){
    /* Configure functions. */
    // cthis->iErr.setErr = setErr;

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnSource CpnSource_ctor(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   : hCpnSource - cthis/OOPC_NULL
 * Others   : CpnSource class constructor.
 **********************************************/
CC(CpnSource){
    cthis->init = CpnSource_init;
    cthis->regist = CpnSource_regist;
    cthis->change = CpnSource_change;
    cthis->sine = CpnSource_sine;
    cthis->pulse = CpnSource_pulse;
    cthis->countUp = CpnSource_countUp;
    cthis->countDown = CpnSource_countDown;
    cthis->countUpDown = CpnSource_countUpDown;
    cthis->wave = CpnSource_wave;
    cthis->run = CpnSource_run;
    cthis->err = CpnSource_err;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCpnSource CpnSource_dtor(hCpnSource cthis)
 * Input    : cthis - CpnSource class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnSource class destructor.
 **********************************************/
CD(CpnSource){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
