/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : BlockM.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 08:56:12
 * Description  : BlockM class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "BlockM.h"
#include "Func.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/

/***********************************************************
 * BlockM class definition.
 **********************************************************/
/* Function : BlockM_malloc(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
void * BlockM_malloc(hBlockM cthis, uint16 size){
    uint16 uwCount = 0u;
    blockMType ulIndex = 0u;
    void *pointer = OOPC_NULL;

    /* get block count. */
    uwCount = (size/cthis->blockMSize);
    if(size > (uwCount*cthis->blockMSize)){
        uwCount++;
    }
    do{
        /* judge count */
        if(uwCount == 0u){
            break;
        }
        if(uwCount == 1u){
            ulIndex = cthis->findMinIndex(cthis);
            if(ulIndex >= cthis->blockMMax){
                break;
            }
            cthis->setMaskIndex(cthis,ulIndex);
        }else{
            ulIndex = cthis->findContinueMinIndex(cthis,uwCount);
            if(ulIndex >= cthis->blockMMax){
                break;
            }
            cthis->setContinueMaskIndex(cthis,ulIndex,uwCount);
        }
        /* get pointer */
        pointer = cthis->getAddr(cthis,ulIndex);
    }while(0);
    return pointer;
}

/* Function : BlockM_free(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
uint8 BlockM_free(hBlockM cthis, void *pointer){
    blockMType ulIndex = 0u;
    uint8 ucRet = FALSE;

    ulIndex = cthis->getIndex(cthis,pointer);
    if((ulIndex < cthis->blockMMax)
    && cthis->isIndexSet(cthis,ulIndex)){
        if(cthis->isIndexContinueSet(cthis,ulIndex)){
            cthis->clearContinueMaskIndex(cthis,ulIndex);
        }else{
            cthis->clearMaskIndex(cthis,ulIndex);
        }
        ucRet = TRUE;
    }
    return ucRet;
}

/* Function : BlockM_findMinIndex(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
blockMType BlockM_findMinIndex(hBlockM cthis){
    blockMType ulIndex = cthis->blockMMax;
    blockMType ulMaskIndex = 0U;
    blockMType ulMask = 0u;
    blockMType i = 0u;

    for(i = 0; i < cthis->blockMMaskMaskMax; i++){
        /* if blockMMaskMaskMask full, then continue */
        if(cthis->blockMMaskMaskMask[i] == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            continue;
        }
        /* get blockMMaskMaskMask index */
        ulMask = cthis->blockMMaskMaskMask[i];
        ulMask = (~ulMask);
        ulMask = MASK_FIRST_BIT(ulMask);
        ulMaskIndex = ((i<<BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
        /* get blockMMaskMask index */
        ulMask = cthis->blockMMaskMask[ulMaskIndex];
        ulMask = (~ulMask);
        ulMask = MASK_FIRST_BIT(ulMask);
        ulMaskIndex = ((ulMaskIndex<<BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
        if(ulMaskIndex >= cthis->blockMMax){
            /* Overflow return */
            break;
        }
        /* get blockMMask/blockMMaskContinue index */
        /* All blockMMask and blockMMaskContinue mask */
        ulMask = (cthis->blockMMask[ulMaskIndex]|cthis->blockMMaskContinue[ulMaskIndex]);
        ulMask = (~ulMask);
        ulMask = MASK_FIRST_BIT(ulMask);
        ulIndex = ((ulMaskIndex<<BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
        break;
    }
    return ulIndex;
}

/* Function : BlockM_setMaskIndex(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
void BlockM_setMaskIndex(hBlockM cthis, blockMType index){
    blockMType ulMaskIndex = 0U;
    blockMType ulMask = 0u, ulBlockMask = 0u;

    ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index));
    ulMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    do{
        /* if blockMMask is unmasked, then set bit */
        if((cthis->blockMMask[ulMaskIndex]&ulMask)){
            break;
        }
        cthis->blockMCounter++;
        cthis->blockMMask[ulMaskIndex] |= ulMask;
        /* if blockMMask is full, then set blockMMaskMask bit */
        ulBlockMask = cthis->blockMMask[ulMaskIndex];
        /* All blockMMask and blockMMaskContinue mask */
        ulBlockMask |= cthis->blockMMaskContinue[ulMaskIndex];
        if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            /* mask not full, directly return. */
            break;
        }
        ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
        ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
        cthis->blockMMaskMask[ulMaskIndex] |= ulMask;
        if(cthis->blockMMaskMask[ulMaskIndex] != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            /* mask not full, directly return. */
            break;
        }
        ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
        ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
        cthis->blockMMaskMaskMask[ulMaskIndex] |= ulMask;
    }while(0);
}

/* Function : BlockM_clearMaskIndex(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
void BlockM_clearMaskIndex(hBlockM cthis, blockMType index){
    blockMType ulMaskIndex = 0U;
    blockMType ulMask = 0u, ulBlockMask = 0u;

    ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index));
    ulMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    ulBlockMask = cthis->blockMMask[ulMaskIndex];
    do{
        if(!(ulBlockMask&ulMask)){
            /* blockMMask not set, directly return. */
            break;
        }
        /* if blockMMask is set, then clear bit */
        cthis->blockMCounter--;
        cthis->blockMMask[ulMaskIndex] &= (~ulMask);
        /* if last blockMMask is full, then clear blockMMaskMask bit */
        /* All blockMMask and blockMMaskContinue mask */
        ulBlockMask |= cthis->blockMMaskContinue[ulMaskIndex];
        if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            /* mask not full, directly return. */
            break;
        }
        ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
        ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
        ulBlockMask = cthis->blockMMaskMask[ulMaskIndex];
        cthis->blockMMaskMask[ulMaskIndex] &= (~ulMask);
        if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            /* mask not full, directly return. */
            break;
        }
        ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
        ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
        cthis->blockMMaskMaskMask[ulMaskIndex] &= (~ulMask);
    }while(0);
}

/* Function : BlockM_findContinueMinIndex(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
static inline void BlockM_maskContinue(hBlockM cthis,blockMType *ulBlockMask,
    blockMType *ulIndex, uint16 *uwCountResidue, uint16 count, blockMType uwGroupIndex){
    blockMType ulMaskIndex = 0U;
    blockMType ulMask = 0u, ulContinueMask = 0u;
    uint16 uwShift = 0u;

    /* get mask first bit, and calculate start index */
    ulMask = *ulBlockMask;
    ulMask = ~ulMask;
    ulMask = MASK_FIRST_BIT(ulMask);
    ulMaskIndex = log_2n(ulMask);
    if(*uwCountResidue == count){
        *ulIndex = (ulMaskIndex + (uwGroupIndex * (sizeof(blockMType)<<3u)));
        if(((*ulIndex) + count) > cthis->blockMMax){
            /* Overflow, judge index maxCount. */
            *ulIndex = cthis->blockMMax;
        }
    }
    /* calculate continue, and try to match */
    ulContinueMask = BLOCKM_BITINDEX_MASK(ulMaskIndex);
    ulContinueMask = MASK_BIT_UP_IN_FULL(ulContinueMask);
    if(((sizeof(blockMType)<<3u) - ulMaskIndex) >= (*uwCountResidue)){
        uwShift = (uint16)(((sizeof(blockMType)<<3u) - ulMaskIndex) - (*uwCountResidue));
        ulContinueMask = ((ulContinueMask << uwShift) >> uwShift);
        *uwCountResidue = 0u;
    }else{
        /* find residue blank */
        *uwCountResidue = (uint16)(*uwCountResidue-((sizeof(blockMType)<<3u)-ulMaskIndex));
    }

    /* return residue mask */
    ulMask = ((*ulBlockMask) & ulContinueMask);
    if(ulMask){
        *uwCountResidue = count; /* if not match, reset match count */
        ulMask = (ulMask|(ulMask-1u)); /* mask lower bits */
    }else{/* match */
        ulMask = (ulContinueMask|(ulContinueMask-1u)); /* mask lower bits */
    }
    *ulBlockMask = (ulMask|(*ulBlockMask)); /* calculate residue unmasked bits, and return mask */
}
blockMType BlockM_findContinueMinIndex(hBlockM cthis, uint16 count){
    blockMType ulIndex = cthis->blockMMax;
    blockMType ulMaskIndex = 0U;
    uint16 uwCountResidue = 0U;
    blockMType ulMask = 0u;
    blockMType i = 0u, j = 0u, k = 0u;
    uint8 ucBlankFound = FALSE;

    uwCountResidue = count;
    /* search cthis->blockMMaskMaskMask */
    for(i = 0; i < cthis->blockMMaskMaskMaskMax; i++){
        ulMask = cthis->blockMMaskMaskMask[i];
        /* if blockMMaskMaskMask full, then continue */
        if(ulMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            continue;
        }
        /* find unmasked blockMMaskMask index */
        ulMask = (~ulMask);
        ulMask = MASK_FIRST_BIT(ulMask);
        ulMaskIndex = ((i << BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
        if(ulMaskIndex >= cthis->blockMMax){
            /* Overflow return */
            break;
        }
        /* search cthis->blockMMaskMask */
        for(j = ulMaskIndex; j < ((sizeof(blockMType)<<3u) + (i<<BLOCKMCFG_MANAG_TYPE_BITS)); j++){
            ulMask = cthis->blockMMaskMask[j];
            /* if blockMMaskMask full, then continue */
            if(ulMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                continue;
            }
            /* find unmasked blockMMask/blockMMaskContinue index */
            ulMask = (~ulMask);
            ulMask = MASK_FIRST_BIT(ulMask);
            ulMaskIndex = ((j<<BLOCKMCFG_MANAG_TYPE_BITS) + log_2n(ulMask));
            /* search cthis->blockMMask */
            for(k = ulMaskIndex; k < ((sizeof(blockMType)<<3u) + (j<<BLOCKMCFG_MANAG_TYPE_BITS)); k++){
                if(uwCountResidue < count){
                    /* residue blank not start from next mask start bit, refind. */
                    if(cthis->blockMMask[k]&1u){
                        uwCountResidue = count;
                    }
                }
                /* All blockMMask and blockMMaskContinue mask */
                ulMask = (cthis->blockMMask[k]|cthis->blockMMaskContinue[k]);
                do{
                    BlockM_maskContinue(cthis,&ulMask,&ulIndex,&uwCountResidue,count,k);
                    if(!uwCountResidue){
                        ucBlankFound = TRUE;
                        break;
                    }
                }while(ulMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK);
                /* blank found, return */
                if(ucBlankFound){
                    break;
                }
            }

            if(uwCountResidue && (uwCountResidue < count)){
                /* residue blank not start from next mask start bit, refind. */
                if(cthis->blockMMask[k]&1u){
                    uwCountResidue = count;
                }
            }
            if(ucBlankFound){
                break;
            }
        }
        if(ucBlankFound){
            break;
        }
    }
    if(ucBlankFound == FALSE){
        ulIndex = cthis->blockMMax;
    }
    return ulIndex;
}

/* Function : BlockM_setContinueMaskIdex(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
void BlockM_setContinueMaskIndex(hBlockM cthis, blockMType index, uint16 count){
    blockMType ulStartMaskIndex = 0U, ulMaskIndex = 0U;
    uint16 uwCountResidue = 0U, uwCountSet = 0U, uwShift = 0U;
    blockMType ulMask = 0u, ulContinueMask = 0U;

    uwCountSet = (uint16)((sizeof(blockMType)<<3u)-BLOCKM_INDEX_BITINDEX(index));
    ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index));
    ulStartMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    ulMaskIndex = ulStartMaskIndex;
    if(!(cthis->blockMMask[ulMaskIndex]&ulMask)){
        /* set blockMMask bit */
        cthis->blockMMask[ulMaskIndex] |= ulMask;
    }
    uwCountResidue = count;
    while(uwCountResidue){
        /* if continue mask set, return */
        if(cthis->blockMMaskContinue[ulMaskIndex]&ulMask){
            break;
        }
        /* calculate continue mask */
        if(uwCountResidue == count){
            uwShift = 0U;
            if(uwCountSet >= count){
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
        cthis->blockMMaskContinue[ulMaskIndex] |= ulContinueMask;
        ulMask = (cthis->blockMMask[ulMaskIndex]|cthis->blockMMaskContinue[ulMaskIndex]); /* All blockMMask and blockMMaskContinue mask */
        if(ulMask == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
            ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
            ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
            cthis->blockMMaskMask[ulMaskIndex] |= ulMask;
            if(cthis->blockMMaskMask[ulMaskIndex] == BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
                ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
                cthis->blockMMaskMaskMask[ulMaskIndex] |= ulMask;
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
        ulStartMaskIndex++;
        ulMaskIndex = ulStartMaskIndex;
    }
}

/* Function : BlockM_clearContinueMaskIndex(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
typedef enum{
    CLEAR_BEGIN,
    CLEAR_CONTINUE,
    CLREA_END
} teClearContinueStep;
void BlockM_clearContinueMaskIndex(hBlockM cthis, blockMType index){
    blockMType uwStartMaskIndex = 0U, ulMaskIndex = 0U, ulIndex = 0U;
    blockMType ulMask = 0u, ulContinueMask = 0U, ulBlockMask = 0u;
    teClearContinueStep teClearStep = CLEAR_BEGIN;

    ulIndex = (index&BLOCKMCFG_MANAG_TYPE_MASK);
    ulMask = BLOCKM_BITINDEX_MASK(ulIndex);
    uwStartMaskIndex = BLOCKM_INDEX_MASKINDEX(index);
    ulMaskIndex = uwStartMaskIndex;
    ulBlockMask = cthis->blockMMask[ulMaskIndex];
    if(ulBlockMask&ulMask){
        /* clear blockMMask bit */
        cthis->blockMMask[ulMaskIndex] &= (~ulMask);
    }
    while(ulMask){
        switch(teClearStep){
        case CLEAR_BEGIN:
            do{
                ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
                /* mask cleared, directly return. */
                if(!(ulBlockMask&ulMask)){
                    teClearStep = CLREA_END;
                    break;
                }
                /* get continue mask up and unmasked ulBlockMask(used to continue mask) */
                ulContinueMask = MASK_BIT_UP_IN_FULL(ulMask);
                ulBlockMask = (~cthis->blockMMask[ulMaskIndex]); /* include continue mask */
                ulMask = (ulBlockMask&ulContinueMask); /* find continue mask exclude low unmasked bit */
                if(ulMask != ulContinueMask){
                    /* mask clear, return */
                    ulMask = ((~ulMask)&ulContinueMask);
                    ulMask = MASK_FIRST_BIT(ulMask); /* find blockMMask upper first masked bit */
                    ulContinueMask = (ulContinueMask&MASK_BIT_DOWN_FULL(ulMask));
                    ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
                    ulContinueMask = (ulContinueMask&ulBlockMask); /* find real continue mask */
                    cthis->blockMMaskContinue[ulMaskIndex] &= (~ulContinueMask); /* clear blockMMaskContinue continue mask */
                    ulMask = MASK_HIGH_FIRST_BIT(ulContinueMask); /* get high bit and calculate count */
                    ulIndex = (log_2n(ulMask)+1u-ulIndex);
                    if(cthis->blockMCounter >= ulIndex){
                        cthis->blockMCounter -= ulIndex;
                    }else{
                        cthis->blockMCounter = 0u;
                    }
                    teClearStep = CLREA_END;
                    break;
                }
                ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
                ulContinueMask = (ulContinueMask&ulBlockMask); /* find real continue mask */
                cthis->blockMMaskContinue[ulMaskIndex] &= (~ulContinueMask);
                if(ulMask != ulContinueMask){
                    /* ulContinueMask not full, clear and return */
                    ulMask = MASK_HIGH_FIRST_BIT(ulContinueMask); /* get high bit and calculate count */
                    ulIndex = (log_2n(ulMask)+1u-ulIndex);
                    if(cthis->blockMCounter >= ulIndex){
                        cthis->blockMCounter -= ulIndex;
                    }else{
                        cthis->blockMCounter = 0u;
                    }
                    teClearStep = CLREA_END;
                    break;
                }
                /* ulContinueMask full, continue to find next mask */
                if(cthis->blockMCounter >= ((sizeof(blockMType)<<3u)-ulIndex)){
                    cthis->blockMCounter -= ((sizeof(blockMType)<<3u)-ulIndex);
                }else{
                    cthis->blockMCounter = 0u;
                }
                teClearStep = CLEAR_CONTINUE;
            }while(0);
            /* clear mask */
            do{
                ulBlockMask |= cthis->blockMMask[ulMaskIndex]; /* All blockMMask and blockMMaskContinue mask */
                if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                    /* not full, directly break. */
                    break;
                }
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
                ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
                ulBlockMask = cthis->blockMMaskMask[ulMaskIndex];
                cthis->blockMMaskMask[ulMaskIndex] &= (~ulMask);
                if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                    /* not full, directly break. */
                    break;
                }
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
                ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
                cthis->blockMMaskMaskMask[ulMaskIndex] &= (~ulMask);
            }while(0);
            uwStartMaskIndex++;
            ulMaskIndex = uwStartMaskIndex;
            ulMask = BLOCKMCFG_MANAG_TYPE_FULL_MASK;
            break;
        case CLEAR_CONTINUE:
            do{
                ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
                /* mask cleared, directly return. */
                if(!(ulBlockMask&1u)){
                    teClearStep = CLREA_END;
                    break;
                }
                ulBlockMask = (~cthis->blockMMask[ulMaskIndex]);
                ulContinueMask = ulMask;
                ulMask = (ulBlockMask&ulContinueMask); /* find continue mask */
                if(ulMask != ulContinueMask){
                    /* mask clear, return */
                    if(ulBlockMask&1u){
                        ulMask = (ulMask&cthis->blockMMaskContinue[ulMaskIndex]); /* find continue mask exclude higher bit */
                        ulMask = (~ulMask);
                        ulMask = MASK_FIRST_BIT(ulMask); /* find continue higher bit */
                        ulContinueMask = MASK_BIT_DOWN_FULL(ulMask); /* find continue mask */
                        ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
                        cthis->blockMMaskContinue[ulMaskIndex] &= (~ulContinueMask);
                        ulIndex = log_2n(ulMask);
                        if(cthis->blockMCounter >= ulIndex){
                            cthis->blockMCounter -= ulIndex;
                        }else{
                            cthis->blockMCounter = 0u;
                        }
                    }
                    teClearStep = CLREA_END;
                    break;
                }
                /* continue to find next mask */
                ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
                ulContinueMask = (ulContinueMask&ulBlockMask); /* find real continue mask */
                cthis->blockMMaskContinue[ulMaskIndex] &= (~ulContinueMask);
                if(ulMask != ulContinueMask){
                    /* ulContinueMask not full, clear and return */
                    ulMask = MASK_HIGH_FIRST_BIT(ulContinueMask); /* get high bit and calculate count */
                    ulIndex = (log_2n(ulMask)+1u);
                    if(cthis->blockMCounter >= ulIndex){
                        cthis->blockMCounter -= ulIndex;
                    }else{
                        cthis->blockMCounter = 0u;
                    }
                    teClearStep = CLREA_END;
                    break;
                }
                /* ulContinueMask full, continue to find next mask */
                if(cthis->blockMCounter >= (sizeof(blockMType)<<3u)){
                    cthis->blockMCounter -= (sizeof(blockMType)<<3u);
                }else{
                    cthis->blockMCounter = 0u;
                }
                teClearStep = CLEAR_CONTINUE;
            }while(0);
            /* clear mask */
            do{
                ulBlockMask |= cthis->blockMMask[ulMaskIndex]; /* All blockMMask and blockMMaskContinue mask */
                if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                    /* not full, directly break. */
                    break;
                }
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
                ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
                ulBlockMask = cthis->blockMMaskMask[ulMaskIndex];
                cthis->blockMMaskMask[ulMaskIndex] &= (~ulMask);
                if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                    /* not full, directly break. */
                    break;
                }
                ulMask = BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(ulMaskIndex));
                ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulMaskIndex);
                cthis->blockMMaskMaskMask[ulMaskIndex] &= (~ulMask);
            }while(0);
            uwStartMaskIndex++;
            ulMaskIndex = uwStartMaskIndex;
            ulMask = BLOCKMCFG_MANAG_TYPE_FULL_MASK;
            break;
        case CLREA_END:
            ulMask = 0u;
            break;
        default:
            ulMask = 0u;
            break;
        }
    }
}

/* Function : BlockM_isPointerSet(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
uint8 BlockM_isPointerSet(hBlockM cthis, void *pointer){
    uint8 ucRet = FALSE;
    blockMType ulIndex = cthis->getIndex(cthis,pointer);

    if(ulIndex < cthis->blockMMax){
        ucRet = cthis->isIndexSet(cthis,ulIndex);
    }
    return ucRet;
}

/* Function : BlockM_isIndexSet(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
uint8 BlockM_isIndexSet(hBlockM cthis, blockMType index){
    uint8 ucRet = FALSE;
    blockMType ulIndex = 0u;

    if(index<cthis->blockMMax){
        ulIndex = BLOCKM_INDEX_MASKINDEX(index);
        if(cthis->blockMMask[ulIndex]
        & BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index))){
            ucRet = TRUE;
        }
    }
    return ucRet;
}

/* Function : BlockM_isIndexContinueSet(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
uint8 BlockM_isIndexContinueSet(hBlockM cthis, blockMType index){
    uint8 ucRet = FALSE;
    blockMType ulIndex = 0u;

    if(index<cthis->blockMMax){
        ulIndex = BLOCKM_INDEX_MASKINDEX(index);
        if((cthis->blockMMask[ulIndex]
        & cthis->blockMMaskContinue[ulIndex])
        & BLOCKM_BITINDEX_MASK(BLOCKM_INDEX_BITINDEX(index))){
            ucRet = TRUE;
        }
    }
    return ucRet;
}

/* Function : BlockM_isFull(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
uint8 BlockM_isFull(hBlockM cthis){
    uint8 ucRet = FALSE;

    if(cthis->blockMCounter < cthis->blockMMax){
        ucRet = TRUE;
    }
    return ucRet;
}

/* Function : BlockM_getSize(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
typedef enum{
    GET_SIZE_BEGIN,
    GET_SIZE_CONTINUE,
    GET_SIZE_END
} TE_GET_SIZE_STEP;
uint16 BlockM_getSize(hBlockM cthis, void *pointer){
    uint16 uwSize = 0u;
    blockMType ulIndex = 0u, ulMaskIndex = 0U;
    blockMType ulMask = 0u, ulBlockMask = 0u;
    TE_GET_SIZE_STEP teGetStep = GET_SIZE_BEGIN;

    ulIndex = cthis->getIndex(cthis,pointer);
    if(ulIndex >= cthis->blockMMax){
        teGetStep = GET_SIZE_END;
    }
    ulMaskIndex = BLOCKM_INDEX_MASKINDEX(ulIndex);
    ulIndex = BLOCKM_INDEX_BITINDEX(ulIndex);
    ulMask = BLOCKM_BITINDEX_MASK(ulIndex);
    do{
        switch(teGetStep){
        case GET_SIZE_BEGIN:
            do{
                /* if blockMMask unmasked, return */
                if(!(cthis->blockMMask[ulMaskIndex]&ulMask)){
                    teGetStep = GET_SIZE_END;
                    break;
                }
                /* if blockMMaskContinue unmasked, return size 1 */
                if(!(cthis->blockMMaskContinue[ulMaskIndex]&ulMask)){
                    uwSize = 1u;
                    teGetStep = GET_SIZE_END;
                    break;
                }
                ulMask = MASK_BIT_UP_FULL(ulMask);
                //ulBlockMask = (cthis->blockMMask[ulMaskIndex]&ulMask);
                ulBlockMask = cthis->blockMMask[ulMaskIndex];
                ulBlockMask &= ulMask;
                if(ulBlockMask){
                    /* if blockMMask has another index, then pointer size in current mask */
                    ulBlockMask = MASK_FIRST_BIT(ulBlockMask);
                    ulBlockMask = MASK_BIT_DOWN_FULL(ulBlockMask);
                    ulBlockMask = (ulBlockMask&ulMask); /* mask between two masked bit in blockMMask */
                    if((ulBlockMask&cthis->blockMMaskContinue[ulMaskIndex])!=ulBlockMask){
                        /* mask is not full between two masked bit, and unmasked those */
                        ulBlockMask = (ulBlockMask&cthis->blockMMaskContinue[ulMaskIndex]);
                    }
                    ulMask &= (~ulBlockMask);
                    if(ulMask){
                        ulMask = MASK_FIRST_BIT(ulMask);
                        uwSize = (uint16)(log_2n(ulMask)-ulIndex);
                    }else{
                        uwSize = (uint16)((sizeof(blockMType)<<3u)-ulIndex);
                    }
                    teGetStep = GET_SIZE_END;
                    break;
                }
                /* if(!ulBlockMask) */
                ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
                ulBlockMask &= ulMask;
                if(ulBlockMask != ulMask){
                    /* if blockMMaskContinue is not full, then pointer size in current mask */
                    ulBlockMask = ((~ulBlockMask)&ulMask);
                    if(ulBlockMask){
                        ulMask = MASK_FIRST_BIT(ulBlockMask);
                        uwSize = (uint16)(log_2n(ulMask)-ulIndex);
                    }else{
                        uwSize = (uint16)((sizeof(blockMType)<<3u)-ulIndex);
                    }
                    teGetStep = GET_SIZE_END;
                    break;
                }
                /* continue to find pointer size in current and next mask */
                uwSize = (uint16)((sizeof(blockMType)<<3u)-ulIndex);
                ulMaskIndex++;
                teGetStep = GET_SIZE_CONTINUE;
            }while(0);
            break;
        case GET_SIZE_CONTINUE:
            ulBlockMask = cthis->blockMMaskContinue[ulMaskIndex];
            while((ulBlockMask&1u) && (!(cthis->blockMMask[ulMaskIndex]&1u))){
                if(cthis->blockMMask[ulMaskIndex]){
                    /* find end */
                    ulMask = MASK_FIRST_BIT(cthis->blockMMask[ulMaskIndex]);
                    ulMask = MASK_BIT_DOWN_FULL(ulMask);
                    ulBlockMask = (ulMask&ulBlockMask); /* mask from 0 to masked bit in blockMMask */
                    ulBlockMask = (~ulBlockMask);
                    ulMask = MASK_FIRST_BIT(ulBlockMask); /* first unmasked bit */
                    uwSize += log_2n(ulMask);
                    break;
                }
                /* if(!cthis->blockMMask[ulMaskIndex]) */
                if(ulBlockMask != BLOCKMCFG_MANAG_TYPE_FULL_MASK){
                    /* find end */
                    ulBlockMask = (~ulBlockMask);
                    ulMask = MASK_FIRST_BIT(ulBlockMask);
                    uwSize += log_2n(ulMask);
                    break;
                }
                /* continue to find */
                uwSize += (sizeof(blockMType)<<3u);
                ulMaskIndex++;
            }
            teGetStep = GET_SIZE_END;
            break;
        case GET_SIZE_END:
            break;
        default:
            teGetStep = GET_SIZE_END;
            break;
        }
    }while(teGetStep != GET_SIZE_END);

    return uwSize;
}

/* Function : BlockM_getIndex(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
blockMType BlockM_getIndex(hBlockM cthis, void *pointer){
    blockMType ulIndex = cthis->blockMMax;

    if((uint8*)pointer >= cthis->blockMPointer){
        ulIndex = ((blockMType)((uint8*)pointer-cthis->blockMPointer)/cthis->blockMSize);
    }
    return ulIndex;
}

/* Function : BlockM_getAddr(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
void* BlockM_getAddr(hBlockM cthis, blockMType index){
    return (void*)(cthis->blockMPointer + (((blockMType)cthis->blockMSize) * index));
}

/* Function : BlockM_getCounts(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
blockMType BlockM_getCounts(hBlockM cthis){
    return cthis->blockMCounter;
}

/* Function : BlockM_getMax(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   :
 * Others   : BlockM class function.
 **********************************************/
blockMType BlockM_getMax(hBlockM cthis){
    return cthis->blockMMax;
}

/* Function : hBlockM BlockM_init(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   : hBlockM - cthis/OOPC_NULL
 * Others   : BlockM class initial function.
 **********************************************/
hBlockM BlockM_init(hBlockM cthis, uint8 *blockMSpace, uint16 blockMSize, blockMType blockMMax){
    blockMType ulMaskIndex = 0U;
    blockMType i = 0U;

    /* Configure functions. */

    /* Configure parameters. */
    cthis->blockMSpace = blockMSpace;
    cthis->blockMSize = blockMSize;
    cthis->blockMMax = blockMMax;

    ulMaskIndex = (cthis->blockMMax>>BLOCKMCFG_MANAG_TYPE_BITS);
    if(cthis->blockMMax&BLOCKMCFG_MANAG_TYPE_MASK){
        ulMaskIndex++;
    }
    cthis->blockMMaskMax = ulMaskIndex;
    ulMaskIndex = (cthis->blockMMaskMax>>BLOCKMCFG_MANAG_TYPE_BITS);
    if(cthis->blockMMaskMax&BLOCKMCFG_MANAG_TYPE_MASK){
        ulMaskIndex++;
    }
    cthis->blockMMaskMaskMax = ulMaskIndex;
    ulMaskIndex = (cthis->blockMMaskMaskMax>>BLOCKMCFG_MANAG_TYPE_BITS);
    if(cthis->blockMMaskMaskMax&BLOCKMCFG_MANAG_TYPE_MASK){
        ulMaskIndex++;
    }
    cthis->blockMMaskMaskMaskMax = ulMaskIndex;

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

/* Function : hBlockM BlockM_ctor(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   : hBlockM - cthis/OOPC_NULL
 * Others   : BlockM class constructor.
 **********************************************/
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
    cthis->isIndexContinueSet = BlockM_isIndexContinueSet;
    cthis->isFull = BlockM_isFull;
    cthis->getSize = BlockM_getSize;
    cthis->getIndex = BlockM_getIndex;
    cthis->getAddr = BlockM_getAddr;
    cthis->getCounts = BlockM_getCounts;
    cthis->getMax = BlockM_getMax;

    /* Configure parameters. */
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

/* Function : hBlockM BlockM_dtor(hBlockM cthis)
 * Input    : cthis - BlockM class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : BlockM class destructor.
 **********************************************/
CD(BlockM){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
