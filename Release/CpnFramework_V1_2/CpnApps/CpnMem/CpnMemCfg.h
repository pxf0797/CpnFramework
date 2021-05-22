/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMemCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/09 11:38:50
* Description  :
* Others       :
* History      : 201209 pxf 初次建立
***************************************************************************/

#ifndef CPNMEMCFG_H_
#define CPNMEMCFG_H_

/*头文件包含*/
#include "../../cpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
* 配置参数
***********************************************************/
/*CpnMemCfg错误上报ID，需要在CpnErrCfg.h文件内进行注册
***********************************************/
//#define CPNMEMCFG_ERR_ID                0U    /* CpnMemCfg组件报错配置ID */
#define CPNMEMCFG_MEM_SPACE_SIZE          (8U*1024U) /* 管理内存空间大小 */

#define CPNMEMCFG_DBG_INFO_PRINT_FILE     1U  /* 打印到文件，0否，1是 */



#endif /*CPNMEMCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
