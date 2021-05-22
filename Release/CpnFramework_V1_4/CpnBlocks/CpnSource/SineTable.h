/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SineTable.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 15:33:52
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef SINETABLE_H_
#define SINETABLE_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define SINETABLE_MACRO_VERSION         0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

//#define PI 3.1415926535897932384626433832795028841971
#define PI 3.14159265359

/* Function : SineTable()
 * Input    : pi needs to calculate the sine radian value, the range is 0--2*PI, if not satisfied, it needs to be converted first
 * Output   : The sine of the input value pi
 * Others   :
 **********************************************/
float32 SineTable(float32 angle);

#endif /*SINETABLE_H_*/

/**************************** Copyright(C) pxf ****************************/
