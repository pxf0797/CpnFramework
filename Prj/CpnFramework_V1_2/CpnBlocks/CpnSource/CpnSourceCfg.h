/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  :
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

#ifndef CPNSOURCECFG_H_
#define CPNSOURCECFG_H_

/*头文件包含*/
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
* 配置参数
***********************************************************/
/*CpnSourceCfg错误上报ID，需要在CpnErrCfg.h文件内进行注册
***********************************************/
//#define CPNSOURCECFG_ERR_ID             0U    /* CpnSourceCfg组件报错配置ID */
#define CPNSOURCECFG_WAVE_TYPE_GROUPS       1U    /* 信号波形对应组数 */

/*errDefine
***********************************************************************************************************************/
#define CPNSOURCECFG_WAVE_GROUP_FULL                      0x0000U                   /* 信号组已满 */
#define CPNSOURCECFG_WAVE_INDEX_OUT_RANGE                 0x0010U                   /* 信号索引超范围 */
#define CPNSOURCECFG_WAVE_INDEX_NOT_EXIST                 0x0011U                   /* 信号索不存在 */
#define CPNSOURCECFG_WAVE_NO_SUCH_KIND                    0x0020U                   /* 无此信号类型 */
#define CPNSOURCECFG_WAVE_DUTY_OUT_RANGE                  0x0030U                   /* 参数-占空比超范围 */
#define CPNSOURCECFG_WAVE_PHASE_OUT_RANGE                 0x0031U                   /* 参数-相位超范围 */

#endif /*CPNSOURCECFG_H_*/

/**************************** Copyright(C) pxf ****************************/
