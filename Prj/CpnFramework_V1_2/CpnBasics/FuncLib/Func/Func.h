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
#include <string.h>

#define USE_STANDARD_FUNC                TRUE  /* 使用标准库中函数 */

/*名称 : 低通滤波(Low-pass filter)
* 输入 : 无
* 输出 : 无
* 其他 : // a=0-1，本次滤波结果=(1-a)*本次采样值+a*上次滤波结果
        // Y(n) = αX(n)+(1-α)Y(n-1)
        // 为了优化计算效率，a只取1/(2^N)，最小值为1/2
        // Y(n)= (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
        //     = (X(n)+((2^N)-1)Y(n-1))/(2^N)
***********************************************/
#define lowpassFilter(newValue, lastValue, n)  (((newValue)+(((lastValue)<<(n))-(lastValue)))>>(n))

/*名称 : memCopy
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
#if PLATFORM_END == LITTLE_END
#define MEMCOPY16_MASK  0x00FFU
#define MEMCOPY32_MASK(len)  ((0x1UL<<(((len)&0x3U)<<3U))-1UL)
#else
#define MEMCOPY16_MASK  0xFF00U
#define MEMCOPY32_MASK(len)  (0xFFFFFFFFUL<<((4U-((len)&0x3U))<<3U))
#endif
#if USE_STANDARD_FUNC
#define memCopy memcpy
#else
#define memCopy(destination, source, len) do{                 \
    uint8 *pucDest = (uint8 *)(destination);                  \
    uint8 *pucSource = (uint8 *)(source);                     \
    uint16 i = 0U;                                            \
    while(i < len){                                           \
        pucDest[i] = pucSource[i];                            \
        i++;                                                  \
    }                                                         \
}while(0)
#endif

/*名称 : memSet
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
#if USE_STANDARD_FUNC
#define memSet memset
#else
#define memSet(destination, data, len) do{                    \
    uint8 *pucDest = (uint8 *)(destination);                  \
    uint16 i = 0U;                                            \
    while(i < len){                                           \
        pucDest[i] = data;                                    \
        i++;                                                  \
    }                                                         \
}while(0)
#endif

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

/*log_2n 纯粹求2^n的对应的对数n
* 输入: 2^n
* 输出: n
***********************************************/
static inline uint16 log_2n(uint32 num){
    uint16 n = 0u;
    if(num&0xFFFF0000U){n += 16u;}
    if(num&0xFF00FF00U){n += 8u;}
    if(num&0xF0F0F0F0U){n += 4u;}
    if(num&0xCCCCCCCCU){n += 2u;}
    if(num&0xAAAAAAAAU){n += 1u;}
    return n;
}

/*名称 : MASK_FIRST_BIT
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
#define MASK_FIRST_BIT(mask)       ((mask)&(0u-(mask)))
#define MASK_BIT_DOWN_FULL(mask)   ((mask)-1u) /* mask mast be single bit, exclude bit */
#define MASK_BIT_UP_FULL(mask)     (~((mask<<1u)-1u)) /* mask mast be single bit, exclude bit */
#define MASK_BIT_DOWN_IN_FULL(mask) ((mask<<1u)-1u) /* mask mast be single bit, include bit */
#define MASK_BIT_UP_IN_FULL(mask)  (~((mask)-1u)) /* mask mast be single bit, include bit */

#define MASK_HIGH_FIRST_BIT(mask)  ((((mask)>>1u)^(mask))&(mask)) /* mask mast be continue bit, get high first bit */

#endif /*FUNC_H_*/

/**************************** Copyright(C) pxf ****************************/
