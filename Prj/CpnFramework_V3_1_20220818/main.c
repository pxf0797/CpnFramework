/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : main.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:30:09
* Description  :
* Others       :
* History      : 191228 pxf ���ν���
***************************************************************************/

/*ͷ�ļ�����*/
#include "main.h"
#include <time.h>

/*���� : main()
* ���� : ��
* ��� : ��
* ���� : ��
***********************************************/
int main(void){
    uint16 uwTickCnt = 0;
//    clock_t start;

    trig_Abi_init();
//    start = clock();
    for(;;){
//        extern uint16 uwTimeCnt;
//        uwTimeCnt += 100;

        if(!(uwTickCnt & 0x0007)){
            trig_Abi_tick();
        }
        uwTickCnt++;
//        if(clock() != start){ //CLOCKS_PER_SEC
//            start = clock();
//            trig_Abi_tick();
//        }
        trig_Abi_run();
    }
    return 0;
}



/**************************** Copyright(C) pxf ****************************/
