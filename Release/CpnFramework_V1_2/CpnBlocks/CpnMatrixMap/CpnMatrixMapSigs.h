/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMatrixMapSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/21 10:36:48
* Description  : CpnMatrixMap����ź�����ͷ�ļ�
* Others       :
* History      : 201121 pxf ���ν���
***************************************************************************/

#ifndef CPNMATRIXMAPSIGS_H_
#define CPNMATRIXMAPSIGS_H_

/*ͷ�ļ�����*/
#include "../../cpnRte/Rte/Rte.h"
#include "../CpnFrameMatrix/CpnFrameMatrixCfg.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNMATRIXMAPSIGS_MACRO_VERSION  0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */


/***********************************************************
* �ź�ӳ��
***********************************************************/
/*�����ź�����
***********************************************/
// #define FRAME_SET_SIG_LIST(_,...)                                               \
//     /* sig_name,            id,          bit_start, bit_len, dynamic parameters */ \
//     _(ulDataA,              0xAAAU,      20U,       5U,      __VA_ARGS__)       \
//     _(ulDataB,              0xAAAU,      28U,       1U,      __VA_ARGS__)       \
//     _(ulDataC,              0x100U,       0U,       5U,      __VA_ARGS__)       \
//     _(ulDataD,              0x100U,      19U,       9U,      __VA_ARGS__)       \
//     _(ulDataE,              0xF0AU,      10U,       2U,      __VA_ARGS__)       \
//     _(ulDataF,              0xF0AU,      17U,       3U,      __VA_ARGS__)       \
//     _(ulDataG,              0xF0AU,      40U,       5U,      __VA_ARGS__)       \

/*�����ź�����
***********************************************/
// #define FRAME_GET_SIG_LIST(_,...)                                               \
//     /* sig_name,            id,          bit_start, bit_len, dynamic parameters */ \
//     _(ulData1,              0x200U,      40U,       5U,      __VA_ARGS__)       \
//     _(ulData2,              0x200U,      28U,       1U,      __VA_ARGS__)       \
//     _(ulData3,              0x200U,       0U,       5U,      __VA_ARGS__)       \
//     _(ulData4,              0x200U,      19U,       9U,      __VA_ARGS__)       \
//     _(ulData5,              0xF8AU,      10U,       2U,      __VA_ARGS__)       \
//     _(ulData6,              0xF8AU,      17U,       3U,      __VA_ARGS__)       \
//     _(ulData7,              0xF8AU,      40U,       5U,      __VA_ARGS__)       \
//     _(ulData8,              0xF8AU,      60U,       1U,      __VA_ARGS__)       \


/***********************************************************
* ���ܺ�
***********************************************************/
#define FRAME_SET_SIG_ENUM_COMBINE(name,id,bit_start,bit_len,fill)    set_sig_##name,                              /* �����ź�ö������ */
#define FRAME_GET_SIG_ENUM_COMBINE(name,id,bit_start,bit_len,fill)    get_sig_##name,                              /* �����ź�ö������ */
#define FRAME_SET_SIG_ENUM_EXPANTION(frame_list)                      frame_list(FRAME_SET_SIG_ENUM_COMBINE,fill)  /* �����ź�ö����չ */
#define FRAME_GET_SIG_ENUM_EXPANTION(frame_list)                      frame_list(FRAME_GET_SIG_ENUM_COMBINE,fill)  /* �����ź�ö����չ */

#define FRAME_SET_SIG_COMBINE(name,id,bit_start,bit_len,fill)         {set_sig_##name,id,bit_start,bit_len,sig_trig_CpnMatrixMap_set_frame}, /* �����ź�ӳ��� */
#define FRAME_GET_SIG_COMBINE(name,id,bit_start,bit_len,fill)         {get_sig_##name,id,bit_start,bit_len,sig_trig_CpnMatrixMap_get_frame}, /* �����ź�ӳ��� */
#define FRAME_SET_SIG_EXPANTION(frame_list)                           frame_list(FRAME_SET_SIG_COMBINE,fill)       /* �����ź�ö����չ */
#define FRAME_GET_SIG_EXPANTION(frame_list)                           frame_list(FRAME_GET_SIG_COMBINE,fill)       /* �����ź�ö����չ */

#define FRAME_SET_SIG_SERV_DEC(name,id,bit_start,bit_len,fill)        void serv_CpnMatrixMap_set_##name(void *buff); /* set_sig���������� */
#define FRAME_GET_SIG_SERV_DEC(name,id,bit_start,bit_len,fill)        void serv_CpnMatrixMap_get_##name(void *buff); /* get_sig���������� */
#define FRAME_GET_SIG_SERV_DEC_EXPANTION(frame_list)                  frame_list(FRAME_GET_SIG_SERV_DEC,fill)      /* �����źŷ���������չ */
#define FRAME_SET_SIG_SERV_DEC_EXPANTION(frame_list)                  frame_list(FRAME_SET_SIG_SERV_DEC,fill)      /* �����źŷ���������չ */

//extern const TS_FRAME_MAP frameMapDatasSet[];
//extern const TS_FRAME_MAP frameMapDatasGet[];
#define FRAME_SET_SIG_SERV_DEF(name,id_,bit_start_,bit_len_,fill)        /* set_sig���������� */             \
void serv_CpnMatrixMap_set_##name(void *buff){                                                                \
    TS_FRAME_GETSET setData;                                                                                  \
    setData.id = frameMapDatasSet[set_sig_##name].id;                                                         \
    setData.bit_start = frameMapDatasSet[set_sig_##name].bit_start;                                           \
    setData.bit_len = frameMapDatasSet[set_sig_##name].bit_len;                                               \
    setData.value = ((uint32*)buff);                                                                          \
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasSet[set_sig_##name].sig_operation_name, (uint8*)&setData); \
}
#define FRAME_GET_SIG_SERV_DEF(name,id_,bit_start_,bit_len_,fill)        /* get_sig���������� */             \
void serv_CpnMatrixMap_get_##name(void *buff){                                                                \
    TS_FRAME_GETSET getData;                                                                                  \
    getData.id = frameMapDatasGet[get_sig_##name].id;                                                         \
    getData.bit_start = frameMapDatasGet[get_sig_##name].bit_start;                                           \
    getData.bit_len = frameMapDatasGet[get_sig_##name].bit_len;                                               \
    getData.value = ((uint32*)buff);                                                                          \
    clRteSynSigs.trig(clRteSynSigs.self, frameMapDatasGet[get_sig_##name].sig_operation_name, (uint8*)&getData); \
}
#define FRAME_SET_SIG_SERV_DEF_EXPANTION(frame_list)     frame_list(FRAME_SET_SIG_SERV_DEF,fill)                   /* �����źŷ�������չ */
#define FRAME_GET_SIG_SERV_DEF_EXPANTION(frame_list)     frame_list(FRAME_GET_SIG_SERV_DEF,fill)                   /* �����źŷ�������չ */

#define FRAME_SET_SIG_SERV_LIST_RTESYN(name,id,bit_start,bit_len,X) X(sig_serv_CpnMatrixMap_set_##name,serv_CpnMatrixMap_set_##name) /* RTE�����ź����� */
#define FRAME_GET_SIG_SERV_LIST_RTESYN(name,id,bit_start,bit_len,X) X(sig_serv_CpnMatrixMap_get_##name,serv_CpnMatrixMap_get_##name) /* RTE�����ź����� */
#define FRAME_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)      FRAME_SET_SIG_LIST(FRAME_SET_SIG_SERV_LIST_RTESYN,_)      /* RTE�����ź���չ */ \
                                                         FRAME_SET_SIG_LIST(FRAME_GET_SIG_SERV_LIST_RTESYN,_)      /* RTE�����ź���չҲ�ɶ� */
#define FRAME_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)      FRAME_GET_SIG_LIST(FRAME_GET_SIG_SERV_LIST_RTESYN,_)      /* RTE�����ź���չ */

#define matrixMapSet(sig)                                sig_serv_CpnMatrixMap_set_##sig                           /* �����ź�ӳ�� */
#define matrixMapGet(sig)                                sig_serv_CpnMatrixMap_get_##sig                           /* �����ź�ӳ�� */

/***********************************************************
* get set �������Ͷ���
* һ��ֻ����set���ݣ�get�������õ�ǰͷ�ļ�
* ֻ��Ҫ�ѷ��͵����ݶ���������շ��ӿ�ʹ�õ���ͳһ�ӿڣ�����������
* �ź���������һ����˵����ǿ�ƶ���һ�飬�������֪���źŶ�Ӧ������ʲô
***********************************************************/
/*������������
***********************************************/




/***********************************************************
* serv trig �������Ͷ���
* һ��ֻ����serv���ݣ�trig�������õ�ǰͷ�ļ�
* ֻ��Ҫ�ѷ��͵����ݶ���������շ��ӿ�ʹ�õ���ͳһ�ӿڣ�����������
* �ź���������һ����˵����ǿ�ƶ���һ�飬�������֪���źŶ�Ӧ������ʲô
***********************************************************/
/*������������
***********************************************/
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
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnMatrixMap_init(void);
/*����--����
* serv_CpnMatrixMap_set_ulDataA
***********************************************/
FRAME_SET_SIG_SERV_DEC_EXPANTION(FRAME_SET_SIG_LIST)
/*����--����
* serv_CpnMatrixMap_get_ulData1
***********************************************/
FRAME_GET_SIG_SERV_DEC_EXPANTION(FRAME_GET_SIG_LIST)
FRAME_GET_SIG_SERV_DEC_EXPANTION(FRAME_SET_SIG_LIST)


/*�ӿڴ���
***********************************************/
//void trig_CpnMatrixMap_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMATRIXMAP(_)            \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMATRIXMAP(_)        \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMATRIXMAP(_)            \
    _(sig_serv_CpnMatrixMap_init,serv_CpnMatrixMap_init)   \
    /*_(sig_serv_CpnMatrixMap_set_ulDataA,serv_CpnMatrixMap_set_ulDataA)*/ \
    /*_(sig_serv_CpnMatrixMap_get_ulData1,serv_CpnMatrixMap_get_ulData1)*/ \
    FRAME_SET_SIG_SERV_LIST_RTESYN_EXPANTION(_)            \
    FRAME_GET_SIG_SERV_LIST_RTESYN_EXPANTION(_)            \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMATRIXMAP(_)        \
    _(sig_trig_CpnMatrixMap_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnMatrixMap_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnMatrixMap_delay,sig_serv_CpnSch_delay)   \
    _(sig_trig_CpnMatrixMap_now,sig_serv_CpnSch_now)       \
    _(sig_trig_CpnMatrixMap_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnMatrixMap_get_frame,sig_serv_CpnFrameMatrix_get_frame) \
    _(sig_trig_CpnMatrixMap_set_frame,sig_serv_CpnFrameMatrix_set_frame) \
    _(sig_trig_CpnMatrixMap_update_frame,sig_serv_CpnFrameMatrix_update_frame) \
    _(sig_trig_CpnMatrixMap_get_frame_byte,sig_serv_CpnFrameMatrix_get_frame_byte) \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
// void taskCpnMatrixMap(void);

#endif /*CPNMATRIXMAPSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
