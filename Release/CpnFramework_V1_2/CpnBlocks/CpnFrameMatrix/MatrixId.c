/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : MatrixId.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/23 13:40:26
* Description  : MatrixId������ܺ�������Դ�ļ�
* Others       :
* History      : 201123 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./MatrixId.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* MatrixId�ඨ��
***********************************************************/
/*���� : MatrixId_getIdIndex(hMatrixId cthis)
* ���� : cthis - MatrixId��ָ��
* ��� : ��
* ���� : MatrixId�๦�ܺ���
***********************************************/
uint16 MatrixId_getIdIndex(hMatrixId cthis, uint32 ulMatrixId){
    /* bin search id index */
    uint16 low = 0, mid = 0, high = 0;
    uint16 idIndex = cthis->ulMatrixIdNum;

    high = cthis->ulMatrixIdNum-1;
    while(low <= high){
        mid = ((low+high)>>1U);    /* ������������ż���и�ֵ���� */
        if(ulMatrixId < cthis->ulMatrixId[mid]){
            if(mid == 0){
                break;
            }
            high = (mid-1U);       /* ��mid-1����Ϊmid�Ѿ��ȽϹ��� */
        }else if(ulMatrixId > cthis->ulMatrixId[mid]){
            low = (mid+1U);
        }else{
            idIndex = cthis->uwMatrixIdIndex[mid];
            break;
        }
    }

    return idIndex;
}

/*���� : hMatrixId MatrixId_init(hMatrixId cthis)
* ���� : cthis - MatrixId��ָ��
* ��� : hMatrixId - cthis/OOPC_NULL
* ���� : MatrixId���ʼ������
***********************************************/
hMatrixId MatrixId_init(hMatrixId cthis, FrameMatrix matrixDatas[], uint32 ulMatrixId[], uint16 uwMatrixIdIndex[], uint16 ulMatrixIdNum){
    uint16 i = 0;
    uint16 j = 0;

    // ���ܺ�������
    //cthis->getIdIndex = MatrixId_getIdIndex;
    //TODO

    // ��������
    cthis->ulMatrixId = ulMatrixId;
    cthis->uwMatrixIdIndex = uwMatrixIdIndex;
    cthis->ulMatrixIdNum = ulMatrixIdNum;

    /* insert sort ids */
    cthis->ulMatrixId[0] = matrixDatas[0].id;
    cthis->uwMatrixIdIndex[0] = 0U;
    for(i = 1U; i < cthis->ulMatrixIdNum; i++){
        j = i;
        while(j>0U){
            if(matrixDatas[i].id < cthis->ulMatrixId[j-1U]){
                cthis->ulMatrixId[j] = cthis->ulMatrixId[j-1U];
                cthis->uwMatrixIdIndex[j] = cthis->uwMatrixIdIndex[j-1U];
                cthis->ulMatrixId[j-1U] = matrixDatas[i].id;
                cthis->uwMatrixIdIndex[j-1U] = i;
            }else{
                cthis->ulMatrixId[j] = matrixDatas[i].id;
                cthis->uwMatrixIdIndex[j] = i;
                break;
            }
            j--;
        }
    }

    return cthis;
}

/*���� : hMatrixId MatrixId_ctor(hMatrixId cthis)
* ���� : cthis - MatrixId��ָ��
* ��� : hMatrixId - cthis/OOPC_NULL
* ���� : MatrixId�๹�캯��
***********************************************/
CC(MatrixId){
    cthis->init = MatrixId_init;
    cthis->getIdIndex = MatrixId_getIdIndex;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hMatrixId MatrixId_dtor(hMatrixId cthis)
* ���� : cthis - MatrixId��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : MatrixId����������
***********************************************/
CD(MatrixId){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
