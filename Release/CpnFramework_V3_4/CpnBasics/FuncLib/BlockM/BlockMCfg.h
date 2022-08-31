/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : BlockMCfg.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 09:07:04
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef BLOCKMCFG_H_
#define BLOCKMCFG_H_

/* Include head files. */

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define BLOCKMCFG_MACRO_VERSION         0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Configure parameters.
 **********************************************************/
/* Memory parameters.
 **********************************************/
typedef uint32 blockMType; /* size should not bigger than 32, otherwise BLOCKMCFG_MANAG_TYPE_BITS need to be configured manually */
#define BLOCKMCFG_MANAG_TYPE_BITS               ((sizeof(blockMType)>>1u)+3u)//0x5u//0x4u//
#define BLOCKMCFG_MANAG_TYPE_MASK               ((((blockMType)1u)<<BLOCKMCFG_MANAG_TYPE_BITS)-1u)//0x0000001Ful//0x000Fu//
#define BLOCKMCFG_MANAG_TYPE_FULL_MASK          (((blockMType)0u)-1u)//0xFFFFFFFFul//0xFFFFu//

#define BLOCKMCFG_MASK_SIZE(num)                ((num)>>BLOCKMCFG_MANAG_TYPE_BITS)
#define BLOCKMCFG_MASK_ADD_SIZE(num)            (((num)&BLOCKMCFG_MANAG_TYPE_MASK)?1U:0U)
#define BLOCKMCFG_CAL_MASK_SIZE(num)            (BLOCKMCFG_MASK_SIZE(num)+BLOCKMCFG_MASK_ADD_SIZE(num))

/* !!! The current macro must be added when allocating management space,
 * otherwise the space is not enough, and it will overflow when it approaches the maximum allocated number. */
#define BLOCKMCFG_CAL_ALL_MASK_SIZE(num)        (sizeof(blockMType)*((BLOCKMCFG_CAL_MASK_SIZE(num)<<1U) \
                                                +BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(num)) \
                                                +BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(num)))))
/* !!! Use the current macro to calculate the management space size. */
#define BLOCKMCFG_CAL_MANAGE_SIZE(dataType,num) (BLOCKMCFG_CAL_ALL_MASK_SIZE(num)+((num)*sizeof(dataType)))

/*
 * Example:
 * Take managing uint32 allocation as an example.
 *
 * #define MANAG_BLOCK_SIZE   80u
 * //uint8 ulDataSpace[BLOCKMCFG_CAL_ALL_MASK_SIZE(MANAG_BLOCK_SIZE)+(MANAG_BLOCK_SIZE*sizeof(uint32))];
 * uint8 ulDataSpace[BLOCKMCFG_CAL_MANAGE_SIZE(uint32,MANAG_BLOCK_SIZE)];
 */

#endif /*BLOCKMCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
