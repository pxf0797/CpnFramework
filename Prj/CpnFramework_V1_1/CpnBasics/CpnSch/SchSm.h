/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SchSm.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 14:24:20
* Description  : 状态机SchSm声明及状态机使用示例头文件
* Others       : 
* History      : 191228 pxf 初次建立
***************************************************************************/

#ifndef SCHSM_H_
#define SCHSM_H_

/*头文件包含*/
#include "../sm/sm.h"
#include "../standType/standType.h"
#include "./CpnSchCfg.h"

/*状态机SchSm使用示例：
* 当前状态机已在SMDF中定义出实体SchSm，需要做的只是让其运行起来
* 状态机运行方式有两种直接给时钟驱动的SMR和使用自定义记录状态后进驱动的SMRE
***********************************************
* SMR方式
***********************************************
void test(void){
    while(1){SMR(SchSm);};
}
***********************************************
* SMRE方式
***********************************************
void test2(void){
    static SchSmRec SchSmRunRec = {SchSm_sta_init};
    while(1){SMRE(SchSm, SchSmRunRec);};
}
***********************************************/

/*接口声明
***********************************************/
typedef void(*task)(void);                        // 任务定义

/*任务组声明
***********************************************/
typedef struct{
    uint16 startTick[sizeof(taskGroupType)*8];    // 调度周期起始节拍
    uint16 prdTick[sizeof(taskGroupType)*8];      // 周期调度节拍
    taskGroupType unstartMask;                    // 任务未启动掩码
    taskGroupType actMask;                        // 激活请求任务掩码
    taskGroupType taskMask;                       // 已分配任务掩码
    task taskGroup[sizeof(taskGroupType)*8];      // 任务组
} taskGroupSm;

/*状态机SchSm状态序列定义
* 注意其中SchSm_init,SchSm_default未在此定义，默认会给出
***********************************************/
#define SCHSM_LIST(_)         \
    _(SchSm, update)          \
    _(SchSm, execute)         \
    _(SchSm, updateBgTask)


/*状态机SchSm声明
* 已给出状态记录next,及上一状态last，其他参数需自行添加
***********************************************/
SMDC(SchSm, SCHSM_LIST){
    sta next;               // 运行状态记录
    sta last;               // 上一状态记录
    uint16 ticker;          // 计数
    uint16 tickerLast;      // 旧计数
    uint16 taskGroupNum;    // 任务组数
    taskGroupSm taskGroups[CPN_SCH_GROUP_TOTAL_NUMS];  // 任务组
    void *CpnSch;           // 注入组件类
};
extern SchSmRec SchSmRunRec;

/*log_2n 纯粹求2^n的对应的对数n
* 输入: 2^n
* 输出: n
***********************************************/
static inline uint16 log_2n(uint32 num){
    uint16 n = 0;
    if(num & 0xFFFF0000U){n += 16;}
    if(num & 0xFF00FF00U){n += 8;}
    if(num & 0xF0F0F0F0U){n += 4;}
    if(num & 0xCCCCCCCCU){n += 2;}
    if(num & 0xAAAAAAAAU){n += 1;}
    return n;
}

// 低通滤波(Low-pass filter)
// a=0-1，本次滤波结果=(1-a)*本次采样值+a*上次滤波结果
// Y(n) = αX(n)+(1-α)Y(n-1)
// 为了优化计算效率，a只取1/(2^N)，最小值为1/2
// Y(n)= (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
//     = (X(n)+((2^N)-1)Y(n-1))/(2^N)
#define lowpassFilter(newValue, lastValue, n)  (((newValue) + (((lastValue) << (n)) - (lastValue))) >> (n))

#endif /*SCHSM_H_*/

/**************************** Copyright(C) pxf ****************************/
