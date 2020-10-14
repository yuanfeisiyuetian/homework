/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"
#include "stm32l1xx_it.h"

#define GREEN_LED GPIO_Pin_5
#define BSRR_VAL 0x80

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

uint16_t CCR1_Val = 1000;
uint16_t CCR2_Val = 500;
uint16_t CCR3_Val = 250;
uint16_t CCR4_Val = 125;
uint16_t PrescalerValue = 0;


int irflag = 0;

int main(void)
{

	 RCC_PCLK1Config(RCC_HCLK_Div4); 

   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//NVIC Configuration of TIM3
   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
  
	//GPIO Configuration of A6\A7	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);//Channel_1
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);//Channel_2
  //GPIO Configuration of B0\B1
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);  
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);//Channel_3
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);//Channel_4
	 
	 //Time-Base Parameter config 
	 PrescalerValue = 16000 - 1;
   TIM_TimeBaseStructure.TIM_Period = 65535;          
   TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;       
   TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
   TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
   //Output comparison channel_1 settings
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;                   
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
   TIM_OCInitStructure.TIM_Pulse = CCR1_Val; 
   TIM_OC1Init(TIM3, &TIM_OCInitStructure);   
   TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
	 //Output comparison channel_2 settings
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;                   
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
   TIM_OCInitStructure.TIM_Pulse = CCR2_Val;    
   TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
   TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);
   //Output comparison channel_3 settings
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;                   
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
   TIM_OCInitStructure.TIM_Pulse = CCR3_Val;  
   TIM_OC3Init(TIM3, &TIM_OCInitStructure);
   TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable); 
   //Output comparison channel_4 settings
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;                   
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
   TIM_OC4Init(TIM3, &TIM_OCInitStructure);
   TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);
   //Output comparison channel Enable
   TIM_ITConfig(TIM3,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE);
   TIM_Cmd(TIM3, ENABLE);  //launch timer


		//waiting for Interrupt
		while (1)
		{

		}

}
