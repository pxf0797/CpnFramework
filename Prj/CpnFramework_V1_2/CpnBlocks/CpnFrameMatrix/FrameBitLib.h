/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : FrameBitLib.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:45:00
* Description  :
* Others       :
* History      : 201120 pxf 初次建立
***************************************************************************/

#ifndef FRAMEBITLIB_H_
#define FRAMEBITLIB_H_

/*头文件包含*/
#include "./CpnFrameMatrix.h"

/***********************************************************
* 版本定义
***********************************************************/
#define FRAMEBITLIB_MACRO_VERSION       0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/* 获取帧字节 */
// #define GET_BYTE(frame,index)                                         \
//         ((CPNFRAMEMATRIXCFG_CHIP_END_TYPE==CHIP_LE32) ?               \
//         ((frame).byte[index]) :                                       \
//         ((frame).byte[(((index)>>2U)<<2U)+(3U-((index)&0x3U))]))
#if CPNFRAMEMATRIXCFG_CHIP_END_TYPE==CHIP_LE32
#define BYTE_INDEX(frame,index)         ((frame).byte[index])
#else
#define BYTE_INDEX(frame,index)         ((frame).byte[(((index)>>2U)<<2U)+(3U-((index)&0x3U))]))
#endif


/*名称 : setFrameData()
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
void setFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32 value);

/*名称 : getFrameData()
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
void getFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32* value);

#endif /*FRAMEBITLIB_H_*/

/**************************** Copyright(C) pxf ****************************/
