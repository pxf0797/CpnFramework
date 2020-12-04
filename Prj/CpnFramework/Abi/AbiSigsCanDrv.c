/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : AbiSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/29 20:17:54
* Description  :
* Others       :
* History      : 191229 pxf 初次建立
***************************************************************************/

/*头文件包含*/
// #include "./AbiSigs.h"
// #include "../CpnRte/RteSigs/RteSigs.h"
#include "../CpnBasics/FuncLib/FuncLib.h"

#include "../../APP/Can/AppCan.h"
#include "../../APP/Can/AppCanObc.h"

/*发送数据处理
***********************************************/
void trig_Abi_sentCanFrameDrv(uint32 id, uint8 data[]){
    Can_Frame tCanFrame = {0};
    tCanFrame.id = id;
    tCanFrame.len = 8;
    memCopy(tCanFrame.data, data, tCanFrame.len);
    CanPublic_Send_msg(CAN_MSG_ID_GET_TYPE2(tCanFrame.id), &tCanFrame);
}

/**************************** Copyright(C) pxf ****************************/
