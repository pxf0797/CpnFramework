/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrixCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  :
* Others       :
* History      : 201120 pxf ���ν���
***************************************************************************/

#ifndef CPNFRAMEMATRIXCFG_H_
#define CPNFRAMEMATRIXCFG_H_

/*ͷ�ļ�����*/
#include "../../cpnBasics/CpnErr/CpnErrCfg.h"
#include "../../cpnBasics/standType/standType.h"

/***********************************************************
* ���ò���
***********************************************************/
/*CpnFrameMatrixCfg�����ϱ�ID����Ҫ��CpnErrCfg.h�ļ��ڽ���ע��
***********************************************/
//#define CPNFRAMEMATRIXCFG_ERR_ID        0U    /* CpnFrameMatrixCfg�����������ID */
#define CHIP_LE32                            0U    /* оƬС�� */
#define CHIP_BE32                            1U    /* оƬ��� */
#define CPNFRAMEMATRIXCFG_CHIP_END_TYPE      CHIP_LE32

#define CPNFRAMEMATRIXCFG_FRAME_BYTES        8U    /* ֡�����ֽڳ��ȣ�һ����8��12��24��32��64bytes */
#define CPNFRAMEMATRIXCFG_TASK_EXECUTE_PRD   5*MS_T /* ��������������� */

/*�����������Ͷ���
***********************************************/
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
* �źų�ʼ��
***********************************************************/
/*��������
***********************************************/
extern const FrameMatrix matrixDatas[];
#define FRAME_MATRIX_CFG_LIST(_)                                                \
    /* id,             rxtx,         frame_type,         period */              \
    _(0xAABUL,         FRAME_TX,     FF_INTEL_STANDARD,  110U)                  \
    _(0x100UL,         FRAME_TX,     FF_MOTOROLA_LSB,    20U)                   \
    _(0x22FUL,         FRAME_RX,     FF_MOTOROLA_LSB,    0U)                    \
    _(0xF0AUL,         FRAME_TX,     FF_INTEL_STANDARD,  300U)                  \
    _(0x03AD554EUL,    FRAME_RX,     FF_INTEL_STANDARD,  0U)                    \

/***********************************************************
* �ź�ӳ��
***********************************************************/
/*�����ź�����
***********************************************/
#define FRAME_SET_SIG_LIST(_,...)                                               \
    /* sig_name,          id,            bit_start, bit_len, dynamic parameters */ \
    _(ulDataA,            0xAABUL,       20U,       16U,     __VA_ARGS__)       \
    _(ulDataB,            0xAABUL,       54U,       4U,      __VA_ARGS__)       \
    _(ulDataC,            0x100UL,       20U,       16U,     __VA_ARGS__)       \
    _(ulDataD,            0x100UL,       54U,       4U,      __VA_ARGS__)       \
    _(ulDataE,            0xF0AUL,       10U,       8U,      __VA_ARGS__)       \
    _(ulDataF,            0xF0AUL,       27U,       7U,      __VA_ARGS__)       \
    _(ulDataG,            0xF0AUL,       44U,       5U,      __VA_ARGS__)       \

/*�����ź�����
***********************************************/
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
* ���ܺ�
***********************************************************/
/*��������Զ���չ
***********************************************/
#define CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS  (sizeof(matrixDatas)/sizeof(FrameMatrix)) /* ͨ�ž����ĸ��� */
#define FRAME_EXPANTION(id,rxtx,frame_type,period) {id,rxtx,frame_type,period},        /* ֡�ṹ��������չ */
#define MATRIX_EXPANTION(matrix_list) matrix_list(FRAME_EXPANTION)                     /* ������չ */

#endif /*CPNFRAMEMATRIXCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
