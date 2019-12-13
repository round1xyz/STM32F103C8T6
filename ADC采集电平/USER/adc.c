/**********************************************
 * 文件名  ：adc.c
 * 描述    ：DMA方式读取雨滴传感器及烟雾传感器
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：PA6（雨滴传感器）
 *           PA7（烟雾传感器　）
 * 库版本  ：ST3.5.0
***********************************************/
#include "adc.h"

#define ADC1_DR_Address ((u32)0x4001244C)

__IO uint16_t ADC1_Con[2];

/*配置ADC1的工作模式为DMA模式  */
void ADC1_Mode_Config(void) {
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能DMA1时钟
    /* DMA channel1 configuration */
    DMA_DeInit(DMA1_Channel1); //指定DMA通道
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; //设置DMA外设地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC1_Con; //设置DMA内存地址，ADC转换结果直接放入该地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //外设为设置为数据传输的来源
    DMA_InitStructure.DMA_BufferSize = 2; //DMA缓冲区设置为2；
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* Enable DMA channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);  //使能DMA通道

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

    /* ADC1 configuration */
    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //使用独立模式，扫描模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //无需外接触发器
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //使用数据右对齐
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 2; // 2个转换通道
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channel11 configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5); //通道6采样周期55.5个时钟周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_55Cycles5); //通道7采样周期55.5个时钟周期

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE); //使能ADC的DMA

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE); //使能ADC1

    /* Enable ADC1 reset calibaration register */
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while (ADC_GetResetCalibrationStatus(ADC1));

    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while (ADC_GetCalibrationStatus(ADC1));

    /* Start ADC1 Software Conversion */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //开始转换
}
