/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"
#include "stm32l1xx_it.h"

GPIO_InitTypeDef  GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;


uint16_t CCR1_Val = 2667;
uint16_t CCR2_Val = 1334;
uint16_t CCR3_Val = 889;
uint16_t CCR4_Val = 667;
uint16_t PrescalerValue = 0;

//void Delay(__IO uint32_t nCount)
//{
//	while(nCount--)
//	{
//		
//	}
//}

void Configuration(void)
{
	/*GPIOD Periph clock enable*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
	//zhubanshangde
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);

	
	TIM_TimeBaseStructure.TIM_Period = 5334;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM11, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM11, ENABLE);

	TIM_Cmd(TIM11,ENABLE);
	
   
 //TIM3???????GPIO????
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   //PA7????GPIO????
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
// TIM3????
   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	  // TIM3 PWM??????,??2,???,CCR2????,CCR1??    ???,???????
   TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
   TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
   TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
   TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
   TIM_ICInitStructure.TIM_ICFilter = 0x0;
   //??PWMIConfig?????
   TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);
   //??????TI2
   TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);
   //????????????
   TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
   //??????
   TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
	 TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE); //??TIM3??2??
   TIM_Cmd(TIM3, ENABLE); //?????
  
}

int main(void)
{
	Configuration();
	while(1){		}
}	
