/**********************************************
 * 文件名  ：chipid.c
 * 描述    ：获取CPU的ID函数，每个芯片都有唯一的 96bit unique ID
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：无
 * 库版本  ：ST3.5.0
***********************************************/
#include "chipid.h"

uint32_t ChipUniqueID[3];

/* 获取芯片ID */
void Get_ChipID(void) {
    ChipUniqueID[0] = *(__IO uint32_t *)(0X1FFFF7F0); //高字节
    ChipUniqueID[1] = *(__IO uint32_t *)(0X1FFFF7EC);
    ChipUniqueID[2] = *(__IO uint32_t *)(0X1FFFF7E8); //低字节
}
