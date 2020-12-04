/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrixSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  : CpnFrameMatrix组件信号声明头文件
* Others       :
* History      : 201120 pxf 初次建立
***************************************************************************/

#ifndef CPNFRAMEMATRIXSIGS_H_
#define CPNFRAMEMATRIXSIGS_H_

/*头文件包含*/
#include "../../cpnRte/Rte/Rte.h"
#include "./CpnFrameMatrixCfg.h"
#include "./CpnFrameMatrix.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNFRAMEMATRIXSIGS_MACRO_VERSION 0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/***********************************************************
* get set 数据类型定义
* 一般只定义set数据，get类型引用当前头文件
* 只需要把发送的数据定义出来，收发接口使用的是统一接口，无其他定义
* 信号数据类型一般来说都得强制定义一遍，否则很难知道信号对应数据是什么
***********************************************************/
/*发送数据类型
***********************************************/


/***********************************************************
* serv trig 数据类型定义
* 一般只定义serv数据，trig类型引用当前头文件
* 只需要把发送的数据定义出来，收发接口使用的是统一接口，无其他定义
* 信号数据类型一般来说都得强制定义一遍，否则很难知道信号对应数据是什么
***********************************************************/
/*服务数据类型
***********************************************/
typedef struct{
    uint32 id;
    hTU_BYTES_DATA frame;
} TS_FRAME_TRANS, *hTS_FRAME_TRANS;
typedef struct{
    uint32 id;
    uint16 bit_start;
    uint16 bit_len;
    uint32* value;
} TS_FRAME_GET, *hTS_FRAME_GET;
typedef struct{
    uint32 id;
    uint16 bit_start;
    uint16 bit_len;
    uint32 value;
} TS_FRAME_SET, *hTS_FRAME_SET;
typedef struct{
    uint32 id;
    uint16 byte_index;
    uint8* value;
} TS_FRAME_BYTE, *hTS_FRAME_BYTE;

/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnFrameMatrix_init(void);
/*服务
***********************************************/
void serv_CpnFrameMatrix_get_frame(void *buff);
/*服务
***********************************************/
void serv_CpnFrameMatrix_set_frame(void *buff);
/*服务--更新帧数据
***********************************************/
void serv_CpnFrameMatrix_update_frame(void *buff);
/*服务--读取索引字节
***********************************************/
void serv_CpnFrameMatrix_get_frame_byte(void *buff);

/*接口触发
***********************************************/
void trig_CpnFrameMatrix_inf_sentFrame(uint32 id, hTU_BYTES_DATA frame);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNFRAMEMATRIX(_)          \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNFRAMEMATRIX(_)      \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNFRAMEMATRIX(_)          \
    _(sig_serv_CpnFrameMatrix_init,serv_CpnFrameMatrix_init) \
    _(sig_serv_CpnFrameMatrix_get_frame,serv_CpnFrameMatrix_get_frame) \
    _(sig_serv_CpnFrameMatrix_set_frame,serv_CpnFrameMatrix_set_frame) \
    _(sig_serv_CpnFrameMatrix_update_frame,serv_CpnFrameMatrix_update_frame) \
    _(sig_serv_CpnFrameMatrix_get_frame_byte,serv_CpnFrameMatrix_get_frame_byte) \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNFRAMEMATRIX(_)      \
    _(sig_trig_CpnFrameMatrix_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnFrameMatrix_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnFrameMatrix_delay,sig_serv_CpnSch_delay) \
    _(sig_trig_CpnFrameMatrix_now,sig_serv_CpnSch_now)     \
    _(sig_trig_CpnFrameMatrix_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnFrameMatrix_sentFrame,sig_serv_Abi_sentCanFrame) \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
void taskCpnFrameMatrix(void);

#endif /*CPNFRAMEMATRIXSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
