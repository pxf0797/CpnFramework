/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnCan.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 16:09:24
* Description  : CpnCan������ܺ�������Դ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnCan.h"
#include "../../CpnRte/RteSigs/RteSigs.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
Fifo clFifoCpnCan;
static tDataSig dataBUff[CPNCAN_FIFO_BUFF_LENGTH];

/***********************************************************
* CpnCan�ඨ��
***********************************************************/
/*���� : CpnCan_run(hCpnCan cthis)
* ���� : cthis - CpnCan��ָ��
* ��� : ��
* ���� : CpnCan�๦�ܺ���
***********************************************/
void CpnCan_run(hCpnCan cthis){
    cthis->send(cthis);
}

/*���� : CpnCan_send(hCpnCan cthis)
* ���� : cthis - CpnCan��ָ��
* ��� : ��
* ���� : CpnCan�๦�ܺ���
***********************************************/
void CpnCan_send(hCpnCan cthis){
    tDataSig sendData;
    if(cthis->clFifoSend->fout(cthis->clFifoSend,&sendData)){
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnCan_sendSig, (uint8*)&sendData);
    }
}

/*���� : CpnCan_receive(hCpnCan cthis)
* ���� : cthis - CpnCan��ָ��
* ��� : ��
* ���� : CpnCan�๦�ܺ���
***********************************************/
void CpnCan_receive(hCpnCan cthis){
    //TODO
}

/*���� : hCpnCan CpnCan_init(hCpnCan cthis)
* ���� : cthis - CpnCan��ָ��
* ��� : hCpnCan - cthis/OOPC_NULL
* ���� : CpnCan���ʼ������
***********************************************/
hCpnCan CpnCan_init(hCpnCan cthis, hFifo clFifoSend){
    // ���ܺ�������
    //cthis->run = CpnCan_run;
    //TODO

    // ��������
    cthis->clFifoSend = clFifoSend;

    return cthis;
}

/*���� : hCpnCan CpnCan_ctor(hCpnCan cthis)
* ���� : cthis - CpnCan��ָ��
* ��� : hCpnCan - cthis/OOPC_NULL
* ���� : CpnCan�๹�캯��
***********************************************/
CC(CpnCan){
    cthis->init = CpnCan_init;
    cthis->run = CpnCan_run;
    cthis->send = CpnCan_send;
    cthis->receive = CpnCan_receive;
    //TODO

    // ��������
    //TODO

    CN(Fifo, &clFifoCpnCan, dataBUff, sizeof(dataBUff), sizeof(tDataSig));
    if(OPRS(clFifoCpnCan) == OOPC_NULL){
        return OOPC_NULL;
    }

    return cthis;
}

/*���� : hCpnCan CpnCan_dtor(hCpnCan cthis)
* ���� : cthis - CpnCan��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : CpnCan����������
***********************************************/
CD(CpnCan){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
