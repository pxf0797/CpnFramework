/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Fifo.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:31:48
* Description  : Fifo������ܺ�������Դ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./Fifo.h"

/***********************************************************
* Fifo�ඨ��
***********************************************************/
/*���� : Fifo_push(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : ��
* ���� : Fifo�๦�ܺ���
***********************************************/
static uint16 Fifo_push(hFifo t, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = NULL;
    uint16 i = 0;

    if(t->currLen < t->saveObjMaxLen){
        // ����洢λ�ò��洢
        desPtr = (t->listBuffer + (t->top * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }

        // ���±�־
        t->currLen++;
        t->top++;
        if (t->top >= t->saveObjMaxLen){
            t->top = 0;
        }

        rtv = TRUE;
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/*���� : Fifo_pop(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : ��
* ���� : Fifo�๦�ܺ���
***********************************************/
static uint16 Fifo_pop(hFifo t, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0;

    if (t->currLen > 0){
        // ���±�־
        t->currLen--;
        t->top--;
        if (t->top <= 0){
            t->top = (t->saveObjMaxLen - 1);
        }

        // ����洢λ�ò��洢
        srcPtr = (t->listBuffer + (t->top * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }

        rtv = TRUE;
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/*���� : Fifo_fout(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : ��
* ���� : Fifo�๦�ܺ���
***********************************************/
static uint16 Fifo_fout(hFifo t, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0;

    if (t->currLen > 0){
        // ����洢λ�ò��洢
        srcPtr = (t->listBuffer + (t->bottom * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }

        // ���±�־
        t->currLen--;
        t->bottom++;
        if (t->bottom >= t->saveObjMaxLen){
            t->bottom = 0;
        }

        rtv = TRUE;
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/*���� : Fifo_del(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : ��
* ���� : Fifo�๦�ܺ���
***********************************************/
static uint16 Fifo_del(hFifo t, void *data, void *fifoObjTempBuff){
    uint16 rtv = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = (uint8 *)fifoObjTempBuff;
    uint16 i = 0;
    uint16 j = t->currLen;
    uint16 lastMaxLen = t->currLen;

    if (t->currLen > 0){
        // ȫ���в������ݣ��ҵ���ɾ��
        for (j = t->currLen; j > 0; j--){
            // ��ȡ����
            if (TRUE == t->fout(t, fifoObjTempBuff)){
                // �ж������Ƿ���ͬ����ͬ��ɾ������ͬ���ض���
                srcPtr = (uint8 *)data;
                desPtr = (uint8 *)fifoObjTempBuff;
                for (i = 0; i < t->fifoObjSize; i++){
                    if (*desPtr++ != *srcPtr++){
                        break;
                    }
                }

                if (i < t->saveObjMaxLen){
                    // �ǲ������ݴ�ض���
                    if (TRUE != t->push(t, fifoObjTempBuff)){
                        rtv = FALSE;
                    }else{
                        rtv = TRUE;
                    }
                }else{
                    rtv = TRUE;
                }
            }else{
                rtv = FALSE;
            }

            if (FALSE == rtv){
                break;
            }
        }

        // �ж��Ƿ��ҵ���ɾ�����ݣ������ز������
        if ((TRUE == rtv) && (t->currLen < lastMaxLen)){
            rtv = TRUE;
        }else{
            rtv = FALSE;
        }
    }else{
        rtv = FALSE;
    }

    return rtv;
}

/*���� : Fifo_isFull(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : ��
* ���� : Fifo�๦�ܺ���
***********************************************/
static uint16 Fifo_isFull(hFifo t){
    uint16 retType = FALSE;

    if(t->currLen == t->saveObjMaxLen){
        retType = TRUE;
    }
    return retType;
}

/*���� : Fifo_isEmpty(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : ��
* ���� : Fifo�๦�ܺ���
***********************************************/
static uint16 Fifo_isEmpty(hFifo t){
    uint16 retType = TRUE;

    if(t->currLen){
        retType = FALSE;
    }
    return retType;
}

/*���� : Fifo_clearAll(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : ��
* ���� : Fifo�๦�ܺ���
***********************************************/
static uint16 Fifo_clearAll(hFifo t){
    uint16 retType = FALSE;

    if(t->currLen){
        t->currLen = 0;
        t->bottom = t->top;
        retType = TRUE;
    }
    return retType;
}

/*���� : hFifo Fifo_init(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : hFifo - cthis/OOPC_NULL
* ���� : Fifo���ʼ������
***********************************************/
static hFifo Fifo_init(hFifo cthis, void *listBuffer, uint16 listBuffSize, uint16 fifoObjSize){
    // ���ܺ�������
    //cthis->push = Fifo_push;
    //TODO

    // ��������
    cthis->listBuffer = (uint8 *)listBuffer;
    cthis->listBuffSize = listBuffSize;
    cthis->fifoObjSize = fifoObjSize;
    cthis->saveObjMaxLen = (cthis->listBuffSize / cthis->fifoObjSize);

    return cthis;
}

/*���� : hFifo Fifo_ctor(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : hFifo - cthis/OOPC_NULL
* ���� : Fifo�๹�캯��
***********************************************/
CC(Fifo){
    cthis->init = Fifo_init;
    cthis->push = Fifo_push;
    cthis->pop = Fifo_pop;
    cthis->fout = Fifo_fout;
    cthis->del = Fifo_del;
    cthis->isFull = Fifo_isFull;
    cthis->isEmpty = Fifo_isEmpty;
    cthis->clearAll = Fifo_clearAll;

    // ��������
    cthis->listBuffer = NULL;
    cthis->listBuffSize = 0;
    cthis->fifoObjSize = 0;

    cthis->saveObjMaxLen = 0;
    cthis->currLen = 0;
    cthis->top = 0;
    cthis->bottom = 0;

    return cthis;
}

/*���� : hFifo Fifo_dtor(hFifo cthis)
* ���� : cthis - Fifo��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : Fifo����������
***********************************************/
CD(Fifo){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
