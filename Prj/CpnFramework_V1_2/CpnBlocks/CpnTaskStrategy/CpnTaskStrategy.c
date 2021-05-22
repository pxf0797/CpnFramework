/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnTaskStrategy.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/18 11:34:48
* Description  : CpnTaskStrategy������ܺ�������Դ�ļ�
* Others       :
* History      : 201218 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnTaskStrategy.h"
#include "../../cpnRte/RteSigs/RteSigs.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* CpnTaskStrategy�ඨ��
***********************************************************/
/*���� : CpnTaskStrategy_updateStrategy(hCpnTaskStrategy cthis)
* ���� : cthis - CpnTaskStrategy��ָ��
* ��� : ��
* ���� : CpnTaskStrategy�๦�ܺ���
***********************************************/
void CpnTaskStrategy_updateStrategy(hCpnTaskStrategy cthis, strategy strgMask, uint16 addTime, uint16 delTime){
    cthis->strgMaskNew = strgMask;
    cthis->addTime = (addTime/CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD);
    cthis->delTime = (delTime/CPNTASKSTRATEGYCFG_TASK_EXECUTE_PRD);
    cthis->strgType = strategy_delay;
}

/*���� : CpnTaskStrategy_updateStrategyCond(hCpnTaskStrategy cthis)
* ���� : cthis - CpnTaskStrategy��ָ��
* ��� : ��
* ���� : CpnTaskStrategy�๦�ܺ���
***********************************************/
void CpnTaskStrategy_updateStrategyCond(hCpnTaskStrategy cthis, strategy strgMask, condition cond){
    cthis->strgMaskNew = strgMask;
    cthis->cond = cond;
    cthis->strgType = strategy_cond;
}

/*���� : CpnTaskStrategy_run(hCpnTaskStrategy cthis)
* ���� : cthis - CpnTaskStrategy��ָ��
* ��� : ��
* ���� : CpnTaskStrategy�๦�ܺ���
***********************************************/
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

/*���� : hCpnTaskStrategy CpnTaskStrategy_init(hCpnTaskStrategy cthis)
* ���� : cthis - CpnTaskStrategy��ָ��
* ��� : hCpnTaskStrategy - cthis/OOPC_NULL
* ���� : CpnTaskStrategy���ʼ������
***********************************************/
hCpnTaskStrategy CpnTaskStrategy_init(hCpnTaskStrategy cthis){
    // ���ܺ�������
    //cthis->updateStrategy = CpnTaskStrategy_updateStrategy;
    //TODO

    // ��������
    //TODO

    return cthis;
}

/*���� : hCpnTaskStrategy CpnTaskStrategy_ctor(hCpnTaskStrategy cthis)
* ���� : cthis - CpnTaskStrategy��ָ��
* ��� : hCpnTaskStrategy - cthis/OOPC_NULL
* ���� : CpnTaskStrategy�๹�캯��
***********************************************/
CC(CpnTaskStrategy){
    cthis->init = CpnTaskStrategy_init;
    cthis->updateStrategy = CpnTaskStrategy_updateStrategy;
    cthis->updateStrategyCond = CpnTaskStrategy_updateStrategyCond;
    cthis->run = CpnTaskStrategy_run;
    //TODO

    // ��������
    cthis->strgMask = DEFAULT_STRATEGY_TASK_GROUPS;
    cthis->strgMaskNew = DEFAULT_STRATEGY_TASK_GROUPS;
    cthis->strgType = strategy_delay;
    cthis->addTime = 0u;
    cthis->delTime = 0u;
    cthis->cond = OOPC_NULL;

    return cthis;
}

/*���� : hCpnTaskStrategy CpnTaskStrategy_dtor(hCpnTaskStrategy cthis)
* ���� : cthis - CpnTaskStrategy��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnTaskStrategy����������
***********************************************/
CD(CpnTaskStrategy){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
