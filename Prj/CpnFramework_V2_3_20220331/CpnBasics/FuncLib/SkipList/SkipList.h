/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SkipList.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/10 21:46:26
 * Description  : SkipList class and interface declaration file.
 * Others       : 
 * History      : 20211010 pxf Initially established.
 **************************************************************************/

#ifndef SKIPLIST_H_
#define SKIPLIST_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "BlockM.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define SKIPLIST_MACRO_VERSION                  0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef uint32 slType;
#define SKIPLIST_TYPE_BITS                       ((sizeof(slType)>>1u)+3u)//0x5u//0x4u//
#define SKIPLIST_TYPE_WIDTH                      (1u<<SKIPLIST_TYPE_BITS)
#define SKIPLIST_TYPE_MASK                       (SKIPLIST_TYPE_WIDTH-1u)
/* skip list node */
typedef struct tsSLNode tsSLNode,*htsSLNode,**hhtsSLNode;
struct tsSLNode{
    htsSLNode next;     /* indicate next one, previous is not important. */
    void *block;        /* indicate list block. */
};
#define SKIPLIST_MANA_SIZE(num)                  ((sizeof(htsSLNode)*num)+BLOCKMCFG_CAL_MANAGE_SIZE(tsSLNode,num))
/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
INF(blockOrder){
    slType (*blockOrder)(void *block);
};

/***********************************************************
 * SkipList class definition.
 **********************************************************/
/* SkipList class declaration.
 **********************************************/
CL(SkipList){
    hSkipList self;
    hSkipList (*init)(hSkipList cthis, uint16 slBuffMaxNum, uint8 *space);

    /* SkipList class parameters. */
    uint16 slBuffMaxNum;           /* skip list maximum buffered number. */
    uint16 arrayCnt;               /* array has buffered counter. */
    /* indicate skip list array start address, the length is slBuffMaxNum.
     * it also is the space start address.
     * array is sort in increase order.
     */
    htsSLNode slArray;
    uint8 *slSpace;              /* BlockM manage space, indicate skip list buff, the length is slBuffMaxNum. */
    htsSLNode slHead;            /* indicate skip list head. */

    /* SkipList class functions. */
    /* return OOPC_NULL, not find the order.
     * return others, the node of the specific order.
     */
    htsSLNode (*find)(hSkipList cthis, slType order);
    /* return arrayCnt is abnormal.
     * return 0, may be the node bigger than the order.
     * return others, the node is smaller or equal than the order.
     */
    uint16 (*findSmallEqual)(hSkipList cthis, slType order);
    uint8 (*add)(hSkipList cthis, void *block);             /* TRUE/FALSE */
    uint8 (*del)(hSkipList cthis, slType order);            /* TRUE/FALSE */
    void (*dynUpdate)(hSkipList cthis, uint16 arrayIndex);
    
    IMPL(blockOrder);
    IMPL(BlockM);
};

#endif /*SKIPLIST_H_*/

/**************************** Copyright(C) pxf ****************************/
