/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : main.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/12/28 23:30:09
* Description  : 
* Others       : 
* History      : 191228 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./main.h"

/*名称 : main()
* 输入 : 无
* 输出 : 无
* 其他 : 无
***********************************************/
int main(void){
    uint16 uwTickCnt = 0;

    trig_Abi_init();
    for(;;){
        extern uint16 uwTimeCnt;
        uwTimeCnt += 100;

        if(!(uwTickCnt & 0x0007)){
            trig_Abi_tick();
        }
        uwTickCnt++;
        trig_Abi_run();
    }
}



/**************************** Copyright(C) pxf ****************************/
