/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : FrameBitLib.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:57:04
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef FRAMEBITLIB_H_
#define FRAMEBITLIB_H_

/* Include head files. */
#include "./CpnFrameMatrix.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define FRAMEBITLIB_MACRO_VERSION       0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/* Get frame bytes. */
/* #define GET_BYTE(frame,index)                                         \
         ((CPNFRAMEMATRIXCFG_CHIP_END_TYPE==CHIP_LE32) ?               \
         ((frame).byte[index]) :                                       \
         ((frame).byte[(((index)>>2U)<<2U)+(3U-((index)&0x3U))]))
 */
#if CPNFRAMEMATRIXCFG_CHIP_END_TYPE==CHIP_LE32
#define BYTE_INDEX(frame,index)         ((frame).byte[index])
#else
#define BYTE_INDEX(frame,index)         ((frame).byte[(((index)>>2U)<<2U)+(3U-((index)&0x3U))]))
#endif

/* Function : setFrameData()
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
void setFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32 value);

/* Function : getFrameData()
 * Input    :
 * Output   :
 * Others   :
 **********************************************/
void getFrameData(uint32 frame_data[], TE_FRAME_FORMAT format, uint16 bit_start, uint16 bit_len, uint32* value);

#endif /*FRAMEBITLIB_H_*/

/**************************** Copyright(C) pxf ****************************/
