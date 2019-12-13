/**********************************************
 * 文件名  ：main.c
 * 描述    ：开发板通过串口接收到数据立即回传给电脑。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "usart.h"
#include "SysTick.h"
#include "dht11.h"
#include <stdio.h>

int main(void) {
    SystemInit(); //配置系统时钟为72M
    USART1_Init();
    SysTick_Init(); //SysTick初始化
    while (1) {
        uint8_t buffer[5];
        double hum, temp;
        if (dht11_read_data(buffer) == 0) {
            hum = buffer[0] + buffer[1] / 10.0;
            temp = buffer[2] + buffer[3] / 10.0;
        }
        printf("temperature: %.2f, humidness: %.2f\r\n", temp, hum);
        Delay_us(1000000);
    }
}
