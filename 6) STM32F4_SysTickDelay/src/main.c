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
		Delay_Ms(1000);
		GPIO_WriteBit(LED_ALL_GPIO, LED_ALL_PINS, Bit_SET);
		Delay_Ms(1000);
		GPIO_WriteBit(LED_ALL_GPIO, LED_ALL_PINS, Bit_RESET);
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

static void Delay_Ms(uint32_t delayMs)
{
	g_delayTick = delayMs;
	
	while(g_delayTick != 0);
}



