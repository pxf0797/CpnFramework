/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnCrcSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 16:29:06
 * Description  : CpnCrc component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
//#include "CpnCrc.h"
#include "CpnCrcSigs.h"
#include "RteSigs.h"
#include "FuncLib.h"
// #include "CpnCrcTest.h"

/***********************************************************
 * CpnCrc class definition.
 **********************************************************/
/* CpnCrc class.
 **********************************************/
#define CRC_TYPE_NUM    3
static Crc clCrc[CRC_TYPE_NUM];


/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnCrc_init(void){
    hCrc opRes = OOPC_NULL;
    CN(Crc, &clCrc[0], crc_8, 0x07U, 0x00U, 0x00U, invert_yes);
    CN(Crc, &clCrc[1], crc_16, 0x1021U, 0x0000U, 0x0000U, invert_yes);
    CN(Crc, &clCrc[2], crc_32, 0x04C11DB7UL, 0x0000UL, 0x0000UL, invert_yes);
    for(uint16 i = 0U; i < CRC_TYPE_NUM; i++){
        opRes = (OPRS(clCrc[i]));
        if(opRes == OOPC_NULL){
            break;
        }
    }
    if(opRes != OOPC_NULL){
        ;
    }
}


/* getCrc8 Service.
 **********************************************/
void serv_CpnCrc_getCrc8(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[0].crc(clCrc[0].self,crcData->s,crcData->len);
}
/* getCrc16 Service.
 **********************************************/
void serv_CpnCrc_getCrc16(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[1].crc(clCrc[1].self,crcData->s,crcData->len);
}
/* getCrc32 Service.
 **********************************************/
void serv_CpnCrc_getCrc32(void *buff){
    hTS_CRC_DATA crcData = (hTS_CRC_DATA)buff;
    crcData->crc = clCrc[2].crc(clCrc[2].self,crcData->s,crcData->len);
}

/* Interface trigger.
 **********************************************/
//void trig_CpnCrc_inf_infFunc(void){}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnCrc(void){}

/**************************** Copyright(C) pxf ****************************/
