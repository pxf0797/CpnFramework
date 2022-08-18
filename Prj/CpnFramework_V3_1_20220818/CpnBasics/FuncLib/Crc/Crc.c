/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : Crc.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 17:59:42
 * Description  : Crc class functions definition source files.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "Crc.h"
#include "Func.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * Crc class definition.
 **********************************************************/
/* Function : Crc_invert(hCrc cthis)
 * Input    : cthis - Crc class pointer
 * Output   :
 * Others   : Crc class function.
 **********************************************/
uint32 Crc_invert(hCrc cthis, uint32 data, uint16 len){
    uint32 invertData = 0UL;

    invertData = SWAP32_BIT16(data);
    invertData = SWAP32_BIT8(invertData);
    invertData = SWAP32_BIT4(invertData);
    invertData = SWAP32_BIT2(invertData);
    invertData = SWAP32_BIT1(invertData);
    invertData = (invertData>>(32U-len));
    return invertData;
}

/* Function : Crc_crcAlgorithm(hCrc cthis)
 * Input    : cthis - Crc class pointer
 * Output   :
 * Others   : Crc class function.
 **********************************************/
uint32 Crc_crcAlgorithm(hCrc cthis, const uint8* s, uint32 len){
    uint32 crc = cthis->initial;
    uint8 *p = (uint8*)s;

    /* Simulate the process of XOR division, that is, put the measured data bit by bit into the register for division. */
    /* Judge the highest bit, if the bit is 0, shift it to the left by one bit, if it is 1,
     * shift it to the left by one bit and then XOR with the polynomial Hex code. */
    // while(len--){
    //     //crc ^= (*p++);        /* The result of calculating the CRC from the previous byte is XORed by the next byte, and the CRC is calculated again. */
    //     temp = (*p++);
    //     if(cthis->invertType){
    //         temp = (uint8)(cthis->invert(cthis, (uint32)temp, 8U));
    //     }
    //     crc ^= temp;
    //     for(uint8 j = 8U; j > 0U; j--){
    //         crc &= mask;
    //         if(crc & highBit){   /* The high bit is 1, and XOR is required; otherwise, it is not required. */
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

    /* Optimization, shift left to shift right, directly reverse the polynomial,
     * and the calculation result does not need to be reversed again. */
    if(cthis->invertType){
        while(len--){
            crc ^= (*p++); /* The result of calculating the CRC from the previous byte is XORed by the next byte, and the CRC is calculated again. */
            for(uint8 i = 8U; i > 0U; i--){
                if(crc & 0x1UL){ /* The low bit is 1, and XOR is required; otherwise, it is not required. */
                    crc >>= 1U;
                    crc ^= cthis->invertPoly;
                }else{
                    crc >>= 1U;
                }
            }
        }
    }else{
        while(len--){
            //crc ^= (*p++); /* The result of calculating the CRC from the previous byte is XORed by the next byte, and the CRC is calculated again. */
            if(cthis->crcType > crc_8){
                crc ^= (((uint32)(*p++))<<(cthis->crcType-crc_8)); /* Align high byte to shift out. */
            }else{
                crc ^= (*p++);
            }
            for(uint8 i = 8U; i > 0U; i--){
                crc &= cthis->mask;
                if(crc & cthis->highBit){ /* The high bit is 1, and XOR is required; otherwise, it is not required. */
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

/* Function : Crc_crc(hCrc cthis)
 * Input    : cthis - Crc class pointer
 * Output   :
 * Others   : Crc class function.
 **********************************************/
uint32 Crc_crc(hCrc cthis, const uint8* s, uint32 len){
    uint8 *p = (uint8*)s;
    uint32 r = 0UL;                   /* r is a register, first initialized to 0. */

    /*len += (1U<<cthis->crcType);
    while(len--){                     // len is the length of the data to be measured after 0 has been expanded.
        uint8 t = (r>>24U)&0xFFU;
        r = (r<<8U)|(*p++);           // p is a pointer to the data to be tested (the data to be tested must have been expanded by 0).
        r^=cthis->crcTable[t];        // Find table.
    }*/

    /* Optimization1 */
    /*len += (1U<<cthis->crcType);
    while(len--){                     // len is the byte length of the data to be measured after 0 has been expanded.
        r = ((r<<8U)|(*p++))^cthis->crcTable[(r>>24)&0xFFU]; // p is the pointer to the data to be tested (the data to be tested must have been expanded by 0), t is the lookup table.
    }*/

    /* Optimization2 */
    /*while(len--){                   // len is the byte length of the data to be tested (without extension 0).
        r = (r<<8U)^cthis->crcTable[(r>>24U)^(*p++)]; // p is a pointer to the data to be tested, t is the lookup table.
    }*/

    /* The relationship between the original CRC and the current CRC is the remainder after the original CRC is left shifted by 8 bits + the CRC of the new data. */
    /* It is similar to the direct solution, except that the crc is split into two parts, and it becomes the form of FF000000 and 00FFFFFF.
     * Among them, the CRC value of the latter is itself, and the previous value can be obtained by looking up the table. */
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

/* Function : hCrc Crc_init(hCrc cthis)
 * Input    : cthis - Crc class pointer
 * Output   : hCrc - cthis/OOPC_NULL
 * Others   : Crc class initial function.
 **********************************************/
hCrc Crc_init(hCrc cthis, TE_CRC_TYPE crcType, uint32 poly, uint32 initial, uint32 final, TE_INVERT_TYPE invertType){
    uint8 temp = 0U;

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
    for(uint16 i = 0U; i < 256U; i++){
        temp = (uint8)i;
        cthis->crcTable[i] = cthis->crcAlgorithm(cthis, &temp, 1U);
    }

    return cthis;
}

/* Function : hCrc Crc_ctor(hCrc cthis)
 * Input    : cthis - Crc class pointer
 * Output   : hCrc - cthis/OOPC_NULL
 * Others   : Crc class constructor.
 **********************************************/
CC(Crc){
    cthis->init = Crc_init;
    cthis->invert = Crc_invert;
    cthis->crcAlgorithm = Crc_crcAlgorithm;
    cthis->crc = Crc_crc;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCrc Crc_dtor(hCrc cthis)
 * Input    : cthis - Crc class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : Crc class destructor.
 **********************************************/
CD(Crc){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
