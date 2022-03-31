/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : Sm.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/09 11:53:22
 * Description  : This document provides a series of macros to facilitate the creation of state machines;
 *                1. The first step of creating the state machine must define the state set sta_list, the basic init state will be given by default;
 *                2. The second step of state machine creation uses the macro SMDC to declare the state record structure StaRec
 *                   during the operation of the state machine, and the basic sta next parameters are indispensable;
 *                3. The third step of state machine creation is to define the state machine, using the macro SMDF;
 *                4. The fourth step of state machine creation is to establish state actions for each state respectively void sm_type##_##_act_##sm_sta(void *hStaRec);
 *                5. The fifth step of creating the state machine uses the macro SMR as the input clock for the state machine to drive the state machine;
 * Others       : 
 * History      : 20210409 pxf Initially established.
 **************************************************************************/

#ifndef SM_H_
#define SM_H_

/* Include head files. */

/***********************************************************
 * MACRO VERTION 
 **********************************************************/
#define SM_MACRO_VERSION                0xC03D00    /* C represent V,D represent ., Current version is V3.00 */

/* Basic types definition.
 **********************************************/
typedef unsigned char sta;
typedef void (*staAct)(void *hStaRec);  /* State action. */
typedef staAct *hstaAct, **hhstaAct;    /* State machine pointer. */

/* State definition.
 **********************************************/
#define SD(sm_type, sm_sta)     sm_type##_sta_##sm_sta,                     /* state define, Note that there is "," after the state. */
#define SADC(sm_type, sm_sta)   void sm_type##_act_##sm_sta(void *hStaRec); /* state action declaration, Note that there is ";" after the state action declaration, each state action output declaration. */
#define SADF(sm_type, sm_sta)   sm_type##_act_##sm_sta,                     /* state action define, Note that there is "," after it. */

/* State machine function macros.
 **********************************************/
/* List the state types of the state machine states.
 * Among them, the state of init is given by default when the state machine is declared,
 * so it is not necessary to list it when the state is listed here. */
/* #define STA_LIST(_)          \
    _(sm_type, count)        \
    _(sm_type, done)         \
 */
/* use X_MACRO.
 * The state record structure that needs to declare the state action of the state machine.
 * Where next is a required parameter, as the next action corresponding to the state machine running. */
/* typedef struct StaRec{ // Encapsulate state record for state machine parameters.
        sta next;    // Required and must be placed first, as the next action of the state machine.
        //sta last;  // According to the need, whether the last state entered.
        ...          // According to need, whether to enter some other parameters.
    } *hStaRec, StaRec;
 */
/* State machine declaration. */
#define SMDC(sm_type, sta_list)                                 \
typedef struct sm_type##Rec *h##sm_type##Rec, sm_type##Rec;     \
enum sm_type##_stas{                                            \
    sta_list(SD)                                                \
    sm_type##_sta_init,                                         \
    sm_type##_sta_num_max                                       \
};                                                              \
sta_list(SADC)                                                  \
void sm_type##_act_init(void *hStaRec);                         \
extern staAct sm_type[sm_type##_sta_num_max];                   \
struct sm_type##Rec
/* State machine definition. */
#define SMDF(sm_type, sta_list)                                 \
staAct sm_type[sm_type##_sta_num_max] = {                       \
    sta_list(SADF)                                              \
    sm_type##_act_init                                          \
}
/* State machine run. Relatively speaking, it is to give the clock cycle. */
#define SMR(sm_type) do{                                        \
    static sm_type##Rec sm_type##RunRec = {sm_type##_sta_init}; \
    sm_type[sm_type##RunRec.next](&sm_type##RunRec);            \
}while(0)
/* state machine run entity. In the case of state machine pointer definition, SMR running state machine is not used. */
#define SMRE(sm_entity_ptr, sm_rec)  (sm_entity_ptr)[(sm_rec).next](&(sm_rec))
#define SMREH(sm_entity_ptr, sm_rec_ptr)  (sm_entity_ptr)[sm_rec_ptr->next](sm_rec_ptr)

#endif /*SM_H_*/

/**************************** Copyright(C) pxf ****************************/
