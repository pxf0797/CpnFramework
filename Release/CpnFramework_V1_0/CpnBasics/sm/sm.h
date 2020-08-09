/*************************************************
 * Copyright ? person
 * File name    : sm.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/3/10
 * Description  : ���ļ�Ϊ����״̬�������ṩһϵ�кꣻ
 *                1.״̬��������һ�����붨���״̬����sta_list������init,default��״̬Ĭ�ϻ������;
 *                2.״̬�������ڶ���ʹ�ú�SMDC����״̬�����й�����״̬��¼�ṹ��StaRec������sta next�����ز����٣�
 *                3.״̬����������������״̬����ʹ�ú�SMDF��
 *                4.״̬���������Ĳ�Ϊ��״̬�ֱ���״̬����void sm_type##_##_act_##sm_sta(void *hStaRec)��
 *                5.״̬���������岽ʹ�ú�SMRΪ״̬������ʱ�Ӷ�״̬������������
 * Others       : ��
 * History      : 180310 pxf ���ν���
 *                180819 pxf 1.����״̬��ָ��hstaAct/hhstaAct��
 *                           2.����״̬��ָ�����к�SMRE
 ************************************************/

#ifndef SM_H_
#define SM_H_

// �汾����---------------------------------------------------------------------
#define SM_VERSION    0xC01D01          // C����v��D����.���汾v1.01

// �������Ͷ���
typedef unsigned char sta;
typedef void (*staAct)(void *hStaRec);  // state action
typedef staAct *hstaAct, **hhstaAct;    // ״̬��ָ��

// ״̬��״̬���
#define SD(sm_type, sm_sta) sm_type##_sta_##sm_sta,                       // state define ע�����","����״̬����
#define SADC(sm_type, sm_sta) void sm_type##_act_##sm_sta(void *hStaRec); // state action declaration ע�����";"����״̬�����������
#define SADF(sm_type, sm_sta) sm_type##_act_##sm_sta,                     // state action define ע�����","����״̬�����������

// ״̬����״̬���ͽ�������
// ����init,default������״̬��״̬������ʱĬ�ϻ����������������״̬����ʱ�Ͳ���Ҫ���г�����
/*
#define STA_LIST(_)          \
    _(sm_type, count)        \
    _(sm_type, done)
    */

// ʹ��X_MACRO
// state machine declaration ״̬������
// ��Ҫ����״̬��״̬������״̬��¼�ṹ��
// ����nextΪ�����������Ϊ״̬������ʱ��Ӧ����һ����
/*
    typedef struct StaRec   // ��״̬��������װstate record
    {
        sta next;    // ��ѡ���ұ�����ڵ�һ������Ϊ״̬������һ�ζ���
        //sta last;  // ������Ҫ���Ƿ��������һ��״̬
        ...          // ������Ҫ���Ƿ�����һЩ��������
    } *hStaRec, StaRec;
    */
#define SMDC(sm_type, sta_list)                                 \
typedef struct sm_type##Rec *h##sm_type##Rec, sm_type##Rec;     \
enum sm_type##_stas{                                            \
    sm_type##_sta_init = 0,                                     \
    sta_list(SD)                                                \
    sm_type##_sta_default                                       \
};                                                              \
void sm_type##_act_init(void *hStaRec);                         \
sta_list(SADC)                                                  \
void sm_type##_act_default(void *hStaRec);                      \
extern staAct sm_type[sm_type##_sta_default + 1];               \
struct sm_type##Rec
// state machine define ״̬������
#define SMDF(sm_type, sta_list)                                 \
staAct sm_type[sm_type##_sta_default + 1] = {                   \
    sm_type##_act_init,                                         \
    sta_list(SADF)                                              \
    sm_type##_act_default                                       \
}
// state machine run ״̬�����������˵���Ǹ�ʱ������
//static StaRec StaRunRec = {sm_type##_sta_init}; // ���붨���ʼ״̬
#define SMR(sm_type)                                            \
do{                                                             \
    static sm_type##Rec sm_type##RunRec = {sm_type##_sta_init}; \
    sm_type[sm_type##RunRec.next](&sm_type##RunRec);            \
}while(0)
// state machine run entity ʹ��״̬��ָ������
// ��ǰ������״̬��ָ�붨������£���ʹ��SMR����״̬��
#define SMRE(sm_entity_ptr, sm_rec)  (sm_entity_ptr)[(sm_rec).next](&(sm_rec))
#define SMREH(sm_entity_ptr, sm_rec_ptr)  (sm_entity_ptr)[sm_rec_ptr->next](sm_rec_ptr)

#endif /* SM_H_ */

/**************************** Copyright(C) pxf ****************************/
