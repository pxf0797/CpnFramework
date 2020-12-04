/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSinksCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/30 11:50:50
* Description  :
* Others       :
* History      : 200730 pxf ���ν���
***************************************************************************/

#ifndef CPNSINKSCFG_H_
#define CPNSINKSCFG_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
* ���ò���
***********************************************************/
/*CpnSinksCfg�����ϱ�ID����Ҫ��CpnErrCfg.h�ļ��ڽ���ע��
***********************************************/
//#define CPNSINKSCFG_ERR_ID              0U    /* CpnSinksCfg�����������ID */
#define CPNSINKSCFG_CACHE_TYPE_GROUPS       1U    /* �źŲ��ζ�Ӧ���� */

/*errDefine
***********************************************************************************************************************/
#define CPNSINKSCFG_CACHE_GROUP_FULL                      0x0000U                   /* �ź������� */
#define CPNSINKSCFG_CACHE_INDEX_OUT_RANGE                 0x0010U                   /* �ź���������Χ */
#define CPNSINKSCFG_CACHE_INDEX_NOT_EXIST                 0x0011U                   /* �ź��������� */
#define CPNSINKSCFG_CACHE_NO_SUCH_KIND                    0x0020U                   /* �޴��ź����� */
#define CPNSINKSCFG_CACHE_DATA_SIZE_ERR                   0x0030U                   /* �ź����ݴ�С���� */
#define CPNSINKSCFG_CACHE_DATA_BUFF_ERR                   0x0031U                   /* �ź����ݻ����ַ���� */
#define CPNSINKSCFG_CACHE_FIFO_INIT_ERR                   0x0032U                   /* �����ʼ��ʧ�� */

#endif /*CPNSINKSCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
