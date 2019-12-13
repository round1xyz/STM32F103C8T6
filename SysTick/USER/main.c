/**********************************************
 * 文件名  ：main.c
 * 描述    ：LED在SysTick控制下，以500ms的频率闪烁。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "SysTick.h"
#include "led.h"

int main(void) {
    SystemInit(); //配置系统时钟为72M
    LED_GPIO_Config(); //LED端口初始化
    SysTick_Init(); //SysTick初始化

    while (1) {
        LED_ON;
        Delay_us(500000); //500000 * 1us = 500ms
        LED_OFF;
        Delay_us(500000);
    }
}
