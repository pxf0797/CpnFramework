/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : SkipList.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/10/10 21:46:26
 * Description  : SkipList class functions definition source file.
 * Others       : 
 * History      : 20211010 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "SkipList.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* TODO */

/***********************************************************
 * SkipList class definition.
 **********************************************************/
/* Function : SkipList_find(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   :  
 * Others   : SkipList class function.
 **********************************************/
htsSLNode SkipList_find(hSkipList cthis, slType order){
    htsSLNode slNodeRet = OOPC_NULL;
    htsSLNode slNode = OOPC_NULL;
    slType orderFind = 0u;
    slType low = 0u, mid = 0u, high = 0u;
    do{
        /* dispose abnormal. */
        if(cthis->arrayCnt == 0u){
            break;
        }

        /* bin search id index */
        low = 0u;
        high = (cthis->arrayCnt-1u);
        while(low <= high){
            /* Odd number, no matter even or odd, just have a value. */
            mid = ((low+high)>>1u);

            orderFind = cthis->blockOrder.blockOrder(cthis->slArray[mid].block);
            if(order == orderFind){
                slNodeRet = *(hhtsSLNode)&cthis->slArray[mid];
                break;
            }
            if(order < orderFind){
                if(mid == 0u){
                    break;
                }
                /* Is mid-1, because mid has been compared. */
                high = (mid-1u);

                orderFind = cthis->blockOrder.blockOrder(cthis->slArray[high].block);
                if(order >= orderFind){
                    /* find the region, judge the block. */
                    if(order == orderFind){
                        slNodeRet = *(hhtsSLNode)&cthis->slArray[high];
                        break;
                    }
                    slNode = *(hhtsSLNode)&cthis->slArray[high];
                    /* if next node exist, then judge. */
                    while(slNode->next && (slNode != *(hhtsSLNode)&cthis->slArray[mid])){
                        slNode = slNode->next;
                        orderFind = cthis->blockOrder.blockOrder(slNode->block);
                        if(order == orderFind){
                            slNodeRet = slNode;
                            break;
                        }
                    }
                    break;
                }
                continue;
            }
            /* if(order > orderFind) */
            /* Is mid+1, because mid has been compared. */
            low = (mid+1u);

            orderFind = cthis->blockOrder.blockOrder(cthis->slArray[low].block);
            if(order <= orderFind){
                /* find the region, judge the block. */
                if(order == orderFind){
                    slNodeRet = *(hhtsSLNode)&cthis->slArray[low];
                    break;
                }
                slNode = *(hhtsSLNode)&cthis->slArray[mid];
                /* if next node exist, then judge. */
                while(slNode->next && (slNode != *(hhtsSLNode)&cthis->slArray[low])){
                    slNode = slNode->next;
                    orderFind = cthis->blockOrder.blockOrder(slNode->block);
                    if(order == orderFind){
                        slNodeRet = slNode;
                        break;
                    }
                }
                break;
            }
            if(low >= (cthis->arrayCnt-1u)){
                /* find the last index, judge whether exist the order. */
                slNode = *(hhtsSLNode)&cthis->slArray[low];
                /* if next node exist, then judge. */
                while(slNode->next){
                    slNode = slNode->next;
                    orderFind = cthis->blockOrder.blockOrder(slNode->block);
                    if(order == orderFind){
                        slNodeRet = slNode;
                        break;
                    }
                }
                break;
            }
        }
    }while(0);
    return slNodeRet;
}

/* Function : SkipList_findSmallEqual(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   :  
 * Others   : SkipList class function.
 **********************************************/
uint16 SkipList_findSmallEqual(hSkipList cthis, slType order){
    uint16 slArrayIndex = cthis->arrayCnt;
    slType orderFind = 0u;
    slType low = 0u, mid = 0u, high = 0u;
    do{
        /* dispose abnormal. */
        if(cthis->arrayCnt == 0u){
            break;
        }

        /* bin search id index */
        low = 0u;
        high = (cthis->arrayCnt-1u);
        while(low <= high){
            /* Odd number, no matter even or odd, just have a value. */
            mid = ((low+high)>>1u);

            orderFind = cthis->blockOrder.blockOrder(cthis->slArray[mid].block);
            if(order == orderFind){
                /* find the equal index. */
                slArrayIndex = mid;
                break;
            }
            if(order < orderFind){
                if(mid == 0u){
                    /* there is no smaller one, so return 0 index. */
                    slArrayIndex = 0u;
                    break;
                }
                /* Is mid-1, because mid has been compared. */
                high = (mid-1u);

                orderFind = cthis->blockOrder.blockOrder(cthis->slArray[high].block);
                if(order >= orderFind){
                    /* find the smaller or equal index. */
                    slArrayIndex = high;
                    break;
                }
                continue;
            }
            /*if(order > orderFind)*/
            /* Is mid+1, because mid has been compared. */
            low = (mid+1u);

            orderFind = cthis->blockOrder.blockOrder(cthis->slArray[low].block);
            if(order <= orderFind){
                /* find the smaller index. */
                slArrayIndex = mid;
                break;
            }
            if(low >= (cthis->arrayCnt-1u)){
                /* find the last index, so return the last one. */
                slArrayIndex = low;
                break;
            }
        }
    }while(0);
    return slArrayIndex;
}

/* Function : SkipList_add(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   :  
 * Others   : SkipList class function.
 **********************************************/
uint8 SkipList_add(hSkipList cthis, void *block){
    htsSLNode slNode = OOPC_NULL;
    htsSLNode slNodeFind = OOPC_NULL;
    htsSLNode slNodeNext = OOPC_NULL;
    slType order = 0u;
    slType orderFind = 0u;
    uint16 slArrayIndex = cthis->arrayCnt;
    uint16 biggerDispose = 0u;
    uint8 opRes = TRUE;

    order = cthis->blockOrder.blockOrder(block);
    slArrayIndex = cthis->findSmallEqual(cthis,order);
    do{
        /* abnormal dispose. */
        /*if(slArrayIndex >= cthis->arrayCnt){
            break;
        }*/
        /* create node. */
        slNode = cthis->BlockM.malloc(cthis->BlockM.self,sizeof(tsSLNode));
        slNode->block = block;
        /* (cthis->arrayCnt == 0u) dispose. */
        if(cthis->arrayCnt == 0u){
            /* insert the node in the list, and update skip list array. */
            slNode->next = cthis->slHead;
            cthis->slHead = slNode;
            *(hhtsSLNode)&cthis->slArray[0] = slNode;
            cthis->arrayCnt = 1u;
            break;
        }
        do{
            /* (cthis->arrayCnt == 1u) dispose. */
            if(cthis->arrayCnt == 1u){
                orderFind = cthis->blockOrder.blockOrder(cthis->slArray[0].block);
                /* It is not processed if it is considered equal */
                if(order == orderFind){
                    cthis->BlockM.free(cthis->BlockM.self,slNode);
                    opRes = FALSE;
                    break;
                }
                if(order < orderFind){
                    /* insert the node in the begin of the list, and update skip list array.
                     */
                    slNode->next = cthis->slHead;
                    cthis->slHead = slNode;
                    *(hhtsSLNode)&cthis->slArray[0] = slNode;
                    /* update index. */
                    cthis->dynUpdate(cthis,0u);
                    break;
                }
                /* if(order > orderFind) */
                /* goto bigger dispose */
                slNodeFind = *(hhtsSLNode)&cthis->slArray[0];
                slNodeNext = OOPC_NULL;
                biggerDispose = 1u;
                break;
            }
            /* last index dispose. (cthis->arrayCnt >= 2u) */
            if(slArrayIndex == (cthis->arrayCnt-1u)){
                orderFind = cthis->blockOrder.blockOrder(cthis->slArray[slArrayIndex].block);
                /* It is not processed if it is considered equal or less. */
                if(order <= orderFind){
                    cthis->BlockM.free(cthis->BlockM.self,slNode);
                    opRes = FALSE;
                    break;
                }
                /* if(order > orderFind) */
                /* goto bigger dispose */
                slNodeFind = *(hhtsSLNode)&cthis->slArray[slArrayIndex];
                slNodeNext = OOPC_NULL;
                biggerDispose = 1u;
                break;
            }
            /* other slArrayIndex dispose. */
            {
                orderFind = cthis->blockOrder.blockOrder(cthis->slArray[slArrayIndex].block);
                /* It is not processed if it is considered equal or less. */
                if(order <= orderFind){
                    cthis->BlockM.free(cthis->BlockM.self,slNode);
                    opRes = FALSE;
                    break;
                }
                /* if(order > orderFind) */
                /* goto bigger dispose */
                /* insert the node in the list between next array node. */
                slNodeFind = *(hhtsSLNode)&cthis->slArray[slArrayIndex];
                slNodeNext = *(hhtsSLNode)&cthis->slArray[slArrayIndex+1u];
                biggerDispose = 1u;
                break;
            }
        }while(0);
        /* if not bigger dispose, directly return. */
        if(!biggerDispose){
            break;
        }
        /* bigger dispose */
        while(slNodeFind->next != slNodeNext){
            /* judge next node, whether it is bigger than current insert one. */
            orderFind = cthis->blockOrder.blockOrder(slNodeFind->next->block);
            if(order <= orderFind){
                /* It is not processed if it is considered equal */
                if(order == orderFind){
                    cthis->BlockM.free(cthis->BlockM.self,slNode);
                    opRes = FALSE;
                    break;
                }
                /* insert node after find node. */
                slNode->next = slNodeFind->next;
                slNodeFind->next = slNode;
                /* update index. */
                cthis->dynUpdate(cthis,slArrayIndex);
                break;
            }
            slNodeFind = slNodeFind->next;
        }
        /* if not found, insert node in the end. */
        if(slNodeFind == OOPC_NULL){
            slNode->next = slNodeFind->next;
            slNodeFind->next = slNode;
            /* update index. */
            cthis->dynUpdate(cthis,slArrayIndex);
        }else if(slNodeFind == slNodeNext){
            /* slNodeFind equal to slNodeNext, but slNodeNext not equal to OOPC_NULL */
            cthis->BlockM.free(cthis->BlockM.self,slNode);
            opRes = FALSE;
            break;
        }else{}
    }while(0);
    return opRes;
}

/* Function : SkipList_del(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   :  
 * Others   : SkipList class function.
 **********************************************/
uint8 SkipList_del(hSkipList cthis, slType order){
    htsSLNode slNode = OOPC_NULL;
    htsSLNode slNodeFind = OOPC_NULL;
    htsSLNode slNodeNext = OOPC_NULL;
    slType orderFind = 0u;
    uint16 slArrayIndex = cthis->arrayCnt;
    uint16 biggerDispose = 0u;
    uint8 opRes = TRUE;

    slArrayIndex = cthis->findSmallEqual(cthis,order);
    do{
        /* abnormal dispose. */
        /*if(slArrayIndex >= cthis->arrayCnt){
            break;
        }*/
        /* (cthis->arrayCnt == 0u) dispose. */
        if(cthis->arrayCnt == 0u){
            /* there is no node. */
            opRes = FALSE;
            break;
        }
        do{
            /* (cthis->arrayCnt == 1u) dispose. */
            if(cthis->arrayCnt == 1u){
                orderFind = cthis->blockOrder.blockOrder(cthis->slArray[0].block);
                /* node found, delete. */
                if(order == orderFind){
                    slNode = *(hhtsSLNode)&cthis->slArray[0];
                    cthis->slHead = cthis->slArray[0].next;
                    *(hhtsSLNode)&cthis->slArray[0] = cthis->slHead;
                    cthis->BlockM.free(cthis->BlockM.self,slNode);
                    /* if there is no node, clear counter. */
                    if(*(hhtsSLNode)&cthis->slArray[0] == OOPC_NULL){
                        cthis->arrayCnt = 0u;
                    }
                    break;
                }
                if(order < orderFind){
                    /* node does not in skip list. directly return. */
                    opRes = FALSE;
                    break;
                }
                /* if(order > orderFind) */
                /* goto bigger dispose */
                slNodeFind = *(hhtsSLNode)&cthis->slArray[0];
                slNodeNext = OOPC_NULL;
                biggerDispose = 1u;
                break;
            }
            orderFind = cthis->blockOrder.blockOrder(cthis->slArray[slArrayIndex].block);
            /* equal, delete the node and free the memory. AND set the cthis->slArray[slArrayIndex] to next node. */
            /* if(cthis->arrayCnt >= 2u) */
            if(order == orderFind){
                slNode = *(hhtsSLNode)&cthis->slArray[slArrayIndex];
                if(slArrayIndex == 0u){
                    /* update head. */
                    cthis->slHead = slNode->next;
                }else{
                    /* update previous node. */
                    /* find previous node. */
                    slNodeFind = *(hhtsSLNode)&cthis->slArray[slArrayIndex-1u];
                    while(slNodeFind->next != slNode){
                        slNodeFind = slNodeFind->next;
                    }
                    slNodeFind->next = slNode->next;
                }
                *(hhtsSLNode)&cthis->slArray[slArrayIndex] = slNode->next;
                cthis->BlockM.free(cthis->BlockM.self,slNode);
                /* update index. */
                cthis->dynUpdate(cthis,slArrayIndex);
                break;
            }
            /* It is not processed if it is considered equal or less. */
            if(order < orderFind){
                opRes = FALSE;
                break;
            }
            /* if(order > orderFind) */
            /* bigger dispose */
            slNodeFind = *(hhtsSLNode)&cthis->slArray[slArrayIndex];
            if(slArrayIndex == (cthis->arrayCnt-1u)){
                /* last index dispose. (cthis->arrayCnt >= 2u) */
                slNodeNext = OOPC_NULL;
            }else{
                /* other slArrayIndex dispose. */
                slNodeNext = *(hhtsSLNode)&cthis->slArray[slArrayIndex+1u];
            }
            biggerDispose = 1u;
            break;
        }while(0);
        /* if not bigger dispose, directly return. */
        if(!biggerDispose){
            break;
        }
        while(slNodeFind->next != slNodeNext){
            /* judge next node, whether it is bigger than current node. */
            orderFind = cthis->blockOrder.blockOrder(slNodeFind->next->block);
            if(order <= orderFind){
                /* node found, delete. */
                if(order == orderFind){
                    slNode = slNodeFind->next;
                    slNodeFind->next = slNode->next;
                    cthis->BlockM.free(cthis->BlockM.self,slNode);
                    /* update index. */
                    cthis->dynUpdate(cthis,slArrayIndex);
                    break;
                }
                /* node does not in skip list. directly return. */
                opRes = FALSE;
                break;
            }
            slNodeFind = slNodeFind->next;
        }
        /* if not found, directly return. */
        if(slNodeFind == OOPC_NULL){
            opRes = FALSE;
        }else if(slNodeFind == slNodeNext){
            /* slNodeFind equal to slNodeNext, but slNodeNext not equal to OOPC_NULL */
            opRes = FALSE;
        }else{}
    }while(0);
    return opRes;
}

/* Function : SkipList_dynUpdate(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   :  
 * Others   : SkipList class function.
 **********************************************/
void SkipList_dynUpdate(hSkipList cthis, uint16 arrayIndex){
    htsSLNode slNodeFind = OOPC_NULL;
    uint16 i = 0u, j = 0u;
    do{
        /* dispose abnormal. */
        if(arrayIndex >= cthis->arrayCnt){
            break;
        }
        if(cthis->arrayCnt == 0u){
            break;
        }
        do{
            /* (arrayIndex == (cthis->arrayCnt-2u)) dispose. it has include (cthis->arrayCnt == 2u) */
            if((cthis->arrayCnt >= 2u)
            &&(arrayIndex == (cthis->arrayCnt-2u))){
                cthis->arrayCnt--;
                /* find the same as cthis->slArray[arrayIndex], and clear it. */
                while((arrayIndex > 0u)
                &&(*(hhtsSLNode)&cthis->slArray[arrayIndex] == *(hhtsSLNode)&cthis->slArray[arrayIndex-1u])){
                    arrayIndex--;
                    cthis->arrayCnt--;
                }
                /* goto (arrayIndex == (cthis->arrayCnt-1u)) dispose. */
                break;
            }
            /* (arrayIndex < (cthis->arrayCnt-2u)) dispose. */
            if((cthis->arrayCnt > 2u)
            &&(arrayIndex < (cthis->arrayCnt-2u))){
                /* cthis->slArray restrict only behind index can be same.
                 * so, you can only judge the value behind index.
                 * when the index pointer are the same, or is the next one, count it.
                 */
                i = 0u;
                while(((arrayIndex+1u+i) < cthis->arrayCnt)
                &&((*(hhtsSLNode)&cthis->slArray[arrayIndex+i] == *(hhtsSLNode)&cthis->slArray[arrayIndex+1u+i])
                    ||(cthis->slArray[arrayIndex+i].next == *(hhtsSLNode)&cthis->slArray[arrayIndex+1u+i]))){
                    i++;
                }
                /* tight value to the end. */
                if((arrayIndex+(i<<1)) >= cthis->arrayCnt){
                    cthis->arrayCnt = (arrayIndex+1u);
                    /* goto (arrayIndex == (cthis->arrayCnt-1u)) dispose. */
                    break;
                }
                if(i == 0u){
                    /* adjust cthis->slArray[arrayIndex] and cthis->slArray[arrayIndex+1u] */
                    if(arrayIndex == 0u){
                        slNodeFind = *(hhtsSLNode)&cthis->slArray[0];
                    }else{
                        slNodeFind = *(hhtsSLNode)&cthis->slArray[arrayIndex];
                    }
                    *(hhtsSLNode)&cthis->slArray[arrayIndex+1u] = slNodeFind;
                    i = 0u;
                    while(slNodeFind->next != *(hhtsSLNode)&cthis->slArray[arrayIndex+2u]){
                        if(!(i&1u)){
                            /* cthis->slArray[arrayIndex+1u] save the node of shift i>>1. */
                            *(hhtsSLNode)&cthis->slArray[arrayIndex+1u] = cthis->slArray[arrayIndex+1u].next;
                            if(!(i&3u)){
                                /* cthis->slArray[arrayIndex] save the node of shift i>>2. */
                                if(arrayIndex != 0u){
                                    /* arrayIndex equal 0, do not move. */
                                    *(hhtsSLNode)&cthis->slArray[arrayIndex] = cthis->slArray[arrayIndex].next;
                                }
                            }
                        }
                        i++;
                        slNodeFind = slNodeFind->next;
                    }
                    /* adjust has finished, directly return. */
                    return;
                }
                /* adjust range between cthis->slArray[arrayIndex] and cthis->slArray[arrayIndex+(i<<1)] */
                j = 0u;
                while(j < (i<<1)){
                    j = 0u;
                    /* each array save one node, last one save surplus. */
                    while((j < (i<<1))
                    &&(cthis->slArray[arrayIndex+j].next != *(hhtsSLNode)&cthis->slArray[arrayIndex+(i<<1)])){
                        *(hhtsSLNode)&cthis->slArray[arrayIndex+j+1u] = cthis->slArray[arrayIndex+j].next;
                        j++;
                    }
                    /* every array has save the node, directly return. */
                    if(j >= (i<<1)){
                        return;
                    }
                    /* residue array counts. */
                    i = ((i<<1) - j);
                    /* last has saved node arrayIndex. */
                    arrayIndex = arrayIndex+j;
                    if((arrayIndex+(i<<1)) >= cthis->arrayCnt){
                        cthis->arrayCnt = (arrayIndex+1u);
                        /* goto (arrayIndex == (cthis->arrayCnt-1u)) dispose. */
                        break;
                    }
                }
            }
        }while(0);
        /* (arrayIndex == (cthis->arrayCnt-1u)) or (cthis->arrayCnt == 1u) dispose. */
        slNodeFind = *(hhtsSLNode)&cthis->slArray[cthis->arrayCnt-1u];
        if((arrayIndex == (cthis->arrayCnt-1u))
        ||(cthis->arrayCnt == 1u)){
            i = 0u;
            while(slNodeFind->next != OOPC_NULL){
                /* cthis->slArray save every 2 node. */
                if(!(i&1u)){
                    *(hhtsSLNode)&cthis->slArray[cthis->arrayCnt] = slNodeFind;
                    cthis->arrayCnt++;
                    /* if array counter up to maximum, then get off. */
                    if(cthis->arrayCnt >= cthis->slBuffMaxNum){
                        break;
                    }
                }
                i++;
                slNodeFind = slNodeFind->next;
            }
            break;
        }
    }while(0);
}

/* Function : hSkipList SkipList_init(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   : hSkipList - cthis/OOPC_NULL
 * Others   : SkipList class initial function.
 **********************************************/
hSkipList SkipList_init(hSkipList cthis, uint16 slBuffMaxNum, uint8 *space){
    hSkipList retRes = cthis;

    do{
        /* specific failure detected */
        if(!(slBuffMaxNum&&space)){
            retRes = OOPC_NULL;
            break;
        }
        /* Configure functions. */

        /* Configure parameters. */
        cthis->slBuffMaxNum = slBuffMaxNum;
        cthis->slArray = (htsSLNode)space;
        cthis->slSpace = (uint8*)(cthis->slArray+(sizeof(htsSLNode)*cthis->slBuffMaxNum));
        CN(BlockM, &cthis->BlockM,cthis->slSpace,sizeof(tsSLNode),cthis->slBuffMaxNum);
        if(!OPRS(cthis->BlockM)){
            retRes = OOPC_NULL;
            break;
        }
    }while(0);
    return retRes;
}

/* Function : hSkipList SkipList_ctor(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   : hSkipList - cthis/OOPC_NULL
 * Others   : SkipList class constructor.
 **********************************************/
CC(SkipList){
    hSkipList retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        cthis->init = SkipList_init;
        cthis->find = SkipList_find;
        cthis->findSmallEqual = SkipList_findSmallEqual;
        cthis->add = SkipList_add;
        cthis->del = SkipList_del;
        cthis->dynUpdate = SkipList_dynUpdate;

        /* Configure parameters. */
        cthis->slBuffMaxNum = 0u;
        cthis->arrayCnt = 0u;
        cthis->slArray = OOPC_NULL;
        cthis->slSpace = OOPC_NULL;
        cthis->slHead = OOPC_NULL;
    }while(0);
    return retRes;
}

/* Function : hSkipList SkipList_dtor(hSkipList cthis)
 * Input    : cthis - SkipList class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : SkipList class destructor.
 **********************************************/
CD(SkipList){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
