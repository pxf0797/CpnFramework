/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : TriggerService.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 10:14:39
 * Description  :
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef TRIGGERSERVICE_H_
#define TRIGGERSERVICE_H_

/* Include head files. */
#include "../../CpnBasics/StandType/StandType.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define TRIGGERSERVICE_MACRO_VERSION    0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/* Signals definition.
 **********************************************/
#define SIGNAL_SERV_DEFINE(signal_serv,serv)                        signal_serv,                                          /* Service signal name definition. */
#define SIGNAL_TRIG_DEFINE(signal_trig,signal_serv)                 signal_trig,                                          /* Trigger signal name definition. */
#define SIGNAL_SERV_SERV_DEFINE(signal_serv,serv)                   signal_serv##Serv = serv,                             /* Service signal combine definition. */
#define SIGNAL_TRIG_INDEX_MAP_DEFINE(signal_trig,signal_serv)       signal_trig##Map = signal_serv,                       /* Trigger signal maps Service signal. */
#define SIGNAL_SERV_REGISTER(name,signal_serv,serv)                 name##SigServBuff[signal_serv] = (void*)serv;         /* Service signal register. */
#define SIGNAL_TRIG_REGISTER(name,signal_trig,signal_serv)          name##SigTrigIndex[signal_trig] = signal_trig##Map;   /* Trigger signal register. */

typedef void (*serv_void)(void);
typedef void (*serv_param)(void * buff);

/* Service Signals index definition.
 **********************************************/
#define SIGNAL_SERV_ENUM(name,list_serv)                        \
enum name##SigServ{                                             \
    list_serv(SIGNAL_SERV_DEFINE)                               \
    name##SigServMax                                            \
}

/* Service Signals length definition.
 **********************************************/
#define SIGNAL_SERV_MAP(name,list_serv)                         \
SIGNAL_SERV_ENUM(name,list_serv)

/* Service Signals store definition.
 **********************************************/
#define BUFF_SERV_DEFINE(name,list_serv)                        \
static void * name##SigServBuff[name##SigServMax]


/* Trigger Signals index definition.
 **********************************************/
#define SIGNAL_TRIG_ENUM(name,list_trig)                        \
enum name##SigTrig{                                             \
    list_trig(SIGNAL_TRIG_DEFINE)                               \
    name##SigTrigMax                                            \
}
/* Trigger Signals length definition.
 **********************************************/
#define SIGNAL_TRIG_INDEX_MAP_ENUM(name,list_trig)              \
enum name##SigTrigMap{                                          \
    list_trig(SIGNAL_TRIG_INDEX_MAP_DEFINE)                     \
    name##SigTrigMapMax                                         \
}
/* Trigger Signals maps.
 **********************************************/
 #define SIGNAL_TRIG_MAP(name,list_trig)                         \
SIGNAL_TRIG_ENUM(name,list_trig);                               \
SIGNAL_TRIG_INDEX_MAP_ENUM(name,list_trig)
/* Trigger Signals store definition.
 **********************************************/
#define BUFF_TRIG_DEFINE(name,list_trig)                        \
static uint16 name##SigTrigIndex[name##SigTrigMax]


/* Register Signals.
 **********************************************/
#define SIGNALS_SERVTRIG_REGISTER(list,signal_register)  do{    \
    list(signal_register)                                       \
}while(0)
/* Map Signals.
 **********************************************/
#define SIGNAL_SERVTRIG_MAP(name,list_serv,list_trig)           \
SIGNAL_SERV_MAP(name,list_serv);                                \
SIGNAL_TRIG_MAP(name,list_trig)
/* Store Signals.
 **********************************************/
#define BUFF_SERVTRIG_DEFINE(name,list_serv,list_trig)          \
BUFF_SERV_DEFINE(name,list_serv);                               \
BUFF_TRIG_DEFINE(name,list_trig)

#endif /*TRIGGERSERVICE_H_*/

/**************************** Copyright(C) pxf ****************************/
