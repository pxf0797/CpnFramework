/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Crc.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/24 08:58:28
* Description  : Crc类各功能函数定义源文件
* Others       :
* History      : 201124 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./Crc.h"
#include "../Func/Func.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* Crc类定义
***********************************************************/
/*名称 : Crc_crc(hCrc cthis)
* 输入 : cthis - Crc类指针
* 输出 : 无
* 其他 : Crc类功能函数
***********************************************/
uint32 Crc_invert(hCrc cthis, uint32 data, uint16 len){
    uint32 invertData = 0UL;

    // for(uint16 i = 0U; i < len; i++){
    //     if(data & (1UL<<i)){
    //         invertData |= (len-1-i);
    //     }
    // }

    // invertData = (data<<16U)|(data>>16U);
    // invertData = ((invertData<<8U)&0xFF00FF00U)|((invertData>>8U)&0x00FF00FFU);
    // invertData = ((invertData<<4U)&0xF0F0F0F0U)|((invertData>>4U)&0x0F0F0F0FU);
    // invertData = ((invertData<<2U)&0xCCCCCCCCU)|((invertData>>2U)&0x33333333U);
    // invertData = ((invertData<<1U)&0xAAAAAAAAU)|((invertData>>1U)&0x55555555U);
    invertData = SWAP32_BIT16(data);
    invertData = SWAP32_BIT8(invertData);
    invertData = SWAP32_BIT4(invertData);
    invertData = SWAP32_BIT2(invertData);
    invertData = SWAP32_BIT1(invertData);
    invertData = (invertData>>(32U-len));

    return invertData;
}

/*名称 : Crc_crc(hCrc cthis)
* 输入 : cthis - Crc类指针
* 输出 : 无
* 其他 : Crc类功能函数
***********************************************/
uint32 Crc_crcAlgorithm(hCrc cthis, const uint8* s, uint32 len){
    uint32 crc = cthis->initial;
    // uint32 mask = 0UL;
    // uint32 highBit = 0UL;
    uint8 *p = s;
    // uint8 temp = 0U;
    // uint32 invertPoly = 0UL;

    // if(cthis->crcType == crc_8){
    //     mask = (~((~mask)<<8U));
    //     highBit = ((1UL)<<(8U-1U));
    // }else if(cthis->crcType == crc_16){
    //     mask = (~((~mask)<<16U));
    //     highBit = ((1UL)<<(16U-1U));
    // }else if(cthis->crcType == crc_32){
    //     mask = (~((~mask)<<32U));
    //     highBit = ((1UL)<<(32U-1U));
    // }else{}

    /* 模拟 XOR 除法的过程，即被测数据一位一位放到寄存器中来做除法 */
    /* 判断最高位，若该位为0左移一位，若为1左移一位再与多项式Hex码异或 */
    // while(len--){
    //     //crc ^= (*p++);        /* 前一字节计算CRC后的结果异或上后一字节，再次计算CRC */
    //     temp = (*p++);
    //     if(cthis->invertType){
    //         temp = (uint8)(cthis->invert(cthis, (uint32)temp, 8U));
    //     }
    //     crc ^= temp;

    //     for(uint8 j = 8U; j > 0U; j--){
    //         crc &= mask;
    //         if(crc & highBit){   /* 高位为1，需要异或；否则，不需要 */
    //             crc <<= 1U;
    //             crc ^= cthis->poly;
    //         }else{
    //             crc <<= 1U;
    //         }
    //     }
    // }

    // if(cthis->invertType){
    //     if(cthis->crcType == crc_8){
    //         crc = (uint8)(cthis->invert(cthis, crc, 8U));
    //     }else if(cthis->crcType == crc_16){
    //         crc = (uint16)(cthis->invert(cthis, crc, 16U));
    //     }else if(cthis->crcType == crc_32){
    //         crc = (cthis->invert(cthis, crc, 32U));
    //     }else{}
    // }
    // crc ^= cthis->final;

    /* 优化，左移改为右移，直接逆转多项式，并且计算结果不用再次逆转 */
    if(cthis->invertType){
        while(len--){
            crc ^= (*p++);                      /* 前一字节计算CRC后的结果异或上后一字节，再次计算CRC */
            for(uint8 i = 8U; i > 0U; i--){
                if(crc & 0x1UL){                /* 低位为1，需要异或；否则，不需要 */
                    crc >>= 1U;
                    crc ^= cthis->invertPoly;
                }else{
                    crc >>= 1U;
                }
            }
        }
    }else{
        while(len--){
            //crc ^= (*p++);                          /* 前一字节计算CRC后的结果异或上后一字节，再次计算CRC */
            if(cthis->crcType > crc_8){
                crc ^= (((uint32)(*p++))<<(cthis->crcType-crc_8)); /* 对齐高字节进行移出 */
            }else{
                crc ^= (*p++);
            }
            for(uint8 i = 8U; i > 0U; i--){
                crc &= cthis->mask;
                if(crc & cthis->highBit){           /* 高位为1，需要异或；否则，不需要 */
                    crc <<= 1U;
                    crc ^= cthis->poly;
                }else{
                    crc <<= 1U;
                }
            }
        }
        crc &= cthis->mask;
    }
    crc ^= cthis->final;

    return crc;
}

/*名称 : Crc_crc(hCrc cthis)
* 输入 : cthis - Crc类指针
* 输出 : 无
* 其他 : Crc类功能函数
***********************************************/
uint32 Crc_crc(hCrc cthis, const uint8* s, uint32 len){
    uint8 *p = s;
    uint32 r = 0UL;                   // r 是寄存器，先初始化为 0

    /*len += (1U<<cthis->crcType);
    while(len--){                     // len 是已扩展 0 之后的待测数据的长度
        uint8 t = (r>>24U)&0xFFU;
        r = (r<<8U)|(*p++);           // p 是指向待测数据的指针（待测数据需已经扩展过 0）
        r^=cthis->crcTable[t];        // table 是查询表
    }*/

    /* 优化1 */
    /*len += (1U<<cthis->crcType);
    while(len--){                                             //len 是已扩展 0 之后的待测数据的字节长度
        r = ((r<<8U)|(*p++))^cthis->crcTable[(r>>24)&0xFFU];  //p 是指向待测数据的指针（待测数据需已经扩展过 0）,t 是查询表
    }*/

    /* 优化2 */
    /*while(len--){                                        //len 是待测数据（不用扩展 0）的字节长度
        r = (r<<8U)^cthis->crcTable[(r>>24U)^(*p++)];    //p 是指向待测数据的指针,t 是查询表
    }*/

    /* 原来的CRC和现在的CRC之间的关系是 原来CRC左移8位之后的余项 + 新的数据的CRC */
    /* 和直接求解类似，只不过把crc拆成了两部分，
       变为了FF000000和00FFFFFF的形式，其中，后面一个的CRC值就是其本身，而前面的值可以查表得到 */
    if(cthis->crcType == crc_8){
        while(len--){
            r = cthis->crcTable[(r^(*p++))&0xFFU];
        }
        r &= 0xFFU;
    }else if(cthis->crcType == crc_16){
        if(cthis->invertType){
            while(len--){
                r = (r>>8U)^cthis->crcTable[(r^(*p++))&0xFFU];
            }
        }else{
            while(len--){
                r = (r<<8U)^cthis->crcTable[((r>>8U)^(*p++))&0xFFU];
            }
        }
        r &= 0xFFFFU;
    }else if(cthis->crcType == crc_32){
        if(cthis->invertType){
            while(len--){
                r = (r>>8U)^cthis->crcTable[(r^(*p++))&0xFFU];
            }
        }else{
            while(len--){
                r = (r<<8U)^cthis->crcTable[((r>>24U)^(*p++))&0xFFU];
            }
        }
    }else{}

    return r;
}


/*名称 : hCrc Crc_init(hCrc cthis)
* 输入 : cthis - Crc类指针
* 输出 : hCrc - cthis/OOPC_NULL
* 其他 : Crc类初始化函数
***********************************************/
hCrc Crc_init(hCrc cthis, TE_CRC_TYPE crcType, uint32 poly, uint32 initial, uint32 final, TE_INVERT_TYPE invertType){
    uint8 temp = 0U;

    // 功能函数配置
    //cthis->crc = Crc_crc;
    //TODO

    // 参数配置
    cthis->crcType = crcType;
    cthis->poly = poly;
    cthis->initial = initial;
    cthis->final = final;
    cthis->invertType = invertType;

    cthis->highBit = (0x1UL<<(cthis->crcType-1U));
    cthis->mask = 0x0UL;
    if(cthis->crcType == crc_32){
        cthis->mask = (~cthis->mask);
    }else{
        cthis->mask = (~((~cthis->mask)<<cthis->crcType));
    }
    cthis->invertPoly = cthis->invert(cthis, cthis->poly, cthis->crcType);

    /* init crc table */
    /*for(uint16 i = 0U; i < 256U; i++){
        crc = i;
        for(uint16 j = 0U; j < 8U; j++){
            if(crc & 1U){
                crc = (crc >> 1U) ^ cthis->poly;
            }else{
                crc = (crc>>1U);
            }
        }
        cthis->crcTable[i] = crc;
    }*/
    for(uint16 i = 0U; i < 256U; i++){
        temp = i;
        // if(cthis->invertType){
        //     cthis->crcTable[i/*cthis->invert(cthis, (uint32)i, 8U)*/] = cthis->crcAlgorithm(cthis, &temp, 1U);
        // }else{
        //     cthis->crcTable[i] = cthis->crcAlgorithm(cthis, &temp, 1U);
        // }
        cthis->crcTable[i] = cthis->crcAlgorithm(cthis, &temp, 1U);
    }

    return cthis;
}

/*名称 : hCrc Crc_ctor(hCrc cthis)
* 输入 : cthis - Crc类指针
* 输出 : hCrc - cthis/OOPC_NULL
* 其他 : Crc类构造函数
***********************************************/
CC(Crc){
    cthis->init = Crc_init;
    cthis->invert = Crc_invert;
    cthis->crcAlgorithm = Crc_crcAlgorithm;
    cthis->crc = Crc_crc;
    //TODO

    // 参数配置
    //TODO
    return cthis;
}

/*名称 : hCrc Crc_dtor(hCrc cthis)
* 输入 : cthis - Crc类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : Crc类析构函数
***********************************************/
CD(Crc){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
