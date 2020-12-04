/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : RteAsyn.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/21 11:57:29
* Description  : RteAsyn������ܺ�������Դ�ļ�
* Others       : 
* History      : 191221 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./RteAsyn.h"

/***********************************************************
* RteAsyn�ඨ��
***********************************************************/
/*���� : RteAsyn_set(hRteAsyn cthis)
* ���� : cthis - RteAsyn��ָ��
* ��� : ��
* ���� : RteAsyn�๦�ܺ���
***********************************************/
void RteAsyn_set(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len){
    uint8 *dest = ((uint8*)cthis->set_buff + cthis->set_index[signal]);
    uint8 *source = buff + len;
    uint16 i = len;
    while(i-- > 0){
        dest--;
        source--;
        *dest = *source;
    }
}

/*���� : RteAsyn_get(hRteAsyn cthis)
* ���� : cthis - RteAsyn��ָ��
* ��� : ��
* ���� : RteAsyn�๦�ܺ���
***********************************************/
void RteAsyn_get(hRteAsyn cthis, uint16 signal, uint8 *buff, uint16 len){
    uint8 *dest = buff + len;
    uint8 *source = ((uint8*)cthis->set_buff + cthis->set_index[cthis->get_index[signal]]);
    uint16 i = len;
    while(i-- > 0){
        dest--;
        source--;
        *dest = *source;
    }
}

/*���� : hRteAsyn RteAsyn_init(hRteAsyn cthis)
* ���� : cthis - RteAsyn��ָ��
* ��� : hRteAsyn - cthis/OOPC_NULL
* ���� : RteAsyn���ʼ������
***********************************************/
hRteAsyn RteAsyn_init(hRteAsyn cthis, uint8 *set_buff, uint16 *set_index, uint16 *get_index){
    // ���ܺ�������
    //cthis->set_data = RteAsyn_set_data;
    //TODO

    // ��������
    cthis->set_buff = set_buff;
    cthis->set_index = set_index;
    cthis->get_index = get_index;

    return cthis;
}

/*���� : hRteAsyn RteAsyn_ctor(hRteAsyn cthis)
* ���� : cthis - RteAsyn��ָ��
* ��� : hRteAsyn - cthis/OOPC_NULL
* ���� : RteAsyn�๹�캯��
***********************************************/
CC(RteAsyn){
    cthis->init = RteAsyn_init;
    cthis->set = RteAsyn_set;
    cthis->get = RteAsyn_get;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hRteAsyn RteAsyn_dtor(hRteAsyn cthis)
* ���� : cthis - RteAsyn��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : RteAsyn����������
***********************************************/
CD(RteAsyn){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
