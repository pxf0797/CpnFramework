/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFrameMatrixCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:56:01
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNFRAMEMATRIXCFG_H_
#define CPNFRAMEMATRIXCFG_H_

/* Include head files. */
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"
#include "../../CpnBasics/StandType/StandType.h"

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* CpnFrameMatrixCfg error report ID need to be registered in file CpnErrCfg.h.
 **********************************************/
//#define CPNFRAMEMATRIXCFG_ERR_ID        0U    /* CpnFrameMatrixCfg component error report ID. */
#define CHIP_LE32                            0U    /* Chip little end. */
#define CHIP_BE32                            1U    /* Chip big end. */
#define CPNFRAMEMATRIXCFG_CHIP_END_TYPE      CHIP_LE32

#define CPNFRAMEMATRIXCFG_FRAME_BYTES        8U    /* Frame byte length, usually 8£¬12£¬24£¬32£¬64bytes */
#define CPNFRAMEMATRIXCFG_TASK_EXECUTE_PRD   5*MS_T /* Scheduler period. */

/* Basic data types.
 **********************************************/
typedef enum
{
    FF_INTEL_STANDARD,
    FF_INTEL_SEQUENTIAL,
    FF_MOTOROLA_LSB,
    FF_MOTOROLA_MSB,
    FF_MOTOROLA_SEQUENTIAL
}TE_FRAME_FORMAT;
typedef enum
{
    FRAME_RX,
    FRAME_TX
}TE_RXTX_TYPE;
typedef struct{
    uint32 id;
    TE_RXTX_TYPE rxtx;
    TE_FRAME_FORMAT format;
    uint16 period; /* MS */
} FrameMatrix, *hFrameMatrix;

/***********************************************************
 * Signals initial.
 **********************************************************/
/* Frames configure.
 **********************************************/
extern const FrameMatrix matrixDatas[];
/* The receiving message cycle can be set without setting, the default value 0 can be used;
 * when the sending message cycle is set to 0, the message needs to be triggered before it can be sent. */
#define FRAME_MATRIX_CFG_LIST(_)                                                \
    /* id,             rxtx,         frame_type,         period */              \
    _(0xAABUL,         FRAME_TX,     FF_INTEL_STANDARD,  110U)                  \
    _(0x100UL,         FRAME_TX,     FF_MOTOROLA_LSB,    20U)                   \
    _(0x22FUL,         FRAME_RX,     FF_MOTOROLA_LSB,    0U)                    \
    _(0xF0AUL,         FRAME_TX,     FF_INTEL_STANDARD,  300U)                  \
    _(0x03AD554EUL,    FRAME_RX,     FF_INTEL_STANDARD,  0U)                    \

/***********************************************************
 * Signals map.
 **********************************************************/
/* Sent signals.
 **********************************************/
#define FRAME_SET_SIG_LIST(_,...)                                               \
    /* sig_name,          id,            bit_start, bit_len, dynamic parameters */ \
    _(ulDataA,            0xAABUL,       20U,       16U,     __VA_ARGS__)       \
    _(ulDataB,            0xAABUL,       54U,       4U,      __VA_ARGS__)       \
    _(ulDataC,            0x100UL,       20U,       16U,     __VA_ARGS__)       \
    _(ulDataD,            0x100UL,       54U,       4U,      __VA_ARGS__)       \
    _(ulDataE,            0xF0AUL,       10U,       8U,      __VA_ARGS__)       \
    _(ulDataF,            0xF0AUL,       27U,       7U,      __VA_ARGS__)       \
    _(ulDataG,            0xF0AUL,       44U,       5U,      __VA_ARGS__)       \

/* Receive signals.
 **********************************************/
#define FRAME_GET_SIG_LIST(_,...)                                               \
    /* sig_name,          id,            bit_start, bit_len, dynamic parameters */ \
    _(ulData1,            0x22FUL,       20U,       16U,     __VA_ARGS__)       \
    _(ulData2,            0x22FUL,       54U,       4U,      __VA_ARGS__)       \
    _(ulData3,            0x22FUL,       60U,       2U,      __VA_ARGS__)       \
    _(ulData4,            0x22FUL,       48U,       3U,      __VA_ARGS__)       \
    _(ulData5,            0x03AD554EUL,  20U,       16U,     __VA_ARGS__)       \
    _(ulData6,            0x03AD554EUL,  54U,       4U,      __VA_ARGS__)       \
    _(ulData7,            0x03AD554EUL,  60U,       2U,      __VA_ARGS__)       \
    _(ulData8,            0x03AD554EUL,  48U,       3U,      __VA_ARGS__)       \


/***********************************************************
 * Function macros.
 **********************************************************/
/* Automatic expansion of matrix parameters.
 **********************************************/
#define CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS  (sizeof(matrixDatas)/sizeof(FrameMatrix)) /* Communication Matrix Frame counters. */
#define FRAME_EXPANTION(id,rxtx,frame_type,period) {id,rxtx,frame_type,period},        /* Frame contents extention. */
#define MATRIX_EXPANTION(matrix_list) matrix_list(FRAME_EXPANTION)                     /* Matrix extention. */

#endif /*CPNFRAMEMATRIXCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
