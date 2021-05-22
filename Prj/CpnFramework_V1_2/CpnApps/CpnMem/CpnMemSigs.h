/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMemSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/09 11:38:50
* Description  : CpnMem组件信号声明头文件
* Others       :
* History      : 201209 pxf 初次建立
***************************************************************************/

#ifndef CPNMEMSIGS_H_
#define CPNMEMSIGS_H_

/*头文件包含*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* 版本定义
***********************************************************/
#define CPNMEMSIGS_MACRO_VERSION        0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

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
    void *pointer;
    /* if function is memMalloc and getSize, then indication is size;
     * if function is isPointerSet, then indication is TRUE/FALSE;
     * if function is getIndex, then indication is index;
     * */
    uint16 indication;
} TS_MEM_POINTER, *hTS_MEM_POINTER;


/***********************************************************
* serv trig 信号接口定义
* 类继承的接口就是触发信号接口，在接口函数中使用触发信号进行触发
***********************************************************/
/*组件初始化服务
***********************************************/
void serv_CpnMem_init(void);
/*服务
***********************************************/
void serv_CpnMem_memMalloc(void *buff);
/*服务
***********************************************/
void serv_CpnMem_memFree(void *buff);
/*服务
***********************************************/
void serv_CpnMem_isPointerSet(void *buff);
/*服务
***********************************************/
void serv_CpnMem_getSize(void *buff);
/*服务
***********************************************/
void serv_CpnMem_getIndex(void *buff);

/*服务
***********************************************/
void serv_CpnMem_memStatus(void *buff);

/*接口触发
***********************************************/
//void trig_CpnMem_inf_infFunc(void);



/***********************************************************
* get set信号列表
***********************************************************/
/*发送信号列表
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMEM(_)                  \

/*接收信号列表
* 配置信号时需要检查发送信号的长度对信号进行映射
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEM(_)              \



/***********************************************************
* trig serv信号列表
***********************************************************/
/*服务信号列表
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMEM(_)                  \
    _(sig_serv_CpnMem_init,serv_CpnMem_init)               \
    _(sig_serv_CpnMem_memMalloc,serv_CpnMem_memMalloc)     \
    _(sig_serv_CpnMem_memFree,serv_CpnMem_memFree)         \
    _(sig_serv_CpnMem_isPointerSet,serv_CpnMem_isPointerSet) \
    _(sig_serv_CpnMem_getSize,serv_CpnMem_getSize)         \
    _(sig_serv_CpnMem_getIndex,serv_CpnMem_getIndex)       \
    _(sig_serv_CpnMem_memStatus,serv_CpnMem_memStatus)     \

/*触发信号列表
* 配置信号时需要检查服务信号的长度对信号进行映射
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEM(_)              \
    _(sig_trig_CpnMem_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnMem_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnMem_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnMem_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnMem_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
* 组件运行任务
***********************************************************/
/*运行任务声明
***********************************************/
// void taskCpnMem(void);

#endif /*CPNMEMSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
