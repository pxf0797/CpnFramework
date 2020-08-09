/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Func.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/07 11:40:58
* Description  : 
* Others       : 
* History      : 200707 pxf 初次建立
***************************************************************************/

#ifndef FUNC_H_
#define FUNC_H_

/*头文件包含*/
#include "../../standType/standType.h"


/*名称 : 低通滤波(Low-pass filter)
* 输入 : 无
* 输出 : 无
* 其他 : // a=0-1，本次滤波结果=(1-a)*本次采样值+a*上次滤波结果
		// Y(n) = αX(n)+(1-α)Y(n-1)
		// 为了优化计算效率，a只取1/(2^N)，最小值为1/2
		// Y(n)= (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
		//     = (X(n)+((2^N)-1)Y(n-1))/(2^N)
***********************************************/
#define lowpassFilter(newValue, lastValue, n)  (((newValue) + (((lastValue) << (n)) - (lastValue))) >> (n))


#endif /*FUNC_H_*/

/**************************** Copyright(C) pxf ****************************/
