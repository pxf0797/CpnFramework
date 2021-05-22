/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/21 10:36:48
* Description  : CpnMatrixMap组件信号声明头文件
* Others       :
* History      : 201121 pxf 初次建立
***************************************************************************/

#ifndef CPNMATRIXMAPSIGS_H_
#define CPNMATRIXMAPSIGS_H_

/*头文件包含*/
#include "../../cpnRte/Rte/Rte.h"
#include "../CpnFrameMatrix/CpnFrameMatrixCfg.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNMATRIXMAPSIGS_MACRO_VERSION  0xC01D00    /* C代表V，D代表.，当前版本V1.00 */


/***********************************************************
* 信号映射
***********************************************************/
/*发送信号配置
***********************************************/
// #define FRAME_SET_SIG_LIST(_,...)                                               \
//     /* sig_name,            id,          bit_start, bit_len, dynamic parameters */ \
//     _(ulDataA,              0xAAAU,      20U,       5U,      __VA_ARGS__)       \
//     _(ulDataB,              0xAAAU,      28U,       1U,      __VA_ARGS__)       \
//     _(ulDataC,              0x100U,       0U,       5U,      __VA_ARGS__)       \
//     _(ulDataD,              0x100U,      19U,       9U,      __VA_ARGS__)       \
//     _(ulDataE,              0xF0AU,      10U,       2U,      __VA_ARGS__)       \
//     _(ulDataF,              0xF0AU,      17U,       3U,      __VA_ARGS__)       \
//     _(ulDataG,              0xF0AU,      40U,       5U,      __VA_ARGS__)       \

/*接收信号配置
***********************************************/
// #define FRAME_GET_SIG_LIST(_,...)                                               \
//     /* sig_name,            id,          bit_start, bit_len, dynamic parameters */ \
//     _(ulData1,              0x200U,      40U,       5U,      __VA_ARGS__)       \
//     _(ulData2,              0x200U,      28U,       1U,      __VA_ARGS__)       \
//     _(ulData3,              0x200U,       0U,       5U,      __VA_ARGS__)       \
//     _(ulData4,              0x200U,      19U,       9U,      __VA_ARGS__)       \
//     _(ulData5,              0xF8AU,      10U,       2U,      __VA_ARGS__)       \
//     _(ulData6,              0xF8AU,      17U,       3U,      __VA_ARGS__)       \
//     _(ulData7,              0xF8AU,      40U,       5U,      __VA_ARGS__)       \
//     _(ulData8,              0xF8AU,      60U,       1U,      __VA_ARGS__)       \


/***********************************************************
* 功能宏
***********************************************************/
#define FRAME_SET_SIG_ENUM_COMBINE(name,id,bit_start,bit_len,fill)    set_sig_##name,                              /* 发送信号枚举索引 */
#define FRAME_GET_SIG_ENUM_COMBINE(name,id,bit_start,bit_len,fill)    get_sig_##name,                              /* 接收信号枚举索引 */
#define FRAME_SET_SIG_ENUM_EXPANTION(frame_list)                      frame_list(FRAME_SET_SIG_ENUM_COMBINE,fill)  /* 发送信号枚举扩展 */
#define FRAME_GET_SIG_ENUM_EXPANTION(frame_list)                      frame_list(FRAME_GET_SIG_ENUM_COMBINE,fill)  /* 接收信号枚举扩展 */

#define FRAME_SET_SIG_COMBINE(name,id,bit_start,bit_len,fill)         {set_sig_##name,id,bit_start,bit_len,sig_trig_CpnMatrixMap_set_frame}, /* 发送信号映射表 */
#define FRAME_GET_SIG_COMBINE(name,id,bit_start,bit_len,fill)         {get_sig_##name,id,bit_start,bit_len,sig_trig_CpnMatrixMap_get_frame}, /* 接收信号映射表 */
#define FRAME_SET_SIG_EXPANTION(frame_list)                           frame_list(FRAME_SET_SIG_COMBINE,fill)       /* 发送信号枚举扩展 */
#define FRAME_GET_SIG_EXPANTION(frame_list)                           frame_list(FRAME_GET_SIG_COMBINE,fill)       /* 接收信号枚举扩展 */

#define FRAME_SET_SIG_SERV_DEC(name,id,bit_start,bit_len,fill)        void serv_CpnMatrixMap_set_##name(void *buff); /* set_sig服务函数声明 */
#define FRAME_GET_SIG_SERV_DEC(name,id,bit_start,bit_len,fill)        void serv_CpnMatrixMap_get_##name(void *buff); /* get_sig服务函数声明 */
#define FRAME_GET_SIG_SERV_DEC_EXPANTION(frame_list)                  frame_list(FRAME_GET_SIG_SERV_DEC,fill)      /* 发送信号服务声明扩展 */
#define FRAME_SET_SIG_SERV_DEC_EXPANTION(frame_list)                  frame_list(FRAME_SET_SIG_SERV_DEC,fill)      /* 接收信号服务声明扩展 */

//extern const TS_FRAME_MAP frameMapDatasSet[];
//extern const TS_FRAME_MAP frameMapDatasGet[];
#define FRAME_SET_SIG_SERV_DEF(name,id_,bit_start_,bit_len_,fill)        /* set_sig服务函数定义 */             \
void serv_CpnMatrixMap_set_##name(void *buff){                                                                \
    TS_FRAME_GETSET setData;                                                                                  \
    setData.id = frameMapDatasSet[set_sig_##name].id;                                                         \
    setData.bit_start = frameMapDatasSet[set_sig_##name].bit_start;                                           \
    setData.bit_len = frameMapDatasSet[set_sig_##name].bit_len;                                               \
    setData.value = ((uint32*)buff);                                                                          \
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasSet[set_sig_##name].sig_operation_name, (uint8*)&setData); \
}
#define FRAME_GET_SIG_SERV_DEF(name,id_,bit_start_,bit_len_,fill)        /* get_sig服务函数定义 */             \
void serv_CpnMatrixMap_get_##name(void *buff){                                                                \
    TS_FRAME_GETSET getData;                                                                                  \
    getData.id = frameMapDatasGet[get_sig_##name].id;                                                         \
    getData.bit_start = frameMapDatasGet[get_sig_##name].bit_start;                                           \
    getData.bit_len = frameMapDatasGet[get_sig_##name].bit_len;                                               \
    getData.value = ((uint32*)buff);                                                                          \
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasGet[get_sig_##name].sig_operation_name, (uint8*)&getData); \
}
#define FRAME_SET_SIG_SERV_DEF_EXPANTION(frame_list)     frame_list(FRAME_SET_SIG_SERV_DEF,fill)                   /* 发送信号服务定义扩展 */
#define FRAME_GET_SIG_SERV_DEF_EXPANTION(frame_list)     frame_list(FRAME_GET_SIG_SERV_DEF,fill)                   /* 接收信号服务定义扩展 */

#define FRAME_SET_SIG_SERV_LIST_RTESYN(name,id,bit_start,bit_len,X) X(sig_serv_CpnMatrixMap_set_##name,serv_CpnMatrixMap_set_##name) /* RTE发送信号配置 */
#define FRAME_GET_SIG_SERV_LIST_RTESYN(name,id,bit_start,bit_len,X) X(sig_serv_CpnMatrixMap_get_##name,serv_CpnMatrixMap_get_##name) /* RTE接收信号配置 */
#define FRAME_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)      FRAME_SET_SIG_LIST(FRAME_SET_SIG_SERV_LIST_RTESYN,_)      /* RTE发送信号扩展 */ \
                                                         FRAME_SET_SIG_LIST(FRAME_GET_SIG_SERV_LIST_RTESYN,_)      /* RTE发送信号扩展也可读 */
#define FRAME_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)      FRAME_GET_SIG_LIST(FRAME_GET_SIG_SERV_LIST_RTESYN,_)      /* RTE接收信号扩展 */

#define matrixMapSet(sig)                                sig_serv_CpnMatrixMap_set_##sig                           /* 发送信号映射 */
#define matrixMapGet(sig)                                sig_serv_CpnMatrixMap_get_##sig                           /* 接收信号映射 */

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
typedef enum{
    FRAME_SET_SIG_ENUM_EXPANTION(FRAME_SET_SIG_LIST)
    set_sig_num_max
} TE_FRAME_SET_SIG;
typedef enum{
    FRAME_GET_SIG_ENUM_EXPANTION(FRAME_GET_SIG_LIST)
    FRAME_GET_SIG_ENUM_EXPANTION(FRAME_SET_SIG_LIST)
    get_sig_num_max
} TE_FRAME_GET_SIG;
typedef struct{
    uint16 sig_index;
    uint32 id;
    uint16 bit_start;
    uint16 bit_len;
    uint16 sig_operation_name;
} TS_FRAME_MAP, *hTS_FRAME_MAP;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnMatrixMap_init(void);
/*服务--发送
* serv_CpnMatrixMap_set_ulDataA
***********************************************/
FRAME_SET_SIG_SERV_DEC_EXPANTION(FRAME_SET_SIG_LIST)
/*服务--接收
* serv_CpnMatrixMap_get_ulData1
***********************************************/
FRAME_GET_SIG_SERV_DEC_EXPANTION(FRAME_GET_SIG_LIST)
FRAME_GET_SIG_SERV_DEC_EXPANTION(FRAME_SET_SIG_LIST)


/*接口触发
***********************************************/
//void trig_CpnMatrixMap_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAP(_)            \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAP(_)        \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAP(_)            \
    _(sig_serv_CpnMatrixMap_init,serv_CpnMatrixMap_init)   \
    /*_(sig_serv_CpnMatrixMap_set_ulDataA,serv_CpnMatrixMap_set_ulDataA)*/ \
    /*_(sig_serv_CpnMatrixMap_get_ulData1,serv_CpnMatrixMap_get_ulData1)*/ \
    FRAME_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)            \
    FRAME_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)            \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAP(_)        \
    _(sig_trig_CpnMatrixMap_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMatrixMap_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMatrixMap_delay,sig_serv_CpnSch_delay)   \
    _(sig_trig_CpnMatrixMap_now,sig_serv_CpnSch_now)       \
    _(sig_trig_CpnMatrixMap_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnMatrixMap_get_frame,sig_serv_CpnFrameMatrix_get_frame) \
    _(sig_trig_CpnMatrixMap_set_frame,sig_serv_CpnFrameMatrix_set_frame) \
    _(sig_trig_CpnMatrixMap_update_frame,sig_serv_CpnFrameMatrix_update_frame) \
    _(sig_trig_CpnMatrixMap_get_frame_byte,sig_serv_CpnFrameMatrix_get_frame_byte) \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
// void taskCpnMatrixMap(void);

#endif /*CPNMATRIXMAPSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
