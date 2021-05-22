/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : BlockM.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2021/03/20 16:42:53
* Description  : BlockM类各功能函数定义源文件
* Others       :
* History      : 210320 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./BlockM.h"
#include "../Func/Func.h"

/***********************************************************
* 数据类型定义
***********************************************************/
/*数据定义
***********************************************/
//TODO
// #define MANAG_BLOCK_SIZE   80u
// uint8 ulDataSpace[BLOCKMCFG_CAL_ALL_MASK_SIZE(MANAG_BLOCK_SIZE)+(MANAG_BLOCK_SIZE*sizeof(uint32))];

/***********************************************************
* BlockM类定义
***********************************************************/
/*名称 : BlockM_malloc(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
void * BlockM_malloc(hBlockM cthis, uint16 size){
    uint16 uwCount = 0u, uwIndex = 0u;
    uint8 *pointer = OOPC_NULL;

    uwCount = (size/cthis->blockMSize);
    if(size > (uwCount*cthis->blockMSize)){
        uwCount++;
    }
    /* judge count */
    if(uwCount <= 1u){
        uwIndex = cthis->findMinIndex(cthis);
        if(uwIndex<cthis->blockMMax){
            cthis->setMaskIndex(cthis,uwIndex);
        }
    }else{
        uwIndex = cthis->findContinueMinIndex(cthis,uwCount);
        if(uwIndex<cthis->blockMMax){
            cthis->setContinueMaskIndex(cthis,uwIndex,uwCount);
        }
    }
    /* get pointer */
    if(uwIndex<cthis->blockMMax){
        pointer = (uint8*)cthis->getAddr(cthis,uwIndex);
    }
    return (void*)pointer;
}


/*名称 : BlockM_free(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_free(hBlockM cthis, void *pointer){
    uint16 uwIndex = 0u;
    uint16 uwRet = FALSE;

    uwIndex = cthis->getIndex(cthis,pointer);
    if(uwIndex<cthis->blockMMax){
        if(cthis->isIndexSet(cthis,uwIndex)){
            if(cthis->isIndexContiueSet(cthis,uwIndex)){
                cthis->clearContinueMaskIndex(cthis,uwIndex);
            }else{
                cthis->clearMaskIndex(cthis,uwIndex);
            }
            uwRet = TRUE;
        }
    }
    return uwRet;
}


/*名称 : BlockM_findMinIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_findMinIndex(hBlockM cthis){
    uint16 uwIndex = cthis->blockMMax;
    uint16 uwMaskIndex = 0U;
    blockMType ulMask = 0u;
    uint16 i = 0u;

    for(i = 0; i < cthis->blockMMaskMaskMax; i++){
        /* if blockMMaskMaskMask full, then continue */
        if(cthis->blockMMaskMaskMask[i] == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            continue;
        }
        /* get blockMMaskMaskMask index */
        ulMask = cthis->blockMMaskMaskMask[i];
        ulMask = ~ulMask;
        ulMask = MASK_FIRST_BIT(ulMask);
        uwMaskIndex = ((i<<BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
        /* get blockMMaskMask index */
        ulMask = cthis->blockMMaskMask[uwMaskIndex];
        ulMask = ~ulMask;
        ulMask = MASK_FIRST_BIT(ulMask);
        uwMaskIndex = ((uwMaskIndex<<BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
        /* get blockMMask/blockMMaskContinue index */
        ulMask = (cthis->blockMMask[uwMaskIndex]|cthis->blockMMaskContinue[uwMaskIndex]); /* All blockMMask and blockMMaskContinue mask */
        ulMask = ~ulMask;
        ulMask = MASK_FIRST_BIT(ulMask);
        uwIndex = ((uwMaskIndex<<BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
        break;
    }
    return uwIndex;
}

/*名称 : BlockM_setMaskIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
void BlockM_setMaskIndex(hBlockM cthis, uint16 index){
    uint16 uwMaskIndex = 0U;
    blockMType ulMask = 0u, ulBlockMask = 0u;

    ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index));
    uwMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    if(!(cthis->blockMMask[uwMaskIndex]&ulMask)){ /* if blockMMask is unmasked, then set bit */
        cthis->blockMCounter++;
        cthis->blockMMask[uwMaskIndex] |= ulMask;
        /* if blockMMask is full, then set blockMMaskMask bit */
        ulBlockMask = cthis->blockMMask[uwMaskIndex];
        ulBlockMask |= cthis->blockMMaskContinue[uwMaskIndex]; /* All blockMMask and blockMMaskContinue mask */
        if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
            uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
            cthis->blockMMaskMask[uwMaskIndex] |= ulMask;
            if(cthis->blockMMaskMask[uwMaskIndex] == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
                uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
                cthis->blockMMaskMaskMask[uwMaskIndex] |= ulMask;
            }
        }
    }
}


/*名称 : BlockM_clearMaskIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
void BlockM_clearMaskIndex(hBlockM cthis, uint16 index){
    uint16 uwMaskIndex = 0U;
    blockMType ulMask = 0u, ulBlockMask = 0u;

    ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index));
    uwMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    ulBlockMask = cthis->blockMMask[uwMaskIndex];
    if(ulBlockMask&ulMask){ /* if blockMMask is set, then clear bit */
        cthis->blockMCounter--;
        cthis->blockMMask[uwMaskIndex] &= (~ulMask);
        /* if last blockMMask is full, then clear blockMMaskMask bit */
        ulBlockMask |= cthis->blockMMaskContinue[uwMaskIndex]; /* All blockMMask and blockMMaskContinue mask */
        if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
            uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
            ulBlockMask = cthis->blockMMaskMask[uwMaskIndex];
            cthis->blockMMaskMask[uwMaskIndex] &= (~ulMask);
            if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
                uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
                cthis->blockMMaskMaskMask[uwMaskIndex] &= (~ulMask);
            }
        }
    }
}


/*名称 : BlockM_findMinIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
static inline void BlockM_maskContinue(hBlockM cthis,blockMType *ulBlockMask, uint16 *uwIndex, uint16 *uwCountResidue, uint16 count, uint16 uwGroupIndex){
    uint16 uwMaskIndex = 0U;
    blockMType ulMask = 0u, ulContinueMask = 0u;
    uint16 uwShift = 0u;

    /* get mask first bit, and calculate start index */
    ulMask = *ulBlockMask;
    ulMask = ~ulMask;
    ulMask = MASK_FIRST_BIT(ulMask);
    uwMaskIndex = log_2n(ulMask);
    if(*uwCountResidue == count){
        *uwIndex = (uwMaskIndex+(uwGroupIndex*(sizeof(blockMType)<<3u)));
    }
    /* calculate continue, and try to match */
    ulContinueMask = BLOCKM_BITINDEX_MASK(uwMaskIndex);
    ulContinueMask = MASK_BIT_UP_IN_FULL(ulContinueMask);
    if(((sizeof(blockMType)<<3u)-uwMaskIndex) >= *uwCountResidue){
        uwShift = ((sizeof(blockMType)<<3u)-uwMaskIndex-*uwCountResidue);
        ulContinueMask = ((ulContinueMask<<uwShift)>>uwShift);
        *uwCountResidue = 0u;
    }else{
        *uwCountResidue = (*uwCountResidue-((sizeof(blockMType)<<3u)-uwMaskIndex)); /* find reside blank */
    }

    /* return residue mask */
    ulMask = ((*ulBlockMask)&ulContinueMask);
    if(ulMask){
        *uwCountResidue = count; /* if not match, reset match count */
        ulMask = (ulMask|(ulMask-1u)); /* mask lower bits */
    }else{/* match */
        ulMask = (ulContinueMask|(ulContinueMask-1u)); /* mask lower bits */
    }
    *ulBlockMask = (ulMask|(*ulBlockMask)); /* calculate residue unmasked bits, and return mask */
}
uint16 BlockM_findContinueMinIndex(hBlockM cthis, uint16 count){
    uint16 uwIndex = cthis->blockMMax;
    uint16 uwMaskIndex = 0U, uwCountResidue = 0U;
    blockMType ulMask = 0u;
    uint16 i = 0u, j = 0u, k = 0u;

    uwCountResidue = count;
    for(i = 0; i < cthis->blockMMaskMaskMaskMax; i++){
        ulMask = cthis->blockMMaskMaskMask[i];
        /* if blockMMaskMaskMask full, then continue */
        if(ulMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            continue;
        }
        /* find blockMMaskMask index */
        ulMask = ~ulMask;
        ulMask = MASK_FIRST_BIT(ulMask);
        uwMaskIndex = ((i<<BLOCKMCFG_MANAG_TYPE_BITS)+log_2n(ulMask));
        for(j = uwMaskIndex; j < ((sizeof(blockMType)<<3u)+(i<<BLOCKMCFG_MANAG_TYPE_BITS)); j++){
            ulMask = cthis->blockMMaskMask[j];
            /* if blockMMaskMask full, then continue */
            if(ulMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                continue;
            }
            /* find blockMMask/blockMMaskContinue index */
            ulMask = ~ulMask;
            ulMask = MASK_FIRST_BIT(ulMask);
            uwMaskIndex = ((j<<BLOCKMCFG_MANAG_TYPE_BITS)+log_2n(ulMask));
            for(k = uwMaskIndex; k < ((sizeof(blockMType)<<3u)+(j<<BLOCKMCFG_MANAG_TYPE_BITS)); k++){
                if(uwCountResidue < count){
                    /* residue blank not start from next mask start bit, refind. */
                    if(cthis->blockMMask[k]&1u){
                        uwCountResidue = count;
                    }
                }
                ulMask = (cthis->blockMMask[k]|cthis->blockMMaskContinue[k]); /* All blockMMask and blockMMaskContinue mask */
                do{
                    BlockM_maskContinue(cthis,&ulMask,&uwIndex,&uwCountResidue,count,k);
                    if(!uwCountResidue){
                        break;
                    }
                }while(ulMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK);
                /* blank found, return */
                if(!uwCountResidue){
                    break;
                }
            }
            if(uwCountResidue&&(uwCountResidue<count)){
                /* residue blank not start from next mask start bit, refind. */
                if(cthis->blockMMask[k]&1u){
                    uwCountResidue = count;
                }
            }
            if(!uwCountResidue){
                break;
            }
        }
        if(!uwCountResidue){
            break;
        }
    }
    if(uwCountResidue){
        uwIndex = cthis->blockMMax;
    }
    return uwIndex;
}

/*名称 : BlockM_setMaskIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
void BlockM_setContinueMaskIndex(hBlockM cthis, uint16 index, uint16 count){
    uint16 uwStartMaskIndex = 0U, uwMaskIndex = 0U, uwCountResidue = 0U, uwCountSet = 0U, uwShift = 0U;
    blockMType ulMask = 0u, ulContinueMask = 0U;

    uwCountSet = ((sizeof(blockMType)<<3u)-BLOCKM_INDEX_BITINDEX(index));
    ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index));
    uwStartMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    uwMaskIndex = uwStartMaskIndex;
    if(!(cthis->blockMMask[uwMaskIndex]&ulMask)){
        /* set blockMMask bit */
        cthis->blockMMask[uwMaskIndex] |= ulMask;
    }
    uwCountResidue = count;
    while(uwCountResidue){
        /* if continue mask set, return */
        if(cthis->blockMMaskContinue[uwMaskIndex]&ulMask){
            break;
        }
        /* calculate continue mask */
        if(uwCountResidue == count){
            uwShift = 0U;
            if(uwCountSet>=count){
                uwShift = (uwCountSet-count);
                uwCountSet = count;
            }
            ulContinueMask = MASK_BIT_UP_IN_FULL(ulMask);
            ulContinueMask = ((ulContinueMask<<uwShift)>>uwShift);
        }else{
            ulContinueMask = ulMask;
        }
        /* set mask */
        uwCountResidue -= uwCountSet;
        cthis->blockMCounter += uwCountSet;
        cthis->blockMMaskContinue[uwMaskIndex] |= ulContinueMask;
        ulMask = (cthis->blockMMask[uwMaskIndex]|cthis->blockMMaskContinue[uwMaskIndex]); /* All blockMMask and blockMMaskContinue mask */
        if(ulMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
            uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
            cthis->blockMMaskMask[uwMaskIndex] |= ulMask;
            if(cthis->blockMMaskMask[uwMaskIndex] == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
                uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
                cthis->blockMMaskMaskMask[uwMaskIndex] |= ulMask;
            }
        }
        /* set next continue mask */
        if(uwCountResidue >= (sizeof(blockMType)<<3u)){
            ulMask = BLOCKMCFG_MANAG_TYPE_FULL_MASK;
            uwCountSet = (sizeof(blockMType)<<3u);
        }else{
            ulMask = BLOCKM_BITINDEX_MASK(uwCountResidue);
            ulMask = MASK_BIT_DOWN_FULL(ulMask);
            uwCountSet = uwCountResidue;
        }
        uwStartMaskIndex++;
        uwMaskIndex = uwStartMaskIndex;
    }
}


/*名称 : BlockM_clearMaskIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
typedef enum{
    CLEAR_BEGIN,
    CLEAR_CONTINUE,
    CLREA_END
} TE_CLEAR_CONTINUE_STEP;
void BlockM_clearContinueMaskIndex(hBlockM cthis, uint16 index){
    uint16 uwStartMaskIndex = 0U, uwMaskIndex = 0U, uwIndex = 0U;
    blockMType ulMask = 0u, ulContinueMask = 0U, ulBlockMask = 0u;
    TE_CLEAR_CONTINUE_STEP teClearStep = CLEAR_BEGIN;

    uwIndex = (index&BLOCKMCFG_MANAG_TYPE_MASK);
    ulMask = BLOCKM_BITINDEX_MASK(uwIndex);
    uwStartMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    uwMaskIndex = uwStartMaskIndex;
    ulBlockMask = cthis->blockMMask[uwMaskIndex];
    if(ulBlockMask&ulMask){
        /* clear blockMMask bit */
        cthis->blockMMask[uwMaskIndex] &= (~ulMask);
    }
    while(ulMask){
        switch(teClearStep){
            case CLEAR_BEGIN:{
                ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                if(ulBlockMask&ulMask){
                    /* get continue mask up and unmasked ulBlockMask(used to continue mask) */
                    ulContinueMask = MASK_BIT_UP_IN_FULL(ulMask);
                    ulBlockMask = (~cthis->blockMMask[uwMaskIndex]); /* include continue mask */
                    ulMask = (ulBlockMask&ulContinueMask); /* find continue mask exclude low unmask bit */
                    if(ulMask==ulContinueMask){
                        ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                        ulContinueMask = (ulContinueMask&ulBlockMask); /* find real continue mask */
                        cthis->blockMMaskContinue[uwMaskIndex] &= (~ulContinueMask);
                        if(ulContinueMask==ulMask){
                            /* ulContinueMask full, continue to find next mask */
                            if(cthis->blockMCounter >= ((sizeof(blockMType)<<3u)-uwIndex)){
                                cthis->blockMCounter -= ((sizeof(blockMType)<<3u)-uwIndex);
                            }else{
                                cthis->blockMCounter = 0u;
                            }
                            teClearStep = CLEAR_CONTINUE;
                        }else{
                            /* ulContinueMask not full, clear and return */
                            ulMask = MASK_HIGH_FIRST_BIT(ulContinueMask); /* get high bit and calculate count */
                            uwIndex = (log_2n(ulMask)+1u-uwIndex);
                            if(cthis->blockMCounter >= uwIndex){
                                cthis->blockMCounter -= uwIndex;
                            }else{
                                cthis->blockMCounter = 0u;
                            }
                            teClearStep = CLREA_END;
                        }
                    }else{
                        /* mask clear, return */
                        ulMask = ((~ulMask)&ulContinueMask);
                        ulMask = MASK_FIRST_BIT(ulMask); /* find blockMMask upper first masked bit */
                        ulContinueMask = (ulContinueMask&MASK_BIT_DOWN_FULL(ulMask));
                        ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                        ulContinueMask = (ulContinueMask&ulBlockMask); /* find real continue mask */
                        cthis->blockMMaskContinue[uwMaskIndex] &= (~ulContinueMask); /* clear blockMMaskContinue continue mask */
                        ulMask = MASK_HIGH_FIRST_BIT(ulContinueMask); /* get high bit and calculate count */
                        uwIndex = (log_2n(ulMask)+1u-uwIndex);
                        if(cthis->blockMCounter >= uwIndex){
                            cthis->blockMCounter -= uwIndex;
                        }else{
                            cthis->blockMCounter = 0u;
                        }
                        teClearStep = CLREA_END;
                    }
                    /* clear mask */
                    ulBlockMask |= cthis->blockMMask[uwMaskIndex]; /* All blockMMask and blockMMaskContinue mask */
                    if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                        ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
                        uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
                        ulBlockMask = cthis->blockMMaskMask[uwMaskIndex];
                        cthis->blockMMaskMask[uwMaskIndex] &= (~ulMask);
                        if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                            ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
                            uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
                            cthis->blockMMaskMaskMask[uwMaskIndex] &= (~ulMask);
                        }
                    }
                }else{
                    teClearStep = CLREA_END;
                }
                uwStartMaskIndex++;
                uwMaskIndex = uwStartMaskIndex;
                ulMask = BLOCKMCFG_MANAG_TYPE_FULL_MASK;
                break;
            }
            case CLEAR_CONTINUE:{
                ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                if(ulBlockMask&1u){
                    ulBlockMask = (~cthis->blockMMask[uwMaskIndex]);
                    ulContinueMask = ulMask;
                    ulMask = (ulBlockMask&ulContinueMask); /* find continue mask */
                    if(ulMask==ulContinueMask){
                        /* continue to find next mask */
                        ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                        ulContinueMask = (ulContinueMask&ulBlockMask); /* find real continue mask */
                        cthis->blockMMaskContinue[uwMaskIndex] &= (~ulContinueMask);
                        if(ulContinueMask==ulMask){
                            /* ulContinueMask full, continue to find next mask */
                            if(cthis->blockMCounter >= (sizeof(blockMType)<<3u)){
                                cthis->blockMCounter -= (sizeof(blockMType)<<3u);
                            }else{
                                cthis->blockMCounter = 0u;
                            }
                            teClearStep = CLEAR_CONTINUE;
                        }else{
                            /* ulContinueMask not full, clear and return */
                            ulMask = MASK_HIGH_FIRST_BIT(ulContinueMask); /* get high bit and calculate count */
                            uwIndex = (log_2n(ulMask)+1u);
                            if(cthis->blockMCounter >= uwIndex){
                                cthis->blockMCounter -= uwIndex;
                            }else{
                                cthis->blockMCounter = 0u;
                            }
                            teClearStep = CLREA_END;
                        }
                    }else{
                        /* mask clear, return */
                        if(ulBlockMask&1u){
                            ulMask = (ulMask&cthis->blockMMaskContinue[uwMaskIndex]); /* find continue mask exclude higher bit */
                            ulMask = (~ulMask);
                            ulMask = MASK_FIRST_BIT(ulMask); /* find continue higher bit */
                            ulContinueMask = MASK_BIT_DOWN_FULL(ulMask); /* find continue mask */
                            ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                            cthis->blockMMaskContinue[uwMaskIndex] &= (~ulContinueMask);
                            uwIndex = log_2n(ulMask);
                            if(cthis->blockMCounter >= uwIndex){
                                cthis->blockMCounter -= uwIndex;
                            }else{
                                cthis->blockMCounter = 0u;
                            }
                        }
                        teClearStep = CLREA_END;
                    }
                    /* clear mask */
                    ulBlockMask |= cthis->blockMMask[uwMaskIndex]; /* All blockMMask and blockMMaskContinue mask */
                    if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                        ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
                        uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
                        ulBlockMask = cthis->blockMMaskMask[uwMaskIndex];
                        cthis->blockMMaskMask[uwMaskIndex] &= (~ulMask);
                        if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                            ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(uwMaskIndex));
                            uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwMaskIndex);
                            cthis->blockMMaskMaskMask[uwMaskIndex] &= (~ulMask);
                        }
                    }
                }else{
                    teClearStep = CLREA_END;
                }
                uwStartMaskIndex++;
                uwMaskIndex = uwStartMaskIndex;
                ulMask = BLOCKMCFG_MANAG_TYPE_FULL_MASK;
                break;
            }
            case CLREA_END:{
                ulMask = 0u;
                break;
            }
            default:{
                ulMask = 0u;
                break;
            }
        }
    }
}


/*名称 : BlockM_isPointerSet(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_isPointerSet(hBlockM cthis, void *pointer){
    uint16 uwRet = FALSE;
    uint16 uwIndex = cthis->getIndex(cthis,pointer);

    if(uwIndex<cthis->blockMMax){
        uwRet = cthis->isIndexSet(cthis,uwIndex);
    }
    return uwRet;
}


/*名称 : BlockM_isIndexSet(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_isIndexSet(hBlockM cthis, uint16 index){
    uint16 uwRet = FALSE;
    uint16 uwIndex = 0u;

    if(index<cthis->blockMMax){
        uwIndex = BLOCKM_INDEX_MASKINDEX(index);
        if(cthis->blockMMask[uwIndex] \
        &BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index))){
            uwRet = TRUE;
        }
    }
    return uwRet;
}


/*名称 : BlockM_isIndexContiueSet(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_isIndexContiueSet(hBlockM cthis, uint16 index){
    uint16 uwRet = FALSE;
    uint16 uwIndex = 0u;

    if(index<cthis->blockMMax){
        uwIndex = BLOCKM_INDEX_MASKINDEX(index);
        if((cthis->blockMMask[uwIndex] \
        &cthis->blockMMaskContinue[uwIndex]) \
        &BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index))){
            uwRet = TRUE;
        }
    }
    return uwRet;
}


/*名称 : BlockM_isFull(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_isFull(hBlockM cthis){
    uint16 uwRet = FALSE;

    if(cthis->blockMCounter < cthis->blockMMax)
    {
        uwRet = TRUE;
    }
    return uwRet;
}


/*名称 : BlockM_getIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
typedef enum{
    GET_SIZE_BEGIN,
    GET_SIZE_CONTINUE,
    GET_SIZE_END
} TE_GET_SIZE_STEP;
uint16 BlockM_getSize(hBlockM cthis, void *pointer){
    uint16 uwSize = 0u;
    uint16 uwIndex = 0u, uwMaskIndex = 0U;
    blockMType ulMask = 0u, ulBlockMask = 0u;
    TE_GET_SIZE_STEP teGetStep = GET_SIZE_BEGIN;

    uwIndex = cthis->getIndex(cthis,pointer);
    if(uwIndex>=cthis->blockMMax){
        teGetStep = GET_SIZE_END;
    }
    uwMaskIndex = BLOCKM_INDEX_MASKINDEX(uwIndex);
    uwIndex = BLOCKM_INDEX_BITINDEX(uwIndex);
    ulMask = BLOCKM_BITINDEX_MASK(uwIndex);
    do{
        switch(teGetStep){
            case GET_SIZE_BEGIN:{
                /* if blockMMask unmasked, return */
                if(!(cthis->blockMMask[uwMaskIndex]&ulMask)){
                    teGetStep = GET_SIZE_END;
                    break;
                }
                /* if blockMMaskContinue unmasked, return size 1 */
                if(!(cthis->blockMMaskContinue[uwMaskIndex]&ulMask)){
                    uwSize = 1u;
                    teGetStep = GET_SIZE_END;
                    break;
                }
                ulMask = MASK_BIT_UP_FULL(ulMask);
                //ulBlockMask = (cthis->blockMMask[uwMaskIndex]&ulMask);
                ulBlockMask = cthis->blockMMask[uwMaskIndex];
                ulBlockMask &= ulMask;
                if(ulBlockMask){
                    /* if blockMMask has another index, then pointer size in current mask */
                    ulBlockMask = MASK_FIRST_BIT(ulBlockMask);
                    ulBlockMask = MASK_BIT_DOWN_FULL(ulBlockMask);
                    ulBlockMask = (ulBlockMask&ulMask); /* mask between two masked bit in blockMMask */
                    if((ulBlockMask&cthis->blockMMaskContinue[uwMaskIndex])!=ulBlockMask){
                        /* mask is not full between two masked bit, and unmasked those */
                        ulBlockMask = (ulBlockMask&cthis->blockMMaskContinue[uwMaskIndex]);
                    }
                    ulMask &= (~ulBlockMask);
                    if(ulMask){
                        ulMask = MASK_FIRST_BIT(ulMask);
                        uwSize = (log_2n(ulMask)-uwIndex);
                    }else{
                        uwSize = ((sizeof(blockMType)<<3u)-uwIndex);
                    }
                    teGetStep = GET_SIZE_END;
                }else{
                    ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                    ulBlockMask &= ulMask;
                    if(ulBlockMask!=ulMask){
                        /* if blockMMaskContinue is not full, then pointer size in current mask */
                        ulBlockMask = ((~ulBlockMask)&ulMask);
                        if(ulBlockMask){
                            ulMask = MASK_FIRST_BIT(ulBlockMask);
                            uwSize = (log_2n(ulMask)-uwIndex);
                        }else{
                            uwSize = ((sizeof(blockMType)<<3u)-uwIndex);
                        }
                        teGetStep = GET_SIZE_END;
                    }else{
                        /* continue to find pointer size in current and next mask */
                        uwSize = ((sizeof(blockMType)<<3u)-uwIndex);
                        uwMaskIndex++;
                        teGetStep = GET_SIZE_CONTINUE;
                    }
                }
                break;
            }
            case GET_SIZE_CONTINUE:{
                ulBlockMask = cthis->blockMMaskContinue[uwMaskIndex];
                while((ulBlockMask&1u)&&(!(cthis->blockMMask[uwMaskIndex]&1u))){
                    if(cthis->blockMMask[uwMaskIndex]){
                        /* find end */
                        ulMask = MASK_FIRST_BIT(cthis->blockMMask[uwMaskIndex]);
                        ulMask = MASK_BIT_DOWN_FULL(ulMask);
                        ulBlockMask = (ulMask&ulBlockMask); /* mask from 0 to masked bit in blockMMask */
                        ulBlockMask = (~ulBlockMask);
                        ulMask = MASK_FIRST_BIT(ulBlockMask); /* first unmasked bit */
                        uwSize += log_2n(ulMask);
                        break;
                    }else{
                        if(ulBlockMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                            /* continue to find */
                            uwSize += (sizeof(blockMType)<<3u);
                            uwMaskIndex++;
                        }else{
                            /* find end */
                            ulBlockMask = (~ulBlockMask);
                            ulMask = MASK_FIRST_BIT(ulBlockMask);
                            uwSize += log_2n(ulMask);
                            break;
                        }
                    }
                }
                teGetStep = GET_SIZE_END;
                break;
            }
            case GET_SIZE_END:{
                break;
            }
            default:{
                teGetStep = GET_SIZE_END;
                break;
            }
        }
    }while(teGetStep != GET_SIZE_END);

    return uwSize;
}


/*名称 : BlockM_getIndex(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_getIndex(hBlockM cthis, void *pointer){
    uint16 uwIndex = cthis->blockMMax;

    if((uint8*)pointer >= cthis->blockMPointer){
        uwIndex = (uint16)((uint32)((uint8*)pointer-cthis->blockMPointer)/cthis->blockMSize);
    }
    return uwIndex;
}


/*名称 : BlockM_getAddr(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
void* BlockM_getAddr(hBlockM cthis, uint16 index){
    return (void*)(cthis->blockMPointer+(((uint32)cthis->blockMSize)*index));
}


/*名称 : BlockM_getCounts(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_getCounts(hBlockM cthis){
    return cthis->blockMCounter;
}


/*名称 : BlockM_getMax(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : 无
* 其他 : BlockM类功能函数
***********************************************/
uint16 BlockM_getMax(hBlockM cthis){
    return cthis->blockMMax;
}


/*名称 : hBlockM BlockM_init(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : hBlockM - cthis/OOPC_NULL
* 其他 : BlockM类初始化函数
***********************************************/
hBlockM BlockM_init(hBlockM cthis, uint8 *blockMSpace, uint16 blockMSize, uint16 blockMMax){
    uint16 uwMaskIndex = 0U;
    uint16 i = 0U;

    // 功能函数配置
    //TODO

    // 参数配置
    cthis->blockMSpace = blockMSpace;
    cthis->blockMSize = blockMSize;
    cthis->blockMMax = blockMMax;

    uwMaskIndex = (cthis->blockMMax>>BLOCKMCFG_MANAG_TYPE_BITS);
    if(cthis->blockMMax&BLOCKMCFG_MANAG_TYPE_MASK){
        uwMaskIndex++;
    }
    cthis->blockMMaskMax = uwMaskIndex;
    uwMaskIndex = (cthis->blockMMaskMax>>BLOCKMCFG_MANAG_TYPE_BITS);
    if(cthis->blockMMaskMax&BLOCKMCFG_MANAG_TYPE_MASK){
        uwMaskIndex++;
    }
    cthis->blockMMaskMaskMax = uwMaskIndex;
    uwMaskIndex = (cthis->blockMMaskMaskMax>>BLOCKMCFG_MANAG_TYPE_BITS);
    if(cthis->blockMMaskMaskMax&BLOCKMCFG_MANAG_TYPE_MASK){
        uwMaskIndex++;
    }
    cthis->blockMMaskMaskMaskMax = uwMaskIndex;

    cthis->blockMPointer = (cthis->blockMSpace+((cthis->blockMMaskMaskMaskMax+cthis->blockMMaskMaskMax+(cthis->blockMMaskMax<<1U))*sizeof(blockMType)));
    cthis->blockMMaskMaskMask = (blockMType*)cthis->blockMSpace;
    cthis->blockMMaskMask = (blockMType*)(cthis->blockMSpace+(cthis->blockMMaskMaskMaskMax*sizeof(blockMType)));
    cthis->blockMMask = (blockMType*)(cthis->blockMSpace+((cthis->blockMMaskMaskMaskMax+cthis->blockMMaskMaskMax)*sizeof(blockMType)));
    cthis->blockMMaskContinue = (blockMType*)(cthis->blockMSpace+((cthis->blockMMaskMaskMaskMax+cthis->blockMMaskMaskMax+cthis->blockMMaskMax)*sizeof(blockMType)));

    for(i = 0U; i < cthis->blockMMaskMaskMax; i++){
        cthis->blockMMaskMask[i] = 0U;
    }
    for(i = 0U; i < cthis->blockMMaskMax; i++){
        cthis->blockMMask[i] = 0U;
        cthis->blockMMaskContinue[i] = 0U;
    }

    return cthis;
}

/*名称 : hBlockM BlockM_ctor(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : hBlockM - cthis/OOPC_NULL
* 其他 : BlockM类构造函数
***********************************************/
CC(BlockM){
    cthis->init = BlockM_init;

    cthis->malloc = BlockM_malloc;
    cthis->free = BlockM_free;

    cthis->findMinIndex = BlockM_findMinIndex;
    cthis->setMaskIndex = BlockM_setMaskIndex;
    cthis->clearMaskIndex = BlockM_clearMaskIndex;

    cthis->findContinueMinIndex = BlockM_findContinueMinIndex;
    cthis->setContinueMaskIndex = BlockM_setContinueMaskIndex;
    cthis->clearContinueMaskIndex = BlockM_clearContinueMaskIndex;

    cthis->isPointerSet = BlockM_isPointerSet;
    cthis->isIndexSet = BlockM_isIndexSet;
    cthis->isIndexContiueSet = BlockM_isIndexContiueSet;
    cthis->isFull = BlockM_isFull;

    cthis->getSize = BlockM_getSize;
    cthis->getIndex = BlockM_getIndex;
    cthis->getAddr = BlockM_getAddr;

    cthis->getCounts = BlockM_getCounts;
    cthis->getMax = BlockM_getMax;

    // 参数配置
    cthis->blockMSpace = NULL;
    cthis->blockMSize = 0u;
    cthis->blockMMax = 0u;
    cthis->blockMCounter = 0u;
    cthis->blockMMaskMaskMaskMax = 0u;
    cthis->blockMMaskMaskMax = 0u;
    cthis->blockMMaskMax = 0u;
    cthis->blockMMaskMaskMask = NULL;
    cthis->blockMMaskMask = NULL;
    cthis->blockMMask = NULL;
    cthis->blockMMaskContinue = NULL;

    return cthis;
}

/*名称 : hBlockM BlockM_dtor(hBlockM cthis)
* 输入 : cthis - BlockM类指针
* 输出 : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
* 其他 : BlockM类析构函数
***********************************************/
CD(BlockM){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
