#include <stdio.h>
#include "main.h"
#include "defines.h"

/* ! */
uint32_t g_delayTick = 0;

int main(void)
{
	/* General Configuration */
	SYSTEM_Config();

	while (1)
  {
		SPI_WriteByte(SPI1, (uint16_t)'B');
		Delay_Ms(500);
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
	SPI_Config();
	
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
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
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(BUTTON_GPIO, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
}

static void SPI_Config(void)
{
	SPI_InitTypeDef	SPI_InitStructure;
	
	SPI_InitStructure.SPI_Mode 								= SPI_Mode_Master;
	SPI_InitStructure.SPI_FirstBit 						= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_DataSize						= SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction						= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_CPOL								= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA								= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_BaudRatePrescaler 	= SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_NSS									= SPI_NSS_Soft;
	SPI_InitStructure.SPI_CRCPolynomial 			= 0;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}

static void Delay_Ms(uint32_t delayMs)
{
	g_delayTick = delayMs;
	
	while(g_delayTick != 0);
}
	
static void SPI_WriteByte(SPI_TypeDef* SPIx, uint16_t Data)
{
	SPI_WAIT(SPIx);

	SPIx->DR = Data;
}


