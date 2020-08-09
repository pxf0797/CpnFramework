/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSource.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  : CpnSource������ܺ�������Դ�ļ�
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnSource.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./SineTable.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnSource�ඨ��
***********************************************************/
/*���� : CpnSource_regist(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_regist(hCpnSource cthis, htSourceParams source){
    uint16 i = 0;
    uint16 curMask = 0;
    uint16 curIndex = 0;

    curMask = cthis->waveGroups[source->type][CPNSOURCECFG_WAVE_TYPE_GROUPS-1].sourceMask;
    if((curMask+1)==0){
        cthis->err(cthis, CPNSOURCECFG_WAVE_GROUP_FULL);
        return;
    }
    for(i = 0; i < CPNSOURCECFG_WAVE_TYPE_GROUPS; i++){
        curMask = cthis->waveGroups[source->type][i].sourceMask;
        if((curMask+1)!=0){
            curMask = (~curMask);
            curMask = (curMask & (-curMask));
            cthis->waveGroups[source->type][i].sourceMask |= curMask;
            curIndex = log_2n((uint32)curMask);
            source->type_index = (16*i+curIndex);

            cthis->waveGroups[source->type][i].sourceParams[curIndex].type = source->type;
            cthis->waveGroups[source->type][i].sourceParams[curIndex].trig_sig = source->trig_sig;
            cthis->waveGroups[source->type][i].sourceParams[curIndex].type_index = source->type_index;
            cthis->waveGroups[source->type][i].sourceParams[curIndex].amplitude = source->amplitude;
            cthis->waveGroups[source->type][i].sourceParams[curIndex].step = source->step;
            cthis->waveGroups[source->type][i].sourceParams[curIndex].period = source->period;
            if(source->duty <= 1000){
                cthis->waveGroups[source->type][i].sourceParams[curIndex].duty = source->duty;
            }else{
                cthis->err(cthis, CPNSOURCECFG_WAVE_DUTY_OUT_RANGE);
            }
            if(source->phase <= 3600){
                cthis->waveGroups[source->type][i].sourceParams[curIndex].phase = source->phase;
            }else{
                cthis->err(cthis, CPNSOURCECFG_WAVE_PHASE_OUT_RANGE);
            }
            cthis->waveGroups[source->type][i].sourceCounter[curIndex] = 0;
        }
    }
}

/*���� : CpnSource_change(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_change(hCpnSource cthis, htSourceParams source){
    uint16 curGroup = 0;
    uint16 curIndex = 0;

    curGroup = source->type_index>>4;
    curIndex = source->type_index&0x000FU;
    if(curGroup >= CPNSOURCECFG_WAVE_TYPE_GROUPS){
        cthis->err(cthis, CPNSOURCECFG_WAVE_INDEX_OUT_RANGE);
        return;
    }
    if(!(((cthis->waveGroups[source->type][curGroup].sourceMask)>>curIndex)&0x0001U)){
        cthis->err(cthis, CPNSOURCECFG_WAVE_INDEX_NOT_EXIST);
        return;
    }

    //cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].type = source->type;
    //cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].serv_sig = source->serv_sig;
    //cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].type_index = source->type_index;
    cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].amplitude = source->amplitude;
    cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].step = source->step;
    cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].period = source->period;
    if(source->duty <= 1000){
        cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].duty = source->duty;
    }else{
        cthis->err(cthis, CPNSOURCECFG_WAVE_DUTY_OUT_RANGE);
    }
    if(source->phase <= 3600){
        cthis->waveGroups[source->type][curGroup].sourceParams[curIndex].phase = source->phase;
    }else{
        cthis->err(cthis, CPNSOURCECFG_WAVE_PHASE_OUT_RANGE);
    }
    cthis->waveGroups[source->type][curGroup].sourceCounter[curIndex] = (uint16)(((uint32)source->phase)*source->period/3600);
}

/*���� : CpnSource_sine(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_sine(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 input = 0;
    float32 output = 0;

    input = counter*2*PI/source->period;
    output = SineTable(input);
    output *= source->amplitude;
    cthis->wave(cthis, source, &output);
}

/*���� : CpnSource_pulse(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_pulse(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0;
    uint16 high = 0;

    high = (uint16)(((uint32)source->duty * source->period)/1000);
    if(counter < high){
        output = source->amplitude;
    }
    cthis->wave(cthis, source, &output);
}

/*���� : CpnSource_countUp(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_countUp(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0;

    output = source->amplitude*counter/source->period;
    cthis->wave(cthis, source, &output);
}

/*���� : CpnSource_countDown(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_countDown(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0;

    output = source->amplitude*(source->period-counter)/source->period;
    cthis->wave(cthis, source, &output);
}

/*���� : CpnSource_countUpDown(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_countUpDown(hCpnSource cthis, htSourceParams source, uint16 counter){
    float32 output = 0;

    if(counter < (source->period>>1)){
        output = source->amplitude*counter*2/source->period;
    }else{
        output = source->amplitude*(source->period-counter)*2/source->period;
    }

    cthis->wave(cthis, source, &output);
}

/*���� : CpnSource_wave(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_wave(hCpnSource cthis, htSourceParams source, float32 *output){
    clRteSynSigs.trig(clRteSynSigs.self, source->trig_sig, (uint8*)output);
}

/*���� : CpnSource_run(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_run(hCpnSource cthis){
    uint16 i = 0, j = 0;
    uint16 groupMask = 0;
    uint16 curMask = 0;
    uint16 curIndex = 0;

    for(i = 0; i < w_waveTypeMax; i++){
        for(j = 0; j < CPNSOURCECFG_WAVE_TYPE_GROUPS; j++){
            groupMask = cthis->waveGroups[i][j].sourceMask;
            while(groupMask){
                curMask = (groupMask & (-groupMask));
                groupMask &= (~curMask);
                curIndex = log_2n((uint32)curMask);
                if(++cthis->waveGroups[i][j].sourceCounter[curIndex] >= cthis->waveGroups[i][j].sourceParams[curIndex].period){
                    cthis->waveGroups[i][j].sourceCounter[curIndex] = 0;
                }
                if((cthis->waveGroups[i][j].sourceParams->step)&&(cthis->waveGroups[i][j].sourceCounter[curIndex])){
                    if((cthis->waveGroups[i][j].sourceCounter[curIndex]%cthis->waveGroups[i][j].sourceParams->step)){
                        continue;
                    }
                }

                if(i == w_sine){
                    cthis->sine(cthis, &cthis->waveGroups[i][j].sourceParams[curIndex], cthis->waveGroups[i][j].sourceCounter[curIndex]);
                }else if(i == w_pluse){
                    cthis->pulse(cthis, &cthis->waveGroups[i][j].sourceParams[curIndex], cthis->waveGroups[i][j].sourceCounter[curIndex]);
                }else if(i == w_countUp){
                    cthis->countUp(cthis, &cthis->waveGroups[i][j].sourceParams[curIndex], cthis->waveGroups[i][j].sourceCounter[curIndex]);
                }else if(i == w_countDown){
                    cthis->countDown(cthis, &cthis->waveGroups[i][j].sourceParams[curIndex], cthis->waveGroups[i][j].sourceCounter[curIndex]);
                }else if(i == w_countUpDown){
                    cthis->countUpDown(cthis, &cthis->waveGroups[i][j].sourceParams[curIndex], cthis->waveGroups[i][j].sourceCounter[curIndex]);
                }else{
                    cthis->err(cthis, CPNSOURCECFG_WAVE_NO_SUCH_KIND);
                }
            }
        }
    }
}

/*���� : CpnSource_err(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : ��
* ���� : CpnSource�๦�ܺ���
***********************************************/
void CpnSource_err(hCpnSource cthis, uint16 code){
    cthis->iErr.setErr(CPNSOURCECFG_ERR_ID, code);
}

/*���� : hCpnSource CpnSource_init(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : hCpnSource - cthis/OOPC_NULL
* ���� : CpnSource���ʼ������
***********************************************/
hCpnSource CpnSource_init(hCpnSource cthis, void (*setErr)(uint16 id, uint16 code)){
    // ���ܺ�������
    cthis->iErr.setErr = setErr;

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnSource CpnSource_ctor(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : hCpnSource - cthis/OOPC_NULL
* ���� : CpnSource�๹�캯��
***********************************************/
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
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCpnSource CpnSource_dtor(hCpnSource cthis)
* ���� : cthis - CpnSource��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnSource����������
***********************************************/
CD(CpnSource){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
