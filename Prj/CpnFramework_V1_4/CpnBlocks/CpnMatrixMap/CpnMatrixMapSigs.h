/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMatrixMapSigs.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 14:30:29
 * Description  : CpnMatrixMap component signals declaration head file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

#ifndef CPNMATRIXMAPSIGS_H_
#define CPNMATRIXMAPSIGS_H_

/* Include head files. */
#include "../../CpnRte/Rte/Rte.h"
#include "../CpnFrameMatrix/CpnFrameMatrixCfg.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define CPNMATRIXMAPSIGS_MACRO_VERSION  0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Signals map.
 **********************************************************/
/* Set data map.
 **********************************************/
    /* sig_name,            id,          bit_start, bit_len, dynamic parameters */
/* #define FRAME_SET_SIG_LIST(_,...)                                               \
     _(ulDataA,              0xAAAU,      20U,       5U,      __VA_ARGS__)       \
     _(ulDataB,              0xAAAU,      28U,       1U,      __VA_ARGS__)       \
     _(ulDataC,              0x100U,       0U,       5U,      __VA_ARGS__)       \
     _(ulDataD,              0x100U,      19U,       9U,      __VA_ARGS__)       \
     _(ulDataE,              0xF0AU,      10U,       2U,      __VA_ARGS__)       \
     _(ulDataF,              0xF0AU,      17U,       3U,      __VA_ARGS__)       \
     _(ulDataG,              0xF0AU,      40U,       5U,      __VA_ARGS__)       \
*/
/* Get data map.
 **********************************************/
    /* sig_name,            id,          bit_start, bit_len, dynamic parameters */
/* #define FRAME_GET_SIG_LIST(_,...)                                               \
     _(ulData1,              0x200U,      40U,       5U,      __VA_ARGS__)       \
     _(ulData2,              0x200U,      28U,       1U,      __VA_ARGS__)       \
     _(ulData3,              0x200U,       0U,       5U,      __VA_ARGS__)       \
     _(ulData4,              0x200U,      19U,       9U,      __VA_ARGS__)       \
     _(ulData5,              0xF8AU,      10U,       2U,      __VA_ARGS__)       \
     _(ulData6,              0xF8AU,      17U,       3U,      __VA_ARGS__)       \
     _(ulData7,              0xF8AU,      40U,       5U,      __VA_ARGS__)       \
     _(ulData8,              0xF8AU,      60U,       1U,      __VA_ARGS__)       \
*/

/***********************************************************
 * Function marcos.
 **********************************************************/
 /* Get data map.
 **********************************************/
#define FRAME_SET_SIG_ENUM_COMBINE(name,id,bit_start,bit_len,fill)    set_sig_##name,                              /* Set signal enum index. */
#define FRAME_GET_SIG_ENUM_COMBINE(name,id,bit_start,bit_len,fill)    get_sig_##name,                              /* Get signal enum index. */
#define FRAME_SET_SIG_ENUM_EXPANTION(frame_list)                      frame_list(FRAME_SET_SIG_ENUM_COMBINE,fill)  /* Set signal enum extention. */
#define FRAME_GET_SIG_ENUM_EXPANTION(frame_list)                      frame_list(FRAME_GET_SIG_ENUM_COMBINE,fill)  /* Get signal enum extention. */

#define FRAME_SET_SIG_COMBINE(name,id,bit_start,bit_len,fill)         {set_sig_##name,id,bit_start,bit_len,sig_trig_CpnMatrixMap_setFrame}, /* Set signal map array. */
#define FRAME_GET_SIG_COMBINE(name,id,bit_start,bit_len,fill)         {get_sig_##name,id,bit_start,bit_len,sig_trig_CpnMatrixMap_getFrame}, /* Get signal map array. */
#define FRAME_SET_SIG_EXPANTION(frame_list)                           frame_list(FRAME_SET_SIG_COMBINE,fill)       /* Set signal enum extention. */
#define FRAME_GET_SIG_EXPANTION(frame_list)                           frame_list(FRAME_GET_SIG_COMBINE,fill)       /* Get signal enum extention. */

#define FRAME_SET_SIG_SERV_DEC(name,id,bit_start,bit_len,fill)        void serv_CpnMatrixMap_set_##name(void *buff); /* set_sig serv declaration. */
#define FRAME_GET_SIG_SERV_DEC(name,id,bit_start,bit_len,fill)        void serv_CpnMatrixMap_get_##name(void *buff); /* get_sig serv declaration. */
#define FRAME_GET_SIG_SERV_DEC_EXPANTION(frame_list)                  frame_list(FRAME_GET_SIG_SERV_DEC,fill)      /* Set serv declaration extention. */
#define FRAME_SET_SIG_SERV_DEC_EXPANTION(frame_list)                  frame_list(FRAME_SET_SIG_SERV_DEC,fill)      /* Get serv declaration extention. */

/* Get data map.
 **********************************************/
//extern const TS_FRAME_MAP frameMapDatasSet[];
//extern const TS_FRAME_MAP frameMapDatasGet[];
#define FRAME_SET_SIG_SERV_DEF(name,id_,bit_start_,bit_len_,fill)        /* set_sig serv definiton. */        \
void serv_CpnMatrixMap_set_##name(void *buff){                                                                \
    TS_FRAME_GETSET setData;                                                                                  \
    setData.id = frameMapDatasSet[set_sig_##name].id;                                                         \
    setData.bit_start = frameMapDatasSet[set_sig_##name].bit_start;                                           \
    setData.bit_len = frameMapDatasSet[set_sig_##name].bit_len;                                               \
    setData.value = ((uint32*)buff);                                                                          \
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasSet[set_sig_##name].sig_operation_name, (uint8*)&setData); \
}
#define FRAME_GET_SIG_SERV_DEF(name,id_,bit_start_,bit_len_,fill)        /* get_sig serv definiton. */        \
void serv_CpnMatrixMap_get_##name(void *buff){                                                                \
    TS_FRAME_GETSET getData;                                                                                  \
    getData.id = frameMapDatasGet[get_sig_##name].id;                                                         \
    getData.bit_start = frameMapDatasGet[get_sig_##name].bit_start;                                           \
    getData.bit_len = frameMapDatasGet[get_sig_##name].bit_len;                                               \
    getData.value = ((uint32*)buff);                                                                          \
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasGet[get_sig_##name].sig_operation_name, (uint8*)&getData); \
}
#define FRAME_SET_SIG_SERV_DEF_EXPANTION(frame_list)     frame_list(FRAME_SET_SIG_SERV_DEF,fill)                   /* Set serv definition extention. */
#define FRAME_GET_SIG_SERV_DEF_EXPANTION(frame_list)     frame_list(FRAME_GET_SIG_SERV_DEF,fill)                   /* Get serv definition extention. */

#define FRAME_SET_SIG_SERV_LIST_RTESYN(name,id,bit_start,bit_len,X) X(sig_serv_CpnMatrixMap_set_##name,serv_CpnMatrixMap_set_##name) /* RTE set signal configure. */
#define FRAME_GET_SIG_SERV_LIST_RTESYN(name,id,bit_start,bit_len,X) X(sig_serv_CpnMatrixMap_get_##name,serv_CpnMatrixMap_get_##name) /* RTE get signal configure. */
#define FRAME_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)      FRAME_SET_SIG_LIST(FRAME_SET_SIG_SERV_LIST_RTESYN,_)      /* RTE set signal extention. */ \
                                                         FRAME_SET_SIG_LIST(FRAME_GET_SIG_SERV_LIST_RTESYN,_)      /* RTE get signal extention. */
#define FRAME_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)      FRAME_GET_SIG_LIST(FRAME_GET_SIG_SERV_LIST_RTESYN,_)      /* RTE get signal extention. */

#define matrixMapSet(sig)                                sig_serv_CpnMatrixMap_set_##sig                           /* Set signals map. */
#define matrixMapGet(sig)                                sig_serv_CpnMatrixMap_get_##sig                           /* Get signals map. */


/***********************************************************
 * Get Set data type definition.
 * Generally, only the set data is defined, and the get type refers to the current header file.
 * Only need to define the data sent, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Sent data type.
 **********************************************/



/***********************************************************
 * Serv Trig data type definition.
 * Generally, only the serv data is defined, and the trig type refers to the current header file.
 * Only need to define the data sent, the transceiver interface uses a unified interface, no other definitions.
 * Generally speaking, the signal data type must be defined once,
 * otherwise it is difficult to know what the corresponding data of the signal is.
 **********************************************************/
/* Serv data type.
 **********************************************/
typedef enum{
    FRAME_SET_SIG_ENUM_EXPANTION(FRAME_SET_SIG_LIST)
    set_sig_num_max
} TE_FRAME_SET_SIG;
typedef enum{
    FRAME_GET_SIG_ENUM_EXPANTION(FRAME_GET_SIG_LIST)
    FRAME_GET_SIG_ENUM_EXPANTION(FRAME_SET_SIG_LIST)
    get_sig_num_max
} TE_FRAME_GET_SIG;
typedef struct{
    uint16 sig_index;
    uint32 id;
    uint16 bit_start;
    uint16 bit_len;
    uint16 sig_operation_name;
} TS_FRAME_MAP, *hTS_FRAME_MAP;


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnMatrixMap_init(void);
/* Set serv.
 * serv_CpnMatrixMap_set_ulDataA
 **********************************************/
FRAME_SET_SIG_SERV_DEC_EXPANTION(FRAME_SET_SIG_LIST)
/* Get serv.
 * serv_CpnMatrixMap_get_ulData1
 **********************************************/
FRAME_GET_SIG_SERV_DEC_EXPANTION(FRAME_GET_SIG_LIST)
FRAME_GET_SIG_SERV_DEC_EXPANTION(FRAME_SET_SIG_LIST)

/* Trigger interface.
 **********************************************/
//void trig_CpnMatrixMap_inf_infFunc(void);



/***********************************************************
 * Get Set signal list.
 **********************************************************/
/* Set signal list.
 **********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAP(_)            \

/* Get signal list.
 * When configuring the signal, you need to check the length of the transmitted signal to map the signal.
 **********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAP(_)        \



/***********************************************************
 * Trig Serv signal list.
 **********************************************************/
/* Serv signal list.
 **********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAP(_)            \
    _(sig_serv_CpnMatrixMap_init,serv_CpnMatrixMap_init)   \
    /*_(sig_serv_CpnMatrixMap_set_ulDataA,serv_CpnMatrixMap_set_ulDataA)*/ \
    /*_(sig_serv_CpnMatrixMap_get_ulData1,serv_CpnMatrixMap_get_ulData1)*/ \
    FRAME_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)            \
    FRAME_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)            \

/* Trig signal list.
 * When configuring the signal, you need to check the length of the service signal to map the signal.
 **********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAP(_)        \
    _(sig_trig_CpnMatrixMap_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMatrixMap_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMatrixMap_delay,sig_serv_CpnSch_delay)   \
    _(sig_trig_CpnMatrixMap_now,sig_serv_CpnSch_now)       \
    _(sig_trig_CpnMatrixMap_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnMatrixMap_getFrame,sig_serv_CpnFrameMatrix_getFrame) \
    _(sig_trig_CpnMatrixMap_setFrame,sig_serv_CpnFrameMatrix_setFrame) \
    _(sig_trig_CpnMatrixMap_updateFrame,sig_serv_CpnFrameMatrix_updateFrame) \
    _(sig_trig_CpnMatrixMap_getFrameByte,sig_serv_CpnFrameMatrix_getFrameByte) \



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task declaration.
 **********************************************/
// void taskCpnMatrixMap(void);

#endif /*CPNMATRIXMAPSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
