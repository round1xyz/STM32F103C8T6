#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

#define BEEP_ON GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define BEEP_OFF GPIO_SetBits(GPIOA,GPIO_Pin_5)

void BEEP_GPIO_Config(void);

#endif /* __BEEP_H */
