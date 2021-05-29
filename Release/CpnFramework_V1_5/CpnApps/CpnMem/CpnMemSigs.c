/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:39:10
 * Description  : CpnMem component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnMemSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "./CpnMemCfg.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "stdio.h"

/***********************************************************
 * CpnMem class definition.
 **********************************************************/
/* CpnMem class.
 **********************************************/
#define MEM_BLOCK_MANAG_NUM    (4u*1024u)
// static uint8 memSpace[BLOCKMCFG_CAL_ALL_MASK_SIZE(MEM_BLOCK_MANAG_NUM)+(MEM_BLOCK_MANAG_NUM*sizeof(uint32))];
static uint8 memSpace[BLOCKMCFG_CAL_MANAGE_SIZE(uint32,MEM_BLOCK_MANAG_NUM)];
static BlockM clBlockM;

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnMem_init(void){
    // CNNP(CpnMem,&clCpnMem);
    // if(OPRS(clCpnMem) != NULL){
    //     initTaskParam taskParam;
    //     taskParam.level = level1;
    //     taskParam.t = taskCpnMem;
    //     taskParam.prdTick = 11*MS_T;
    //     taskParam.startTick = 5*MS_T;
    //     clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnMem_addTask, (uint8*)&taskParam);
    // }
    CN(BlockM,&clBlockM,memSpace,sizeof(uint32),MEM_BLOCK_MANAG_NUM);
    if(OPRS(clBlockM) != OOPC_NULL){
        ;
    }
}

/* memMalloc Service.
 **********************************************/
void serv_CpnMem_memMalloc(void *buff){
    hTS_MEM_POINTER memPointer = (hTS_MEM_POINTER)buff;
    if(memPointer->indication){
        memPointer->pointer = clBlockM.malloc(clBlockM.self, memPointer->indication);
    }
}
/* memFree Service.
 **********************************************/
void serv_CpnMem_memFree(void *buff){
    uint16 uwOpRes = OOPC_FALSE;

    if(buff){
        uwOpRes = clBlockM.free(clBlockM.self, buff);
        if(uwOpRes == OOPC_FALSE){
            /* dispose error */
        }
    }
}
/* isPointerSet Service.
 **********************************************/
void serv_CpnMem_isPointerSet(void *buff){
    hTS_MEM_POINTER memPointer = (hTS_MEM_POINTER)buff;
    memPointer->indication = clBlockM.isPointerSet(clBlockM.self, memPointer->pointer);
}
/* getSize Service.
 **********************************************/
void serv_CpnMem_getSize(void *buff){
    hTS_MEM_POINTER memPointer = (hTS_MEM_POINTER)buff;
    memPointer->indication = clBlockM.getSize(clBlockM.self, memPointer->pointer);
}
/* getIndex Service.
 **********************************************/
void serv_CpnMem_getIndex(void *buff){
    hTS_MEM_POINTER memPointer = (hTS_MEM_POINTER)buff;
    memPointer->indication = clBlockM.getIndex(clBlockM.self, memPointer->pointer);
}
/* memStatus Service.
 **********************************************/
void serv_CpnMem_memStatus(void *buff){
    hBlockM pclBlockM = clBlockM.self;
#define FILE_POINTER  ((FILE *)buff)
#if CPNMEMCFG_DBG_INFO_PRINT_FILE == 0U
#define CPNMEMCFG_MEM_DBG_INFO     printf
#else
#define CPNMEMCFG_MEM_DBG_INFO(...)     fprintf(FILE_POINTER, __VA_ARGS__)
#endif
    uint16 i = 0U, j = 0U, ulMaxIndex = 0U;
    static uint16 uwLastCounter = 0u;

//#define POINTER_ALIGN  -8lX

    /* mask */
    CPNMEMCFG_MEM_DBG_INFO("\n___________________________________________\nBasic BlockM message as follow:\n");
    CPNMEMCFG_MEM_DBG_INFO("blockMSpace:0x%-8lX  blockMPointer:0x%-8lX  blockMSize:%u  blockMMax:%u  blockMCounter:%u\n",
            pclBlockM->blockMSpace,pclBlockM->blockMPointer,pclBlockM->blockMSize,pclBlockM->blockMMax,pclBlockM->blockMCounter);
    i = (pclBlockM->blockMCounter>uwLastCounter)?((pclBlockM->blockMCounter-uwLastCounter)):(uwLastCounter-pclBlockM->blockMCounter);
    uwLastCounter=pclBlockM->blockMCounter;
    CPNMEMCFG_MEM_DBG_INFO("blockMMaskMaskMaskMax:%u  blockMMaskMaskMax:%u  blockMMaskMax:%u  blockMMax:%u  blockMCounterDiff:%u\n",
            pclBlockM->blockMMaskMaskMaskMax,pclBlockM->blockMMaskMaskMax,pclBlockM->blockMMaskMax,pclBlockM->blockMMax,i);

    /* every mask details */
    CPNMEMCFG_MEM_DBG_INFO("\nEvery blockMMaskMaskMask detail as follow:\n");
    for(i = 0U; i < pclBlockM->blockMMaskMaskMaskMax; i++){
        CPNMEMCFG_MEM_DBG_INFO("[%u]:0x%-8lX ", i, pclBlockM->blockMMaskMaskMask[i]);
        if((i&0x1FU)==0x1FU){
            CPNMEMCFG_MEM_DBG_INFO("\n");
        }
    }
    CPNMEMCFG_MEM_DBG_INFO("\nEvery blockMMaskMask detail as follow:\n");
    for(i = 0U; i < pclBlockM->blockMMaskMaskMax; i++){
        CPNMEMCFG_MEM_DBG_INFO("[%u]:0x%-8lX ", i, pclBlockM->blockMMaskMask[i]);
        if((i&0x1FU)==0x1FU){
            CPNMEMCFG_MEM_DBG_INFO("\n");
        }
    }
    CPNMEMCFG_MEM_DBG_INFO("\nEvery blockMMask detail as follow:\n");
    i = 0U;
    while(i<pclBlockM->blockMMaskMax){
        ulMaxIndex = (i+8u);
        if(ulMaxIndex>pclBlockM->blockMMaskMax){
            ulMaxIndex = pclBlockM->blockMMaskMax;
        }
        for(j = i; j < ulMaxIndex; j++){
            CPNMEMCFG_MEM_DBG_INFO("[%u]:0x%-8lX ", j, pclBlockM->blockMMask[j]);
        }
        CPNMEMCFG_MEM_DBG_INFO("\n");
        for(j = i; j < ulMaxIndex; j++){
            CPNMEMCFG_MEM_DBG_INFO("[%u]:0x%-8lX ", j, pclBlockM->blockMMaskContinue[j]);
        }
        CPNMEMCFG_MEM_DBG_INFO("\n");
        i = ulMaxIndex;
    }
    CPNMEMCFG_MEM_DBG_INFO("___________________________________________\n");
}

/* Interface trigger.
 **********************************************/
//void trig_CpnMem_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
// void taskCpnMem(void){}

/**************************** Copyright(C) pxf ****************************/
