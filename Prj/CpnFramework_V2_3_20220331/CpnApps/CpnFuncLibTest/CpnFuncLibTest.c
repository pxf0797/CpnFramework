/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFuncLibTest.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/11/03 14:55:04
 * Description  : CpnFuncLibTest class functions definition source file.
 * Others       :
 * History      : 20211103 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnFuncLibTest.h"
#include "RteSigs.h"
#include "stdio.h"
#include "string.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
/* CRC test */
#define  CRC_TYPE_NUM_T  6
Crc clCrcT[CRC_TYPE_NUM_T];
#define TEST_BYTE_NUM          8U
#define TEST_BYTE_NUM2         8U
uint8 ucCrcData[TEST_BYTE_NUM] = {0x12,0x23,0x34,0x45,0x56,0x78,0x89,0x90};
uint8 ucCrcData2[TEST_BYTE_NUM2] = {0x48,0xc4,0x2c,0xa2,0x6a,0x1e,0x91,0x09};
uint32 crcRestult[4][CRC_TYPE_NUM_T];

/* RBTree test */
#define TEST_ALL_SITUTAITON    FALSE//TRUE
#define RBTREE_STORE_NUM       250u//8u//30u//60u//120u//250u
static RBTree clRBTree;
static uint8 rbSpace[RED_BLACK_MANA_SIZE(RBTREE_STORE_NUM)];
typedef struct {
    uint16 index;
    uint32 data;
} tsRBBlock, *htsRBBlock;
rbType get_rbOrder(void *block){
    return (rbType)(((htsRBBlock)block)->index);
}
blockMType nodeLen = 0u;
static htsRBNode nodes[20000/*RBTREE_STORE_NUM<<4*/];
static htsRBNode fifoNodes[RBTREE_STORE_NUM];
static uint16 uwAddTestIndex[RBTREE_STORE_NUM];
static uint16 uwDelTestIndex[RBTREE_STORE_NUM];

#define FILE_POINTER  fp
//#define CPNFUNCLIBTEST_DBG_INFO         printf
#define CPNFUNCLIBTEST_DBG_INFO(...)     fprintf(FILE_POINTER, __VA_ARGS__)
static void CpnFuncLibTest_printAddDelIndex(void);

#define TO_STR(s) #s
#define TO_STR_(s) TO_STR(s)
#define TO_FILE_STR(s)  "D:\\CpnFuncLibTest\\"TO_STR(s)"_"TO_STR_(RBTREE_STORE_NUM)".txt"
static FILE *fp;
#define CreadAndOpenFile(test_case) do{\
    fp = fopen(TO_FILE_STR(test_case),"w");\
    CpnFuncLibTest_printAddDelIndex();\
}while(0)
#define CloseFile() do{\
    fclose(fp);\
}while(0)
typedef enum{
    test_case_1,
    test_case_2,
    test_case_3,
    test_case_4,
    test_case_5,
    test_case_6,
    test_case_7,
    test_case_8,
    test_case_9,
    test_case_10,
    test_case_11,
    test_case_12,
    test_case_13,
    test_case_14,
    test_case_15,
    test_case_16,
    test_case_17,
    test_case_18,
    test_case_19,
    test_case_20,
    test_case_21,
    test_case_22,
    test_case_23,
    test_case_24,
    test_case_25,
    test_case_26,
    test_case_27,
    test_case_28,
    test_case_29,
    test_case_30,
    test_case_31,
    test_case_32,
    test_case_33,
    test_case_34,
    test_case_35,
    test_case_36,
    test_case_default
} teRBTreeTestCase;
static teRBTreeTestCase tesCase = test_case_default;
static uint8 ucInitFlg = 3u;

/***********************************************************
 * CpnFuncLibTest class definition.
 **********************************************************/
/* Function : CpnFuncLibTest_run(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_run(hCpnFuncLibTest cthis){
    cthis->rbTreeTest(cthis);
    cthis->skipListTest(cthis);
}

/***********************************************************
 * CpnFuncLibTest class definition.
 **********************************************************/
typedef enum{
    reset_dis,
    reset_en
} teResetEn;
/* Function : void CpnFuncLibTest_upCount()
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_upCount(uint16 *count, uint8 reset, uint16 resetData){
    static uint16 countData = 0u;
    if(reset){
        //*count = resetData;
        countData = resetData;
    }else{
        *count = countData;
        countData++;
    }
}

/* Function : void CpnFuncLibTest_skipInc()
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_skipInc(uint16 *count, uint8 reset, uint16 resetData, uint8 incCount, uint8 skipCount){
    static uint16 countData = 0u;
    static uint8 incCnt = 0u;
    if(reset){
        //*count = resetData;
        countData = resetData;
        incCnt = 0u;
    }else{
        if(skipCount){
            if(incCnt < incCount){
                *count = countData;
            }else{
                incCnt = 0u;
                countData += skipCount;
                *count = countData;
            }
            countData++;
            incCnt++;
        }else{
            *count = countData;
            countData++;
        }
    }
}

typedef enum{
    invert_dis,
    invert_en
} teInvertEn;
typedef enum{
    exchange_dis,
    exchange_en
} teExchangeOrder;
/* Function : void CpnFuncLibTest_addDelInit()
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_addDelInit(uint8 addSkip, uint8 addInc, teExchangeOrder addEx, teInvertEn addInvert,
uint8 deSkip, uint8 delInc, teExchangeOrder delEx, teInvertEn delInvert){
    uint16 i = 0u, j = 0u, firstData = 0u;
    uint8 skipCount = 0u, incCount = 0u;

    if(addEx&&addSkip){
        firstData = addInc;
        skipCount = addInc;
        incCount = addSkip;
    }else{
        firstData = 0u;
        skipCount = addSkip;
        incCount = addInc;
    }
    CpnFuncLibTest_skipInc(&j,reset_en,firstData/*resetData*/,incCount/*incCount*/,skipCount/*skipCount*/);
    for(i = 0u; i < RBTREE_STORE_NUM; i++){
        CpnFuncLibTest_skipInc(&j,reset_dis,firstData,incCount,skipCount);
        if(j >= RBTREE_STORE_NUM){
            /* swap increase and skip. */
            if(addEx&&addSkip){
                firstData = 0u;
                skipCount = addSkip;
                incCount = addInc;
            }else{
                firstData = addInc;
                skipCount = addInc;
                incCount = addSkip;
            }
            CpnFuncLibTest_skipInc(&j,reset_en,firstData,incCount,skipCount);
            CpnFuncLibTest_skipInc(&j,reset_dis,firstData,incCount,skipCount);
        }
        if(addInvert){
            j = (RBTREE_STORE_NUM-1u-j);
        }
        uwAddTestIndex[i] = j;
    }

    if(delEx&&deSkip){
        firstData = delInc;
        skipCount = delInc;
        incCount = deSkip;
    }else{
        firstData = 0u;
        skipCount = deSkip;
        incCount = delInc;
    }
    CpnFuncLibTest_skipInc(&j,reset_en,firstData/*resetData*/,incCount/*incCount*/,skipCount/*skipCount*/);
    for(i = 0u; i < RBTREE_STORE_NUM; i++){
        CpnFuncLibTest_skipInc(&j,reset_dis,firstData,incCount,skipCount);
        if(j >= RBTREE_STORE_NUM){
            /* swap increase and skip. */
            if(delEx&&deSkip){
                firstData = 0u;
                skipCount = deSkip;
                incCount = delInc;
            }else{
                firstData = delInc;
                skipCount = delInc;
                incCount = deSkip;
            }
            CpnFuncLibTest_skipInc(&j,reset_en,firstData,incCount,skipCount);
            CpnFuncLibTest_skipInc(&j,reset_dis,firstData,incCount,skipCount);
        }
        if(delInvert){
            j = (RBTREE_STORE_NUM-1u-j);
        }
        uwDelTestIndex[i] = j;
    }
}

/* Function : void CpnFuncLibTest_addDelInit()
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
static void CpnFuncLibTest_printAddDelIndex(void){
    uint16 i = 0u;

    CPNFUNCLIBTEST_DBG_INFO("\nuwAddTestIndex[]:\n");
    for(i = 0u; i < RBTREE_STORE_NUM; i++){
        CPNFUNCLIBTEST_DBG_INFO(" %-3lu|",uwAddTestIndex[i]);
        if((i&0xFu)==0xFu){
            CPNFUNCLIBTEST_DBG_INFO("\n");
        }
    }

    CPNFUNCLIBTEST_DBG_INFO("\nuwDelTestIndex[]:\n");
    for(i = 0u; i < RBTREE_STORE_NUM; i++){
        CPNFUNCLIBTEST_DBG_INFO(" %-3lu|",uwDelTestIndex[i]);
        if((i&0xFu)==0xFu){
            CPNFUNCLIBTEST_DBG_INFO("\n");
        }
    }
}

/* Function : CpnFuncLibTest_rbTreeTest(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_rbTreeTest(hCpnFuncLibTest cthis){
    static uint16 index = 0u;
    //static uint8 addSkip = 0u,addInc = 0u,delSkip = 0u,delInc = 0u;
    //static teExchangeOrder addEx = exchange_dis, delEx = exchange_dis;
    //static teInvertEn addInvert = invert_dis, delInvert = invert_dis;
    tsMemPointer tsMem;
    htsRBNode rbNode = OOPC_NULL;

    switch(ucInitFlg){
    case 0:/* init */
        #if TEST_ALL_SITUTAITON == TRUE
        /*       inc
         *       |0|1|2|3|
         * skip 0|-|v|-|-|
         *      1|-|v|v|v|
         *      2|-|-|v|v|
         *      3|-|-|-|v|
         * 7
         * to decrease test case, add and del use the same counter, and only exchange invert_dis.
         * when inc=2, exchange_dis; when inc=3, exchange_en;
         */
        ucInitFlg = 1u;
        index = 0u;
        CpnFuncLibTest_addDelInit(addSkip/*addSkip*/,addInc/*addInc*/,exchange_dis,invert_dis,delSkip/*delSkip*/,delInc/*delInc*/,exchange_dis,invert_dis);
        CreadAndOpenFile(test_case_1);
        #else
        ucInitFlg = 1u;
        index = 0u;
        /* random index. */
        switch(tesCase){
        case test_case_1:
            CpnFuncLibTest_addDelInit(0u/*addSkip*/,1u/*addInc*/,exchange_dis,invert_dis,0u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_1);
            break;
        case test_case_2:
            CpnFuncLibTest_addDelInit(0u/*addSkip*/,1u/*addInc*/,exchange_dis,invert_en,0u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_2);
            break;
        case test_case_3:
            CpnFuncLibTest_addDelInit(0u/*addSkip*/,1u/*addInc*/,exchange_en,invert_dis,0u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_3);
            break;
        case test_case_4:
            CpnFuncLibTest_addDelInit(0u/*addSkip*/,1u/*addInc*/,exchange_dis,invert_en,0u/*delSkip*/,1u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_4);
            break;
        case test_case_5:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,1u/*addInc*/,exchange_dis,invert_dis,1u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_5);
            break;
        case test_case_6:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,1u/*addInc*/,exchange_en,invert_dis,1u/*delSkip*/,1u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_6);
            break;
        case test_case_7:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,1u/*addInc*/,exchange_en,invert_en,1u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_7);
            break;
        case test_case_8:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,1u/*addInc*/,exchange_dis,invert_en,1u/*delSkip*/,1u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_8);
            break;
        case test_case_9:
            CpnFuncLibTest_addDelInit(2u/*addSkip*/,2u/*addInc*/,exchange_dis,invert_dis,2u/*delSkip*/,2u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_9);
            break;
        case test_case_10:
            CpnFuncLibTest_addDelInit(2u/*addSkip*/,2u/*addInc*/,exchange_dis,invert_en,2u/*delSkip*/,2u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_10);
            break;
        case test_case_11:
            CpnFuncLibTest_addDelInit(2u/*addSkip*/,2u/*addInc*/,exchange_en,invert_dis,2u/*delSkip*/,2u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_11);
            break;
        case test_case_12:
            CpnFuncLibTest_addDelInit(2u/*addSkip*/,2u/*addInc*/,exchange_en,invert_en,2u/*delSkip*/,2u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_12);
            break;
        case test_case_13:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,3u/*addInc*/,exchange_dis,invert_dis,1u/*delSkip*/,3u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_13);
            break;
        case test_case_14:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,3u/*addInc*/,exchange_dis,invert_en,1u/*delSkip*/,3u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_14);
            break;
        case test_case_15:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,3u/*addInc*/,exchange_en,invert_en,1u/*delSkip*/,3u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_15);
            break;
        case test_case_16:
            CpnFuncLibTest_addDelInit(1u/*addSkip*/,3u/*addInc*/,exchange_en,invert_dis,1u/*delSkip*/,3u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_16);
            break;
        case test_case_17:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_dis,4u/*delSkip*/,4u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_17);
            break;
        case test_case_18:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_en,4u/*delSkip*/,4u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_18);
            break;
        case test_case_19:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_en,4u/*delSkip*/,4u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_19);
            break;
        case test_case_20:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_dis,4u/*delSkip*/,4u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_20);
            break;
        case test_case_21:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_dis,0u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_21);
            break;
        case test_case_22:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_en,0u/*delSkip*/,1u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_22);
            break;
        case test_case_23:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_en,0u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_23);
            break;
        case test_case_24:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_dis,0u/*delSkip*/,1u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_24);
            break;
        case test_case_25:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_dis,1u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_25);
            break;
        case test_case_26:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_en,1u/*delSkip*/,1u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_26);
            break;
        case test_case_27:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_en,1u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_27);
            break;
        case test_case_28:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_dis,1u/*delSkip*/,1u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_28);
            break;
        case test_case_29:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_dis,2u/*delSkip*/,2u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_29);
            break;
        case test_case_30:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_en,2u/*delSkip*/,2u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_30);
            break;
        case test_case_31:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_en,2u/*delSkip*/,2u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_31);
            break;
        case test_case_32:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_dis,2u/*delSkip*/,2u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_32);
            break;
        case test_case_33:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_dis,1u/*delSkip*/,3u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_33);
            break;
        case test_case_34:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_dis,invert_en,1u/*delSkip*/,3u/*delInc*/,exchange_en,invert_dis);
            CreadAndOpenFile(test_case_34);
            break;
        case test_case_35:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_en,1u/*delSkip*/,3u/*delInc*/,exchange_dis,invert_en);
            CreadAndOpenFile(test_case_35);
            break;
        case test_case_36:
            CpnFuncLibTest_addDelInit(4u/*addSkip*/,4u/*addInc*/,exchange_en,invert_dis,1u/*delSkip*/,3u/*delInc*/,exchange_en,invert_en);
            CreadAndOpenFile(test_case_36);
            break;
        default:
            CpnFuncLibTest_addDelInit(0u/*addSkip*/,1u/*addInc*/,exchange_dis,invert_dis,0u/*delSkip*/,1u/*delInc*/,exchange_dis,invert_dis);
            CreadAndOpenFile(test_case_1);
            break;
        }
        #endif
        break;
    case 1:/* add item into RBTree. */
        tsMem.indication = sizeof(tsRBBlock);
        if(index < RBTREE_STORE_NUM){
            clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFuncLibTest_memMalloc, (uint8*)&tsMem);
            if(tsMem.pointer){
                ((htsRBBlock)tsMem.pointer)->index = uwAddTestIndex[index];
                clRBTree.add(clRBTree.self, tsMem.pointer);
                CPNFUNCLIBTEST_DBG_INFO("\naddIndex: %-3lu| addNode: %-3lu|\n",index,uwAddTestIndex[index]);
            }
            /* print tree status. */
            cthis->rbPrintTree(cthis);
        }
        if(++index >= RBTREE_STORE_NUM){
            index = 0u;
            ucInitFlg = 2u;
        }
        break;
    case 2:/* delete item from RBTree. */
        if(index < RBTREE_STORE_NUM){
            /* find block, and delete it. */
            rbNode = clRBTree.find(clRBTree.self, uwDelTestIndex[index]);
            if(rbNode != OOPC_NULL){
                tsMem.pointer = rbNode->block;
                //clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFuncLibTest_memFree, (uint8*)&tsMem);
            }
            /* delete node. */
            clRBTree.del(clRBTree.self, uwDelTestIndex[index]);
            CPNFUNCLIBTEST_DBG_INFO("\ndeteleteIndex: %-3lu| deleteNode: %-3lu|\n",index,uwDelTestIndex[index]);
            /* delete block. */
            if(tsMem.pointer != OOPC_NULL){
                clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFuncLibTest_memFree, (uint8*)&tsMem);
            }
            /* print tree status. */
            cthis->rbPrintTree(cthis);
            if(++index >= RBTREE_STORE_NUM){
                index = 0u;
                ucInitFlg = 0u;//3u;//0u;
                CloseFile();
                #if TEST_ALL_SITUTAITON == TRUE
                if(++tesCase >= 120){
                    ucInitFlg = 3u;
                }
                #else
                if(++tesCase >= test_case_default){
                    ucInitFlg = 3u;
                }
                #endif
            }
        }
        break;
    default:
        break;
    }
}

/* Function : CpnFuncLibTest_rbPrintTree(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_rbPrintTree(hCpnFuncLibTest cthis){
    uint16 depth = 0u;
    blockMType nums = 0u;
    uint16 i = 0u, j = 0u, k = 0u, spaceCnt = 0u;

    depth = clRBTree.depth(clRBTree.self);
    nums = clRBTree.BlockM.getCounts(clRBTree.BlockM.self);
    CPNFUNCLIBTEST_DBG_INFO("\ndepth:[%u] nodes:[%lu]",depth,nums);
    /* print buffer nodes. */
    for(j = 0u; j < 4u; j++){
        if(j == 0u){
            CPNFUNCLIBTEST_DBG_INFO("\nprevious order node in tree:\n");
            clRBTree.preOrder(clRBTree.self,(hhtsRBNode)&nodes);
        }else if(j == 1u){
            CPNFUNCLIBTEST_DBG_INFO("\nmiddle order node in tree:\n");
            clRBTree.midOrder(clRBTree.self,(hhtsRBNode)&nodes);
        }else if(j == 2u){
            CPNFUNCLIBTEST_DBG_INFO("\npost order node in tree:\n");
            clRBTree.postOrder(clRBTree.self,(hhtsRBNode)&nodes);
        }else if(j == 3u){
            CPNFUNCLIBTEST_DBG_INFO("\nred black node in tree:\n");
            clRBTree.rbTreeOrder(clRBTree.self,(hhtsRBNode)&nodes);
        }

        /* print nodes. */
        for(i = 0u; i < nums; i++){
            if(nodes[i]){
                if(RED_BLACK_ISRED(nodes[i])){
                    CPNFUNCLIBTEST_DBG_INFO("_%-3lu|",clRBTree.rbOrder.rbOrder(nodes[i]->block));
                }else{
                    CPNFUNCLIBTEST_DBG_INFO(" %-3lu|",clRBTree.rbOrder.rbOrder(nodes[i]->block));
                }
            }else{
                CPNFUNCLIBTEST_DBG_INFO("     ");
            }
            if((i&0xFu)==0xFu){
                CPNFUNCLIBTEST_DBG_INFO("\n");
            }
        }
    }

    /* get search tree order. */
    clRBTree.sTreeOrder(clRBTree.self,(hhtsRBNode)&nodes,&nodeLen);
    depth = log_2n(nodeLen+1u);
    CPNFUNCLIBTEST_DBG_INFO("\ndepth:[%u] nodes:[%lu]\n",depth,nodeLen);
    j = 1u;
    for(i = 0u; i < nodeLen; i++){
        if(nodes[i]){
            if(RED_BLACK_ISRED(nodes[i])){
                CPNFUNCLIBTEST_DBG_INFO("_%-3lu|",clRBTree.rbOrder.rbOrder(nodes[i]->block));
            }else{
                CPNFUNCLIBTEST_DBG_INFO(" %-3lu|",clRBTree.rbOrder.rbOrder(nodes[i]->block));
            }
        }else{
            CPNFUNCLIBTEST_DBG_INFO("     ");
        }
        /* print space. */
        spaceCnt = ((1u<<(depth-j))-1u);
        if(spaceCnt > (1u<<depth)){spaceCnt = 0u;}
        for(k = 0u; k < spaceCnt; k++){
            CPNFUNCLIBTEST_DBG_INFO("     ");
        }
        if(i == ((1u<<j)-2)){
            j++;
            CPNFUNCLIBTEST_DBG_INFO("\n");
        }
    }
    CPNFUNCLIBTEST_DBG_INFO("\n\n");
}

/* Function : CpnFuncLibTest_skipListTest(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_skipListTest(hCpnFuncLibTest cthis){
    /* TODO */
}

/* Function : CpnFuncLibTest_crcTest(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   :
 * Others   : CpnFuncLibTest class function.
 **********************************************/
void CpnFuncLibTest_crcTest(hCpnFuncLibTest cthis){
    for(uint16 i = 0; i < CRC_TYPE_NUM_T; i++){
        crcRestult[0][i] = clCrcT[i].crcAlgorithm(clCrcT[i].self,ucCrcData,TEST_BYTE_NUM);
        crcRestult[1][i] = clCrcT[i].crc(clCrcT[i].self,ucCrcData,TEST_BYTE_NUM);
        crcRestult[2][i] = clCrcT[i].crcAlgorithm(clCrcT[i].self,ucCrcData2,TEST_BYTE_NUM2);
        crcRestult[3][i] = clCrcT[i].crc(clCrcT[i].self,ucCrcData2,TEST_BYTE_NUM2);
    }
}

/* Function : hCpnFuncLibTest CpnFuncLibTest_init(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   : hCpnFuncLibTest - cthis/OOPC_NULL
 * Others   : CpnFuncLibTest class initial function.
 **********************************************/
hCpnFuncLibTest CpnFuncLibTest_init(hCpnFuncLibTest cthis){
    hCpnFuncLibTest retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        /* Configure functions. */
        //cthis->run = CpnFuncLibTest_run;
        /* TODO */

        /* Configure parameters. */
        /* CRC configure. */
        hCrc opRes = OOPC_NULL;
        CN(Crc, &clCrcT[0], crc_8, 0x07U, 0x00U, 0x00U, invert_yes);
        CN(Crc, &clCrcT[1], crc_8, 0x07U, 0x00U, 0x00U, invert_no);
        CN(Crc, &clCrcT[2], crc_16, 0x1021U, 0x0000U, 0x0000U, invert_yes);
        CN(Crc, &clCrcT[3], crc_16, 0x1021U, 0x0000U, 0x0000U, invert_no);
        CN(Crc, &clCrcT[4], crc_32, 0x04C11DB7UL, 0x0000UL, 0x0000UL, invert_yes);
        CN(Crc, &clCrcT[5], crc_32, 0x04C11DB7UL, 0x0000UL, 0x0000UL, invert_no);
        for(uint16 i = 0U; i < CRC_TYPE_NUM_T; i++){
            opRes = (OPRS(clCrcT[i]));
            if(opRes == OOPC_NULL){
                break;
            }
        }
        /* RBTree configure. */
        CN(RBTree, &clRBTree, rbSpace, RBTREE_STORE_NUM, get_rbOrder);

        /* initial fifo. */
        CN(Fifo, &cthis->Fifo, (uint8*)&fifoNodes, sizeof(fifoNodes), sizeof(htsRBNode));
    }while(0);
    return retRes;
}

/* Function : hCpnFuncLibTest CpnFuncLibTest_ctor(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   : hCpnFuncLibTest - cthis/OOPC_NULL
 * Others   : CpnFuncLibTest class constructor.
 **********************************************/
CC(CpnFuncLibTest){
    hCpnFuncLibTest retRes = cthis;

    do{
        /* specific failure detected */
        /*
        if(condition){
            break;
        }
        */
        cthis->init = CpnFuncLibTest_init;
        cthis->run = CpnFuncLibTest_run;
        cthis->rbTreeTest = CpnFuncLibTest_rbTreeTest;
        cthis->rbPrintTree = CpnFuncLibTest_rbPrintTree;
        cthis->skipListTest = CpnFuncLibTest_skipListTest;
        cthis->crcTest = CpnFuncLibTest_crcTest;

        /* Configure parameters. */
        /* TODO */
    }while(0);
    return retRes;
}

/* Function : hCpnFuncLibTest CpnFuncLibTest_dtor(hCpnFuncLibTest cthis)
 * Input    : cthis - CpnFuncLibTest class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnFuncLibTest class destructor.
 **********************************************/
CD(CpnFuncLibTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
