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
#define RED_BLACK_NODE_MASK                      ((addrType)0u-2u)//(addrType)((htsRBNode)0u-2u)
#define RED_BLACK_COLOR_MASK                     ((addrType)1u)//(addrType)((htsRBNode)1u)
#define RED_BLACK_GET_NODE_FATHER(hNode,father_) do{father_.all = hNode->father.all; father_.bit.red = 0u;}while(0)

#define RED_BLACK_ISRED(hNode)                   (hNode->father.bit.red)
#define RED_BLACK_SETRED(hNode)                  (hNode->father.bit.red = 1u)
#define RED_BLACK_CLEARRED(hNode)                (hNode->father.bit.red = 0u)

#define RED_BLACK_CLEARLEFT(hNode)               (hNode->left = OOPC_NULL)
#define RED_BLACK_CLEARRIGHT(hNode)              (hNode->right = OOPC_NULL)
#define RED_BLACK_SETLEFT(hNode,kid)             (hNode->left = kid)
#define RED_BLACK_SETRIGHT(hNode,kid)            (hNode->right = kid)
#define RED_BLACK_SETFATHER(hNode,father_)       do{if(RED_BLACK_ISRED(hNode)){hNode->father.all=father_;RED_BLACK_SETRED(hNode);}else{hNode->father.all=father_;RED_BLACK_CLEARRED(hNode);}}while(0)

#define RED_BLACK_HAVELEFT(hNode)                (hNode->left != OOPC_NULL)
#define RED_BLACK_HAVERIGHT(hNode)               (hNode->right != OOPC_NULL)
#define RED_BLACK_HAVEFATHER(hNode)              ((hNode->father.bit.node) != (addrType)0u)

#define RED_BLACK_ISLEFT(hNode,father_)          (father_.all->left == hNode)
#define RED_BLACK_ISRIGHT(hNode,father_)         (father_.all->right == hNode)




/* retree list node */
typedef struct tsRBNode tsRBNode,*htsRBNode,**hhtsRBNode;
typedef union {
    /* pointer bit0 indicate red black attribute. red is set. */
    htsRBNode all;
    struct {
        addrType red:1;
        addrType node:((sizeof(addrType)<<3u)-1u);
    } bit;
} tuRBNode, *htuRBNode;
struct tsRBNode{
    tuRBNode father;           /* father node. pointer bit0 indicate red black attribute. red is set. */
    htsRBNode left;            /* left node. */
    htsRBNode right;           /* right node. */
    void *block;               /* indicate node block. */
};
/* if stack only use to adjust node, stack lenght only need tree depth.
 * if you want to print order, stack lenght need max layer lenth.
 */
#define RED_BLACK_STACK_LENGTH                    50u//2050u
#define RED_BLACK_STACK_SIZE                      (sizeof(htsRBNode)*RED_BLACK_STACK_LENGTH)
#define RED_BLACK_MANA_SIZE(num)                  (RED_BLACK_STACK_SIZE+BLOCKMCFG_CAL_MANAGE_SIZE(tsRBNode,num))
typedef enum {
    node_none = 0u,
    node_predecessor,
    node_successor
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
    hRBTree (*init)(hRBTree cthis, uint8 *rbSpace, uint32 blockMMax,
            rbType (*rbOrder)(void *block));

    /* RBTree class parameters. */
    uint8 *rbSpace;
    htsRBNode root;

    /* RBTree class functions. */
    /* return OOPC_NULL, not find the order.
     * return others, the node of the specific order.
     */
    htsRBNode (*find)(hRBTree cthis, rbType order);
    uint8 (*add)(hRBTree cthis, void *block);           /* TRUE/FALSE */
    uint8 (*del)(hRBTree cthis, rbType order);          /* TRUE/FALSE */
    void (*lRotate)(hRBTree cthis, htsRBNode node);
    void (*rRotate)(hRBTree cthis, htsRBNode node);
    void (*llRedTrans)(hRBTree cthis, htsRBNode node);
    void (*lrRedTrans)(hRBTree cthis, htsRBNode node);
    void (*rlRedTrans)(hRBTree cthis, htsRBNode node);
    void (*lRedRSubRedTrans)(hRBTree cthis, htsRBNode node);
    htsRBNode (*predecessor)(hRBTree cthis, htsRBNode node);
    htsRBNode (*successor)(hRBTree cthis, htsRBNode node);
    htsRBNode (*nodeForward)(hRBTree cthis, htsRBNode node);
    htsRBNode (*nodeNext)(hRBTree cthis, htsRBNode node);
    void (*getNode)(hRBTree cthis, rbType equal, rbType less, hhtsRBNode nodes, rbType *len);
    void (*preOrder)(hRBTree cthis, hhtsRBNode nodes);
    void (*midOrder)(hRBTree cthis, hhtsRBNode nodes);
    void (*postOrder)(hRBTree cthis, hhtsRBNode nodes);
    void (*rbTreeOrder)(hRBTree cthis, hhtsRBNode nodes);                  /* red black tree order. */
    void (*sTreeOrder)(hRBTree cthis, hhtsRBNode nodes, rbType *len);  /* search tree order. */
    htsRBNode (*min)(hRBTree cthis);
    htsRBNode (*max)(hRBTree cthis);
    uint16 (*depth)(hRBTree cthis);

    IMPL(rbOrder);
    IMPL(BlockM);
    IMPL(Fifo);
};

#endif /*RBTREE_H_*/

/**************************** Copyright(C) pxf ****************************/
