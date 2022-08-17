/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnInfoSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/05/26 16:35:22
 * Description  : CpnInfo component signals definition source file.
 * Others       :
 * History      : 20210526 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "CpnInfo.h"
#include "CpnInfoSigs.h"
#include "RteSigs.h"
#include "FuncLib.h"

/***********************************************************
 * CpnInfo class definition.
 **********************************************************/
#if (CPNINFOCFG_REPORT_ENABLE == TRUE)
/* CpnInfo class.
 **********************************************/
static CpnInfo clCpnInfo;
/* memory size align.
 **********************************************/
typedef struct {uint32 uwManaType[2];} tsManaType;
#define CPNINFOCFG_FIFO_CLASS_ALIGN_SIZE        ALIGN_SIZE(sizeof(tsManaType),sizeof(Fifo))
#define CPNINFOCFG_FIFO_OBJECT_ALIGN_SIZE       (ALIGN_SIZE(sizeof(tsManaType),sizeof(tsInfoFifoBuff))*CPNINFOCFG_FIFO_OBJECT_NUM)
#define CPNINFOCFG_INFO_BUFF_ALIGN_SIZE         (ALIGN_SIZE(sizeof(tsManaType),CPNINFOCFG_INFO_BUFF_SIZE)*CPNINFOCFG_FIFO_OBJECT_NUM)
#define CPNINFOCFG_MEM_ALIGN_SIZE               (CPNINFOCFG_FIFO_CLASS_ALIGN_SIZE+CPNINFOCFG_FIFO_OBJECT_ALIGN_SIZE+CPNINFOCFG_INFO_BUFF_ALIGN_SIZE)
/* memory size align.
 **********************************************/
static uint8 ucInfoSpace[BLOCKMCFG_CAL_MANAGE_SIZE(tsManaType,CPNINFOCFG_MEM_ALIGN_SIZE/sizeof(tsManaType))];
static BlockM clBlockM;
#endif

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnInfo_init(void){
#if (CPNINFOCFG_REPORT_ENABLE == TRUE)
    CN(CpnInfo,&clCpnInfo,&clBlockM,ucInfoSpace,sizeof(tsManaType),CPNINFOCFG_MEM_ALIGN_SIZE/sizeof(tsManaType));
    if(OPRS(clCpnInfo) != NULL){
        tsInitTask taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnInfo;
        taskParam.prdTick = 3*MS_T;
        taskParam.startTick = 5*MS_T;
        taskParam.e.all = e_info;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnInfo_initTask, (uint8*)&taskParam);
    }
#endif
}

/* info Service.
 **********************************************/
void serv_CpnInfo_info(const char *file, const char *func, const uint16 line, const char *format, ...){
#if (CPNINFOCFG_REPORT_ENABLE == TRUE)
    va_list args;

    va_start(args, format);
    clCpnInfo.info(clCpnInfo.self,file,func,line,format,args);
    va_end(args);
#endif
}

/* Interface trigger.
 **********************************************/
//void trig_CpnInfo_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnInfo(void){
#if (CPNINFOCFG_REPORT_ENABLE == TRUE)
    clCpnInfo.run(clCpnInfo.self);
#endif
}

/**************************** Copyright(C) pxf ****************************/
