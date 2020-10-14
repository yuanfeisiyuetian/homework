
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_tim.h"

uint32_t SCC=16000000;
uint32_t DutyCycle;
uint32_t Frequency;

	 uint16_t CCR1Val = 1500;
   uint16_t CCR2_Val = 1500;
   uint16_t CCR3_Val = 250;
   uint16_t CCR4_Val = 125;
   uint16_t PrescalerValue = 16000;

int main(void)
{

	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

	

   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//PB9 OUTPUT PWM
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_TIM9);

	 TIM_TimeBaseStructure.TIM_Period = 5333;          
   TIM_TimeBaseStructure.TIM_Prescaler = 0;       
   TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
   TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
	 
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_Pulse = 2667;
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
   TIM_OC1Init(TIM9, &TIM_OCInitStructure);
   TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
   TIM_ARRPreloadConfig(TIM9, ENABLE);

   TIM_Cmd(TIM9, ENABLE); 
	 
	 
	

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


	 


  
   NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);


	 
	 
	 
	 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;//PA7
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	 GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);


	 TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
   TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
   TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
   TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
   TIM_ICInitStructure.TIM_ICFilter = 0x0;
	 TIM_ICInit(TIM4,&TIM_ICInitStructure);
   TIM_PWMIConfig(TIM4, &TIM_ICInitStructure);
   TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2);
   TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
   TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);
   TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE); 
   TIM_Cmd(TIM4, ENABLE);

 
	 
while (1)
  {

  }
}


void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}
