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

void Delay(__IO u32 nCount) {
    for (; nCount != 0; nCount--);
}

/* 配置按键用到的I/O口 */
void Key_GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //开启按键端口的时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //选择对应的引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //端口配置为上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化端口
}

/* 检测是否有按键按下 */
u8 Key_Scan(GPIO_TypeDef *GPIOx, u16 GPIO_Pin) {
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {
        /* 延时消抖 */
        Delay(50000);
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {
            /* 等待按键释放 */
            while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON);
            return KEY_ON;
        } else
            return KEY_OFF;
    } else
        return KEY_OFF;
}
