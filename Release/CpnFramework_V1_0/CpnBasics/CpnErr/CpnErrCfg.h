/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnErrCfg.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:54:53
* Description  :
* Others       :
* History      : 200707 pxf ���ν���
***************************************************************************/

#ifndef CPNERRCFG_H_
#define CPNERRCFG_H_

/*ͷ�ļ�����*/


/***********************************************************
* ���ò���
***********************************************************/
#define CPNERR_FIFO_BUFF_LENGTH            64U   /* ���д洢���ϸ��� */
/*�����ϱ�ID����Ҫ������ģ�鶼�ڴ��ļ��ڽ���ע��
***********************************************/
typedef enum{
    CPNSCHCFG_ERR_ID,
    CPNSOURCECFG_ERR_ID,
    CPNSINKSCFG_ERR_ID
} TE_ERR_ID;




#endif /*CPNERRCFG_H_*/

/**************************** Copyright(C) pxf ****************************/
