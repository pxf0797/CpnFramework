/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  :
* Others       :
* History      : 200730 pxf 初次建立
***************************************************************************/

#ifndef CPNSINKSCFG_H_
#define CPNSINKSCFG_H_

/*头文件包含*/
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
* 配置参数
***********************************************************/
/*CpnSinksCfg错误上报ID，需要在CpnErrCfg.h文件内进行注册
***********************************************/
//#define CPNSINKSCFG_ERR_ID              0U    /* CpnSinksCfg组件报错配置ID */
#define CPNSINKSCFG_CACHE_TYPE_GROUPS       1U    /* 信号波形对应组数 */

/*errDefine
***********************************************************************************************************************/
#define CPNSINKSCFG_CACHE_GROUP_FULL                      0x0000U                   /* 信号组已满 */
#define CPNSINKSCFG_CACHE_INDEX_OUT_RANGE                 0x0010U                   /* 信号索引超范围 */
#define CPNSINKSCFG_CACHE_INDEX_NOT_EXIST                 0x0011U                   /* 信号索不存在 */
#define CPNSINKSCFG_CACHE_NO_SUCH_KIND                    0x0020U                   /* 无此信号类型 */
#define CPNSINKSCFG_CACHE_DATA_SIZE_ERR                   0x0030U                   /* 信号数据大小错误 */
#define CPNSINKSCFG_CACHE_DATA_BUFF_ERR                   0x0031U                   /* 信号数据缓存地址错误 */
#define CPNSINKSCFG_CACHE_FIFO_INIT_ERR                   0x0032U                   /* 缓存初始化失败 */

#endif /*CPNSINKSCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
