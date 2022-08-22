/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnMemTest.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:45:13
 * Description  : CpnMemTest class functions definition source files.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnMemTest.h"
#include "RteSigs.h"
#include "stdio.h"
#include "string.h"

/***********************************************************
 * Data type definition.
 **********************************************************/
/* Data definition.
 **********************************************/
extern hBlockM pblockM;
#define MEM_TEST_BUFF_MAX      128U
#define MEM_TEST_BYTE_SIZE     4U
static tsMemPointer memPointer[MEM_TEST_BUFF_MAX];

#define TO_STR(s) #s
//#define TO_FILE_STR(s)  "D:\\CpnMemTest\\"TO_STR(s)"_"__DATE__".txt"
//#define TO_FILE_STR(s)  "D:\\CpnMemTest\\"TO_STR(s)"_"__DATE__"_"__TIME__".txt"
#define TO_FILE_STR(s)  "D:\\CpnMemTest\\"TO_STR(s)".txt"
typedef enum{
    /* big end */
    test_case_0x00_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xFE_0x00,

    test_case_0x00_0xFF_0x5F_0x00,
    test_case_0x00_0xFF_0xAF_0x00,
    test_case_0x00_0xFF_0xF5_0x00,
    test_case_0x00_0xFF_0xFA_0x00,

    test_case_0x00_0xFF_0x3F_0x00,
    test_case_0x00_0xFF_0xCF_0x00,
    test_case_0x00_0xFF_0xF3_0x00,
    test_case_0x00_0xFF_0xFC_0x00,

    test_case_0x00_0xFF_0x1F_0x00,
    test_case_0x00_0xFF_0x8F_0x00,
    test_case_0x00_0xFF_0xF1_0x00,
    test_case_0x00_0xFF_0xF8_0x00,

    test_case_0x00_0xFF_0x3F_0xBF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xCF_0xEF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xF3_0xF7_0xFF_0xFE_0x00,
    test_case_0x00_0xFF_0xFC_0xFD_0xFF_0xFE_0x00,

    test_case_0x00_0xFF_0x3F_sizeAdd1_0xBF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xCF_sizeAdd1_0xEF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xF3_sizeAdd1_0xF7_0xFF_0xFE_0x00,
    test_case_0x00_0xFF_0xFC_sizeAdd1_0xFD_0xFF_0xFE_0x00,

    test_case_0x00_0xFF_0x3F_sizeDoubleAdd1_0xBF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xCF_sizeDoubleAdd1_0xEF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xF3_sizeDoubleAdd1_0xF7_0xFF_0xFE_0x00,
    test_case_0x00_0xFF_0xFC_sizeDoubleAdd1_0xFD_0xFF_0xFE_0x00,

    test_case_0x00_0xFF_0x3F_sizeHalf_0xBF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xCF_sizeHalf_0xEF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_0xF3_sizeHalf_0xF7_0xFF_0xFE_0x00,
    test_case_0x00_0xFF_0xFC_sizeHalf_0xFD_0xFF_0xFE_0x00,

    test_case_0x00_0xFF_inc_0x3F_sizeDoubleAdd1_0xBF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_dec_0xCF_sizeDoubleAdd1_0xEF_0xFF_0x7F_0x00,
    test_case_0x00_0xFF_inc_0xF3_sizeDoubleAdd1_0xF7_0xFF_0xFE_0x00,
    test_case_0x00_0xFF_dec_0xFC_sizeDoubleAdd1_0xFD_0xFF_0xFE_0x00,

    test_case_default
} TE_MEM_TESE_CASE;
static TE_MEM_TESE_CASE te_test_case = test_case_default;
typedef enum{
    test_up,
    test_up2,
    test_up3,
    test_down,
    test_down2,
    test_down3,

    test_null
} TE_TESTING;
TE_TESTING te_testing = test_up;
static uint16 index = 0U;

typedef enum{
    open_file,
    testing,
    close_file,
    finish
} TE_TEST_OPERATION;
static TE_TEST_OPERATION te_test_op = open_file;

static FILE *fp;
#define CreadAndOpenFile(test_case) do{\
    fp = fopen(TO_FILE_STR(test_case),"w");\
}while(0)
#define CloseFile(test_case) do{\
    fclose(fp);\
}while(0)

#define WAIT_TIME_S   10//S
uint16 uwDelayS = 0u;
tick ulWaitTime = 1000*MS_T;
#define INCREASE_DELAYS() do{\
        SYN_TRIG(sig_trig_CpnMemTest_delay, &ulWaitTime); \
        if(IS_TIMEOUT(ulWaitTime)){ \
            ulWaitTime = 1000*MS_T; \
            uwDelayS++; \
        }\
    }while(0)

/*#define OpenAndCloseFile(test_case) do{ \
    if(te_test_op == open_file){ \
            CreadAndOpenFile(test_case); \
            SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp); \
            te_test_op = testing; \
        }else if(te_test_op == close_file){ \
            CloseFile(test_case); \
            te_test_op = finish; \
            te_test_op = open_file; \
            te_testing = test_up; \
            index = 0U; \
            if(te_test_case < test_case_default){ \
                te_test_case++; \
            } \
        }else{} \
}while(0)*/
#define OpenAndCloseFile(test_case) do{ \
    if(te_test_op == open_file){ \
            CreadAndOpenFile(test_case); \
            SYN_TRIG(sig_trig_CpnMemTest_memStatus, &fp); \
            te_test_op = testing; \
            uwDelayS = 0u; \
            ulWaitTime = 1000*MS_T; \
            memset(memPointer,0,sizeof(tsMemPointer)*MEM_TEST_BUFF_MAX);\
        }else if(te_test_op == close_file){ \
            if(uwDelayS >= WAIT_TIME_S){\
                CloseFile(test_case); \
                te_test_op = finish; \
                te_test_op = open_file; \
                te_testing = test_up; \
                index = 0U; \
                if(te_test_case < test_case_default){ \
                    te_test_case++; \
                } \
            }else{\
                INCREASE_DELAYS(); \
            }\
        }else{} \
}while(0)


/*#define CASE_INFO do{\
        printf("\nCurrent case %u is completed!\n", te_test_case);\
    }while(0);*/
#define CASE_INFO

#if 1
void PointerInfo(void){
#define FILE_POINTER  fp
//#if CPNMEMCFG_DBG_INFO_PRINT_FILE == 0U
//#define CPNMEMCFG_MEM_DBG_INFO     printf
//#else
#define CPNMEMCFG_MEM_DBG_INFO(...)     fprintf(FILE_POINTER, __VA_ARGS__)
//#endif

    uint16 i = 0u;
    tsMemPointer dataTempBuf;
    uint32 addrOffset = 0u;

    addrOffset = ADDR_VALUE(pblockM->blockMPointer);
    CPNMEMCFG_MEM_DBG_INFO("testing:%d  index:%d\nBasic Address:0x%lX\nEvery pointer detail as follow:\n",te_testing,index,addrOffset);
    for(i = 0u; i < MEM_TEST_BUFF_MAX; i++){
        dataTempBuf.pointer = memPointer[i].pointer;
        SYN_TRIG(sig_trig_CpnMemTest_isPointerSet, &dataTempBuf);
        if(dataTempBuf.pointer){addrOffset = (uint32)((uint8*)dataTempBuf.pointer-pblockM->blockMPointer);}else{addrOffset = 0u;}
        CPNMEMCFG_MEM_DBG_INFO("[%-3u]:0x%-4lX isSet:%lu ", i, addrOffset, dataTempBuf.indication);
        SYN_TRIG(sig_trig_CpnMemTest_getIndex, &dataTempBuf);
        CPNMEMCFG_MEM_DBG_INFO("index:%-5lu ", dataTempBuf.indication);
        SYN_TRIG(sig_trig_CpnMemTest_getSize, &dataTempBuf);
        CPNMEMCFG_MEM_DBG_INFO("size:%-2lu  ", dataTempBuf.indication);
        if((i&0x3u)==0x3u){
            CPNMEMCFG_MEM_DBG_INFO("\n");
        }
//        if(i==126){
//            dataTempBuf.indication=i;
//        }
    }
    //CPNMEMCFG_MEM_DBG_INFO("\n");
}
#else
/*#define PointerInfo()  /\
/*/
void PointerInfo(void){
#define FILE_POINTER  fp
//#if CPNMEMCFG_DBG_INFO_PRINT_FILE == 0U
//#define CPNMEMCFG_MEM_DBG_INFO     printf
//#else
#define CPNMEMCFG_MEM_DBG_INFO(...)     fprintf(FILE_POINTER, __VA_ARGS__)
//#endif
    CPNMEMCFG_MEM_DBG_INFO("testing:%d  index:%d\n",te_testing,index);
}
#endif

//typedef enum{
//    test_up,
//    test_up2,
//    test_up3,
//    test_down,
//    test_down2,
//    test_down3,
//
//    test_null
//} TE_TESTING;
//TE_TESTING te_testing = test_up;
//static uint16 index = 0U;
typedef enum{
    increase_1,
    increase_2,
    increase_3,
    decrease_1,
    decrease_2,
    decrease_3,

    increase_null
} TE_SWITCH_INC;
static TE_SWITCH_INC incType = increase_1;
static uint16 changeInc = 0U;

uint16 uwStartTestMem = 0U;


/***********************************************************
 * CpnMemTest class definition.
 **********************************************************/
/* Function : CpnMemTest_run(hCpnMemTest cthis)
 * Input    : cthis - CpnMemTest class pointer
 * Output   :
 * Others   : CpnMemTest class function.
 **********************************************/
void CpnMemTest_run(hCpnMemTest cthis){
#if 1
    switch (te_test_case){
#if 1
    case test_case_0x00_0xFF_0x7F_0x00:
        /*if(te_test_op == open_file){
            CreadAndOpenFile(test_case_0x00_0xFF_0x7F_0x00);
            SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
            te_test_op = testing;
        }else if(te_test_op == close_file){
            CloseFile(test_case_0x00_0xFF_0x7F_0x00);
            te_test_op = finish;
        }else{}*/
        OpenAndCloseFile(test_case_0x00_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
//                    if(index == 20){
//                        index=index;
//                    }
                }else{
                    index = 0U;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;


    case test_case_0x00_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = (MEM_TEST_BUFF_MAX-1U);
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
//                    if(index == 117){
//                        index=index;
//                    }
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;

    case test_case_0x00_0xFF_0x5F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x5F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 2U;
                }else{
                    index = 1U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 2U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xAF_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xAF_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 1U;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 2U;
                }else{
                    index = 0U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 2U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF5_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF5_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 1U){
                    index -= 2U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 1U){
                    index -= 2U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xFA_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xFA_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 1U){
                    index -= 2U;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 1U){
                    index -= 2U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;

    case test_case_0x00_0xFF_0x3F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x3F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 2U;
                    changeInc = 0U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xCF_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xCF_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 0U;
                    changeInc = 0U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF3_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF3_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 2U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xFC_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xFC_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 2U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    changeInc = 0U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;

    case test_case_0x00_0xFF_0x1F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x1F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 3U){
                        changeInc = 0U;
                        index += 1U;
                    }
                }else{
                    index = 3U;
                    changeInc = 0U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;

    case test_case_0x00_0xFF_0x8F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x8F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 3U){
                        changeInc = 0U;
                        index += 1U;
                    }
                }else{
                    index = 0U;
                    changeInc = 0U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF1_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF1_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 3U){
                        changeInc = 0U;
                        if(index > 0U){
                            index -= 1U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF8_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF8_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 1U){
                    index--;
                    if(++changeInc >= 3U){
                        changeInc = 0U;
                        if(index > 0U){
                            index -= 1U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-4U;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
//#endif
//#if 1
    case test_case_0x00_0xFF_0x3F_0xBF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x3F_0xBF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 0U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
//                    if(index==106){
//                        index=index;
//                    }
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xCF_0xEF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xCF_0xEF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 2U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 3U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF3_0xF7_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF3_0xF7_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-4U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xFC_0xFD_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xFC_0xFD_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 2U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
#endif



#if 1
    case test_case_0x00_0xFF_0x3F_sizeAdd1_0xBF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x3F_sizeAdd1_0xBF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
//                    if(index == 4|| index == 5|| index == 6|| index == 7){
//                        index = index;
//                    }
                }else{
                    index = 0U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xCF_sizeAdd1_0xEF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xCF_sizeAdd1_0xEF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 2U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 3U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF3_sizeAdd1_0xF7_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF3_sizeAdd1_0xF7_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-4U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xFC_sizeAdd1_0xFD_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xFC_sizeAdd1_0xFD_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 2U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
//#endif
//#if 1
    case test_case_0x00_0xFF_0x3F_sizeDoubleAdd1_0xBF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x3F_sizeDoubleAdd1_0xBF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 0U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xCF_sizeDoubleAdd1_0xEF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xCF_sizeDoubleAdd1_0xEF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 2U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 3U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF3_sizeDoubleAdd1_0xF7_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF3_sizeDoubleAdd1_0xF7_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-4U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;

    case test_case_0x00_0xFF_0xFC_sizeDoubleAdd1_0xFD_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xFC_sizeDoubleAdd1_0xFD_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 2U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
#endif

    case test_case_0x00_0xFF_0x3F_sizeHalf_0xBF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0x3F_sizeHalf_0xBF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 0U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xCF_sizeHalf_0xEF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xCF_sizeHalf_0xEF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 2U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 3U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xF3_sizeHalf_0xF7_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xF3_sizeHalf_0xF7_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-4U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_0xFC_sizeHalf_0xFD_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_0xFC_sizeHalf_0xFD_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 2U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE>>1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;


    case test_case_0x00_0xFF_inc_0x3F_sizeDoubleAdd1_0xBF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_inc_0x3F_sizeDoubleAdd1_0xBF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = (index+1u);
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 0U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_dec_0xCF_sizeDoubleAdd1_0xEF_0xFF_0x7F_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_dec_0xCF_sizeDoubleAdd1_0xEF_0xFF_0x7F_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = (MEM_TEST_BUFF_MAX-index);
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = 2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        index += 2U;
                    }
                }else{
                    index = 2U;
                    changeInc = 0U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 3U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index += 4U;
                }else{
                    index = 0U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                if(index < MEM_TEST_BUFF_MAX){
                    SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;
    case test_case_0x00_0xFF_inc_0xF3_sizeDoubleAdd1_0xF7_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_inc_0xF3_sizeDoubleAdd1_0xF7_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = (index+1u);
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-3U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-4U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;

    case test_case_0x00_0xFF_dec_0xFC_sizeDoubleAdd1_0xFD_0xFF_0xFE_0x00:
        OpenAndCloseFile(test_case_0x00_0xFF_dec_0xFC_sizeDoubleAdd1_0xFD_0xFF_0xFE_0x00);
        if(te_test_op == testing){
            if(te_testing == test_up){
                if(index < MEM_TEST_BUFF_MAX){
                    memPointer[index].indication = (MEM_TEST_BUFF_MAX-index);
                    SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                    SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                    PointerInfo();
                    index++;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = decrease_1;
                    te_testing = test_down;
                }
            }else if(te_testing == test_down){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 2U){
                    index--;
                    if(++changeInc >= 2U){
                        changeInc = 0U;
                        if(index > 1U){
                            index -= 2U;
                        }
                    }
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    te_testing = test_up2;
                }
            }else if(te_testing == test_up2){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-2U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_up3;
                }
            }else if(te_testing == test_up3){
                memPointer[index].indication = MEM_TEST_BYTE_SIZE*2U+1U;
                SYN_TRIG(sig_trig_CpnMemTest_memMalloc, &memPointer[index]);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 3U){
                    index -= 4U;
                }else{
                    index = MEM_TEST_BUFF_MAX-1U;
                    changeInc = 0U;
                    incType = increase_1;
                    te_testing = test_down2;
                }
            }else if(te_testing == test_down2){
                SYN_TRIG(sig_trig_CpnMemTest_memFree, memPointer[index].pointer);
                SYN_TRIG(sig_trig_CpnMemTest_memStatus, fp);
                PointerInfo();
                if(index > 0U){
                    index--;
                }else{
                    te_testing = test_null;
                    te_test_op = close_file;
                    CASE_INFO
                }
            }else{}
        }
        break;


    default:
        te_test_op = open_file;
        te_testing = test_up;
        index = 0U;
        if(te_test_case < test_case_default){
            te_test_case++;
        }
        if(uwStartTestMem){
            uwStartTestMem = 0U;
            te_test_case = 0U;
        }
        break;
    }
#endif
}


/* Function : hCpnMemTest CpnMemTest_init(hCpnMemTest cthis)
 * Input    : cthis - CpnMemTest class pointer
 * Output   : hCpnMemTest - cthis/OOPC_NULL
 * Others   : CpnMemTest class initial function.
 **********************************************/
hCpnMemTest CpnMemTest_init(hCpnMemTest cthis){
    /* Configure functions. */
    //cthis->run = CpnMemTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */

    return cthis;
}

/* Function : hCpnMemTest CpnMemTest_ctor(hCpnMemTest cthis)
 * Input    : cthis - CpnMemTest class pointer
 * Output   : hCpnMemTest - cthis/OOPC_NULL
 * Others   : CpnMemTest class constructor.
 **********************************************/
CC(CpnMemTest){
    cthis->init = CpnMemTest_init;
    cthis->run = CpnMemTest_run;
    /* TODO */

    /* Configure parameters. */
    /* TODO */
    return cthis;
}

/* Function : hCpnMemTest CpnMemTest_dtor(hCpnMemTest cthis)
 * Input    : cthis - CpnMemTest class pointer
 * Output   : OOPC_RETURN_DATATYPE - OOPC_TRUE/OOPC_FALSE
 * Others   : CpnMemTest class destructor.
 **********************************************/
CD(CpnMemTest){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
