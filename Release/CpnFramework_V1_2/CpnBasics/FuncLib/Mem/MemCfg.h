/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : MemCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/05 13:47:11
* Description  :
* Others       :
* History      : 201205 pxf 初次建立
***************************************************************************/

#ifndef MEMCFG_H_
#define MEMCFG_H_

/*头文件包含*/

/***********************************************************
* 版本定义
***********************************************************/
#define MEMCFG_MACRO_VERSION            0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/***********************************************************
* 配置参数
***********************************************************/
/*内存配置参数
***********************************************/
typedef uint32 memMType;
#define MEM_MANAG_TYPE_BITS              0x5u//0x4u//
#define MEM_MANAG_TYPE_MASK              0x0000001Ful//0x000Fu//
#define MEM_MANAG_TYPE_FULL_MASK         0xFFFFFFFFul//0xFFFFu//
#define MEMCFG_MEM_NEW_MAX_NUM           (4U*32U)     /* 最大新建变量个数n*32，因当前以uint32作为MemBlock管理映射 */


#define MEMCFG_MEM_UNUSED_MAX_NUM        ((MEMCFG_MEM_NEW_MAX_NUM>>1U)+1U)
#define MEMCFG_MEM_BLOCK_MAX_NUM         (MEMCFG_MEM_NEW_MAX_NUM<<1U)//(MEMCFG_MEM_NEW_MAX_NUM+MEMCFG_MEM_UNUSED_MAX_NUM)//
#define MEMCFG_MEM_BLOCK_MASK_MAX_NUM    (MEMCFG_MEM_BLOCK_MAX_NUM>>MEM_MANAG_TYPE_BITS)
#if ((MEMCFG_MEM_BLOCK_MAX_NUM>>MEM_MANAG_TYPE_BITS)&MEM_MANAG_TYPE_MASK)
#define MEMCFG_MEM_MASK_MASK_NUM         ((MEMCFG_MEM_BLOCK_MASK_MAX_NUM>>MEM_MANAG_TYPE_BITS)+1U)
#else
#define MEMCFG_MEM_MASK_MASK_NUM         (MEMCFG_MEM_BLOCK_MASK_MAX_NUM>>MEM_MANAG_TYPE_BITS)
#endif



#endif /*MEMCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
