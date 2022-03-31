/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RBTree.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/16 11:56:13
 * Description  : RBTree class and interface declaration file.
 * Others       :
 * History      : 20211016 pxf Initially established.
 **************************************************************************/

#ifndef RBTREE_H_
#define RBTREE_H_

/* Include head files. */
#include "StandType.h"
#include "Oopc.h"
#include "BlockM.h"
#include "Fifo.h"

/***********************************************************
 * MACRO VERTION
 **********************************************************/
#define RBTREE_MACRO_VERSION                    0xC01D00    /* C represent V,D represent ., Current version is V1.00 */

/***********************************************************
 * Data type declaration.
 **********************************************************/
/* Data declaration.
 **********************************************/
typedef uint32 rbType;
#define RED_BLACK_TYPE_BITS                      ((sizeof(rbType)>>1u)+3u)//0x5u//0x4u//
#define RED_BLACK_TYPE_WIDTH                     (1u<<RED_BLACK_TYPE_BITS)
#define RED_BLACK_TYPE_MASK                      (RED_BLACK_TYPE_WIDTH-1u)
/* Basic operation macros.
 **********************************************/
#define RED_BLACK_ISRED(hNode)                   ((addrType)hNode->father&1u)
#define RED_BLACK_SETRED(hNode)                  (*(haddrType)&hNode->father |= 1u)
#define RED_BLACK_CLEARRED(hNode)                (*(haddrType)&hNode->father &= (addrType)((htsRBNode)0u-2u))

#define RED_BLACK_CLEARLEFT(hNode)               (hNode->left = OOPC_NULL)
#define RED_BLACK_CLEARRIGHT(hNode)              (hNode->right = OOPC_NULL)
#define RED_BLACK_SETLEFT(hNode,kid)             (hNode->left = kid)
#define RED_BLACK_SETRIGHT(hNode,kid)            (hNode->right = kid)
#define RED_BLACK_SETFATHER(hNode,father_)       do{if(RED_BLACK_ISRED(hNode)){hNode->father=father_;RED_BLACK_SETRED(hNode);}else{hNode->father=father_;}}while(0)

#define RED_BLACK_HAVELEFT(hNode)                (hNode->left != OOPC_NULL)
#define RED_BLACK_HAVERIGHT(hNode)               (hNode->right != OOPC_NULL)
#define RED_BLACK_HAVEFATHER(hNode)              (((addrType)hNode->father&RED_BLACK_NODE_MASK) != (addrType)OOPC_NULL)

#define RED_BLACK_ISLEFT(hNode)                  (((htsRBNode)((addrType)hNode->father&RED_BLACK_NODE_MASK))->left == hNode)
#define RED_BLACK_ISRIGHT(hNode)                 (((htsRBNode)((addrType)hNode->father&RED_BLACK_NODE_MASK))->right == hNode)

#define RED_BLACK_HNODE(hNode)                   ((addrType)hNode&(addrType)((htsRBNode)0u-2u))
#define RED_BLACK_NODE_MASK                      (addrType)((htsRBNode)0u-2u)
#define RED_BLACK_COLOR_MASK                     (addrType)((htsRBNode)1u)

#define RED_BLACK_ADDR_VALUE(hNode)              (*(haddrType)&hNode)
/* skip list node */
typedef struct tsRBNode tsRBNode,*htsRBNode,**hhtsRBNode;
struct tsRBNode{
    htsRBNode father;          /* father node. pointer bit0 indicate red black attribute. red is set. */
    htsRBNode left;            /* left node. */
    htsRBNode right;           /* right node. */
    void *block;               /* indicate node block. */
};
#define RED_BLACK_STACK_SIZE                      20u
#define RED_BLACK_MANA_SIZE(num)                  ((sizeof(htsRBNode)*num)+BLOCKMCFG_CAL_MANAGE_SIZE(tsRBNode,num)+(sizeof(htsRBNode)*RED_BLACK_STACK_SIZE))
typedef enum {
    node_none = 0u,
    node_successor,
    node_predecessor
}teFindNodeType;
/* Data reference.
 **********************************************/
/* TODO */

/***********************************************************
 * Interface definition.
 **********************************************************/
/* Interface declaration
 **********************************************/
INF(rbOrder){
    rbType (*rbOrder)(void *block);
};

/***********************************************************
 * RBTree class definition.
 **********************************************************/
/* RBTree class declaration.
 * current red black tree is associated to 2-3 tree.
 * 3 node only expressed with red node left-leaning black node.
 **********************************************/
CL(RBTree){
    hRBTree self;
    hRBTree (*init)(hRBTree cthis);

    /* RBTree class parameters. */
    htsRBNode root;

    /* RBTree class functions. */
    /* return OOPC_NULL, not find the order.
     * return others, the node of the specific order.
     */
    htsRBNode (*find)(hRBTree cthis, rbType order);
    uint16 (*add)(hRBTree cthis, void *block);           /* TRUE/FALSE */
    uint16 (*del)(hRBTree cthis, rbType order);          /* TRUE/FALSE */
    void (*lRotate)(hRBTree cthis, htsRBNode node);
    void (*rRotate)(hRBTree cthis, htsRBNode node);
    htsRBNode (*predecessor)(hRBTree cthis, htsRBNode node);
    htsRBNode (*successor)(hRBTree cthis, htsRBNode node);
    void (*preOrder)(hRBTree cthis, hhtsRBNode nodes);
    void (*midOrder)(hRBTree cthis, hhtsRBNode nodes);
    void (*postOrder)(hRBTree cthis, hhtsRBNode nodes);
    htsRBNode (*min)(hRBTree cthis);
    htsRBNode (*max)(hRBTree cthis);

    IMPL(rbOrder);
    IMPL(BlockM);
    IMPL(Fifo);
};

#endif /*RBTREE_H_*/

/**************************** Copyright(C) pxf ****************************/
