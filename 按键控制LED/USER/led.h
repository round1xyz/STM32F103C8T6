#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_ON GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define LED_OFF GPIO_SetBits(GPIOC,GPIO_Pin_13)

void LED_GPIO_Config(void);

#endif /* __LED_H */
