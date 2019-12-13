/**********************************************
 * 文件名  ：key.c
 * 描述    ：按键应用函数库        
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：-----------------
 *           |   PA0 - key   |
 *           -----------------
 * 库版本  ：ST3.5.0 
***********************************************/
#include "key.h"

/* 配置按键用到的I/O口 */
void Key_GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //开启按键端口的时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //选择对应的引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //端口配置为上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化端口
}

/* 按键中断优先级配置 */
void Key_NVIC_Config(void) {
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //组优先级
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //副优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //中断使能
    NVIC_Init(&NVIC_InitStructure);
}

/* 按键外部中断配置 */
void Key_EXIT_Config(void) {
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0; //外部中断线
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //外部中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void Key_Init(void) {
    Key_GPIO_Config();
    Key_NVIC_Config();
    Key_EXIT_Config();
}

void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
        EXTI_ClearITPendingBit(EXTI_Line0); //清除中断标志位
    }
}
