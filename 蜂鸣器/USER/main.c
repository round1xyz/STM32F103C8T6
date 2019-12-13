/**********************************************
 * 文件名  ：main.c
 * 描述    ：无源蜂鸣器驱动。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "beep.h"

void Delay(__IO u32 nCount) {
    for (; nCount != 0; nCount--);
}

int main(void) {
    SystemInit(); //配置系统时钟为72M
    BEEP_GPIO_Config(); //LED端口初始化
    while(1) {
        BEEP_ON;
        Delay(50000);
        BEEP_OFF;
        Delay(50000);
    }
}
