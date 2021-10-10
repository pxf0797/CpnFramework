/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : Func.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 17:13:42
 * Description  :
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef FUNC_H_
#define FUNC_H_

/* Include head files. */
#include "StandType.h"
#include <string.h>

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define FUNC_MACRO_VERSION              0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

#define USE_STANDARD_FUNC               TRUE        /* Use functions in the standard library. */

/* Function : Low-pass filter
 * Input    :
 * Output   :
 * Others   : a=0-1, this filtering result=(1-a)*this sampling value+a*last filtering result.
 *            Y(n) = aX(n)+(1-a)Y(n-1)
 *            In order to optimize the calculation efficiency, a only takes 1/(2^N), and the minimum value is 1/2.
 *            Y(n) = (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
 *                 = (X(n)+((2^N)-1)Y(n-1))/(2^N)
 **********************************************/
#define lowpassFilter(newValue, lastValue, n)  (((newValue)+(((lastValue)<<(n))-(lastValue)))>>(n))

/* Function : memCopy
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
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

/* Function : memSet
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
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

/* Function : strCopy
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
static inline uint16 strCopy(char *dest, char *source){
    uint16 uwStrLen = 0u;

    while(*source){
        *dest++ = *source++;
        uwStrLen++;
    }
    return uwStrLen;
}

/* Function : strNCopy
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
static inline uint16 strNCopy(char *dest, char *source, uint16 maxCount){
    uint16 uwStrLen = 0u;

    while((*source)&&(uwStrLen<maxCount)){
        *dest++ = *source++;
        uwStrLen++;
    }
    return uwStrLen;
}

/* Function : SWAP32_BIT
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
#define SWAP32_BIT16(data)  (((data)<<16U)|((data)>>16U))
#define SWAP32_BIT8(data)  ((((data)<<8U)&0xFF00FF00UL)|(((data)>>8U)&0x00FF00FFUL))
#define SWAP32_BIT4(data)  ((((data)<<4U)&0xF0F0F0F0UL)|(((data)>>4U)&0x0F0F0F0FUL))
#define SWAP32_BIT2(data)  ((((data)<<2U)&0xCCCCCCCCUL)|(((data)>>2U)&0x33333333UL))
#define SWAP32_BIT1(data)  ((((data)<<1U)&0xAAAAAAAAUL)|(((data)>>1U)&0x55555555UL))

/* Function : log_2n
 * Input    :
 * Output   :
 * Others   : Purely find the corresponding logarithm n of 2^n.
 **********************************************/
static inline uint16 log_2n(uint32 num){
    uint16 n = 0u;
    if(num&0xFFFF0000U){n += 16u;}
    if(num&0xFF00FF00U){n += 8u;}
    if(num&0xF0F0F0F0U){n += 4u;}
    if(num&0xCCCCCCCCU){n += 2u;}
    if(num&0xAAAAAAAAU){n += 1u;}
    return n;
}

/* Function : MASK_FIRST_BIT
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
#define MASK_FIRST_BIT(mask)       ((mask)&(0u-(mask)))
#define MASK_BIT_DOWN_FULL(mask)   ((mask)-1u)               /* mask mast be single bit, exclude bit */
#define MASK_BIT_UP_FULL(mask)     (~((mask<<1u)-1u))        /* mask mast be single bit, exclude bit */
#define MASK_BIT_DOWN_IN_FULL(mask) ((mask<<1u)-1u)          /* mask mast be single bit, include bit */
#define MASK_BIT_UP_IN_FULL(mask)  (~((mask)-1u))            /* mask mast be single bit, include bit */

#define MASK_HIGH_FIRST_BIT(mask)  ((((mask)>>1u)^(mask))&(mask)) /* mask mast be continue bit, get high first bit */

/* Function : ALIGN_SIZE
 * Input    :
 * Output   :
 * Others   : memory size align.
 **********************************************/
#define ALIGN_SIZE(align,size)                  (((((size)+((align)-1u)))/(align))*(align)) /* align*n */

#endif /*FUNC_H_*/

/**************************** Copyright(C) pxf ****************************/
