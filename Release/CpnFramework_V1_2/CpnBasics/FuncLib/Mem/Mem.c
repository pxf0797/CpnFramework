/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : Mem.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/12/05 13:45:23
* Description  : Mem类各功能函数定义源文件
* Others       :
* History      : 201205 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./Mem.h"
#include "../Func/Func.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO

/***********************************************************
* Mem类定义
***********************************************************/
/*名称 : Mem_new(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void* Mem_malloc(hMem cthis, uint16 size){
    uint16 uwUnusedIndex = 0U;
    uint16 uwFindIndex = 0U;
    uint16 uwNewMemBlockIndex = 0U;
    uint8 *memNewPointer = OOPC_NULL;
    uint16 uwNewMemSize = 0U;

    uwUnusedIndex = cthis->findUnusedBigerIndex(cthis, size);
    if(size&&(uwUnusedIndex < cthis->memUnusedNum)){
        uwFindIndex = cthis->unusedBlockIndex[uwUnusedIndex].memIndex;
        cthis->delUnusedIndexDirect(cthis,uwUnusedIndex); /* 删除未使用记录 */
        uwNewMemSize = (uint16)(cthis->memBlock[uwFindIndex].memSize-size);
        if(uwNewMemSize){
            /* 更新memBlock新增一个块 */
            uwNewMemBlockIndex = cthis->findBlockMaskMinIndex(cthis);
            if(uwNewMemBlockIndex < MEMCFG_MEM_BLOCK_MAX_NUM){
                //uwFindIndex = cthis->unusedBlockIndex[uwUnusedIndex].memIndex;
                cthis->memBlock[uwNewMemBlockIndex].memPointer = (void*)((cthis->memBlock[uwFindIndex].memPointer) + size);
                cthis->memBlock[uwNewMemBlockIndex].memSize = uwNewMemSize;
                cthis->memBlock[uwNewMemBlockIndex].useStatus = mem_unused;
                cthis->memBlock[uwNewMemBlockIndex].priorIndex = uwFindIndex;
                cthis->memBlock[uwNewMemBlockIndex].nextIndex = cthis->memBlock[uwFindIndex].nextIndex;
                cthis->setBlockMaskIndex(cthis, uwNewMemBlockIndex); /* 占用块使用 */
            }else{
                cthis->addUnusedIndex(cthis,uwFindIndex); /* 新增未使用记录 */
                return memNewPointer;
            }
        }
        /* 旧块更新为使用并调整大小 */
        //cthis->memBlock[uwFindIndex].memPointer;
        cthis->memBlock[uwFindIndex].useStatus = mem_used;
        //cthis->memBlock[uwFindIndex].priorIndex;
        if(uwNewMemSize){
            cthis->memBlock[uwFindIndex].memSize = size;
            cthis->memBlock[uwFindIndex].nextIndex = uwNewMemBlockIndex;
            cthis->addUnusedIndex(cthis,uwNewMemBlockIndex); /* 新增未使用记录 */
        }
        cthis->addUsedIndex(cthis,uwFindIndex); /* 使用记录更新 */
        memNewPointer = cthis->memBlock[uwFindIndex].memPointer;  /* 给出指针 */
    }

    return (void*)memNewPointer;
}

/*名称 : Mem_delete(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
uint16 Mem_free(hMem cthis, void *pointer){
    uint16 uwUsedIndex = 0U;
    uint16 uwFindIndex = 0U;
    uint16 uwOpRes = OOPC_TRUE;

    uwUsedIndex = cthis->findUsedIndex(cthis, pointer);
    if(uwUsedIndex < cthis->memNewNum){
        uwFindIndex = cthis->usedBlockIndex[uwUsedIndex].memIndex;
        /* 旧块更新为未使用 */
        //cthis->memBlock[uwFindIndex].memPointer;
        //cthis->memBlock[uwFindIndex].memSize;
        cthis->memBlock[uwFindIndex].useStatus = mem_unused;
        //cthis->memBlock[uwFindIndex].priorIndex;
        //cthis->memBlock[uwFindIndex].nextIndex;
        cthis->delUsedIndex(cthis,uwFindIndex); /* 使用索引更新 */
        cthis->addUnusedIndex(cthis,uwFindIndex); /* 未使用索引添加新块 */
        /* 释放内存合并 */
        /* 左合并 */
        if(uwFindIndex){
            if(cthis->memBlock[cthis->memBlock[uwFindIndex].priorIndex].useStatus == mem_unused){
                cthis->delUnusedIndex(cthis,cthis->memBlock[uwFindIndex].priorIndex); /* 删除旧块 */
                cthis->delUnusedIndex(cthis,uwFindIndex);
                cthis->mergeMemBlock(cthis, uwFindIndex);
                cthis->addUnusedIndex(cthis,cthis->memBlock[uwFindIndex].priorIndex); /* 添加未使用新块 */
                uwFindIndex = cthis->memBlock[uwFindIndex].priorIndex; /* 完成左合并后进行右合并 */
            }
        }
        /* 右合并 */
        if(cthis->memBlock[uwFindIndex].nextIndex){
            if(cthis->memBlock[cthis->memBlock[uwFindIndex].nextIndex].useStatus == mem_unused){
                cthis->delUnusedIndex(cthis,cthis->memBlock[uwFindIndex].nextIndex); /* 删除旧块 */
                cthis->delUnusedIndex(cthis,uwFindIndex);
                cthis->mergeMemBlock(cthis, cthis->memBlock[uwFindIndex].nextIndex);
                cthis->addUnusedIndex(cthis,uwFindIndex); /* 添加未使用新块 */
            }
        }
    }else{
        uwOpRes = OOPC_FALSE;
    }

    return uwOpRes;
}

/*名称 : Mem_findUnusedIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
uint16 Mem_findUnusedIndex(hMem cthis, uint32 size, uint16 index){
    /* bin search id index */
    uint16 low = 0U, mid = 0U, high = 0U;
    uint16 uwIndex = MEMCFG_MEM_UNUSED_MAX_NUM;

    if(cthis->memUnusedNum){
        /* 请求大于预留最大值情况下，直接返回未使用个数（即找不到对应索引） */
        high = cthis->memUnusedNum-1U;
        while(low <= high){
            mid = ((low+high)>>1U);    /* 奇数，无论奇偶，有个值就行 */
            if(size < cthis->unusedBlockIndex[mid].memSize){
                if(mid == 0U){         /* 找到第0个值才还没有更小值 */
                    break;
                }
                high = (mid-1U);       /* 是mid-1，因为mid已经比较过了 */
            }else if(size > cthis->unusedBlockIndex[mid].memSize){
                low = (mid+1U);
            }else{
                uwIndex = mid;
                break;
            }
        }

        do{
            /* 左查找 */
            if(cthis->unusedBlockIndex[uwIndex].memIndex != index){
                while((uwIndex > 0U) && (size == cthis->unusedBlockIndex[uwIndex].memSize)){
                    uwIndex--;
                    if(cthis->unusedBlockIndex[uwIndex].memIndex == index){
                        break;
                    }
                }
            }
            /* 右查找 */
            if(cthis->unusedBlockIndex[uwIndex].memIndex != index){
                uwIndex = mid;
                while((uwIndex < (cthis->memUnusedNum-1U)) && (size == cthis->unusedBlockIndex[uwIndex].memSize)){
                    uwIndex++;
                    if(cthis->unusedBlockIndex[uwIndex].memIndex == index){
                        break;
                    }
                }
            }
            if(cthis->unusedBlockIndex[uwIndex].memIndex != index){
                uwIndex = MEMCFG_MEM_UNUSED_MAX_NUM;
            }
        }while(0);
    }

    return uwIndex;
}

/*名称 : Mem_findUnusedBigerIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
uint16 Mem_findUnusedBigerIndex(hMem cthis, uint32 size){
    /* bin search id index */
    uint16 low = 0U, mid = 0U, high = 0U;
    uint16 uwIndex = MEMCFG_MEM_UNUSED_MAX_NUM;

    if(cthis->memUnusedNum){
        /* 请求大于预留最大值情况下，直接返回未使用个数（即找不到对应索引） */
        high = cthis->memUnusedNum-1U;
        if(size <= cthis->unusedBlockIndex[high].memSize){
            while(low <= high){
                mid = ((low+high)>>1U);    /* 奇数，无论奇偶，有个值就行 */
                if(size <= cthis->unusedBlockIndex[mid].memSize){
                    if(mid == 0U){         /* 找到第0个值才还没有更小值 */
                        uwIndex = 0U;
                        break;
                    }
                    high = (mid-1U);       /* 是mid-1，因为mid已经比较过了 */
                    if(size > cthis->unusedBlockIndex[high].memSize){
                        uwIndex = mid;
                        break;
                    }
                }else{
                    low = (mid+1U);
                    if(size <= cthis->unusedBlockIndex[low].memSize){
                        uwIndex = low;
                        break;
                    }
                }
            }
        }
    }

    return uwIndex;
}

/*名称 : Mem_findUsedIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
uint16 Mem_findUsedIndex(hMem cthis, void *pointer){
    /* bin search id index */
    uint16 low = 0U, mid = 0U, high = 0U;
    uint16 uwIndex = MEMCFG_MEM_NEW_MAX_NUM;

    if(cthis->memNewNum){
        /* 请求大于预留最大值情况下，直接返回未使用个数（即找不到对应索引） */
        high = cthis->memNewNum-1U;
        while(low <= high){
            mid = ((low+high)>>1U);
            if(pointer < cthis->usedBlockIndex[mid].memPointer){
                if(mid == 0U){
                    break;
                }
                high = (mid-1U);
            }else if(pointer > cthis->usedBlockIndex[mid].memPointer){
                low = (mid+1U);
            }else{
                uwIndex = mid;
                break;
            }
        }
    }

    return uwIndex;
}

/*名称 : Mem_findUsedBigerIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
uint16 Mem_findUsedBigerIndex(hMem cthis, void *pointer){
    /* bin search id index */
    uint16 low = 0, mid = 0, high = 0;
    uint16 uwIndex = MEMCFG_MEM_NEW_MAX_NUM;

    if(cthis->memNewNum){
        /* 请求大于预留最大值情况下，直接返回未使用个数（即找不到对应索引） */
        high = cthis->memNewNum-1U;
        while(low <= high){
            mid = ((low+high)>>1U);
            if(pointer <= cthis->usedBlockIndex[mid].memPointer){
                if(mid == 0){
                    uwIndex = 0U;
                    break;
                }
                high = (mid-1U);
                if(pointer > cthis->usedBlockIndex[mid].memPointer){
                    uwIndex = mid;
                    break;
                }
            }else{
                low = (mid+1U);
                if(pointer <= cthis->usedBlockIndex[mid].memPointer){
                    uwIndex = low;
                    break;
                }
            }
        }
    }

    return uwIndex;
}

/*名称 : Mem_findBlockMaskMinIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
uint16 Mem_findBlockMaskMinIndex(hMem cthis){
    uint16 uwIndex = MEMCFG_MEM_BLOCK_MAX_NUM;
    uint16 uwMaskIndex = 0U;
    memMType ulMask = 0u;
    uint16 i = 0u;

    for(i = 0; i < MEMCFG_MEM_MASK_MASK_NUM; i++){
        if(cthis->memBlockMaskMask[i] != MEM_MANAG_TYPE_FULL_MASK){
            ulMask = cthis->memBlockMaskMask[i];
            ulMask = ~ulMask;
            ulMask = (ulMask & (0U-ulMask));
            uwMaskIndex = ((i<<MEM_MANAG_TYPE_BITS) + log_2n(ulMask));

            ulMask = cthis->memBlockMask[uwMaskIndex];
            ulMask = ~ulMask;
            ulMask = (ulMask & (0U-ulMask));
            uwIndex = ((uwMaskIndex<<MEM_MANAG_TYPE_BITS) + log_2n(ulMask));
            break;
        }
    }

    return uwIndex;
}

/*名称 : Mem_setBlockMaskIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void Mem_setBlockMaskIndex(hMem cthis, uint16 index){
    uint16 uwIndex = 0U;
    uint16 uwMaskIndex = 0U;

    uwMaskIndex = ((index>>MEM_MANAG_TYPE_BITS)>>MEM_MANAG_TYPE_BITS);
    uwIndex = (index>>MEM_MANAG_TYPE_BITS);
    cthis->memBlockMask[uwIndex] |= (0x1UL<<(index&MEM_MANAG_TYPE_MASK));
    if(cthis->memBlockMask[uwIndex] == MEM_MANAG_TYPE_FULL_MASK){
        cthis->memBlockMaskMask[uwMaskIndex] |= (0x1UL<<((index>>MEM_MANAG_TYPE_BITS)&MEM_MANAG_TYPE_MASK));
    }
}

/*名称 : Mem_clearBlockMaskIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void Mem_clearBlockMaskIndex(hMem cthis, uint16 index){
    uint16 uwIndex = 0U;
    uint16 uwMaskIndex = 0U;

    uwMaskIndex = ((index>>MEM_MANAG_TYPE_BITS)>>MEM_MANAG_TYPE_BITS);
    uwIndex = (index>>MEM_MANAG_TYPE_BITS);
    cthis->memBlockMask[uwIndex] &= (~(0x1UL<<(index&MEM_MANAG_TYPE_MASK)));
    if(cthis->memBlockMask[uwIndex] != MEM_MANAG_TYPE_FULL_MASK){
        cthis->memBlockMaskMask[uwMaskIndex] &= (~(0x1UL<<((index>>MEM_MANAG_TYPE_BITS)&MEM_MANAG_TYPE_MASK)));
    }
}

/*名称 : Mem_mergeMemBlock(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
uint16 Mem_mergeMemBlock(hMem cthis, uint16 index){
    uint16 uwPriorIndex = cthis->memBlock[index].priorIndex;
    uint16 uwOpRes = OOPC_TRUE;

    if((index)&&cthis->memBlock[uwPriorIndex].useStatus == mem_unused){
        /* 更新块状态 */
        // cthis->memBlock[uwPriorIndex].memPointer;
        cthis->memBlock[uwPriorIndex].memSize += cthis->memBlock[index].memSize;
        // cthis->memBlock[uwPriorIndex].useStatus;
        // cthis->memBlock[uwPriorIndex].priorIndex;
        cthis->memBlock[uwPriorIndex].nextIndex = cthis->memBlock[index].nextIndex;
        /* 更新下一使用块状态 */
        // cthis->memBlock[cthis->memBlock[uwPriorIndex].nextIndex].memPointer;
        //cthis->memBlock[cthis->memBlock[uwPriorIndex].nextIndex].memSize;
        // cthis->memBlock[cthis->memBlock[uwPriorIndex].nextIndex].useStatus;
         cthis->memBlock[cthis->memBlock[uwPriorIndex].nextIndex].priorIndex = uwPriorIndex;
        //cthis->memBlock[cthis->memBlock[uwPriorIndex].nextIndex].nextIndex;
        /* 更新块使用 */
        cthis->clearBlockMaskIndex(cthis, index); /* 释放块使用 */
    }else{
        /* 不处理报故障 */
        uwOpRes = OOPC_FALSE;
    }

    return uwOpRes;
}

/*名称 : Mem_delUsedIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void Mem_delUsedIndex(hMem cthis, uint16 index){
    uint16 uwUsedIndex = 0u;

    uwUsedIndex = cthis->findUsedIndex(cthis, cthis->memBlock[index].memPointer);
    if(uwUsedIndex >= MEMCFG_MEM_NEW_MAX_NUM){
        return;
    }
    if(uwUsedIndex < (cthis->memNewNum-1U)){
        memCopy(&(cthis->usedBlockIndex[uwUsedIndex]),&(cthis->usedBlockIndex[uwUsedIndex+1U]),((cthis->memNewNum-uwUsedIndex-1U)*sizeof(TS_USED_BLOCK)));
    }
    cthis->memNewNum--;
}

/*名称 : Mem_addUsedIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void Mem_addUsedIndex(hMem cthis, uint16 index){
    uint16 uwUsedIndex = 0U;

    uwUsedIndex = cthis->findUsedBigerIndex(cthis, cthis->memBlock[index].memPointer);
    if((uwUsedIndex >= MEMCFG_MEM_NEW_MAX_NUM)
    &&(cthis->memNewNum >= MEMCFG_MEM_NEW_MAX_NUM)){
        return;
    }

    if((uwUsedIndex >= MEMCFG_MEM_NEW_MAX_NUM)
    &&(cthis->memNewNum < MEMCFG_MEM_NEW_MAX_NUM)){
        uwUsedIndex = cthis->memNewNum;
    }else{
        if(cthis->memNewNum > 0U){
            if((uwUsedIndex < (cthis->memNewNum-1U))
            || (((!uwUsedIndex)||(uwUsedIndex == (cthis->memNewNum-1U))) && (cthis->memBlock[index].memPointer<cthis->memBlock[uwUsedIndex].memPointer))){
                memCopy(&(cthis->usedBlockIndex[uwUsedIndex+1U]),&(cthis->usedBlockIndex[uwUsedIndex]),((cthis->memNewNum-uwUsedIndex)*sizeof(TS_USED_BLOCK)));
            }else{
                uwUsedIndex = cthis->memNewNum;
            }
        }else{
            uwUsedIndex = 0U;
        }
    }
    cthis->usedBlockIndex[uwUsedIndex].memPointer = cthis->memBlock[index].memPointer;
    cthis->usedBlockIndex[uwUsedIndex].memIndex = index;
    cthis->memNewNum++;
}

/*名称 : Mem_delUnusedIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void Mem_delUnusedIndex(hMem cthis, uint16 index){
    uint16 uwUnusedIndex = 0U;

    uwUnusedIndex = cthis->findUnusedIndex(cthis, cthis->memBlock[index].memSize, index);
    if(uwUnusedIndex >= MEMCFG_MEM_UNUSED_MAX_NUM){
        return;
    }
    if(cthis->memUnusedNum > 1U){
        if(uwUnusedIndex < (cthis->memUnusedNum-1U)){
            memCopy(&(cthis->unusedBlockIndex[uwUnusedIndex]),&(cthis->unusedBlockIndex[uwUnusedIndex+1U]),((cthis->memUnusedNum-uwUnusedIndex-1U)*sizeof(TS_UNUSED_BLOCK)));
        }
    }
    cthis->memUnusedNum--;
}

/*名称 : Mem_delUnusedIndexDirect(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void Mem_delUnusedIndexDirect(hMem cthis, uint16 unusedIndex){
    if(unusedIndex >= MEMCFG_MEM_UNUSED_MAX_NUM){
        return;
    }
    if(cthis->memUnusedNum > 1U){
        if(unusedIndex < (cthis->memUnusedNum-1U)){
            memCopy(&(cthis->unusedBlockIndex[unusedIndex]),&(cthis->unusedBlockIndex[unusedIndex+1U]),((cthis->memUnusedNum-unusedIndex-1U)*sizeof(TS_UNUSED_BLOCK)));
        }
    }
    cthis->memUnusedNum--;
}

/*名称 : Mem_addUnusedIndex(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : 无
* 其他 : Mem类功能函数
***********************************************/
void Mem_addUnusedIndex(hMem cthis, uint16 index){
    uint16 uwUnusedIndex = 0U;

    uwUnusedIndex = cthis->findUnusedBigerIndex(cthis, (uint16)cthis->memBlock[index].memSize);
    if((uwUnusedIndex >= MEMCFG_MEM_UNUSED_MAX_NUM)
    &&(cthis->memUnusedNum >= MEMCFG_MEM_UNUSED_MAX_NUM)){
        return;
    }
    if((uwUnusedIndex >= MEMCFG_MEM_UNUSED_MAX_NUM)
    &&(cthis->memUnusedNum < MEMCFG_MEM_UNUSED_MAX_NUM)){
        uwUnusedIndex = cthis->memUnusedNum;
    }else{
        if(cthis->memUnusedNum > 0U){
            if(uwUnusedIndex < (cthis->memUnusedNum-1U)
            ||(((!uwUnusedIndex)||(uwUnusedIndex == (cthis->memUnusedNum-1U))) && (cthis->memBlock[index].memSize<cthis->unusedBlockIndex[uwUnusedIndex].memSize))){
                memCopy(&(cthis->unusedBlockIndex[uwUnusedIndex+1U]),&(cthis->unusedBlockIndex[uwUnusedIndex]),((cthis->memUnusedNum-uwUnusedIndex)*sizeof(TS_UNUSED_BLOCK)));
            }
            else{
                uwUnusedIndex = cthis->memUnusedNum;
            }
        }else{
            uwUnusedIndex = 0U;
        }
    }
    cthis->unusedBlockIndex[uwUnusedIndex].memSize = cthis->memBlock[index].memSize;
    cthis->unusedBlockIndex[uwUnusedIndex].memIndex = index;
    cthis->memUnusedNum++;
}

/*名称 : hMem Mem_init(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : hMem - cthis/OOPC_NULL
* 其他 : Mem类初始化函数
***********************************************/
hMem Mem_init(hMem cthis, uint8 *memSpace, uint32 memSize){
    // 功能函数配置
    //cthis->new = Mem_new;
    //TODO

    // 参数配置
    cthis->memSpace = memSpace;
    cthis->memSize = memSize;

    cthis->memBlock[0].memPointer = cthis->memSpace;
    cthis->memBlock[0].memSize = cthis->memSize;
    cthis->memBlock[0].useStatus = mem_unused;
    cthis->memBlock[0].priorIndex = 0;
    cthis->memBlock[0].nextIndex = 0;

    cthis->memBlockMask[0] |= 0x00000001UL;
    cthis->unusedBlockIndex[0].memSize = cthis->memBlock[0].memSize;
    cthis->unusedBlockIndex[0].memIndex = 0;
    cthis->memUnusedNum++;

    return cthis;
}

/*名称 : hMem Mem_ctor(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : hMem - cthis/OOPC_NULL
* 其他 : Mem类构造函数
***********************************************/
CC(Mem){
    uint16 i = 0U;

    cthis->init = Mem_init;
    cthis->malloc = Mem_malloc;
    cthis->free = Mem_free;
    cthis->findUnusedIndex = Mem_findUnusedIndex;
    cthis->findUnusedBigerIndex = Mem_findUnusedBigerIndex;
    cthis->findUsedIndex = Mem_findUsedIndex;
    cthis->findUsedBigerIndex = Mem_findUsedBigerIndex;
    cthis->findBlockMaskMinIndex = Mem_findBlockMaskMinIndex;
    cthis->setBlockMaskIndex = Mem_setBlockMaskIndex;
    cthis->clearBlockMaskIndex = Mem_clearBlockMaskIndex;
    cthis->mergeMemBlock = Mem_mergeMemBlock;
    cthis->delUsedIndex = Mem_delUsedIndex;
    cthis->addUsedIndex = Mem_addUsedIndex;
    cthis->delUnusedIndex = Mem_delUnusedIndex;
    cthis->delUnusedIndexDirect = Mem_delUnusedIndexDirect;
    cthis->addUnusedIndex = Mem_addUnusedIndex;

    // 参数配置
    cthis->memSpace = OOPC_NULL;
    cthis->memSize = 0U;
    cthis->memNewNum = 0U;
    cthis->memUnusedNum = 0U;

    for(i = 0U; i < MEMCFG_MEM_MASK_MASK_NUM; i++){
        cthis->memBlockMaskMask[i] = 0U;
    }
    for(i = 0U; i < MEMCFG_MEM_BLOCK_MASK_MAX_NUM; i++){
        cthis->memBlockMask[i] = 0U;
    }

    return cthis;
}

/*名称 : hMem Mem_dtor(hMem cthis)
* 输入 : cthis - Mem类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : Mem类析构函数
***********************************************/
CD(Mem){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
