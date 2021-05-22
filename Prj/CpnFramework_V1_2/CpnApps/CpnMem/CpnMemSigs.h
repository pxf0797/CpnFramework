/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnMemSigs.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/09 11:38:50
* Description  : CpnMem����ź�����ͷ�ļ�
* Others       :
* History      : 201209 pxf ���ν���
***************************************************************************/

#ifndef CPNMEMSIGS_H_
#define CPNMEMSIGS_H_

/*ͷ�ļ�����*/
#include "../../cpnRte/Rte/Rte.h"

/***********************************************************
* �汾����
***********************************************************/
#define CPNMEMSIGS_MACRO_VERSION        0xC01D00    /* C����V��D����.����ǰ�汾V1.00 */

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
    void *pointer;
    /* if function is memMalloc and getSize, then indication is size;
     * if function is isPointerSet, then indication is TRUE/FALSE;
     * if function is getIndex, then indication is index;
     * */
    uint16 indication;
} TS_MEM_POINTER, *hTS_MEM_POINTER;


/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnMem_init(void);
/*����
***********************************************/
void serv_CpnMem_memMalloc(void *buff);
/*����
***********************************************/
void serv_CpnMem_memFree(void *buff);
/*����
***********************************************/
void serv_CpnMem_isPointerSet(void *buff);
/*����
***********************************************/
void serv_CpnMem_getSize(void *buff);
/*����
***********************************************/
void serv_CpnMem_getIndex(void *buff);

/*����
***********************************************/
void serv_CpnMem_memStatus(void *buff);

/*�ӿڴ���
***********************************************/
//void trig_CpnMem_inf_infFunc(void);



/***********************************************************
* get set�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SET_LIST_RTEASYN_CPNMEM(_)                  \

/*�����ź��б�
* �����ź�ʱ��Ҫ��鷢���źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_GET_MAP_LIST_RTEASYN_CPNMEM(_)              \



/***********************************************************
* trig serv�ź��б�
***********************************************************/
/*�����ź��б�
***********************************************/
#define SIGNAL_SERV_LIST_RTESYN_CPNMEM(_)                  \
    _(sig_serv_CpnMem_init,serv_CpnMem_init)               \
    _(sig_serv_CpnMem_memMalloc,serv_CpnMem_memMalloc)     \
    _(sig_serv_CpnMem_memFree,serv_CpnMem_memFree)         \
    _(sig_serv_CpnMem_isPointerSet,serv_CpnMem_isPointerSet) \
    _(sig_serv_CpnMem_getSize,serv_CpnMem_getSize)         \
    _(sig_serv_CpnMem_getIndex,serv_CpnMem_getIndex)       \
    _(sig_serv_CpnMem_memStatus,serv_CpnMem_memStatus)     \

/*�����ź��б�
* �����ź�ʱ��Ҫ�������źŵĳ��ȶ��źŽ���ӳ��
***********************************************/
#define SIGNAL_TRIG_MAP_LIST_RTESYN_CPNMEM(_)              \
    _(sig_trig_CpnMem_addTask,sig_serv_CpnSch_addTask)     \
    _(sig_trig_CpnMem_delTask,sig_serv_CpnSch_delTask)     \
    _(sig_trig_CpnMem_delay,sig_serv_CpnSch_delay)         \
    _(sig_trig_CpnMem_now,sig_serv_CpnSch_now)             \
    _(sig_trig_CpnMem_setErr,sig_serv_CpnErr_setErr)       \



/***********************************************************
* �����������
***********************************************************/
/*������������
***********************************************/
// void taskCpnMem(void);

#endif /*CPNMEMSIGS_H_*/

/**************************** Copyright(C) pxf ****************************/
