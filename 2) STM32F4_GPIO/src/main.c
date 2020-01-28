#include "main.h"
#include "defines.h"

int main(void)
{
	//SystemInit();
	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	
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
	
	//GPIO_SetBits(GPIOx, GPIO_Pin); 					// Ilgili portun ilgili bitini lojik 1 yap
	//GPIO_ResetBits(GPIOx, GPIO_Pin);  			// Ilgili portun ilgili bitini lojik 0 yap
	//GPIO_ToggleBits(GPIOx, GPIO_Pin); 			// Ilgili portun ilgili bitini tersle
	//GPIO_Write(GPIOx, value);								// Ilgili porta value degerini ata
	//GPIO_WriteBit(GPIOx, GPIO_Pin, value); 	// Ilgili portun ilgili bitine value degerini ata
	//GPIO_ReadInputDataBit(GPIOx, GPIO_Pin); // Ilgili portun ilgili bitini oku
	//GPIO_ReadInputData(GPIOx);							// Ödev
	//GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin);// Ödev
	//GPIO_ReadOutputData(GPIOx);							// Ödev

  while (1) // Sonsuz Dongu
  {
		
		/*if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1) 
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		}
		else
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		}*/
		
		/*if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1) 
		{
			GPIO_WriteBit(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, Bit_SET);
		}
		else
		{
			GPIO_WriteBit(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, Bit_RESET);
		}*/
		
		/*if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1) 
		{
			GPIO_Write(GPIOD, 0xF000); // 1111 0000 0000 0000
		}
		else
		{
			GPIO_Write(GPIOD, 0x0000); // 0000 0000 0000 0000
		}*/

		//GPIO_WriteBit(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
		
		uint32_t buttonState = GPIO_ReadInputDataBit(BUTTON_GPIO, BUTTON_PIN);
		
		// Casting islemi (BitAction)buttonState
		GPIO_WriteBit(LED_ALL_GPIO, LED_ALL_PINS, (BitAction)buttonState);
		
  }
}







