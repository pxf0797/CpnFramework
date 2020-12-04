/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErrCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  :
* Others       :
* History      : 200707 pxf 初次建立
***************************************************************************/

#ifndef CPNERRCFG_H_
#define CPNERRCFG_H_

/*头文件包含*/


/***********************************************************
* 配置参数
***********************************************************/
#define CPNERR_FIFO_BUFF_LENGTH            64U   /* 队列存储故障个数 */
/*错误上报ID，需要在所有模块都在此文件内进行注册
***********************************************/
typedef enum{
    CPNSCHCFG_ERR_ID,
    CPNSOURCECFG_ERR_ID,
    CPNSINKSCFG_ERR_ID
} TE_ERR_ID;




#endif /*CPNERRCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
