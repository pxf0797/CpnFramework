/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SetGet.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:14:19
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef SETGET_H_
#define SETGET_H_

/* Include head files. */
#include "StandType.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define SETGET_MACRO_VERSION            0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/* Signals definition.
 **********************************************/
#define SIGNAL_SET_DEFINE(signal_set,len)                       signal_set,                                             /* Send signal name definition. */
#define SIGNAL_GET_DEFINE(signal_get,signal_set)                signal_get,                                             /* Receive signal name definition. */
#define SIGNAL_SET_LEN_DEFINE(signal_set,len)                   signal_set##Len = len,                                  /* Send signal length definition. */
#define SIGNAL_GET_INDEX_MAP_DEFINE(signal_get,signal_set)      signal_get##Map = signal_set,                           /* Receive signal maps. */
#define SIGNAL_SET_LEN_ADD_DEFINE(signal_set,len)               +signal_set##Len                                        /* Send signal length super position. */
#define SIGNAL_SET_REGISTER(name,signal_set,len)                do{                                                      \
                                                                    uint32 index = signal_set;                           \
                                                                    if(!signal_set){                                     \
                                                                        name##SigSetIndex[signal_set] = signal_set##Len; \
                                                                        break;                                           \
                                                                    }                                                    \
                                                                    index--;                                             \
                                                                    name##SigSetIndex[index+1u] = (signal_set##Len+name##SigSetIndex[index]); \
                                                                    /* Send signal register in array. */                 \
                                                                }while(0);
#define SIGNAL_GET_REGISTER(name,signal_get,signal_set)         name##SigGetIndex[signal_get] = signal_get##Map;        /* Receive signal register in array. */


/* Send Signals index definition.
 **********************************************/
#define SIGNAL_SET_ENUM(name,list_set)                 \
enum name##SigSet{                                     \
    list_set(SIGNAL_SET_DEFINE)                        \
    name##SigSetMax                                    \
}
/* Send Signals length definition.
 **********************************************/
#define SIGNAL_SET_LEN_MAX(name,list_set)              (0 list_set(SIGNAL_SET_LEN_ADD_DEFINE))
#define SIGNAL_SET_LEN_ENUM(name,list_set)             \
enum name##SigSetLen{                                  \
    list_set(SIGNAL_SET_LEN_DEFINE)                    \
    name##SigSetLenMax                                 \
}
/* Send Signals maps.
 **********************************************/
#define SIGNAL_SET_MAP(name,list_set)                  \
SIGNAL_SET_ENUM(name,list_set);                        \
SIGNAL_SET_LEN_ENUM(name,list_set)
/* Send Signals store definition.
 **********************************************/
#define BUFF_SET_DEFINE(name,list_set)                 \
static asynType name##SigSetIndex[name##SigSetMax];    \
static uint8 name##SigSetBuff[SIGNAL_SET_LEN_MAX(name,list_set)]


/* Receive Signals index definition.
 **********************************************/
#define SIGNAL_GET_MAP_ENUM(name,list_get)             \
enum name##SigGet{                                     \
    list_get(SIGNAL_GET_DEFINE)                        \
    name##SigGetMax                                    \
}
/* Receive Signals length definition.
 **********************************************/
#define SIGNAL_GET_INDEX_MAP_ENUM(name,list_get)       \
enum name##SigGetMap{                                  \
    list_get(SIGNAL_GET_INDEX_MAP_DEFINE)              \
    name##SigGetMapMax                                 \
}
/* Receive Signals maps.
 **********************************************/
#define SIGNAL_GET_MAP(name,list_get)                  \
SIGNAL_GET_MAP_ENUM(name,list_get);                    \
SIGNAL_GET_INDEX_MAP_ENUM(name,list_get)
/* Receive Signals store definition.
 **********************************************/
#define BUFF_GET_DEFINE(name,list_get)                 \
static asynType name##SigGetIndex[name##SigGetMax]


/* Register Signals.
 **********************************************/
#define SIGNALS_GETSET_REGISTER(list,signal_register)  do{ \
    list(signal_register)                              \
}while(0)
/* Map Signals.
 **********************************************/
#define SIGNAL_SETGET_MAP(name,list_set,list_get)      \
SIGNAL_SET_MAP(name,list_set);                         \
SIGNAL_GET_MAP(name,list_get)
/* Store Signals.
 **********************************************/
#define BUFF_SETGET_DEFINE(name,list_set,list_get)     \
BUFF_SET_DEFINE(name,list_set);                        \
BUFF_GET_DEFINE(name,list_get)

#endif /*SETGET_H_*/

/**************************** Copyright(C) pxf ****************************/
