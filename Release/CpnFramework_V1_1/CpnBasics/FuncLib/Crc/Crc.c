/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Crc.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/24 08:58:28
* Description  : Crc������ܺ�������Դ�ļ�
* Others       :
* History      : 201124 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./Crc.h"
#include "../Func/Func.h"

/***********************************************************
* �������Ͷ���
***********************************************************/
/*���ݶ���
***********************************************/
//TODO

/***********************************************************
* Crc�ඨ��
***********************************************************/
/*���� : Crc_crc(hCrc cthis)
* ���� : cthis - Crc��ָ��
* ��� : ��
* ���� : Crc�๦�ܺ���
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

/*���� : Crc_crc(hCrc cthis)
* ���� : cthis - Crc��ָ��
* ��� : ��
* ���� : Crc�๦�ܺ���
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

    /* ģ�� XOR �����Ĺ��̣�����������һλһλ�ŵ��Ĵ������������� */
    /* �ж����λ������λΪ0����һλ����Ϊ1����һλ�������ʽHex����� */
    // while(len--){
    //     //crc ^= (*p++);        /* ǰһ�ֽڼ���CRC��Ľ������Ϻ�һ�ֽڣ��ٴμ���CRC */
    //     temp = (*p++);
    //     if(cthis->invertType){
    //         temp = (uint8)(cthis->invert(cthis, (uint32)temp, 8U));
    //     }
    //     crc ^= temp;

    //     for(uint8 j = 8U; j > 0U; j--){
    //         crc &= mask;
    //         if(crc & highBit){   /* ��λΪ1����Ҫ��򣻷��򣬲���Ҫ */
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

    /* �Ż������Ƹ�Ϊ���ƣ�ֱ����ת����ʽ�����Ҽ����������ٴ���ת */
    if(cthis->invertType){
        while(len--){
            crc ^= (*p++);                      /* ǰһ�ֽڼ���CRC��Ľ������Ϻ�һ�ֽڣ��ٴμ���CRC */
            for(uint8 i = 8U; i > 0U; i--){
                if(crc & 0x1UL){                /* ��λΪ1����Ҫ��򣻷��򣬲���Ҫ */
                    crc >>= 1U;
                    crc ^= cthis->invertPoly;
                }else{
                    crc >>= 1U;
                }
            }
        }
    }else{
        while(len--){
            //crc ^= (*p++);                          /* ǰһ�ֽڼ���CRC��Ľ������Ϻ�һ�ֽڣ��ٴμ���CRC */
            if(cthis->crcType > crc_8){
                crc ^= (((uint32)(*p++))<<(cthis->crcType-crc_8)); /* ������ֽڽ����Ƴ� */
            }else{
                crc ^= (*p++);
            }
            for(uint8 i = 8U; i > 0U; i--){
                crc &= cthis->mask;
                if(crc & cthis->highBit){           /* ��λΪ1����Ҫ��򣻷��򣬲���Ҫ */
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

/*���� : Crc_crc(hCrc cthis)
* ���� : cthis - Crc��ָ��
* ��� : ��
* ���� : Crc�๦�ܺ���
***********************************************/
uint32 Crc_crc(hCrc cthis, const uint8* s, uint32 len){
    uint8 *p = s;
    uint32 r = 0UL;                   // r �ǼĴ������ȳ�ʼ��Ϊ 0

    /*len += (1U<<cthis->crcType);
    while(len--){                     // len ������չ 0 ֮��Ĵ������ݵĳ���
        uint8 t = (r>>24U)&0xFFU;
        r = (r<<8U)|(*p++);           // p ��ָ��������ݵ�ָ�루�����������Ѿ���չ�� 0��
        r^=cthis->crcTable[t];        // table �ǲ�ѯ��
    }*/

    /* �Ż�1 */
    /*len += (1U<<cthis->crcType);
    while(len--){                                             //len ������չ 0 ֮��Ĵ������ݵ��ֽڳ���
        r = ((r<<8U)|(*p++))^cthis->crcTable[(r>>24)&0xFFU];  //p ��ָ��������ݵ�ָ�루�����������Ѿ���չ�� 0��,t �ǲ�ѯ��
    }*/

    /* �Ż�2 */
    /*while(len--){                                        //len �Ǵ������ݣ�������չ 0�����ֽڳ���
        r = (r<<8U)^cthis->crcTable[(r>>24U)^(*p++)];    //p ��ָ��������ݵ�ָ��,t �ǲ�ѯ��
    }*/

    /* ԭ����CRC�����ڵ�CRC֮��Ĺ�ϵ�� ԭ��CRC����8λ֮������� + �µ����ݵ�CRC */
    /* ��ֱ��������ƣ�ֻ������crc����������֣�
       ��Ϊ��FF000000��00FFFFFF����ʽ�����У�����һ����CRCֵ�����䱾����ǰ���ֵ���Բ��õ� */
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


/*���� : hCrc Crc_init(hCrc cthis)
* ���� : cthis - Crc��ָ��
* ��� : hCrc - cthis/OOPC_NULL
* ���� : Crc���ʼ������
***********************************************/
hCrc Crc_init(hCrc cthis, TE_CRC_TYPE crcType, uint32 poly, uint32 initial, uint32 final, TE_INVERT_TYPE invertType){
    uint8 temp = 0U;

    // ���ܺ�������
    //cthis->crc = Crc_crc;
    //TODO

    // ��������
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

/*���� : hCrc Crc_ctor(hCrc cthis)
* ���� : cthis - Crc��ָ��
* ��� : hCrc - cthis/OOPC_NULL
* ���� : Crc�๹�캯��
***********************************************/
CC(Crc){
    cthis->init = Crc_init;
    cthis->invert = Crc_invert;
    cthis->crcAlgorithm = Crc_crcAlgorithm;
    cthis->crc = Crc_crc;
    //TODO

    // ��������
    //TODO
    return cthis;
}

/*���� : hCrc Crc_dtor(hCrc cthis)
* ���� : cthis - Crc��ָ��
* ��� : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* ���� : Crc����������
***********************************************/
CD(Crc){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
