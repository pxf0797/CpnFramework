/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Func.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:40:58
* Description  : 
* Others       : 
* History      : 200707 pxf ���ν���
***************************************************************************/

#ifndef FUNC_H_
#define FUNC_H_

/*ͷ�ļ�����*/
#include "../../standType/standType.h"


/*���� : ��ͨ�˲�(Low-pass filter)
* ���� : ��
* ��� : ��
* ���� : // a=0-1�������˲����=(1-a)*���β���ֵ+a*�ϴ��˲����
		// Y(n) = ��X(n)+(1-��)Y(n-1)
		// Ϊ���Ż�����Ч�ʣ�aֻȡ1/(2^N)����СֵΪ1/2
		// Y(n)= (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
		//     = (X(n)+((2^N)-1)Y(n-1))/(2^N)
***********************************************/
#define lowpassFilter(newValue, lastValue, n)  (((newValue) + (((lastValue) << (n)) - (lastValue))) >> (n))


#endif /*FUNC_H_*/

/**************************** Copyright(C) pxf ****************************/
