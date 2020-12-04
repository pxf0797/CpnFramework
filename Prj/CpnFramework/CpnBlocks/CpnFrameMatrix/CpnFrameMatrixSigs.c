/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : CpnFrameMatrixSigs.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2020/11/20 14:13:51
* Description  : CpnFrameMatrix����źŶ���Դ�ļ�
* Others       :
* History      : 201120 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "./CpnFrameMatrix.h"
#include "./MatrixId.h"
#include "./CpnFrameMatrixSigs.h"
#include "../../cpnRte/RteSigs/RteSigs.h"
#include "../../CpnBasics/FuncLib/FuncLib.h"
#include "./FrameBitLib.h"

/***********************************************************
* CpnFrameMatrix�ඨ��
***********************************************************/
/*CpnFrameMatrix��
***********************************************/
const FrameMatrix matrixDatas[]={
    MATRIX_EXPANTION(FRAME_MATRIX_CFG_LIST)
};
static CpnFrameMatrix clCpnFrameMatrix[CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS];
static uint32 ulMatrixId[CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS];
static uint16 uwMatrixIdIndex[CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS];
static MatrixId clMatrixId;

/***********************************************************
* serv trig �źŽӿڶ���
* ��̳еĽӿھ��Ǵ����źŽӿڣ��ڽӿں�����ʹ�ô����źŽ��д���
***********************************************************/
/*�����ʼ������
***********************************************/
void serv_CpnFrameMatrix_init(void){
    hCpnFrameMatrix opRes = OOPC_NULL;
    for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
        CN(CpnFrameMatrix,&clCpnFrameMatrix[i], matrixDatas[i].id, matrixDatas[i].rxtx, matrixDatas[i].format, matrixDatas[i].period/CPNFRAMEMATRIXCFG_TASK_EXECUTE_PRD);
    }
    for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
        if(OPRS(clCpnFrameMatrix[i]) == OOPC_NULL){
            opRes = OOPC_NULL;
            break;
        }
        opRes = OPRS(clCpnFrameMatrix[i]);
    }
    CN(MatrixId,&clMatrixId,matrixDatas,ulMatrixId,uwMatrixIdIndex,CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS);
    opRes = OPRS(clMatrixId);
    if(opRes != NULL){
        addTaskParam taskParam;
        taskParam.level = level1;
        taskParam.t = taskCpnFrameMatrix;
        taskParam.prdTick = CPNFRAMEMATRIXCFG_TASK_EXECUTE_PRD;
        taskParam.startTick = 5*MS_T;
        clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFrameMatrix_addTask, (uint8*)&taskParam);
    }
}

/*����
***********************************************/
void serv_CpnFrameMatrix_get_frame(void *buff){
    hTS_FRAME_GET get = (hTS_FRAME_GET)buff;
    // for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
    //     if(clCpnFrameMatrix[i].id == get->id){
    //         clCpnFrameMatrix[i].get_frame(clCpnFrameMatrix[i].self, get->bit_start, get->bit_len, &get->value);
    //     }
    // }
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, get->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        clCpnFrameMatrix[uwIdIndex].get_frame(clCpnFrameMatrix[uwIdIndex].self, get->bit_start, get->bit_len, get->value);
    }
}
/*����
***********************************************/
void serv_CpnFrameMatrix_set_frame(void *buff){
    hTS_FRAME_SET set = (hTS_FRAME_SET)buff;
    // for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
    //     if(clCpnFrameMatrix[i].id == set->id){
    //         clCpnFrameMatrix[i].set_frame(clCpnFrameMatrix[i].self, set->bit_start, set->bit_len, set->value);
    //     }
    // }
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, set->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        clCpnFrameMatrix[uwIdIndex].set_frame(clCpnFrameMatrix[uwIdIndex].self, set->bit_start, set->bit_len, set->value);
    }
}
/*����--����֡����
***********************************************/
void serv_CpnFrameMatrix_update_frame(void *buff){
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

/*����--��ȡ�����ֽ�
***********************************************/
void serv_CpnFrameMatrix_get_frame_byte(void *buff){
    hTS_FRAME_BYTE frame = (hTS_FRAME_BYTE)buff;
    // for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
    //     if(clCpnFrameMatrix[i].id == frame->id){
    //         *(frame->value) = GET_BYTE(clCpnFrameMatrix[i].frame, frame->byte_index);
    //     }
    // }
    uint16 uwIdIndex = clMatrixId.getIdIndex(clMatrixId.self, frame->id);
    if(uwIdIndex < clMatrixId.ulMatrixIdNum){
        *(frame->value) = GET_BYTE(clCpnFrameMatrix[uwIdIndex].frame, frame->byte_index);
    }
}

/*�ӿڴ���
***********************************************/
void trig_CpnFrameMatrix_inf_sentFrame(uint32 id, hTU_BYTES_DATA frame){
    TS_FRAME_TRANS transFrame = {id, frame};
    clRteSynSigs.trig(clRteSynSigs.self, sig_trig_CpnFrameMatrix_sentFrame, (uint8*)&transFrame);
}



/***********************************************************
* �����������
***********************************************************/
/*����������
***********************************************/
void taskCpnFrameMatrix(void){
    /* updtate receive frame matrix */

    /* sent frame matrix */
    for(uint16 i = 0; i < CPNFRAMEMATRIXCFG_MATRIX_FRAME_NUMS; i++){
        if(clCpnFrameMatrix[i].rxtx == FRAME_TX){
            if(++clCpnFrameMatrix[i].counter >= clCpnFrameMatrix[i].period){
                clCpnFrameMatrix[i].counter = 0;
                trig_CpnFrameMatrix_inf_sentFrame(clCpnFrameMatrix[i].id, &clCpnFrameMatrix[i].frame);
            }
        }
    }
}

/**************************** Copyright(C) pxf ****************************/
