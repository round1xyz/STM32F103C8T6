/**********************************************
 * 文件名  ：main.c
 * 描述    ：串口1(USART1)打印当前ADC1(PA0)的转换电压值
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "usart.h"
#include "adc.h"
#include <stdio.h>

extern __IO uint16_t ADC1_Con[2];

void Delay(__IO u32 nCount) {
    for (; nCount != 0; nCount--);
}

int main(void) {
    uint32_t AD1_value, AD2_value;
    SystemInit();
    USART1_Init();
    ADC1_Mode_Config();

    while (1) {
        Delay(10000000);
        AD1_value = 3300000 / 4096 * ADC1_Con[0] / 1000;
        AD2_value = 3300000 / 4096 * ADC1_Con[1] / 1000;
        printf("AD1 = %d mV, AD2 = %d mv\r\n", AD1_value, AD2_value);
    }
}
