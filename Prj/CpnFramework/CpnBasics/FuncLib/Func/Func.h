/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Func.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:40:58
* Description  :
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

#ifndef FUNC_H_
#define FUNC_H_

/*头文件包含*/
#include "../../standType/standType.h"


/*名称 : 低通滤波(Low-pass filter)
* 输入 : 无
* 输出 : 无
* 其他 : // a=0-1，本次滤波结果=(1-a)*本次采样值+a*上次滤波结果
        // Y(n) = αX(n)+(1-α)Y(n-1)
        // 为了优化计算效率，a只取1/(2^N)，最小值为1/2
        // Y(n)= (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
        //     = (X(n)+((2^N)-1)Y(n-1))/(2^N)
***********************************************/
#define lowpassFilter(newValue, lastValue, n)  (((newValue) + (((lastValue) << (n)) - (lastValue))) >> (n))

/*名称 : memCopy
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
#define memCopy(destination, source, len) {                   \
    uint16 i = 0;                                             \
    for (i = 0; i < len; i++)                                 \
    {                                                         \
        *((uint8 *)destination + i) = *((uint8 *)source + i);   \
    }                                                         \
}

/*名称 : memSet
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
#define memSet(destination, data, len) {                      \
    uint16 i = 0;                                             \
    for (i = 0; i < len; i++)                                 \
    {                                                         \
        *((uint8 *)destination + i) = data;                   \
    }                                                         \
}

/*名称 : SWAP32_BIT
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
#define SWAP32_BIT16(data)  (((data)<<16U)|((data)>>16U))
#define SWAP32_BIT8(data)  ((((data)<<8U)&0xFF00FF00UL)|(((data)>>8U)&0x00FF00FFUL))
#define SWAP32_BIT4(data)  ((((data)<<4U)&0xF0F0F0F0UL)|(((data)>>4U)&0x0F0F0F0FUL))
#define SWAP32_BIT2(data)  ((((data)<<2U)&0xCCCCCCCCUL)|(((data)>>2U)&0x33333333UL))
#define SWAP32_BIT1(data)  ((((data)<<1U)&0xAAAAAAAAUL)|(((data)>>1U)&0x55555555UL))

#endif /*FUNC_H_*/

/**************************** Copyright(C) pxf ****************************/
