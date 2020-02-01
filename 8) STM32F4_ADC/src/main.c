#include <stdio.h>
#include "main.h"
#include "defines.h"

/* Global Variables */
uint32_t g_delayTick = 0;
uint32_t g_ADCFlag = 0;
uint32_t g_ADCvalue = 0;

/* Local Variables */
uint16_t adc_FilteredValue = 0;

int main(void)
{
	/* General Configuration */
	SYSTEM_Config();

	while (1)
  {
		if (g_ADCFlag == 1)
		{
			g_ADCFlag = 0;
			
			adc_FilteredValue = MovingAvaregeFilter(g_ADCvalue);
			
			if (adc_FilteredValue > 2048)
				GPIO_WriteBit(LED_ALL_GPIO, LED_ALL_PINS, Bit_SET);
			else
				GPIO_WriteBit(LED_ALL_GPIO, LED_ALL_PINS, Bit_RESET);
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
	ADC_Config();
	NVIC_Config();
	
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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
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
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void ADC_Config(void)
{
	ADC_InitTypeDef						ADC_InitStructure;
	ADC_CommonInitTypeDef			ADC_CommonInitStructure;
	
	ADC_CommonInitStructure.ADC_Mode 							= ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_DMAAccessMode			= ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Prescaler					= ADC_Prescaler_Div4;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_InitStructure.ADC_Resolution 					= ADC_Resolution_12b;
	ADC_InitStructure.ADC_DataAlign						= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ContinuousConvMode 	= ENABLE;
	ADC_InitStructure.ADC_ScanConvMode				= DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv		= ADC_ExternalTrigConv_Ext_IT11;
	ADC_InitStructure.ADC_ExternalTrigConvEdge= ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_NbrOfConversion			= 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles);
	
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_SoftwareStartConv(ADC1);
}

static void NVIC_Config(void)
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel 										= ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd									= ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
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

