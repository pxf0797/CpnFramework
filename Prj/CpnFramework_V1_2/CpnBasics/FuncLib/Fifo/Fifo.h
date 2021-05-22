/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Fifo.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:31:48
* Description  : Fifo类及接口声明头文件
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

/*头文件包含*/
#include "../../standType/standType.h"
#include "../../oopc/oopc.h"

/***********************************************************
* 版本定义
***********************************************************/
#define FIFO_CLASS_VERSION        0xC00D00    // C代表v，D代表.，当前版本v1.00


/***********************************************************
* 接口定义
***********************************************************/
/*接口声明
***********************************************/
//INF(get){
//  uint16(*get)(void);
//};
//TODO

/***********************************************************
* Fifo类定义
***********************************************************/
/*Fifo类声明
***********************************************/
CL(Fifo){
    hFifo self;
    hFifo (*init)(hFifo cthis, void *listBuffer, uint16 listBuffSize, uint16 fifoObjSize);

    // Fifo类参数
    uint8 *listBuffer;                                         // 缓存队列起始地址
    uint16 listBuffSize;                                       // 缓存队列总大小
    uint16 fifoObjSize;                                        // 缓存队列的缓存对象大小

    uint16 saveObjMaxLen;                                      // 缓存队列缓存缓存对象的最大个数
    uint16 currLen;                                            // 缓存队列已缓存缓存对象个数
    uint16 top;                                                // 最新缓存对象进来的存放位置
    uint16 bottom;                                             // 第一个缓存对象进来的存放位置

    // Fifo类功能函数
    uint16 (*push)(hFifo t, void *data);                       // 入列
    uint16 (*pop)(hFifo t, void *data);                        // 最后入列数据出列
    uint16 (*fout)(hFifo t, void *data);                       // 最先入列数据出列，first out
    uint16 (*del)(hFifo t, void *data, void *fifoObjTempBuff); // 删除队列中的某个数据；为删除数据需要提供一个对象临时缓存区FifoObjTempBuff
    uint16 (*isFull)(hFifo t);                                 // 队列是否已满，TRUE/FALSE
    uint16 (*isEmpty)(hFifo t);                                // 队列是否为空，TRUE/FALSE
    uint16 (*clearAll)(hFifo t);                               // 清除队列内全部数据，TRUE/FALSE
};

#endif /*FIFO_H_*/

/**************************** Copyright(C) pxf ****************************/
