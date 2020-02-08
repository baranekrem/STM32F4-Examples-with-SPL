#include <stdio.h>
#include "main.h"
#include "defines.h"

/* Global Variables */
uint32_t g_delayTick = 0;

/* Local Variables */
uint16_t ADC_Values[2];
// ADC_Values[0] = ADC1_IN0 - AKIM
// ADC_Values[1] = ADC1_IN1 - GERILIM

int main(void)
{
	/* General Configuration */
	SYSTEM_Config();

	while (1)
  {
		if (ADC_Values[0] == 1024)
		{
			
		}
		
		if (ADC_Values[1] == 1024)
		{
			
		}
  }
}

static void SYSTEM_Config(void)
{
	/* Set HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	
	/* Wait for clock to stabilize */
	while(RCC_WaitForHSEStartUp() == ERROR);
	
	/* User Configuration */
	RCC_Config();
	GPIO_Config();
	ADC_DMA_Config();
	
	/*****************************************/
	/** SystemCoreClock / 1000      1ms      */
	/** SystemCoreClock / 10000     100us    */
	/** SystemCoreClock / 100000    10us     */
	/** SystemCoreClock / 1000000   1us      */
	/*****************************************/
	while(SysTick_Config(SystemCoreClock / 1000) != 0);
}

static void RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
}

static void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin 	= LED_ALL_PINS; 		// Kullanilacak pinler
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;		// Pinlerin Modu (Çikis - Out)
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// Pinlerin Yapisi (PushPull - PP)
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL; // Pinlerin Direnci (Nopull - NOPULL)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// Pinlerin Frekansi (100 - MHz)
	GPIO_Init(LED_ALL_GPIO, &GPIO_InitStructure); 		// Ayalar yapisini ilgili porta yükle

	GPIO_InitStructure.GPIO_Pin 	= BUTTON_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(BUTTON_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void ADC_DMA_Config(void)
{
	ADC_InitTypeDef						ADC_InitStructure;
	ADC_CommonInitTypeDef			ADC_CommonInitStructure;
	DMA_InitTypeDef						DMA_InitStructure;
	
	DMA_InitStructure.DMA_Channel 						= DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr	= (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr			= (uint32_t)&ADC_Values[0];
	DMA_InitStructure.DMA_DIR									= DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize					= 2;
	DMA_InitStructure.DMA_PeripheralInc         = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc             = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize    = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize        = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode                  = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority              = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode              = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold         = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst           = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst       = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream4, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream4, ENABLE);

	ADC_InitStructure.ADC_Resolution 					= ADC_Resolution_12b;
	ADC_InitStructure.ADC_DataAlign						= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ContinuousConvMode 	= ENABLE;
	ADC_InitStructure.ADC_ScanConvMode				= ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv		= ADC_ExternalTrigConv_Ext_IT11;
	ADC_InitStructure.ADC_ExternalTrigConvEdge= ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_NbrOfConversion			= 2;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_CommonInitStructure.ADC_Mode 							= ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_DMAAccessMode			= ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Prescaler					= ADC_Prescaler_Div4;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_480Cycles);
	
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

static void Delay_Ms(uint32_t delayMs)
{
	g_delayTick = delayMs;
	
	while(g_delayTick != 0);
}

uint16_t MovingAvaregeFilter(uint16_t value)
{
	uint16_t filteredValue = 0;
	uint32_t sum = 0;
	
	const uint32_t movingA_Len = 32;
	static uint16_t adcValues[movingA_Len];
	static uint32_t counter = 0;

	adcValues[counter++] = value;
	
	uint8_t i = 0;
	for (i = 0; i < movingA_Len; i++)
	{
		sum += adcValues[i];
	}
	
	if (counter == movingA_Len)
		counter = 0;
	
	filteredValue = (uint16_t)(sum >> 5); // why 5 ? why shifted ? WTF ?
	
	return (filteredValue);
}

