#include <stdio.h>
#include "main.h"
#include "defines.h"

/* Global Variables */
uint32_t g_delayTick = 0;
uint32_t transferCompleteFlag = 0;

/* Local Variables */
#define DMA_BUFFER_SIZE				(6)

uint8_t src[DMA_BUFFER_SIZE] = {'S', 'T', 'M', '3', '2', 'F'};
uint8_t dst[DMA_BUFFER_SIZE] = {0};

int main(void)
{
	/* General Configuration */
	SYSTEM_Config();

	while (1)
  {
		if (transferCompleteFlag == 1)
		{
			transferCompleteFlag = 0;
			
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
	DMA_Config();
	
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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
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
}

static void DMA_Config(void)
{
	DMA_InitTypeDef						DMA_InitStructure;
	NVIC_InitTypeDef					NVIC_InitStructure;
	
	DMA_InitStructure.DMA_Channel 						= DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr	= (uint32_t)&src[0];
	DMA_InitStructure.DMA_Memory0BaseAddr			= (uint32_t)&dst[0];
	DMA_InitStructure.DMA_DIR									= DMA_DIR_MemoryToMemory;
	DMA_InitStructure.DMA_BufferSize					= (uint32_t)DMA_BUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralInc       = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_MemoryInc           = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize      = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode                = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority            = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode            = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold       = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst         = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst     = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream4, &DMA_InitStructure);
	
	DMA_ITConfig(DMA2_Stream4, DMA_IT_TC, ENABLE);
	
	DMA_Cmd(DMA2_Stream4, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel 										= DMA2_Stream4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
}

static void Delay_Ms(uint32_t delayMs)
{
	g_delayTick = delayMs;
	
	while(g_delayTick != 0);
}


