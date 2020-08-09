/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Fifo.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:31:48
* Description  : Fifo类各功能函数定义源文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./Fifo.h"

/***********************************************************
* Fifo类定义
***********************************************************/
/*名称 : Fifo_push(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : 无
* 其他 : Fifo类功能函数
***********************************************/
static uint16 Fifo_push(hFifo t, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = NULL;
    uint16 i = 0;

    if(t->currLen < t->saveObjMaxLen){
        // 计算存储位置并存储
        desPtr = (t->listBuffer + (t->top * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }

        // 更新标志
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

/*名称 : Fifo_pop(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : 无
* 其他 : Fifo类功能函数
***********************************************/
static uint16 Fifo_pop(hFifo t, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0;

    if (t->currLen > 0){
        // 更新标志
        t->currLen--;
        t->top--;
        if (t->top <= 0){
            t->top = (t->saveObjMaxLen - 1);
        }

        // 计算存储位置并存储
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

/*名称 : Fifo_fout(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : 无
* 其他 : Fifo类功能函数
***********************************************/
static uint16 Fifo_fout(hFifo t, void *data){
    uint16 rtv = TRUE;
    uint8 *srcPtr = NULL;
    uint8 *desPtr = (uint8 *)data;
    uint16 i = 0;

    if (t->currLen > 0){
        // 计算存储位置并存储
        srcPtr = (t->listBuffer + (t->bottom * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++){
            *desPtr++ = *srcPtr++;
        }

        // 更新标志
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

/*名称 : Fifo_del(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : 无
* 其他 : Fifo类功能函数
***********************************************/
static uint16 Fifo_del(hFifo t, void *data, void *fifoObjTempBuff){
    uint16 rtv = TRUE;
    uint8 *srcPtr = (uint8 *)data;
    uint8 *desPtr = (uint8 *)fifoObjTempBuff;
    uint16 i = 0;
    uint16 j = t->currLen;
    uint16 lastMaxLen = t->currLen;

    if (t->currLen > 0){
        // 全队列查找数据，找到就删除
        for (j = t->currLen; j > 0; j--){
            // 读取数据
            if (TRUE == t->fout(t, fifoObjTempBuff)){
                // 判断数据是否相同，相同则删除，不同则存回队列
                srcPtr = (uint8 *)data;
                desPtr = (uint8 *)fifoObjTempBuff;
                for (i = 0; i < t->fifoObjSize; i++){
                    if (*desPtr++ != *srcPtr++){
                        break;
                    }
                }

                if (i < t->saveObjMaxLen){
                    // 非查找数据存回队列
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

        // 判断是否找到并删除数据，并返回操作结果
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

/*名称 : Fifo_isFull(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : 无
* 其他 : Fifo类功能函数
***********************************************/
static uint16 Fifo_isFull(hFifo t){
    uint16 retType = FALSE;

    if(t->currLen == t->saveObjMaxLen){
        retType = TRUE;
    }
    return retType;
}

/*名称 : Fifo_isEmpty(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : 无
* 其他 : Fifo类功能函数
***********************************************/
static uint16 Fifo_isEmpty(hFifo t){
    uint16 retType = TRUE;

    if(t->currLen){
        retType = FALSE;
    }
    return retType;
}

/*名称 : Fifo_clearAll(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : 无
* 其他 : Fifo类功能函数
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

/*名称 : hFifo Fifo_init(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : hFifo - cthis/OOPC_NULL
* 其他 : Fifo类初始化函数
***********************************************/
static hFifo Fifo_init(hFifo cthis, void *listBuffer, uint16 listBuffSize, uint16 fifoObjSize){
    // 功能函数配置
    //cthis->push = Fifo_push;
    //TODO

    // 参数配置
    cthis->listBuffer = (uint8 *)listBuffer;
    cthis->listBuffSize = listBuffSize;
    cthis->fifoObjSize = fifoObjSize;
    cthis->saveObjMaxLen = (cthis->listBuffSize / cthis->fifoObjSize);

    return cthis;
}

/*名称 : hFifo Fifo_ctor(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : hFifo - cthis/OOPC_NULL
* 其他 : Fifo类构造函数
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

    // 参数配置
    cthis->listBuffer = NULL;
    cthis->listBuffSize = 0;
    cthis->fifoObjSize = 0;

    cthis->saveObjMaxLen = 0;
    cthis->currLen = 0;
    cthis->top = 0;
    cthis->bottom = 0;

    return cthis;
}

/*名称 : hFifo Fifo_dtor(hFifo cthis)
* 输入 : cthis - Fifo类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : Fifo类析构函数
***********************************************/
CD(Fifo){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
