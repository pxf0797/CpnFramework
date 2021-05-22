/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : SineTable.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/07/24 16:17:08
* Description  :
* Others       :
* History      : 200724 pxf 初次建立
***************************************************************************/

#ifndef SINETABLE_H_
#define SINETABLE_H_

/*头文件包含*/
#include "../../CpnBasics/standType/standType.h"

//#define PI 3.1415926535897932384626433832795028841971       //定义圆周率值
#define PI 3.14159265359

/*名称 : SineTable()
* 输入 : pi 所要计算正弦值弧度值，范围0--2*PI，不满足时需要先转换
* 输出 : 输入值pi的正弦值
* 其他 : 无
***********************************************/
float32 SineTable(float32 angle);

#endif /*SINETABLE_H_*/

/**************************** Copyright(C) pxf ****************************/
