/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : MatrixId.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/23 13:40:26
* Description  : MatrixId类各功能函数定义源文件
* Others       :
* History      : 201123 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./MatrixId.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* MatrixId类定义
***********************************************************/
/*名称 : MatrixId_getIdIndex(hMatrixId cthis)
* 输入 : cthis - MatrixId类指针
* 输出 : 无
* 其他 : MatrixId类功能函数
***********************************************/
uint16 MatrixId_getIdIndex(hMatrixId cthis, uint32 ulMatrixId){
    /* bin search id index */
    uint16 low = 0, mid = 0, high = 0;
    uint16 idIndex = cthis->ulMatrixIdNum;

    high = cthis->ulMatrixIdNum-1;
    while(low <= high){
        mid = ((low+high)>>1U);    /* 奇数，无论奇偶，有个值就行 */
        if(ulMatrixId < cthis->ulMatrixId[mid]){
            if(mid == 0){
                break;
            }
            high = (mid-1U);       /* 是mid-1，因为mid已经比较过了 */
        }else if(ulMatrixId > cthis->ulMatrixId[mid]){
            low = (mid+1U);
        }else{
            idIndex = cthis->uwMatrixIdIndex[mid];
            break;
        }
    }

    return idIndex;
}

/*名称 : hMatrixId MatrixId_init(hMatrixId cthis)
* 输入 : cthis - MatrixId类指针
* 输出 : hMatrixId - cthis/OOPC_NULL
* 其他 : MatrixId类初始化函数
***********************************************/
hMatrixId MatrixId_init(hMatrixId cthis, FrameMatrix matrixDatas[], uint32 ulMatrixId[], uint16 uwMatrixIdIndex[], uint16 ulMatrixIdNum){
    uint16 i = 0;
    uint16 j = 0;

    // 功能函数配置
    //cthis->getIdIndex = MatrixId_getIdIndex;
    //TODO

    // 参数配置
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

/*名称 : hMatrixId MatrixId_ctor(hMatrixId cthis)
* 输入 : cthis - MatrixId类指针
* 输出 : hMatrixId - cthis/OOPC_NULL
* 其他 : MatrixId类构造函数
***********************************************/
CC(MatrixId){
    cthis->init = MatrixId_init;
    cthis->getIdIndex = MatrixId_getIdIndex;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hMatrixId MatrixId_dtor(hMatrixId cthis)
* 输入 : cthis - MatrixId类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : MatrixId类析构函数
***********************************************/
CD(MatrixId){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
