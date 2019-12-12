/**********************************************
 * 文件名  ：main.c
 * 描述    ：LED点亮。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "led.h"

int main(void) {
    SystemInit(); //配置系统时钟为72M
    LED_GPIO_Config(); //LED端口初始化
    LED_ON;
}
