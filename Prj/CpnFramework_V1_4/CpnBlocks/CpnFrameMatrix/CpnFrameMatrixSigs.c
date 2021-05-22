/**************************************************************************
 * Copyright    : Copyright(C), 2021, pxf, person.
 * File name    : CpnFrameMatrixSigs.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2021/04/10 13:56:01
 * Description  : CpnFrameMatrix component signals definition source file.
 * Others       :
 * History      : 20210410 pxf Initially established.
 **************************************************************************/

/* Include head files. */
#include "./CpnFrameMatrix.h"
#include "./MatrixId.h"
#include "./CpnFrameMatrixSigs.h"
#include "../../CpnRte/RteSigs/RteSigs.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "./FrameBitLib.h"

/***********************************************************
 * CpnFrameMatrix class definition.
 **********************************************************/
/* CpnFrameMatrix class.
 **********************************************/
const FrameMatrix matrixDatas[]={
    MATRIX_EXPANTION(FRAME_MATRIX_CFG_LIST)
};
static CpnFrameMatrix clCpnFrameMatrix[CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS];
static uint32 ulMatrixId[CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS];
static uint16 uwMatrixIdIndex[CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS];
static MatrixId clMatrixId;

/***********************************************************
 * Serv Trig signal interface definition.
 * The interface inherited by the class is the trigger signal interface,
 * and the trigger signal is used in the interface function to trigger.
 **********************************************************/
/* Component initial serv.
 **********************************************/
void serv_CpnFrameMatrix_init(void){
    hCpnFrameMatrix opRes = OOPC_NULL;
    for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
        CN(CpnFrameMatrix,&clCpnFrameMatrix[i], matrixDatas[i].id, matrixDatas[i].rxtx, matrixDatas[i].format, matrixDatas[i].period/CPNFRAMEMATRIXCFG_TASK_EXECUTE_PRD);
    }
    for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
        if(OPRS(clCpnFrameMatrix[i]) == OOPC_NULL){
            //opRes = OOPC_NULL;
            break;
        }
        opRes = OPRS(clCpnFrameMatrix[i]);
    }
    CN(MatrixId,&clMatrixId,matrixDatas,ulMatrixId,uwMatrixIdIndex,CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS);
    opRes = (hCpnFrameMatrix)OPRS(clMatrixId);
    if(opRes != NULL){
        initTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnFrameMatrix;
        taskParam.prdTick = CPNFRAMEMATRIXCFG_TASK_EXECUTE_PRD;
        taskParam.startTick = 5*MS_T;
        taskParam.strgMask = task_strategy_matrix_mask;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFrameMatrix_addTask, (uint8*)&taskParam);
    }
}

/* getFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_getFrame(void *buff){
    hTS_FRAME_GETSET get = (hTS_FRAME_GETSET)buff;
    // for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
    //     if(clCpnFrameMatrix[i].id == get->id){
    //         clCpnFrameMatrix[i].get_frame(clCpnFrameMatrix[i].self, get->bit_start, get->bit_len, &get->value);
    //     }
    // }
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, get->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        clCpnFrameMatrix[uwIdIndex].getFrame(clCpnFrameMatrix[uwIdIndex].self, get->bit_start, get->bit_len, get->value);
    }
}
/* setFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_setFrame(void *buff){
    hTS_FRAME_GETSET set = (hTS_FRAME_GETSET)buff;
    // for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
    //     if(clCpnFrameMatrix[i].id == set->id){
    //         clCpnFrameMatrix[i].set_frame(clCpnFrameMatrix[i].self, set->bit_start, set->bit_len, set->value);
    //     }
    // }
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, set->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        clCpnFrameMatrix[uwIdIndex].setFrame(clCpnFrameMatrix[uwIdIndex].self, set->bit_start, set->bit_len, *(set->value));
    }
}
/* updateFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_updateFrame(void *buff){
    hTS_FRAME_TRANS frame = (hTS_FRAME_TRANS)buff;
    // for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
    //     if(clCpnFrameMatrix[i].id == frame->id){
    //         memCopy(clCpnFrameMatrix[i].frame.data, frame->frame, sizeof(clCpnFrameMatrix[i].frame.data));
    //     }
    // }
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, frame->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        memCopy(clCpnFrameMatrix[uwIdIndex].frame.data, frame->frame, sizeof(clCpnFrameMatrix[uwIdIndex].frame.data));
    }
}
/* getFrameByte Service.
 **********************************************/
void serv_CpnFrameMatrix_getFrameByte(void *buff){
    hTS_FRAME_BYTE frame = (hTS_FRAME_BYTE)buff;
    // for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
    //     if(clCpnFrameMatrix[i].id == frame->id){
    //         *(frame->value) = GET_BYTE(clCpnFrameMatrix[i].frame, frame->byte_index);
    //     }
    // }
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, frame->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        *(frame->value) = BYTE_INDEX(clCpnFrameMatrix[uwIdIndex].frame, frame->byte_index);
    }
}
/* setFrameByte Service.
 **********************************************/
void serv_CpnFrameMatrix_setFrameByte(void *buff){
    hTS_FRAME_BYTE frame = (hTS_FRAME_BYTE)buff;
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, frame->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        BYTE_INDEX(clCpnFrameMatrix[uwIdIndex].frame, frame->byte_index) = *(frame->value);
    }
}
/* sentFrame Service.
 **********************************************/
void serv_CpnFrameMatrix_sentFrame(void *buff){
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, (*(uint32 *)buff));

    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        trig_CpnFrameMatrix_inf_sentFrame(clCpnFrameMatrix[uwIdIndex].id, &clCpnFrameMatrix[uwIdIndex].frame);
    }
}
/* Interface trigger.
 **********************************************/
void trig_CpnFrameMatrix_inf_sentFrame(uint32 id, hTU_BYTES_DATA frame){
    TS_FRAME_TRANS transFrame = {id, frame};
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFrameMatrix_sentFrame, (uint8*)&transFrame);
}



/***********************************************************
 * Component running task.
 **********************************************************/
/* Running task definition.
 **********************************************/
void taskCpnFrameMatrix(void){
    /* updtate receive frame matrix */

    /* sent frame matrix */
    for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
        if(clCpnFrameMatrix[i].rxtx == FRAME_TX){
            if(clCpnFrameMatrix[i].period && (++clCpnFrameMatrix[i].counter >= clCpnFrameMatrix[i].period)){
                clCpnFrameMatrix[i].counter = 0;
                trig_CpnFrameMatrix_inf_sentFrame(clCpnFrameMatrix[i].id, &clCpnFrameMatrix[i].frame);
            }
        }
    }
}

/**************************** Copyright(C) pxf ****************************/
