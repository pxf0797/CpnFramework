/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteSyn.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/22 10:05:34
* Description  : RteSyn������ܺ�������Դ�ļ�
* Others       : 
* History      : 191222 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./RteSyn.h"
#include "./TriggerService.h"

/***********************************************************
* RteSyn�ඨ��
***********************************************************/
/*���� : RteSyn_serv(hRteSyn cthis)
* ���� : cthis - RteSyn��ָ��
* ��� : ��
* ���� : RteSyn�๦�ܺ���
***********************************************/
void RteSyn_serv(hRteSyn cthis, uint16 signal, uint8 *buff){
    void *func = cthis->serv_ServBuff[signal];
    if(func){
        if(buff){
            ((serv_param)func)(buff);
        }else{
            ((serv_void)func)();
        }
    }
}

/*���� : RteSyn_trig(hRteSyn cthis)
* ���� : cthis - RteSyn��ָ��
* ��� : ��
* ���� : RteSyn�๦�ܺ���
***********************************************/
void RteSyn_trig(hRteSyn cthis, uint16 signal, uint8 *buff){
    cthis->serv(cthis, cthis->trig_index[signal], buff);
}

/*���� : hRteSyn RteSyn_init(hRteSyn cthis)
* ���� : cthis - RteSyn��ָ��
* ��� : hRteSyn - cthis/OOPC_NULL
* ���� : RteSyn���ʼ������
***********************************************/
hRteSyn RteSyn_init(hRteSyn cthis, void **serv_ServBuff, uint16 *trig_index){
    // ���ܺ�������
    //cthis->serv = RteSyn_serv;
    //TODO

    // ��������
    cthis->serv_ServBuff = serv_ServBuff;
    cthis->trig_index = trig_index;

    return cthis;
}

/*���� : hRteSyn RteSyn_ctor(hRteSyn cthis)
* ���� : cthis - RteSyn��ָ��
* ��� : hRteSyn - cthis/OOPC_NULL
* ���� : RteSyn�๹�캯��
***********************************************/
CC(RteSyn){
    cthis->init = RteSyn_init;
    cthis->serv = RteSyn_serv;
    cthis->trig = RteSyn_trig;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hRteSyn RteSyn_dtor(hRteSyn cthis)
* ���� : cthis - RteSyn��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : RteSyn����������
***********************************************/
CD(RteSyn){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
