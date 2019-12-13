/**********************************************
 * 文件名  ：main.c
 * 描述    ：开发板通过串口接收到数据立即回传给电脑。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "usart.h"
#include <stdio.h>

int main(void) {
    SystemInit(); //配置系统时钟为72M
    USART1_Init();
    while (1) {}
}
