/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SineTable.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 16:17:08
* Description  :
* Others       :
* History      : 200724 pxf ���ν���
***************************************************************************/

#ifndef SINETABLE_H_
#define SINETABLE_H_

/*ͷ�ļ�����*/
#include "../../CpnBasics/standType/standType.h"

//#define PI 3.1415926535897932384626433832795028841971       //����Բ����ֵ
#define PI 3.14159265359

/*���� : SineTable()
* ���� : pi ��Ҫ��������ֵ����ֵ����Χ0--2*PI��������ʱ��Ҫ��ת��
* ��� : ����ֵpi������ֵ
* ���� : ��
***********************************************/
float32 SineTable(float32 angle);

#endif /*SINETABLE_H_*/

/**************************** Copyright(C) pxf ****************************/
