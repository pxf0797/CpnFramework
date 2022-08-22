/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : StandType.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 14:55:28
 * Description  : Basic data types definition.
 * Others       :
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef STANDTYPE_H_
#define STANDTYPE_H_

/* Include head files. */

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define STANDTYPE_MACRO_VERSION         0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/* Platform definition.
 **********************************************/
#ifndef LITTLE_END
#define LITTLE_END     0
#endif
#ifndef BIG_END
#define BIG_END        1
#endif
#ifndef PLATFORM_END
#define PLATFORM_END   LITTLE_END
#endif

/* Basic data type definition.
 **********************************************/
#ifndef FALSE
#define FALSE    0
#endif
#ifndef TRUE
#define TRUE     1
#endif
#ifndef NULL
#define NULL     ((void *)0)
#endif

/* Integer definition.
 **********************************************/
typedef char                  int8;
typedef short                 int16;
typedef long                  int32;
typedef long long             int64;

/* Unsigned Integer definition.
 **********************************************/
typedef unsigned char         uint8;
typedef unsigned short        uint16;
typedef unsigned long         uint32;
typedef unsigned long long    uint64;

/* Float definition.
 **********************************************/
typedef float                 float32;
typedef double                float64;

/* address width definition.
 **********************************************/
typedef uint32                addrType,*haddrType;
#ifndef ADDR_VALUE
#define ADDR_VALUE(x)         (*(haddrType)(&(x)))
#endif

#endif /*STANDTYPE_H_*/

/**************************** Copyright(C) pxf ****************************/
