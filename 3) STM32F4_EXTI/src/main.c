#include "main.h"
#include "defines.h"

int main(void)
{
	GPIO_Config();
	EXTI_Config();
	NVIC_Config();
	
	/* SystemCoreClock / 1000 = 1mS */
	SysTick_Config(SystemCoreClock / 1000);
	
  while (1)
  {
		
  }
}

static void GPIO_Config(void)
{
	/* RCC Clock Dagilimi */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Ayarlarin Tutulacagi Struct tanimlamasi */
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

static void EXTI_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	EXTI_InitTypeDef	EXTI_InitStructure;
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_InitStructure);
}

static void NVIC_Config(void)
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel 									 	= EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd									= ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}








