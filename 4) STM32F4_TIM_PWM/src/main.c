#include "main.h"
#include "defines.h"

int main(void)
{
	RCC_Config();
	GPIO_Config();
	TIM1_Config();
	
	/*****************************************/
	/** SystemCoreClock / 1000      1ms      */
	/** SystemCoreClock / 10000     100us    */
	/** SystemCoreClock / 100000    10us     */
	/** SystemCoreClock / 1000000   1us      */
	/*****************************************/
	SysTick_Config(SystemCoreClock / 1000);
	
	PWM_SetDuty(TIM1, 1, TIM_PERIOD, 50); // TIM1->CCR1  = PWM_PERIOD / 2 
	PWM_SetDuty(TIM1, 2, TIM_PERIOD, 50); // TIM1->CCR2  = PWM_PERIOD / 2 
	
  while (1)
  {
		
  }
}

static void RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
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
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9 | GPIO_Pin_11; // TIM1_CH1 ve TIM1_CH2
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14; // TIM1_CH1N ve // TIM1_CH2N
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1); // TIM1_CH1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);// TIM1_CH2
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_TIM1);// TIM1_CH1N
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM1);// TIM1_CH2N
}

static void TIM1_Config(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef				TIM_OCInitStructure;
	TIM_BDTRInitTypeDef 		TIM_BDTRInitStructure;
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision 		= TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode 			= TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period						= TIM_PERIOD;
	TIM_TimeBaseInitStructure.TIM_Prescaler					= TIM_PRESCALER;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter	= 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	/* PWM Ayarlari - Kesme için bu blok kullanilmayacak. */
	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse				= TIM_PERIOD / 2;
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity	= TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState= TIM_OCNIdleState_Reset;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	
	TIM_BDTRInitStructure.TIM_OSSRState 			= TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState 			= TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel 			= TIM_LOCKLevel_1;
	TIM_BDTRInitStructure.TIM_DeadTime 				= 100; // Dead Time
	TIM_BDTRInitStructure.TIM_Break 					= TIM_Break_Enable;
	TIM_BDTRInitStructure.TIM_BreakPolarity 	= TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

static void PWM_SetDuty(TIM_TypeDef* TIMx, uint8_t OCx, uint16_t period, uint8_t duty)
{
	switch(OCx)
	{
		case 1: TIMx->CCR1 = (duty * period) / 100; break;
		case 2: TIMx->CCR2 = (duty * period) / 100; break;
		case 3: TIMx->CCR3 = (duty * period) / 100; break;
		case 4: TIMx->CCR4 = (duty * period) / 100; break;
	}
}








