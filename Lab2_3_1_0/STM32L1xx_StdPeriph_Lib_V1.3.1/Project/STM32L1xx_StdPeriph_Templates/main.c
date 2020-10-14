/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"
#include "stm32l1xx_it.h"

GPIO_InitTypeDef  GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;	
TIM_OCInitTypeDef TIM_OCInitStructure;

//void Delay(__IO uint32_t nCount)
//{
//	while(nCount--)
//	{
//		
//	}
//}

void GPIO_Configuration(void)
{
	/*GPIOD Periph clock enable*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	

	/*Configure PB7 in output pushpull mode*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void TIM_Configuration(void)
{
	
}
int flag = 0x00;
int main(void)
{

	GPIO_Configuration(); 
//	NVIC_Configuration();
//	EXTI_Configuration();
	/*GPIOD Periph clock enable*/
	SysTick_Config(500*32*1000);
	while(1)
	{		
		if(flag)
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	}
}	
