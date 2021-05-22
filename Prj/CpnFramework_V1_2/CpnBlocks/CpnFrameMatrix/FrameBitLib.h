/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : FrameBitLib.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:45:00
* Description  :
* Others       :
* History      : 201120 pxf ���ν���
***************************************************************************/

#ifndef FRAMEBITLIB_H_
#define FRAMEBITLIB_H_

/*ͷ�ļ�����*/
#include "./CpnFrameMatrix.h"

/***********************************************************
* �汾����
***********************************************************/
#define FRAMEBITLIB_MACRO_VERSION       0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

/* ��ȡ֡�ֽ� */
// #define GET_BYTE(frame,index)                                         \
//         ((CPNFRAMEMATRIXCFG_CHIP_END_TYPE==CHIP_LE32) ?               \
//         ((frame).byte[index]) :                                       \
//         ((frame).byte[(((index)>>2U)<<2U)+(3U-((index)&0x3U))]))
#if CPNFRAMEMATRIXCFG_CHIP_END_TYPE==CHIP_LE32
#define BYTE_INDEX(frame,index)         ((frame).byte[index])
#else
#define BYTE_INDEX(frame,index)         ((frame).byte[(((index)>>2U)<<2U)+(3U-((index)&0x3U))]))
#endif


/*���� : setFrameData()
* ���� : ��
* ��� : ��
* ���� : ��
***********************************************/
void setFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32 value);

/*���� : getFrameData()
* ���� : ��
* ��� : ��
* ���� : ��
***********************************************/
void getFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32* value);

#endif /*FRAMEBITLIB_H_*/

/**************************** Copyright(C) pxf ****************************/
