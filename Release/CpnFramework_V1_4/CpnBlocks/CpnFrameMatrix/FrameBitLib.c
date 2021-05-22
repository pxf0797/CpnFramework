/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : FrameBitLib.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:57:04
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./FrameBitLib.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"

/* Function : setFrameData()
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
void setFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32 value){
    volatile uint16 leftShift, long_data_index, long_data_bit_index;
    volatile uint32 mask, dataL, dataH, dataL_mask, dataH_mask;

    if(format == FF_INTEL_STANDARD){
        leftShift = bit_start;
    }else if(format == FF_INTEL_SEQUENTIAL){
        leftShift = bit_start^0x7U;
    }else if(format == FF_MOTOROLA_LSB){
        leftShift = bit_start^0x38U;
    }else if(format == FF_MOTOROLA_MSB){
        leftShift = ((bit_start^0x7U)+bit_len-1U)^0x3FU;
    }else if(format == FF_MOTOROLA_SEQUENTIAL){
        leftShift = ((CPNFRAMEMATRIXCFG_FRAME_BYTES<<3U)-bit_len-bit_start);
    }else{
        /* default intel standard */
        leftShift = bit_start;
    }

    long_data_index = (uint16)(leftShift>>5U);
    long_data_bit_index = (uint16)(leftShift&0x1FU);
    mask = (uint32)((0x1UL << bit_len)-1U);

    dataL_mask = (~(mask<<long_data_bit_index));
    dataH_mask = (~(mask>>(32U-long_data_bit_index)));
    dataL = (value<<long_data_bit_index);
    dataH = (value>>(32U-long_data_bit_index));

    if(format > FF_INTEL_SEQUENTIAL){
        dataL_mask = SWAP32_BIT8(SWAP32_BIT16(dataL_mask));
        dataH_mask = SWAP32_BIT8(SWAP32_BIT16(dataH_mask));
        dataL = SWAP32_BIT8(SWAP32_BIT16(dataL));
        dataH = SWAP32_BIT8(SWAP32_BIT16(dataH));

        long_data_index = (((CPNFRAMEMATRIXCFG_FRAME_BYTES>>2U)-1U)-long_data_index);
        frame_data[long_data_index] &= dataL_mask;
        frame_data[long_data_index] |= dataL;
        if(long_data_index > 0U){
            frame_data[long_data_index-1U] &= dataH_mask;
            frame_data[long_data_index-1U] |= dataH;
        }
    }else{
        frame_data[long_data_index] &= dataL_mask;
        frame_data[long_data_index] |= dataL;
        if(long_data_index < ((CPNFRAMEMATRIXCFG_FRAME_BYTES>>2U)-1U)){
            frame_data[long_data_index+1U] &= dataH_mask;
            frame_data[long_data_index+1U] |= dataH;
        }
    }
}

/* Function : getFrameData()
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
void getFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32* value){
    volatile uint16 leftShift, long_data_index, long_data_bit_index;
    volatile uint32 mask, dataL, dataH/*, dataL_mask, dataH_mask*/;

    if(format == FF_INTEL_STANDARD){
        leftShift = bit_start;
    }else if(format == FF_INTEL_SEQUENTIAL){
        leftShift = bit_start^0x7U;
    }else if(format == FF_MOTOROLA_LSB){
        leftShift = bit_start^0x38U;
    }else if(format == FF_MOTOROLA_MSB){
        leftShift = ((bit_start^0x7U)+bit_len-1U)^((CPNFRAMEMATRIXCFG_FRAME_BYTES<<3U)-1U)/*0x3F*/;
    }else if(format == FF_MOTOROLA_SEQUENTIAL){
        leftShift = ((CPNFRAMEMATRIXCFG_FRAME_BYTES<<3U)-bit_len-bit_start);
    }else{
        /* default intel standard */
        leftShift = bit_start;
    }

    long_data_index = (uint16)(leftShift>>5U);
    long_data_bit_index = (uint16)(leftShift&0x1FU);
    mask = (uint32)((0x1UL << bit_len)-1U);

    //dataL_mask = (~(mask<<long_data_bit_index));
    //dataH_mask = (~(mask>>(32U-long_data_bit_index)));
    if(format > FF_INTEL_SEQUENTIAL){
        long_data_index = (((CPNFRAMEMATRIXCFG_FRAME_BYTES>>2U)-1U)-long_data_index);
        dataL = frame_data[long_data_index];
        if(long_data_index > 0U){
            dataH = frame_data[long_data_index-1U];
        }
        dataL = SWAP32_BIT8(SWAP32_BIT16(dataL));
        dataH = SWAP32_BIT8(SWAP32_BIT16(dataH));
    }else{
        dataL = frame_data[long_data_index];
        if(long_data_index < ((CPNFRAMEMATRIXCFG_FRAME_BYTES>>2U)-1U)){
            dataH = frame_data[long_data_index+1U];
        }
    }
    *value = (((dataH<<(32U-long_data_bit_index))|(dataL>>long_data_bit_index))&mask);
}

/**************************** Copyright(C) pxf ****************************/
