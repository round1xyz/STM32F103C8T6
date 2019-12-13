/**********************************************
 * 文件名  ：main.c
 * 描述    ：LED以500ms的频率闪烁(定时器TIM2产生定时)。
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.5.0
***********************************************/
#include "stm32f10x.h"
#include "led.h"
#include "tim.h"

int main(void) {
    SystemInit(); //配置系统时钟为72M
    LED_GPIO_Config(); //LED端口初始化
    TIM2_Init();
    TIM2_StartTime();    //TIM2开始计时

    while (1) {
        if (TIM2_GetTime() >= 500) {
            TIM2_ResetTime();
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))); //LED翻转
        }
    }
}
