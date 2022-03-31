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
uint16 RBTree_add(hRBTree cthis, void *block){
    uint16 opRes = TRUE;
    htsRBNode node = OOPC_NULL;
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeFather = OOPC_NULL;
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
                break;
            }
            /* search left branch. */
            if(order < orderFind){
                if(nodeFind->left == OOPC_NULL){
                    /* find the predecessor node. and set the node next to it. */
                    nodeFind->left = node;
                    RED_BLACK_SETFATHER(node,nodeFind->left);
                    adjust = node_predecessor;
                    break;
                }
                continue;
            }
            /* search right branch. */
            if(nodeFind->right != OOPC_NULL){
                /* find the successor node. and set the node next to it. */
                nodeFind->right = node;
                RED_BLACK_SETFATHER(node,nodeFind->right);
                adjust = node_successor;
                break;
            }
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
            if(RED_BLACK_HAVELEFT(nodeFind)){
                /* if find node has left, it must be red. */
                /* change new node and left color to black. set find node color red. */
                RED_BLACK_SETRED(nodeFind);
                RED_BLACK_CLEARRED(node);
                RED_BLACK_CLEARRED(nodeFind->left);

                /* have not father node. */
                if(!RED_BLACK_HAVEFATHER(nodeFind)){
                    /* if have not father node, set find node black too. and return. */
                    RED_BLACK_CLEARRED(nodeFind);
                    adjust = node_none;
                    break;
                }
                /* have father node. */
                if(RED_BLACK_ISLEFT(nodeFind)){
                    /* if the node is left node. directly return, there is no need operate next. */
                    adjust = node_none;
                    break;
                }
                /* find node is right node, left rotate father node. */
                /* judge father's father node whether is red. */
                nodeFather = RED_BLACK_HNODE(nodeFind->father);
                if(!RED_BLACK_ISRED(nodeFather)){
                    /* if it is not red. left rotate and change color. */
                    cthis->lRotate(cthis,nodeFather);
                    /* change find node color black. and left red. and return. */
                    RED_BLACK_CLEARRED(nodeFind);
                    RED_BLACK_SETRED(nodeFind->left);
                    break;
                }
                /* father's father is red, goto father node is red situation dispose. */
                node = nodeFind;
                nodeFind = RED_BLACK_HNODE(nodeFind->father);
                adjust = node_successor;
            }
        }
        /* situation 2. */
        /* father node is red. */
        /* if find node_predecessor node. */
        /* situation 2.1. */
        if(adjust == node_predecessor){
            /* because find node is red, you should right rotate find node's father node.
             * change new node's color to black.
             * and then goto adjust find node with it's new father.
             */
            cthis->rRotate(cthis,RED_BLACK_HNODE(nodeFind->father));
            RED_BLACK_CLEARRED(node);
            /* have not father node. */
            if(!RED_BLACK_HAVEFATHER(nodeFind)){
                /* if have not father node, set find node black too. and return. */
                RED_BLACK_CLEARRED(nodeFind);
                adjust = node_none;
                break;
            }
            /* have father node. */
            node = nodeFind;
            nodeFind = RED_BLACK_HNODE(nodeFind->father);
            if(RED_BLACK_ISLEFT(nodeFind)){
                /* if the node is left node. goto perform the flow of execution again. */
                adjust = node_predecessor;
            }else{
                adjust = node_predecessor;
            }
            continue;
        }
        /* if find node_successor node. */
        /* if(adjust == node_successor) */
        /* situation 2.2. */
        /* left rotate find node, and the situation is the same as situation 2.1 */
        cthis->lRotate(cthis,nodeFind);
        node = nodeFind;
        nodeFind = RED_BLACK_HNODE(nodeFind->father);
        adjust = node_predecessor;
        /* goto situation 2.1 dispose. */
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
uint16 RBTree_del(hRBTree cthis, rbType order){
    uint16 opRes = TRUE;
    htsRBNode node = OOPC_NULL;
    htsRBNode nodeFind = OOPC_NULL;
    htsRBNode nodeFather = OOPC_NULL;
    rbType orderFind = 0u;
    teFindNodeType adjust = node_none;

    node = cthis->find(cthis,order);
    do{
        /* abnormal dispose. */
        if(node == OOPC_NULL){
            opRes = FALSE;
            break;
        }
        /* if node is red leaf, directly delete. */
        if(RED_BLACK_ISRED(node)&&(!RED_BLACK_HAVELEFT(node))){
            nodeFind = RED_BLACK_HNODE(node->father);
            RED_BLACK_CLEARLEFT(nodeFind);
            cthis->BlockM.free(cthis->BlockM.self,node);
            break;
        }
        /* if the successor is red, it has no kids. if it has two black kids, it is not successor.
         * if the successor is black, it has no kids. if left is red, it is not successor.
         */
        nodeFind = cthis->successor(cthis,node);
        /* directly use successor replace delete node. */
        node->block = nodeFind->block;
        node = nodeFind;
        /* successor is red node. */
        if(RED_BLACK_ISRED(nodeFind)){
            /* there is no need to adjust the nodes. */
            nodeFind = RED_BLACK_HNODE(nodeFind->father);
            RED_BLACK_CLEARLEFT(nodeFind);
            cthis->BlockM.free(cthis->BlockM.self,node);
            break;
        }
        /* successor is black node. */

    }while(0);
    return opRes;
}

/* Function : RBTree_lRotate(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :  
 * Others   : RBTree class function.
 **********************************************/
void RBTree_lRotate(hRBTree cthis, htsRBNode node){
    htsRBNode nodeFind = OOPC_NULL;
    do{
        /* dispose abnormal. */
        nodeFind = node->right;
        /* if right is null, there is no way to rotate. */
        if(nodeFind == OOPC_NULL){
            break;
        }
        /*nodeFind->father = node->father;*/ /* pointer to root, the node color should keep as previous. */
//        nodeFind->father &= RED_BLACK_COLOR_MASK;
//        nodeFind->father |= RED_BLACK_HNODE(node->father);
        RED_BLACK_ADDR_VALUE(nodeFind->father) &= RED_BLACK_COLOR_MASK;
        RED_BLACK_ADDR_VALUE(nodeFind->father) |= RED_BLACK_HNODE(node->father);
        /*node->father = nodeFind;*/         /* change previous father node to father node left. */
        RED_BLACK_ADDR_VALUE(node->father) &= RED_BLACK_COLOR_MASK;
        RED_BLACK_ADDR_VALUE(node->father) |= RED_BLACK_HNODE(nodeFind);
        node->right = nodeFind->left;        /* change father left node to previous father node right. */
        nodeFind->left = node;               /* change current left node to previous node. */
    }while(0);
}

/* Function : RBTree_rRotate(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   :  
 * Others   : RBTree class function.
 **********************************************/
void RBTree_rRotate(hRBTree cthis, htsRBNode node){
    htsRBNode nodeFind = OOPC_NULL;
    do{
        /* dispose abnormal. */
        nodeFind = node->left;
        /* if left is null, there is no way to rotate. */
        if(nodeFind == OOPC_NULL){
            break;
        }
        /*nodeFind->father = node->father;*/ /* pointer to root, the node color should keep as previous. */
        RED_BLACK_ADDR_VALUE(nodeFind->father) &= RED_BLACK_COLOR_MASK;
        RED_BLACK_ADDR_VALUE(nodeFind->father) |= RED_BLACK_HNODE(node->father);
        /*node->father = nodeFind;*/         /* change previous father node to father node right. */
        RED_BLACK_ADDR_VALUE(node->father) &= RED_BLACK_COLOR_MASK;
        RED_BLACK_ADDR_VALUE(node->father) |= RED_BLACK_HNODE(nodeFind);
        node->left = nodeFind->right;        /* change father right node to previous father node left. */
        nodeFind->right = node;              /* change current left node to previous node. */
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
        cthis->Fifo.push(cthis->Fifo.self,cthis->root);
        /* find and push stack. */
        while(!cthis->Fifo.isEmpty(cthis->Fifo.self)){
            cthis->Fifo.pop(cthis->Fifo.self,&nodeFind);
            nodeSave[index++] = nodeFind;
            /* save right first and then save left. */
            if(nodeFind->right != OOPC_NULL){
                cthis->Fifo.push(cthis->Fifo.self,nodeFind->right);
            }
            if(nodeFind->left != OOPC_NULL){
                cthis->Fifo.push(cthis->Fifo.self,nodeFind->left);
            }
        }
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
        cthis->Fifo.push(cthis->Fifo.self,cthis->root);
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
                cthis->Fifo.push(cthis->Fifo.self,nodeFind);
                /* save right first and then save left. */
                if(nodeFind->right != OOPC_NULL){
                    cthis->Fifo.push(cthis->Fifo.self,nodeFind->right);
                }
                if(nodeFind->left != OOPC_NULL){
                    cthis->Fifo.push(cthis->Fifo.self,nodeFind->left);
                }
            }
        }
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

/* Function : hRBTree RBTree_init(hRBTree cthis)
 * Input    : cthis - RBTree class pointer
 * Output   : hRBTree - cthis/OOPC_NULL
 * Others   : RBTree class initial function.
 **********************************************/
hRBTree RBTree_init(hRBTree cthis){
    hRBTree retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        /* Configure functions. */
        //cthis->find = RBTree_find;
        /* TODO */

        /* Configure parameters. */
        /* TODO */
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
        cthis->predecessor = RBTree_predecessor;
        cthis->successor = RBTree_successor;
        cthis->preOrder = RBTree_preOrder;
        cthis->midOrder = RBTree_midOrder;
        cthis->postOrder = RBTree_postOrder;
        cthis->min = RBTree_min;
        cthis->max = RBTree_max;

        /* Configure parameters. */
        /* TODO */
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
