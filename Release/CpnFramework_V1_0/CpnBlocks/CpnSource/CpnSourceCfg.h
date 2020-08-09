/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnSourceCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 15:10:50
* Description  :
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

#ifndef CPNSOURCECFG_H_
#define CPNSOURCECFG_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/CpnErr/CpnErrCfg.h"

/***********************************************************
* ���ò���
***********************************************************/
/*CpnSourceCfg�����ϱ�ID����Ҫ��CpnErrCfg.h�ļ��ڽ���ע��
***********************************************/
//#define CPNSOURCECFG_ERR_ID             0U    /* CpnSourceCfg�����������ID */
#define CPNSOURCECFG_WAVE_TYPE_GROUPS       1U    /* �źŲ��ζ�Ӧ���� */

/*errDefine
***********************************************************************************************************************/
#define CPNSOURCECFG_WAVE_GROUP_FULL                      0x0000U                   /* �ź������� */
#define CPNSOURCECFG_WAVE_INDEX_OUT_RANGE                 0x0010U                   /* �ź���������Χ */
#define CPNSOURCECFG_WAVE_INDEX_NOT_EXIST                 0x0011U                   /* �ź��������� */
#define CPNSOURCECFG_WAVE_NO_SUCH_KIND                    0x0020U                   /* �޴��ź����� */
#define CPNSOURCECFG_WAVE_DUTY_OUT_RANGE                  0x0030U                   /* ����-ռ�ձȳ���Χ */
#define CPNSOURCECFG_WAVE_PHASE_OUT_RANGE                 0x0031U                   /* ����-��λ����Χ */

#endif /*CPNSOURCECFG_H_*/

/**************************** Copyright(C) pxf ****************************/
