/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : RBTree.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/16 11:56:13
 * Description  : RBTree class functions definition source file.
 * Others       :
 * History      : 20211016 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "RBTree.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * RBTree class definition.
 **********************************************************/
/* Function : RBTree_find(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
htsRBNode RBTree_find(hRBTree cthis, rbType order){
    htsRBNode nodeRet = OOPC_NULL;
    htsRBNode nodeFind = OOPC_NULL;
    rbType orderFind = 0u;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        nodeFind = cthis->root;
        while(nodeFind != OOPC_NULL){
            orderFind = cthis->rbOrder.rbOrder(nodeFind->block);
            if(order == orderFind){
                nodeRet = nodeFind;
                break;
            }
            /* search left branch. */
            if(order < orderFind){
                nodeFind = nodeFind->left;
                continue;
            }
            /* search right branch. */
            nodeFind = nodeFind->right;
        }
    }while(0);
    return nodeRet;
}

/* Function : RBTree_add(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
uint8 RBTree_add(hRBTree cthis, void *block){
    uint8 opRes = TRUE;
    htsRBNode node = OOPC_NULL;
    htsRBNode nodeFind = OOPC_NULL;
    tuRBNode nodeFather;
    rbType order = 0u;
    rbType orderFind = 0u;
    teFindNodeType adjust = node_none;

    node = cthis->BlockM.malloc(cthis->BlockM.self,sizeof(tsRBNode));
    node->block = block;
    /* set red and clear kid nodes. */
    RED_BLACK_SETRED(node);
    RED_BLACK_CLEARLEFT(node);
    RED_BLACK_CLEARRIGHT(node);
    order = cthis->rbOrder.rbOrder(node->block);
    do{
        /* cthis->root dispose. */
        if(!cthis->root){
            cthis->root = node;
            /* clear color and set father null. */
            RED_BLACK_CLEARRED(node);
            RED_BLACK_SETFATHER(node,OOPC_NULL);
            opRes = TRUE;
            adjust = node_none;
            break;
        }
        /* find the successor/predecessor node. */
        nodeFind = cthis->root;
        while(nodeFind != OOPC_NULL){
            orderFind = cthis->rbOrder.rbOrder(nodeFind->block);
            /* if there is a equal node, then exit. */
            if(order == orderFind){
                cthis->BlockM.free(cthis->BlockM.self,node);
                opRes = FALSE;
                adjust = node_none;
                break;
            }
            /* search left branch. */
            if(order < orderFind){
                if(nodeFind->left == OOPC_NULL){
                    /* find the successor node. and set the node next to it. */
                    nodeFind->left = node;
                    RED_BLACK_SETFATHER(node,nodeFind);
                    opRes = TRUE;
                    adjust = node_predecessor;
                    break;
                }
                nodeFind = nodeFind->left;
                continue;
            }
            /* search right branch. */
            if(nodeFind->right == OOPC_NULL){
                /* find the predecessor node. and set the node next to it. */
                nodeFind->right = node;
                RED_BLACK_SETFATHER(node,nodeFind);
                opRes = TRUE;
                adjust = node_successor;
                break;
            }
            nodeFind = nodeFind->right;
        }
    }while(0);
    /* if not adjust directly return. */
    while(adjust){
        /* situation 1. */
        /* father node is black. */
        if(!RED_BLACK_ISRED(nodeFind)){
            /* if find node_predecessor node. */
            if(adjust == node_predecessor){
                /* because find node has not left node, so it has not right node too.
                 * it can directly return.
                 */
                adjust = node_none;
                break;
            }
            /* if find node_successor node. */
            /* if(adjust == node_successor) */
            if(RED_BLACK_HAVELEFT(nodeFind)
            &&RED_BLACK_ISRED(nodeFind->left)){
                /* if find node has left, and check whether it is red. */
                /* change new node and left color to black. set find node color red. */
                RED_BLACK_SETRED(nodeFind);
                RED_BLACK_CLEARRED(node);
                RED_BLACK_CLEARRED(nodeFind->left);
                /* have not father node. */
                if(!RED_BLACK_HAVEFATHER(nodeFind)){
                    /* if find node is red, clear it. */
                    RED_BLACK_CLEARRED(nodeFind);
                    adjust = node_none;
                    break;
                }
                /* if find node is left. */
                RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
                if(RED_BLACK_ISLEFT(nodeFind,nodeFather)){
                    /* if nodeFind's father is red. continue adujust. */
                    if(RED_BLACK_ISRED(nodeFather.all)){
                        node = nodeFind;
                        nodeFind = nodeFather.all;
                        adjust = node_predecessor;
                        continue;
                    }
                    adjust = node_none;
                    break;
                }
                /* if find node is right. */
                node = nodeFind;
                nodeFind = nodeFather.all;
                adjust = node_successor;
                continue;
            }
            /* left is black. or there is no left node. also do this operation. */
            /* exchange find node and node color, left rotate find node. */
            RED_BLACK_CLEARRED(node);
            RED_BLACK_SETRED(nodeFind);
            cthis->lRotate(cthis,nodeFind);
            adjust = node_none;
            break;
        }
        /* situation 2. */
        /* father node is red. */
        if(adjust == node_predecessor){
            /* if find node_predecessor node. */
            /* situation 2.1. */
            /* have not father node. */
            if(!RED_BLACK_HAVEFATHER(nodeFind)){
                /* if have not father node, set find node black too. and return. */
                RED_BLACK_CLEARRED(nodeFind);
                adjust = node_none;
                break;
            }
            /* if node and nodeFind is red. do the left left red transform. */
            RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
            cthis->llRedTrans(cthis,nodeFather.all);
        }else{
            /* if find node_successor node. */
            /* if(adjust == node_successor) */
            /* situation 2.2. */
            /* left rotate find node, and the situation is the same as situation 2.1 */
            /* have not father node. */
            if(!RED_BLACK_HAVEFATHER(nodeFind)){
                /* if have not father node, set find node black too. and return. */
                RED_BLACK_CLEARRED(node);
                cthis->lRotate(cthis,nodeFind);
                adjust = node_none;
                break;
            }
            /* if node and nodeFind is red. do the left right red transform. */
            RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
            cthis->lrRedTrans(cthis,nodeFather.all);
            nodeFind = node;
        }
        /* have not father node. */
        if(!RED_BLACK_HAVEFATHER(nodeFind)){
            /* if find node is red, clear it. */
            RED_BLACK_CLEARRED(nodeFind);
            adjust = node_none;
            break;
        }
        /* set node for next adjust. */
        node = nodeFind;
        RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
        /* if the node is left node. goto perform the flow of execution again. */
        if(RED_BLACK_ISLEFT(nodeFind,nodeFather)){
            adjust = node_predecessor;
        }else{
            adjust = node_successor;
        }
        nodeFind = nodeFather.all;
    }
    return opRes;
}

/* Function : RBTree_del(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 *            we use successor node to replace delete node,
 *            because the left node may be red node, can be directly delete.
 **********************************************/
uint8 RBTree_del(hRBTree cthis, rbType order){
    uint8 opRes = TRUE;
    htsRBNode node = OOPC_NULL;
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeStart = OOPC_NULL;
    tuRBNode nodeFather;
    teFindNodeType adjust = node_none;

    /* find the delete node. */
    node = cthis->find(cthis,order);
    do{
        /* abnormal dispose. */
        if(node == OOPC_NULL){
            opRes = FALSE;
            break;
        }
        /* if node is leaf, do correspond operation. */
        if(!RED_BLACK_HAVELEFT(node)){
            RED_BLACK_GET_NODE_FATHER(node,nodeFather);
            nodeFind = nodeFather.all;
            /* the delete node is not root. */
            if(nodeFather.bit.node){
                /* delete the node. right or left. */
                if(RED_BLACK_ISLEFT(node,nodeFather)){
                    adjust = node_predecessor;
                }else{
                    adjust = node_successor;
                }
                break;
            }
            /* the delete node is root. delete the root as node_predecessor. */
            adjust = node_predecessor;
            break;
        }
        /* if node is not leaf, but has not right node.
         * use the left predecessor replace delete node.
         */
        if(!RED_BLACK_HAVERIGHT(node)){
            /* directly use predecessor replace delete node. */
            node->block = node->left->block;
            /* delete the predecessor. */
            nodeFind = node;
            node = node->left;
            adjust = node_predecessor;
            break;
        }
        /* node is not leaf. find the successor.
         * using successor replace the node, and then delete successor.
         * The successor node is the left node, it must be a leaf node.
         */
        nodeFind = cthis->successor(cthis,node);
        /* directly use successor replace delete node. */
        node->block = nodeFind->block;
        node = nodeFind;
        /* delete the successor. */
        RED_BLACK_GET_NODE_FATHER(node,nodeFather);
        nodeFind = nodeFather.all;
        /* judge successor is left or right. */
        if(RED_BLACK_ISLEFT(node,nodeFather)){
            adjust = node_predecessor;
        }else{
            adjust = node_successor;
        }
    }while(0);
    /* delete the node. All the node to be delete is leaf. */
    do{
        /* if it is no need to adjust, directly return. */
        if(!adjust){
            break;
        }
        /* if find node is the root. directly delete. */
        if(nodeFind == OOPC_NULL){
            cthis->root = OOPC_NULL;
            cthis->BlockM.free(cthis->BlockM.self,node);
            adjust = node_none;
            break;
        }
        /* if the delete node is predecessor. */
        if(adjust == node_predecessor){
            /* if the delete node is red, directly delete it. */
            if(RED_BLACK_ISRED(node)){
                RED_BLACK_CLEARLEFT(nodeFind);
                cthis->BlockM.free(cthis->BlockM.self,node);
                adjust = node_none;
                break;
            }
            /* the delete node is black.
             * if delete node's father is red. and the node's father must have two kids.
             * delete the node and left rotate the nodeFind.
             */
            if(RED_BLACK_ISRED(nodeFind)){
                /* if the findNode's right has red left.
                 * delete the node, set nodeFind black, right rotate findNode's right and left rotate the nodeFind.
                 */
                RED_BLACK_CLEARLEFT(nodeFind);
                cthis->BlockM.free(cthis->BlockM.self,node);
                if(RED_BLACK_HAVERIGHT(nodeFind)
                &&RED_BLACK_HAVELEFT(nodeFind->right)
                &&RED_BLACK_ISRED(nodeFind->right->left)){
                    RED_BLACK_CLEARRED(nodeFind);
                    cthis->rRotate(cthis,nodeFind->right);
                }
                //RED_BLACK_CLEARLEFT(nodeFind);
                //cthis->BlockM.free(cthis->BlockM.self,node);
                if(RED_BLACK_HAVERIGHT(nodeFind)){
                    cthis->lRotate(cthis,nodeFind);
                }
                adjust = node_none;
                break;
            }
            /* if the findNode's right has red left.
             * set the red left to black, right rotate findNode's right.
             * delete the node and then left rotate nodeFind.
             */
            if(RED_BLACK_HAVERIGHT(nodeFind)
            &&RED_BLACK_HAVELEFT(nodeFind->right)
            &&RED_BLACK_ISRED(nodeFind->right->left)){
                RED_BLACK_CLEARRED(nodeFind->right->left);
                cthis->rRotate(cthis,nodeFind->right);
                RED_BLACK_CLEARLEFT(nodeFind);
                cthis->BlockM.free(cthis->BlockM.self,node);
                cthis->lRotate(cthis,nodeFind);
                adjust = node_none;
                break;
            }
            /* no red node, find root or father node is red. */
            break;
        }
        /* if the delete node is successor. */
        /* if delete node's father is red. and the node's father must have two kids.
         */
        if(RED_BLACK_ISRED(nodeFind)){
            /* if the opposite have red left,
             * clear nodeFind and opposite's left color, set opposite to red,
             * delete the node, and right rotate nodeFind.
             */
            if(RED_BLACK_HAVELEFT(nodeFind)
            &&RED_BLACK_HAVELEFT(nodeFind->left)
            &&RED_BLACK_ISRED(nodeFind->left->left)){
                RED_BLACK_CLEARRED(nodeFind);
                RED_BLACK_CLEARRED(nodeFind->left->left);
                RED_BLACK_SETRED(nodeFind->left);
                RED_BLACK_CLEARRIGHT(nodeFind);
                cthis->BlockM.free(cthis->BlockM.self,node);
                cthis->rRotate(cthis,nodeFind);
                adjust = node_none;
            }
            /* delete the node and exchange delete node's father and its left kid's color. */
            RED_BLACK_CLEARRIGHT(nodeFind);
            cthis->BlockM.free(cthis->BlockM.self,node);
            if(RED_BLACK_HAVELEFT(nodeFind)){
                RED_BLACK_CLEARRED(nodeFind);
                RED_BLACK_SETRED(nodeFind->left);
            }
            adjust = node_none;
            break;
        }
        /* if delete node's opposite left is red. and opposite left's right has no red child. do down common process.
         * option1:
         * set opposite left black and it's right kid red, delete the node and right rotate nodeFind.
         * option2:
         * right rotate nodeFind, delete the node, next right right rotate nodeFind,
         * and then left rotate origin opposite left.
         * option1 use less time, so we choose this method.
         */
        if(RED_BLACK_HAVELEFT(nodeFind)
        &&RED_BLACK_ISRED(nodeFind->left)){
            /* if opposite left's right has a red left.
             * first, transformat,
             * and then use the red left replace and delete the left.
             */
            if(RED_BLACK_HAVERIGHT(nodeFind->left)
            &&RED_BLACK_HAVELEFT(nodeFind->left->right)
            &&RED_BLACK_ISRED(nodeFind->left->right->left)){
                cthis->lRedRSubRedTrans(cthis,nodeFind);
                if(RED_BLACK_HAVELEFT(node)){
                    node->block = node->left->block;
                    nodeFind = node;
                    node = node->left;
                    RED_BLACK_CLEARLEFT(nodeFind);
                    cthis->BlockM.free(cthis->BlockM.self,node);
                }
                adjust = node_none;
                break;
            }
            /* do the common process as above desrcribe. */
            RED_BLACK_CLEARRED(nodeFind->left);
            if(RED_BLACK_HAVERIGHT(nodeFind->left)){
                RED_BLACK_SETRED(nodeFind->left->right);
            }
            RED_BLACK_CLEARRIGHT(nodeFind);
            cthis->BlockM.free(cthis->BlockM.self,node);
            cthis->rRotate(cthis,nodeFind);
            adjust = node_none;
            break;
        }
        /* no red node, find root or father node is red. */
    }while(0);
    /* find root or father node is red or the findNode opposite is red.
     * and then decrease adjust node position without depth changing.
     */
    do{
        /* if it is no need to adjust, directly return. */
        if(!adjust){
            break;
        }
        /* search father node until father node is red. if there is no red, exchange root to red.
         * and then change self color to black, turn kids nodes color to red, till to the delete node.
         * after change left rotate to restore right red node.
         */
        cthis->Fifo.clearAll(cthis->Fifo.self);
        nodeFind = node;
        RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
        while((nodeFather.all != OOPC_NULL)          /* root. */
        &&(!RED_BLACK_ISRED(nodeFind)                /* father red node. */
        &&(!((RED_BLACK_ISRIGHT(nodeFind,nodeFather))
            && RED_BLACK_HAVELEFT(nodeFather.all)
            &&RED_BLACK_ISRED(nodeFather.all->left)))) /* opposite, left red node. */
                ){
            cthis->Fifo.push(cthis->Fifo.self,&nodeFind);
            RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
            /* get father node. */
            if(nodeFather.all){
                nodeFind = nodeFather.all;
                RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
            }
        }
        /* set node start to find node's father. */
        nodeStart = nodeFather.all;
        if((nodeStart != OOPC_NULL)
        &&(nodeFind != OOPC_NULL)){
            if(RED_BLACK_ISRED(nodeFind)){
                /* find node is red node. */
                RED_BLACK_CLEARRED(nodeFind);
            }else{
                /* if find node not root or father node red, then right rotate.
                 * and clear new father red node color, and set new right red(there is no need do, set kids red directly).
                 * save the find node.
                 */
                cthis->Fifo.push(cthis->Fifo.self,&nodeFind);
                RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
                nodeFind = nodeFather.all;
                cthis->rRotate(cthis,nodeFind);
                //RED_BLACK_SETRED(nodeFind);                  /* there is no need to set red, directly set kids' color. */
                RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);/* change pointer to new father. */
                nodeFind = nodeFather.all;
                RED_BLACK_CLEARRED(nodeFind);
                nodeStart = nodeFather.all;                    /* nodeStart pointer to the red node to be cleared. */
            }
        }else{
            /* find root node directly go on. */
        }
        /* set fifo node's opposite to red. */
        while(!cthis->Fifo.isEmpty(cthis->Fifo.self)){
            /* set the opposite node to red. till to the delete node.
             * if find node is left node, then set right node to red. vice versa.
             */
            cthis->Fifo.pop(cthis->Fifo.self,&nodeFind);
            RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
            if(RED_BLACK_ISLEFT(nodeFind,nodeFather)){
                RED_BLACK_SETRED(nodeFather.all->right);
            }else{
                RED_BLACK_SETRED(nodeFather.all->left);
            }
        }
        /* delete the node. */
        cthis->BlockM.free(cthis->BlockM.self,node);
        RED_BLACK_GET_NODE_FATHER(node,nodeFather);
        nodeFind = nodeFather.all;
        /* get the opposite position, and adjust the red node. */
        if(RED_BLACK_ISLEFT(node,nodeFather)){
            RED_BLACK_CLEARLEFT(nodeFind);
            /* goto merge operation. */
            node = nodeFind->right;
            adjust = node_successor;
        }else{
            RED_BLACK_CLEARRIGHT(nodeFind);
            /* goto merge operation. */
            node = nodeFind->left;
            adjust = node_predecessor;
        }
    }while(0);
    /* if it is no need to adjust, directly return. */
    while(adjust){
        do{
            /* the node to adjust is red.
             * node to adjust is right node.
             * judge whether node has a red left node. if it has do correspond operation.
             */
            if(adjust == node_successor){
                /* split function to basic process unit. and then combine the units for complex function. */
                /* if nodeFind's left is red node.
                 * if it is true, just merge the left node.
                 * this situation may be happened, previous merage create a red left.
                 */
                if(RED_BLACK_HAVELEFT(nodeFind)
                &&RED_BLACK_ISRED(nodeFind->left)){
                    RED_BLACK_CLEARRED(nodeFind->left);
                    RED_BLACK_CLEARRED(nodeFind->right);
                    RED_BLACK_SETRED(nodeFind);
                    break;
                }
                /* if nodeFind's left is black and current node has a red left.
                 * then do the right left red transform.
                 */
                if(RED_BLACK_HAVERIGHT(nodeFind)
                &&RED_BLACK_HAVELEFT(nodeFind->right)
                &&RED_BLACK_ISRED(nodeFind->right->left)){
                    nodeFather.all = nodeFind->right->left; /* tempararoy save the next nodeFind. */
                    cthis->rlRedTrans(cthis,nodeFind);
                    nodeFind = nodeFather.all;
                    break;
                }
                /* if nodeFind's left is black.
                 * setting node's color black and nodeFind's color red.then left rotate nodeFind.
                 */
                RED_BLACK_SETRED(nodeFind);
                RED_BLACK_CLEARRED(node);
                cthis->lRotate(cthis,nodeFind);
                RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
                nodeFind = nodeFather.all;
                break;
            }
            /* if(adjust == node_predecessor) process. */
            /* if nodeFind's right is red.(may be last merage setting the right node's color red.)
             * then clear nodeFind's right node color and the node's color, and set nodeFind's color to red.
             */
            if(RED_BLACK_HAVERIGHT(nodeFind)
            &&RED_BLACK_ISRED(nodeFind->right)){
                RED_BLACK_CLEARRED(nodeFind->left);
                RED_BLACK_CLEARRED(nodeFind->right);
                RED_BLACK_SETRED(nodeFind);
                break;
            }
            /* node's left is red node.
             * then do the left left red transform.
             */
            if(RED_BLACK_HAVELEFT(node)
            &&RED_BLACK_ISRED(node->left)){
                nodeFather.all = node; /* tempararoy save the next nodeFind. */
                cthis->llRedTrans(cthis,nodeFind);
                nodeFind = nodeFather.all;
                break;
            }
            /* only the node is red, continue. */
        }while(0);
        RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
        /* judge upper father. */
        if(nodeFather.all == nodeStart){
            /* if find node is the end node of adjust, directly return and clear fifo. */
            cthis->Fifo.clearAll(cthis->Fifo.self);
            /* if nodeFind is right of nodeStart and nodeFind is red.
             * then setting nodeFind's color black and nodeStart to red and left rotate nodeStart.
             */
            if((nodeStart != OOPC_NULL)
            &&(RED_BLACK_ISRIGHT(nodeFind,nodeFather))
            &&RED_BLACK_ISRED(nodeFind)){
                RED_BLACK_SETRED(nodeStart);
                RED_BLACK_CLEARRED(nodeFind);
                cthis->lRotate(cthis,nodeStart);
            }
            /* keep root node black. */
            if(RED_BLACK_ISRED(cthis->root)){
                RED_BLACK_CLEARRED(cthis->root);
            }
            break;
        }
        /* set node to the opposite of find node. */
        if(RED_BLACK_ISLEFT(nodeFind,nodeFather)){
            nodeFind = nodeFather.all;
            node = nodeFind->right;
            adjust = node_successor;
        }else{
            nodeFind = nodeFather.all;
            node = nodeFind->left;
            adjust = node_predecessor;
        }
    }
    return opRes;
}

/* Function : RBTree_lRotate(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : if right node is red node, it will not increase left depth.
 *            and exchange new father and left color can keep depth balance.
 *            others, it will increase left depth.
 **********************************************/
void RBTree_lRotate(hRBTree cthis, htsRBNode node){
    htsRBNode nodeFind = OOPC_NULL;
    tuRBNode nodeFather;
    do{
        /* dispose abnormal. */
        nodeFind = node->right;
        /* if right is null, there is no way to rotate. */
        if(nodeFind == OOPC_NULL){
            break;
        }
        /* set father node. */
        if(node->father.bit.node){
            /* update father node's kid */
            RED_BLACK_GET_NODE_FATHER(node,nodeFather);
            if(RED_BLACK_ISLEFT(node,nodeFather)){
                RED_BLACK_SETLEFT(nodeFather.all,nodeFind);
            }else{
                RED_BLACK_SETRIGHT(nodeFather.all,nodeFind);
            }
        }else{
            /* update root. */
            cthis->root = nodeFind;
        }
        /* pointer to root, the node color should keep as previous. */
        RED_BLACK_SETFATHER(nodeFind,node->father.all);
        RED_BLACK_SETFATHER(node,nodeFind);
        /* if nodeFind has left, set its new father to node. */
        if(nodeFind->left){
            RED_BLACK_SETFATHER(nodeFind->left,node);
        }
        node->right = nodeFind->left;        /* change father left node to previous father node right. */
        nodeFind->left = node;               /* change current left node to previous node. */
    }while(0);
}

/* Function : RBTree_rRotate(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : if left node is red node, it will not increase right depth.
 *            and exchange new father and right color can keep depth balance.
 *            others, it will increase right depth.
 **********************************************/
void RBTree_rRotate(hRBTree cthis, htsRBNode node){
    htsRBNode nodeFind = OOPC_NULL;
    tuRBNode nodeFather;
    do{
        /* dispose abnormal. */
        nodeFind = node->left;
        /* if left is null, there is no way to rotate. */
        if(nodeFind == OOPC_NULL){
            break;
        }
        /* set father node. */
        if(node->father.bit.node){
            /* update father node's kid */
            RED_BLACK_GET_NODE_FATHER(node,nodeFather);
            if(RED_BLACK_ISLEFT(node,nodeFather)){
                RED_BLACK_SETLEFT(nodeFather.all,nodeFind);
            }else{
                RED_BLACK_SETRIGHT(nodeFather.all,nodeFind);
            }
        }else{
            /* update root. */
            cthis->root = nodeFind;
        }
        /* pointer to root, the node color should keep as previous. */
        RED_BLACK_SETFATHER(nodeFind,node->father.all);
        RED_BLACK_SETFATHER(node,nodeFind);
        /* if nodeFind has right, set its new father to node. */
        if(nodeFind->right){
            RED_BLACK_SETFATHER(nodeFind->right,node);
        }
        node->left = nodeFind->right;        /* change father right node to previous father node left. */
        nodeFind->right = node;              /* change current left node to previous node. */
    }while(0);
}

/* Function : RBTree_llRedTrans(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : left and it's left is red, then transformat the nodes.
 **********************************************/
void RBTree_llRedTrans(hRBTree cthis, htsRBNode node){
    /*
     *         o           o
     *        / \         / \
     *       o   o       r   o
     *      / \         / \
     *     r   o       o   o
     *    / \         / \  /\
     *   r   o       o   oo  o
     *  / \
     * o   o
     */
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeLeft = OOPC_NULL;
    tuRBNode nodeFather;
    do{
        /* dispose abnormal. */
        nodeFind = node->left;
        /* if left is null, there is no way to transformat. */
        if(!(RED_BLACK_HAVELEFT(node)
        &&RED_BLACK_HAVELEFT(node->left))){
            break;
        }
        /* set father node. */
        if(RED_BLACK_HAVEFATHER(node)){
            /* update father node's kid */
            RED_BLACK_GET_NODE_FATHER(node,nodeFather);
            if(RED_BLACK_ISLEFT(node,nodeFather)){
                RED_BLACK_SETLEFT(nodeFather.all,nodeFind);
            }else{
                RED_BLACK_SETRIGHT(nodeFather.all,nodeFind);
            }
        }else{
            /* update root. */
            cthis->root = nodeFind;
            /* clear root color. */
            RED_BLACK_CLEARRED(nodeFind);
        }
        /* clear nodeFind's left color. */
        RED_BLACK_CLEARRED(nodeFind->left);
        /* set the transform nodes father. */
        RED_BLACK_SETFATHER(nodeFind,node->father.all);
        //RED_BLACK_SETFATHER(nodeFind->left,nodeFind);
        RED_BLACK_SETFATHER(node,nodeFind);
        /* set the nodeFind's kids. */
        //nodeFind->left;                    /* nodeFind's left keep unchange. */
        nodeLeft = nodeFind->right;
        nodeFind->right = node;              /* change node to nodeFind's right. */
        /* set the nodeFind left node's kids. */
        //nodeFind->left->left;              /* nodeFind left node's left keep unchange. */
        //nodeFind->left->right;             /* nodeFind left node's right keep unchange. */
        /* set the node's kids. */
        node->left = nodeLeft;               /* change previous nodeFind's right to node's left. */
        /* update node father. */
        if(nodeLeft){
            RED_BLACK_SETFATHER(nodeLeft,nodeFind->right);
        }
        //node->right;                       /* node's right keep unchange. */
    }while(0);
}

/* Function : RBTree_lrRedTrans(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : left and it's right is red, then transformat the nodes.
 **********************************************/
void RBTree_lrRedTrans(hRBTree cthis, htsRBNode node){
    /*
     *         o           o
     *        / \         / \
     *       o   o       r   o
     *      / \         / \
     *     r   o       o   o
     *    / \         / \  /\
     *   o   r       o   oo  o
     *      / \
     *     o   o
     */
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeLeft = OOPC_NULL;
    htsRBNode nodeRight = OOPC_NULL;
    tuRBNode nodeFather;
    do{
        /* dispose abnormal. */
        /* if left's right is null, there is no way to transformat. */
        if(!(RED_BLACK_HAVELEFT(node)
        &&RED_BLACK_HAVERIGHT(node->left))){
            break;
        }
        nodeFind = node->left->right;
        /* set father node. */
        if(RED_BLACK_HAVEFATHER(node)){
            /* update father node's kid */
            RED_BLACK_GET_NODE_FATHER(node,nodeFather);
            if(RED_BLACK_ISLEFT(node,nodeFather)){
                RED_BLACK_SETLEFT(nodeFather.all,nodeFind);
            }else{
                RED_BLACK_SETRIGHT(nodeFather.all,nodeFind);
            }
        }else{
            /* update root. */
            cthis->root = nodeFind;
            /* clear root color. */
            RED_BLACK_CLEARRED(nodeFind);
        }
        /* clear node's right color. */
        RED_BLACK_CLEARRED(node->left);
        /* set the transform nodes father. */
        RED_BLACK_SETFATHER(nodeFind,node->father.all);
        RED_BLACK_SETFATHER(node,nodeFind);
        RED_BLACK_SETFATHER(node->left,nodeFind);
        /* set the nodeFind's kids. */
        nodeRight = nodeFind->left;
        nodeFind->left = node->left;         /* change node's left to nodeFind's left. */
        nodeLeft = nodeFind->right;
        nodeFind->right = node;              /* change node to nodeFind's right. */
        /* set the node's kids. */
        node->left = nodeLeft;               /* change previous nodeFind's right to node's left. */
        //node->right;                       /* node's right keep unchange. */
        /* update node father. */
        if(nodeRight){
            RED_BLACK_SETFATHER(nodeRight,nodeFind->left);
        }
        /* set the previous node right's kids. */
        nodeFind->left->right = nodeRight;   /* change nodeFind's left to previous node's left's right. */
        /* update node father. */
        if(nodeLeft){
            RED_BLACK_SETFATHER(nodeLeft,node);
        }
        //nodeFind->left->right;             /* previous node left's right keep unchange. */
    }while(0);
}

/* Function : RBTree_rlRedTrans(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : right and it's left is red, then transformat the nodes.
 **********************************************/
void RBTree_rlRedTrans(hRBTree cthis, htsRBNode node){
    /*
     *         o               o
     *        / \             / \
     *       o   o           r   o
     *      / \             / \
     *     o   r           o   o
     *        / \         / \  /\
     *       r   o       o   oo  o
     *      / \
     *     o   o
     */
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeLeft = OOPC_NULL;
    htsRBNode nodeRight = OOPC_NULL;
    tuRBNode nodeFather;
    do{
        /* dispose abnormal. */
        /* if right's left is null, there is no way to transformat. */
        if(!(RED_BLACK_HAVERIGHT(node)
        &&RED_BLACK_HAVELEFT(node->right))){
            break;
        }
        nodeFind = node->right->left;
        /* set father node. */
        if(RED_BLACK_HAVEFATHER(node)){
            /* update father node's kid */
            RED_BLACK_GET_NODE_FATHER(node,nodeFather);
            if(RED_BLACK_ISLEFT(node,nodeFather)){
                RED_BLACK_SETLEFT(nodeFather.all,nodeFind);
            }else{
                RED_BLACK_SETRIGHT(nodeFather.all,nodeFind);
            }
        }else{
            /* update root. */
            cthis->root = nodeFind;
            /* clear root color. */
            RED_BLACK_CLEARRED(nodeFind);
        }
        /* clear node's right color. */
        RED_BLACK_CLEARRED(node->right);
        /* set the transform nodes father. */
        RED_BLACK_SETFATHER(nodeFind,node->father.all);
        RED_BLACK_SETFATHER(node,nodeFind);
        RED_BLACK_SETFATHER(node->right,nodeFind);
        /* set the nodeFind's kids. */
        nodeRight = nodeFind->left;
        nodeFind->left = node;               /* change node to nodeFind's left. */
        nodeLeft = nodeFind->right;
        nodeFind->right = node->right;       /* change node's right to nodeFind's right. */
        /* set the node's kids. */
        //node->left;                        /* node's left keep unchange. */
        node->right = nodeRight;             /* change previous nodeFind's left to node's right. */
        /* update node father. */
        if(nodeRight){
            RED_BLACK_SETFATHER(nodeRight,node);
        }
        /* set the previous node right's kids. */
        nodeFind->right->left = nodeLeft;    /* change nodeFind's right to previous node's left's left. */
        /* update node father. */
        if(nodeLeft){
            RED_BLACK_SETFATHER(nodeLeft,nodeFind->right);
        }
        //nodeFind->right->right;            /* previous node right's right keep unchange. */

    }while(0);
}

/* Function : RBTree_lRedRSubRedTrans(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : left and it's sub left is red, then transformat the nodes.
 **********************************************/
void RBTree_lRedRSubRedTrans(hRBTree cthis, htsRBNode node){
    /* 2-3 node transformat
     *         o               o
     *        / \             / \
     *       r   o           r   o
     *      / \             / \  /
     *     o   o           o   or
     *    /   /           /
     *   r   r           r
     */
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeLeft = OOPC_NULL;
    htsRBNode nodeRight = OOPC_NULL;
    tuRBNode nodeFather;
    do{
        /* dispose abnormal. */
        /* if left's right's left is null, there is no way to transformat. */
        if(!(RED_BLACK_HAVELEFT(node)
        &&RED_BLACK_HAVERIGHT(node->left)
        &&RED_BLACK_HAVELEFT(node->left->right))){
            break;
        }
        nodeFind = node->left->right;
        /* set father node. */
        if(node->father.bit.node){
            /* update father node's kid */
            RED_BLACK_GET_NODE_FATHER(node,nodeFather);
            if(RED_BLACK_ISLEFT(node,nodeFather)){
                RED_BLACK_SETLEFT(nodeFather.all,nodeFind);
            }else{
                RED_BLACK_SETRIGHT(nodeFather.all,nodeFind);
            }
        }else{
            /* update root. */
            cthis->root = nodeFind;
            /* clear root color. */
            RED_BLACK_CLEARRED(nodeFind);
        }
        /* clear nodeFind's left color and set node color. */
        RED_BLACK_CLEARRED(nodeFind->left);
        RED_BLACK_SETRED(node);
        /* set the transform nodes father. */
        RED_BLACK_SETFATHER(nodeFind,node->father.all);
        RED_BLACK_SETFATHER(nodeFind->left,node->left);
        RED_BLACK_SETFATHER(node->left,nodeFind);
        RED_BLACK_SETFATHER(node->right,nodeFind);
        RED_BLACK_SETFATHER(node,node->right);
        /* set the nodeFind's kids. */
        nodeRight = nodeFind->left;
        nodeLeft = node;
        nodeFind->left = node->left;         /* change node'left to nodeFind's left. */
        nodeFind->right = node->right;       /* change node's right to nodeFind's right. */
        /* set the previous node left's kids. */
        //nodeFind->left->left;              /* previous node's left keep unchange. */
        nodeFind->left->right = nodeRight;   /* change previous nodeFind's left to previous node's right. */
        /* update node father. */
        // if(nodeRight){
        //     RED_BLACK_SETFATHER(nodeRight,nodeFind->left);
        // }
        /* set the previous node right's kids. */
        RED_BLACK_CLEARLEFT(nodeLeft);
        RED_BLACK_CLEARRIGHT(nodeLeft);
        nodeFind->right->left = nodeLeft;    /* change node to previous node's right's left. */
        /* update node father. */
        // if(nodeLeft){
        //     RED_BLACK_SETFATHER(nodeLeft,nodeFind->right);
        // }
        //nodeFind->right->right;            /* previous node right's right keep unchange. */
    }while(0);
}

/* Function : RBTree_predecessor(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
htsRBNode RBTree_predecessor(hRBTree cthis, htsRBNode node){
    htsRBNode nodeRet = OOPC_NULL;
    do{
        nodeRet = node->left;
        while(nodeRet->right != OOPC_NULL){
            /* search right branch. */
            nodeRet = nodeRet->right;
        }
    }while(0);
    return nodeRet;
}

/* Function : RBTree_successor(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
htsRBNode RBTree_successor(hRBTree cthis, htsRBNode node){
    htsRBNode nodeRet = OOPC_NULL;
    do{
        nodeRet = node->right;
        while(nodeRet->left != OOPC_NULL){
            /* search left branch. */
            nodeRet = nodeRet->left;
        }
    }while(0);
    return nodeRet;
}

/* Function : RBTree_nodeForward(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
htsRBNode RBTree_nodeForward(hRBTree cthis, htsRBNode node){
    htsRBNode nodeRet = OOPC_NULL;
    htsRBNode nodeFind = node;
    tuRBNode nodeFather;
    do{
        /* have not left child node. */
        if(!nodeFind->left){
            /* if the nodeFind is not right, and father node is root. return OOPC_NULL */
            do{
                RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
                /* if nodeFind is root, directly return. */
                if(!nodeFather.all){
                    break;
                }
                /* search father node, if the node is left. */
                if(RED_BLACK_ISRIGHT(nodeFind,nodeFather)){
                    nodeRet = nodeFather.all;
                    break;
                }
                nodeFind = nodeFather.all;
            }while(nodeFind);
            break;
        }
        /* normal search child node. */
        nodeRet = nodeFind->left;
        while(nodeRet->right != OOPC_NULL){
            /* search right branch. */
            nodeRet = nodeRet->right;
        }
    }while(0);
    return nodeRet;
}

/* Function : RBTree_nodeNext(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
htsRBNode RBTree_nodeNext(hRBTree cthis, htsRBNode node){
    htsRBNode nodeRet = OOPC_NULL;
    htsRBNode nodeFind = node;
    tuRBNode nodeFather;
    do{
        /* have not right child node. */
        if(!nodeFind->right){
            /* if the nodeFind is not left, and father node is root. return OOPC_NULL */
            do{
                RED_BLACK_GET_NODE_FATHER(nodeFind,nodeFather);
                /* if nodeFind is root, directly return. */
                if(!nodeFather.all){
                    break;
                }
                /* search father node, if the node is left. */
                if(RED_BLACK_ISLEFT(nodeFind,nodeFather)){
                    nodeRet = nodeFather.all;
                    break;
                }
                nodeFind = nodeFather.all;
            }while(nodeFind);
            break;
        }
        /* normal search child node. */
        nodeRet = nodeFind->right;
        while(nodeRet->left != OOPC_NULL){
            /* search left branch. */
            nodeRet = nodeRet->left;
        }
    }while(0);
    return nodeRet;
}

/* Function : RBTree_getNode(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
void RBTree_getNode(hRBTree cthis, rbType equal, rbType less, hhtsRBNode nodes, rbType *len){
    hhtsRBNode nodeSave = nodes;
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeFirst = OOPC_NULL;
    rbType index = 0u;
    rbType order = 0u;
    rbType orderFirst = 0u;

    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        nodeFind = cthis->root;
        while(nodeFind){
            /* to find the equal or bigger one. */
            order = cthis->rbOrder.rbOrder(nodeFind->block);
            if(order == equal){
                nodeFirst = nodeFind;
                //orderFirst = order;
                //nodeFind = nodeFind->right;
                break;
            }else if(order < equal){
                nodeFind = nodeFind->right;
            }else{
                if((order < orderFirst) || (!orderFirst)){
                    nodeFirst = nodeFind;
                    orderFirst = order;
                }
                nodeFind = nodeFind->left;
            }
        }
        /* get the node between the region. */
        nodeFind = nodeFirst;
        order = cthis->rbOrder.rbOrder(nodeFind->block);
        while((equal <= order) && (order < less)){
            nodeSave[index++] = nodeFind;
            nodeFind = cthis->nodeNext(cthis, nodeFind);
            if(!nodeFind){
                break;
            }
            order = cthis->rbOrder.rbOrder(nodeFind->block);
        }
        *len = index;
    }while(0);
}

/* Function : RBTree_preOrder(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
void RBTree_preOrder(hRBTree cthis, hhtsRBNode nodes){
    hhtsRBNode nodeSave = nodes;
    htsRBNode nodeFind = OOPC_NULL;
    uint16 index = 0u;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        /* push stack. */
        cthis->Fifo.clearAll(cthis->Fifo.self);
        cthis->Fifo.push(cthis->Fifo.self,&cthis->root);
        /* find and push stack. */
        while(!cthis->Fifo.isEmpty(cthis->Fifo.self)){
            cthis->Fifo.pop(cthis->Fifo.self,&nodeFind);
            nodeSave[index++] = nodeFind;
            /* save right first and then save left. */
            if(nodeFind->right != OOPC_NULL){
                cthis->Fifo.push(cthis->Fifo.self,&nodeFind->right);
            }
            if(nodeFind->left != OOPC_NULL){
                cthis->Fifo.push(cthis->Fifo.self,&nodeFind->left);
            }
        }
        cthis->Fifo.clearAll(cthis->Fifo.self);
    }while(0);
}

/* Function : RBTree_midOrder(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
void RBTree_midOrder(hRBTree cthis, hhtsRBNode nodes){
    hhtsRBNode nodeSave = nodes;
    htsRBNode nodeFind = OOPC_NULL;
    uint16 index = 0u;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        nodeFind = cthis->root;
        /* find and push stack. */
        cthis->Fifo.clearAll(cthis->Fifo.self);
        while((!cthis->Fifo.isEmpty(cthis->Fifo.self)) || (nodeFind != OOPC_NULL)){
            /* first push left node, pop last, and then push right node. */
            if(nodeFind != OOPC_NULL){
                cthis->Fifo.push(cthis->Fifo.self,&nodeFind);
                nodeFind = nodeFind->left;
            }else{
                cthis->Fifo.pop(cthis->Fifo.self,&nodeFind);
                nodeSave[index++] = nodeFind;
                nodeFind = nodeFind->right;
            }
        }
        cthis->Fifo.clearAll(cthis->Fifo.self);
    }while(0);
}

/* Function : RBTree_postOrder(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
void RBTree_postOrder(hRBTree cthis, hhtsRBNode nodes){
    hhtsRBNode nodeSave = nodes;
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodePre = OOPC_NULL;
    uint16 index = 0u;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        /* push stack. */
        cthis->Fifo.clearAll(cthis->Fifo.self);
        cthis->Fifo.push(cthis->Fifo.self,&cthis->root);
        /* find and push stack. */
        while(!cthis->Fifo.isEmpty(cthis->Fifo.self)){
            cthis->Fifo.pop(cthis->Fifo.self,&nodeFind);
            /* if pop node is the leaf node, then pop it,
             * if previous pop node is find node left or right node, then pop it,
             * else push it in the stack again.
             */
            if(((nodeFind->left == OOPC_NULL) && (nodeFind->right == OOPC_NULL))
            ||((nodePre != OOPC_NULL) && (((nodePre == nodeFind->left) || (nodePre == nodeFind->right))))){
                nodeSave[index++] = nodeFind;
                nodePre = nodeFind;
            }else{
                cthis->Fifo.push(cthis->Fifo.self,&nodeFind);
                /* save right first and then save left. */
                if(nodeFind->right != OOPC_NULL){
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind->right);
                }
                if(nodeFind->left != OOPC_NULL){
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind->left);
                }
            }
        }
        cthis->Fifo.clearAll(cthis->Fifo.self);
    }while(0);
}

/* Function : RBTree_rbTreeOrder(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
void RBTree_rbTreeOrder(hRBTree cthis, hhtsRBNode nodes){
    hhtsRBNode nodeSave = nodes;
    htsRBNode nodeFind = OOPC_NULL;
    blockMType index = 0u;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        /* push stack. */
        cthis->Fifo.clearAll(cthis->Fifo.self);
        if((cthis->root->left != OOPC_NULL)
        && RED_BLACK_ISRED(cthis->root->left)){
            cthis->Fifo.push(cthis->Fifo.self,&cthis->root->left);
        }
        cthis->Fifo.push(cthis->Fifo.self,&cthis->root);
        /* find and push stack. */
        while(!cthis->Fifo.isEmpty(cthis->Fifo.self)){
            cthis->Fifo.fout(cthis->Fifo.self,&nodeFind);
            nodeSave[index++] = nodeFind;
            /* if output node is the leaf node, then stop push it's kids,
             * if not, save kids,
             * if left kid node has red left node, first save red node, then save left kid,
             * and go on output fifo.
             */
            if(RED_BLACK_HAVELEFT(nodeFind)
            &&(!RED_BLACK_ISRED(nodeFind->left))){
                if(RED_BLACK_HAVELEFT(nodeFind->left)
                && RED_BLACK_ISRED(nodeFind->left->left)){
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind->left->left);
                }
                cthis->Fifo.push(cthis->Fifo.self,&nodeFind->left);
            }
            if(RED_BLACK_HAVERIGHT(nodeFind)){
                if(RED_BLACK_HAVELEFT(nodeFind->right)
                && RED_BLACK_ISRED(nodeFind->right->left)){
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind->right->left);
                }
                cthis->Fifo.push(cthis->Fifo.self,&nodeFind->right);
            }
        }
        cthis->Fifo.clearAll(cthis->Fifo.self);
    }while(0);
}

/* Function : RBTree_sTreeOrder(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
void RBTree_sTreeOrder(hRBTree cthis, hhtsRBNode nodes, rbType *len){
    hhtsRBNode nodeSave = nodes;
    htsRBNode nodeFind = OOPC_NULL;
    rbType index = 0u, i = 0u;
    uint8 haveNodeFlag = FALSE;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        /* push stack. */
        cthis->Fifo.clearAll(cthis->Fifo.self);
        cthis->Fifo.push(cthis->Fifo.self,&cthis->root);
        haveNodeFlag = TRUE;
        /* find and push stack. */
        while((!cthis->Fifo.isEmpty(cthis->Fifo.self))
            &&(haveNodeFlag == TRUE)){
            haveNodeFlag = FALSE;
            i = cthis->Fifo.currCnt;
            while(i > 0u){
                i--;
                cthis->Fifo.fout(cthis->Fifo.self,&nodeFind);
                nodeSave[index++] = nodeFind;
                /* save left and right node, no matter whether it is null.
                 * if node is null, save kids null.
                 */
                if(nodeFind){
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind->left);
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind->right);
                    if(nodeFind->left||nodeFind->right){
                        haveNodeFlag = TRUE;
                    }
                }else{
                    nodeFind = OOPC_NULL;
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind);
                    cthis->Fifo.push(cthis->Fifo.self,&nodeFind);
                }
            }
        }
        cthis->Fifo.clearAll(cthis->Fifo.self);
        *len = index;
    }while(0);
}

/* Function : RBTree_mim(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
htsRBNode RBTree_min(hRBTree cthis){
    htsRBNode nodeRet = OOPC_NULL;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        /* left search the minimum. */
        nodeRet = cthis->root;
        while(nodeRet->left != OOPC_NULL){
            /* search left branch. */
            nodeRet = nodeRet->left;
        }
    }while(0);
    return nodeRet;
}

/* Function : RBTree_max(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
htsRBNode RBTree_max(hRBTree cthis){
    htsRBNode nodeRet = OOPC_NULL;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        /* left search the minimum. */
        nodeRet = cthis->root;
        while(nodeRet->right != OOPC_NULL){
            /* search right branch. */
            nodeRet = nodeRet->right;
        }
    }while(0);
    return nodeRet;
}

/* Function : RBTree_depth(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :
 * Others   : RBTree class function.
 **********************************************/
uint16 RBTree_depth(hRBTree cthis){
    uint16 depth = 0u;
    htsRBNode nodeFind = OOPC_NULL;
    do{
        /* abnormal dispose. */
        if(!cthis->root){
            break;
        }
        /* left search the minimum. */
        nodeFind = cthis->root;
        while(nodeFind != OOPC_NULL){
            if(!RED_BLACK_ISRED(nodeFind)){
                depth++;
            }
            /* search left branch. */
            nodeFind = nodeFind->left;
        }
    }while(0);
    return depth;
}

/* Function : hRBTree RBTree_init(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   : hRBTree - cthis/OOPC_NULL
 * Others   : RBTree class initial function.
 **********************************************/
hRBTree RBTree_init(hRBTree cthis, uint8 *rbSpace, uint32 blockMMax,
        rbType (*rbOrder)(void *block)){
    hRBTree retRes = cthis;

    do{
        /* specific failure detected */
        if(!(rbSpace&&rbOrder)){
            break;
        }
        /* Configure functions. */

        /* Configure parameters. */
        cthis->rbSpace = rbSpace;
        cthis->rbOrder.rbOrder = rbOrder;
        CN(BlockM, &cthis->BlockM,(cthis->rbSpace+RED_BLACK_STACK_SIZE),sizeof(tsRBNode),blockMMax);
        if(!OPRS(cthis->BlockM)){
            retRes = OOPC_NULL;
            break;
        }
        CN(Fifo, &cthis->Fifo,cthis->rbSpace,RED_BLACK_STACK_SIZE,sizeof(htsRBNode));
        if(!OPRS(cthis->Fifo)){
            retRes = OOPC_NULL;
            break;
        }
    }while(0);
    return retRes;
}

/* Function : hRBTree RBTree_ctor(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   : hRBTree - cthis/OOPC_NULL
 * Others   : RBTree class constructor.
 **********************************************/
CC(RBTree){
    hRBTree retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        cthis->init = RBTree_init;
        cthis->find = RBTree_find;
        cthis->add = RBTree_add;
        cthis->del = RBTree_del;
        cthis->lRotate = RBTree_lRotate;
        cthis->rRotate = RBTree_rRotate;
        cthis->llRedTrans = RBTree_llRedTrans;
        cthis->lrRedTrans = RBTree_lrRedTrans;
        cthis->rlRedTrans = RBTree_rlRedTrans;
        cthis->lRedRSubRedTrans = RBTree_lRedRSubRedTrans;
        cthis->predecessor = RBTree_predecessor;
        cthis->successor = RBTree_successor;
        cthis->nodeForward = RBTree_nodeForward;
        cthis->nodeNext = RBTree_nodeNext;
        cthis->getNode = RBTree_getNode;
        cthis->preOrder = RBTree_preOrder;
        cthis->midOrder = RBTree_midOrder;
        cthis->postOrder = RBTree_postOrder;
        cthis->rbTreeOrder = RBTree_rbTreeOrder;
        cthis->sTreeOrder = RBTree_sTreeOrder;
        cthis->min = RBTree_min;
        cthis->max = RBTree_max;
        cthis->depth = RBTree_depth;

        /* Configure parameters. */
        cthis->rbSpace = OOPC_NULL;
        cthis->root = OOPC_NULL;
    }while(0);
    return retRes;
}

/* Function : hRBTree RBTree_dtor(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : RBTree class destructor.
 **********************************************/
CD(RBTree){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
