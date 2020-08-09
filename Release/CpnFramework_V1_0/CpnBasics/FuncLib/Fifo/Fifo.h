/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Fifo.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:31:48
* Description  : Fifo�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

/*ͷ�ļ�����*/
#include "../../standType/standType.h"
#include "../../oopc/oopc.h"

/***********************************************************
* �汾����
***********************************************************/
#define FIFO_CLASS_VERSION        0xC00D00    // C����v��D����.����ǰ�汾v1.00


/***********************************************************
* �ӿڶ���
***********************************************************/
/*�ӿ�����
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* Fifo�ඨ��
***********************************************************/
/*Fifo������
***********************************************/
CL(Fifo){
    hFifo self;
    hFifo (*init)(hFifo cthis, void *listBuffer, uint16 listBuffSize, uint16 fifoObjSize);

    // Fifo�����
    uint8 *listBuffer;                                         // ���������ʼ��ַ
    uint16 listBuffSize;                                       // ��������ܴ�С
    uint16 fifoObjSize;                                        // ������еĻ�������С

    uint16 saveObjMaxLen;                                      // ������л��滺������������
    uint16 currLen;                                            // ��������ѻ��滺��������
    uint16 top;                                                // ���»����������Ĵ��λ��
    uint16 bottom;                                             // ��һ�������������Ĵ��λ��

    // Fifo�๦�ܺ���
    uint16 (*push)(hFifo t, void *data);                       // ����
    uint16 (*pop)(hFifo t, void *data);                        // ����������ݳ���
    uint16 (*fout)(hFifo t, void *data);                       // �����������ݳ��У�first out
    uint16 (*del)(hFifo t, void *data, void *fifoObjTempBuff); // ɾ�������е�ĳ�����ݣ�Ϊɾ��������Ҫ�ṩһ��������ʱ������FifoObjTempBuff
    uint16 (*isFull)(hFifo t);                                 // �����Ƿ�������TRUE/FALSE
    uint16 (*isEmpty)(hFifo t);                                // �����Ƿ�Ϊ�գ�TRUE/FALSE
    uint16 (*clearAll)(hFifo t);                               // ���������ȫ�����ݣ�TRUE/FALSE
};

#endif /*FIFO_H_*/

/**************************** Copyright(C) pxf ****************************/
