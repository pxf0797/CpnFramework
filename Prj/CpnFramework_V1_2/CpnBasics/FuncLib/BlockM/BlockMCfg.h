/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : BlockMCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2021/03/20 15:25:52
* Description  : BlockM�༰�ӿ�����ͷ�ļ�
* Others       :
* History      : 210320 pxf ���ν���
***************************************************************************/

#ifndef BLOCKMCFG_H_
#define BLOCKMCFG_H_

/*ͷ�ļ�����*/

/***********************************************************
* �汾����
***********************************************************/
#define BLOCKMCFG_MACRO_VERSION            0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

/***********************************************************
* ���ò���
***********************************************************/
/*�ڴ����ò���
***********************************************/
typedef uint32 blockMType; /* size should not bigger than 32, otherwise BLOCKMCFG_MANAG_TYPE_BITS need to be configured manually */
#define BLOCKMCFG_MANAG_TYPE_BITS               ((sizeof(blockMType)>>1u)+3u)//0x5u//0x4u//
#define BLOCKMCFG_MANAG_TYPE_MASK               ((((blockMType)1u)<<BLOCKMCFG_MANAG_TYPE_BITS)-1u)//0x0000001Ful//0x000Fu//
#define BLOCKMCFG_MANAG_TYPE_FULL_MASK          (((blockMType)0u)-1u)//0xFFFFFFFFul//0xFFFFu//

#define BLOCKMCFG_MASK_SIZE(num)                (num>>BLOCKMCFG_MANAG_TYPE_BITS)
#define BLOCKMCFG_MASK_ADD_SIZE(num)            ((num&BLOCKMCFG_MANAG_TYPE_MASK)?1U:0U)
#define BLOCKMCFG_CAL_MASK_SIZE(num)            (BLOCKMCFG_MASK_SIZE(num)+BLOCKMCFG_MASK_ADD_SIZE(num))

/* !!!�������ռ�ʱһ��Ҫ�ѵ�ǰ����ϣ�����ռ䲻�����ӽ����������ʱ����� */
#define BLOCKMCFG_CAL_ALL_MASK_SIZE(num)        (sizeof(blockMType)*((BLOCKMCFG_CAL_MASK_SIZE(num)<<1U) \
                                                +BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(num)) \
                                                +BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(BLOCKMCFG_CAL_MASK_SIZE(num)))))
/*
 * ʾ��
 * �Թ���uint32����Ϊ��
 *
 * #define MANAG_BLOCK_SIZE   80u
 * uint8 ulDataSpace[BLOCKMCFG_CAL_ALL_MASK_SIZE(MANAG_BLOCK_SIZE)+(MANAG_BLOCK_SIZE*sizeof(uint32))];
 * */


#endif /*BLOCKMCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
