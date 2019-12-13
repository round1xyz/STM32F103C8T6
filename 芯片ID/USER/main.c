/**********************************************
 * 文件名  ：main.c
 * 描述    ：获取CPU的96bit ID 和 flash的大小，并通过USART1打印出来。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "usart.h"
#include "chipid.h"
#include <stdio.h>

extern uint32_t ChipUniqueID[3];

int main(void) {
    SystemInit();
    USART1_Init();
    Get_ChipID(); //获取芯片信息
    printf("chip ID: %x-%x-%x\r\n", ChipUniqueID[0], ChipUniqueID[1], ChipUniqueID[2]); //输出芯片ID
    printf("chip flash: %dK\r\n", *(__IO uint16_t *)(0X1FFFF7E0)); //输出芯片容量
}
