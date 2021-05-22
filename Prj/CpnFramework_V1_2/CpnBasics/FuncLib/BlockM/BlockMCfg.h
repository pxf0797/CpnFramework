/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : BlockMCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2021/03/20 15:25:52
* Description  : BlockM类及接口声明头文件
* Others       :
* History      : 210320 pxf 初次建立
***************************************************************************/

#ifndef BLOCKMCFG_H_
#define BLOCKMCFG_H_

/*头文件包含*/

/***********************************************************
* 版本定义
***********************************************************/
#define BLOCKMCFG_MACRO_VERSION            0xC01D00    /* C代表V，D代表.，当前版本V1.00 */

/***********************************************************
* 配置参数
***********************************************************/
/*内存配置参数
***********************************************/
typedef uint32 blockMType; /* size should not bigger than 32, otherwise BLOCKMCFG_MANAG_TYPE_BITS need to be configured manually */
#define BLOCKMCFG_MANAG_TYPE_BITS               ((sizeof(blockMType)>>1u)+3u)//0x5u//0x4u//
#define BLOCKMCFG_MANAG_TYPE_MASK               ((((blockMType)1u)<<BLOCKMCFG_MANAG_TYPE_BITS)-1u)//0x0000001Ful//0x000Fu//
#define BLOCKMCFG_MANAG_TYPE_FULL_MASK          (((blockMType)0u)-1u)//0xFFFFFFFFul//0xFFFFu//

#define BLOCKMCFG_MASK_SIZE(num)                (num>>BLOCKMCFG_MANAG_TYPE_BITS)
#define BLOCKMCFG_MASK_ADD_SIZE(num)            ((num&BLOCKMCFG_MANAG_TYPE_MASK)?1U:0U)
#define BLOCKMCFG_CAL_MASK_SIZE(num)            (BLOCKMCFG_MASK_SIZE(num)+BLOCKMCFG_MASK_ADD_SIZE(num))

/* !!!分配管理空间时一定要把当前宏加上，否则空间不够，接近最大分配个数时会溢出 */
#define BLOCKMCFG_CAL_ALL_MASK_SIZE(num)        (sizeof(blockMType)*((BLOCKMCFG_CAL_MASK_SIZE(num)<<1U) \
                                                +BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(num)) \
                                                +BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(num)))))
/*
 * 示例
 * 以管理uint32分配为例
 *
 * #define MANAG_BLOCK_SIZE   80u
 * uint8 ulDataSpace[BLOCKMCFG_CAL_ALL_MASK_SIZE(MANAG_BLOCK_SIZE)+(MANAG_BLOCK_SIZE*sizeof(uint32))];
 * */


#endif /*BLOCKMCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
