/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErr.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  : CpnErr������ܺ�������Դ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnErr.h"
//#include "../RteSigs/RteSigs.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
Fifo clFifoCpnErr;
static uint32 ulErrCodeBuff[CPNERR_FIFO_BUFF_LENGTH];

/***********************************************************
* CpnErr�ඨ��
***********************************************************/
/*���� : CpnErr_run(hCpnErr cthis)
* ���� : cthis - CpnErr��ָ��
* ��� : ��
* ���� : CpnErr�๦�ܺ���
***********************************************/
void CpnErr_run(hCpnErr cthis){
    tErrCode code;
    if(cthis->clFifo->fout(cthis->clFifo, &code)){
        cthis->uwTotalErrNum++;
    }
}

/*���� : CpnErr_setErr(hCpnErr cthis)
* ���� : cthis - CpnErr��ָ��
* ��� : ��
* ���� : CpnErr�๦�ܺ���
***********************************************/
uint16 CpnErr_setErr(hCpnErr cthis, uint32 errCode){
    return cthis->clFifo->push(cthis->clFifo, &errCode);
}

/*���� : hCpnErr CpnErr_init(hCpnErr cthis)
* ���� : cthis - CpnErr��ָ��
* ��� : hCpnErr - cthis/OOPC_NULL
* ���� : CpnErr���ʼ������
***********************************************/
hCpnErr CpnErr_init(hCpnErr cthis, hFifo clFifo){
    // ���ܺ�������
    //cthis->run = CpnErr_run;
    //TODO

    // ��������
    cthis->uwTotalErrNum = 0;
    cthis->clFifo = clFifo;

    return cthis;
}

/*���� : hCpnErr CpnErr_ctor(hCpnErr cthis)
* ���� : cthis - CpnErr��ָ��
* ��� : hCpnErr - cthis/OOPC_NULL
* ���� : CpnErr�๹�캯��
***********************************************/
CC(CpnErr){
    cthis->init = CpnErr_init;
    cthis->run = CpnErr_run;
    cthis->setErr = CpnErr_setErr;
    //TODO

    // ��������
    //TODO

    CN(Fifo, &clFifoCpnErr, ulErrCodeBuff, sizeof(ulErrCodeBuff), sizeof(uint32));
    if(OPRS(clFifoCpnErr) == OOPC_NULL){
        return OOPC_NULL;
    }

    return cthis;
}

/*���� : hCpnErr CpnErr_dtor(hCpnErr cthis)
* ���� : cthis - CpnErr��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnErr����������
***********************************************/
CD(CpnErr){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
