#include <stdio.h>
#include "main.h"
#include "defines.h"

uint8_t g_receivedData = 0;
uint8_t g_receivedFlag = 0;

int main(void)
{
	RCC_Config();
	GPIO_Config();
	USART1_Config();
	NVIC_Config();
	
	/*****************************************/
	/** SystemCoreClock / 1000      1ms      */
	/** SystemCoreClock / 10000     100us    */
	/** SystemCoreClock / 100000    10us     */
	/** SystemCoreClock / 1000000   1us      */
	/*****************************************/
	SysTick_Config(SystemCoreClock / 1000);
  
	while (1)
  {
		if (g_receivedFlag == 1)
		{
			g_receivedFlag = 0;
			
			LED_StateMachine(g_receivedData);
			
			/*
			if (g_receivedData == '1')
			{
				GPIO_WriteBit(LED_ALL_GPIO, LED_ALL_PINS, Bit_SET);
				USART_SendString(USART1, "LEDler aktif.\r\n");
			}
			else if (g_receivedData == '0')
			{
				GPIO_WriteBit(LED_ALL_GPIO, LED_ALL_PINS, Bit_RESET);
				USART_SendString(USART1, "LEDler pasif.\r\n");
			}*/
		}
  }
}

static void RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

static void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIO_DeInit
	//GPIO_StructInit
	
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
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
}

static void USART1_Config(void)
{
	USART_InitTypeDef		USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate						=	9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								= USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_WordLength					= USART_WordLength_8b;
	USART_InitStructure.USART_Parity							= USART_Parity_No;
	USART_InitStructure.USART_StopBits						= USART_StopBits_1; // 8N1
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}

static void NVIC_Config(void)
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel 										= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority					= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd									= ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

static void USART_SendString(USART_TypeDef* USARTx, char* s)
{
	while(*s)
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
		USART_SendData(USARTx, *s);
		s++;
	}
}

/* ['X']['Y'][LedNo][LedValue]['Z'] */
static void LED_StateMachine(uint8_t rxData)
{
	static uint8_t state = 0;
	static uint8_t ledNo = 0;
	static uint8_t ledValue = 0;
	
	switch (state)
	{
		case 0:
			if (rxData == 'X')
			{
				state = 1;
				ledNo = 0;
				ledValue = 0;
			}
			break;
			
		case 1:
			if (rxData == 'Y')
			{
				state = 2;
			}
			break;
			
		case 2:
			if (rxData >= 1 && rxData <= 4 )
			{
				ledNo = rxData;
				state = 3;
			}
			else
			{
				// Tanim araligi disindaki led girisi
				state = 0;
			}
			break;
			
		case 3:
			if (rxData == 0 || rxData == 1)
			{
				ledValue = rxData;
				state = 4;
			}
			else
			{
				// Tanim araligi disindaki led deger girisi
				state = 0;
			}
			break;
			
		case 4:
			if (rxData == 'Z')
			{
				state = 0;
				LED_Control(ledNo, ledValue);
			}
			else
			{
				// Iletisim hatasi
				state = 0;
			}
			break;
	}
}

static void LED_Control(uint8_t ledNo, uint8_t value)
{
	uint8_t buffer[32];

	switch (ledNo)
	{
		case 1: GPIO_WriteBit(LED_GREEN_GPIO, LED_GREEN_PIN, (BitAction)value); break;
		case 2: GPIO_WriteBit(LED_ORANGE_GPIO, LED_ORANGE_PIN, (BitAction)value); break;
		case 3: GPIO_WriteBit(LED_RED_GPIO, LED_RED_PIN, (BitAction)value); break;
		case 4: GPIO_WriteBit(LED_BLUE_GPIO, LED_BLUE_PIN, (BitAction)value); break;
	}

	sprintf((char *)buffer, (const char *)"%d.LED = %d Durumuna Gecti\n", ledNo, value);

	USART_SendString(USART1, (char *)buffer);
}




