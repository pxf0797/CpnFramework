/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrixSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  : CpnFrameMatrix����ź�����ͷ�ļ�
* Others       :
* History      : 201120 pxf ���ν���
***************************************************************************/

#ifndef CPNFRAMEMATRIXSIGS_H_
#define CPNFRAMEMATRIXSIGS_H_

/*ͷ�ļ�����*/
#include "../../cpnRte/Rte/Rte.h"
#include "./CpnFrameMatrixCfg.h"
#include "./CpnFrameMatrix.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNFRAMEMATRIXSIGS_MACRO_VERSION 0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
typedef struct{
    uint32 id;
    hTU_BYTES_DATA frame;
} TS_FRAME_TRANS, *hTS_FRAME_TRANS;
typedef struct{
    uint32 id;
    uint16 bit_start;
    uint16 bit_len;
    uint32* value;
} TS_FRAME_GET, *hTS_FRAME_GET;
typedef struct{
    uint32 id;
    uint16 bit_start;
    uint16 bit_len;
    uint32 value;
} TS_FRAME_SET, *hTS_FRAME_SET;
typedef struct{
    uint32 id;
    uint16 byte_index;
    uint8* value;
} TS_FRAME_BYTE, *hTS_FRAME_BYTE;

/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnFrameMatrix_init(void);
/*����
***********************************************/
void serv_CpnFrameMatrix_get_frame(void *buff);
/*����
***********************************************/
void serv_CpnFrameMatrix_set_frame(void *buff);
/*����--����֡����
***********************************************/
void serv_CpnFrameMatrix_update_frame(void *buff);
/*����--��ȡ�����ֽ�
***********************************************/
void serv_CpnFrameMatrix_get_frame_byte(void *buff);

/*�ӿڴ���
***********************************************/
void trig_CpnFrameMatrix_inf_sentFrame(uint32 id, hTU_BYTES_DATA frame);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNFRAMEMATRIX(_)          \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNFRAMEMATRIX(_)      \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNFRAMEMATRIX(_)          \
    _(sig_serv_CpnFrameMatrix_init,serv_CpnFrameMatrix_init) \
    _(sig_serv_CpnFrameMatrix_get_frame,serv_CpnFrameMatrix_get_frame) \
    _(sig_serv_CpnFrameMatrix_set_frame,serv_CpnFrameMatrix_set_frame) \
    _(sig_serv_CpnFrameMatrix_update_frame,serv_CpnFrameMatrix_update_frame) \
    _(sig_serv_CpnFrameMatrix_get_frame_byte,serv_CpnFrameMatrix_get_frame_byte) \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNFRAMEMATRIX(_)      \
    _(sig_trig_CpnFrameMatrix_addTask,sig_serv_CpnSch_addTask) \
    _(sig_trig_CpnFrameMatrix_delTask,sig_serv_CpnSch_delTask) \
    _(sig_trig_CpnFrameMatrix_delay,sig_serv_CpnSch_delay) \
    _(sig_trig_CpnFrameMatrix_now,sig_serv_CpnSch_now)     \
    _(sig_trig_CpnFrameMatrix_setErr,sig_serv_CpnErr_setErr) \
    _(sig_trig_CpnFrameMatrix_sentFrame,sig_serv_Abi_sentCanFrame) \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
void taskCpnFrameMatrix(void);

#endif /*CPNFRAMEMATRIXSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
