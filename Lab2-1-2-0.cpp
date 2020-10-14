/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"
#include "stm32l1xx_rcc.h"

#define RED_LED GPIO_Pin_7
#define GREEN_LED GPIO_Pin_8
#define BLUE_LED GPIO_Pin_3

GPIO_InitTypeDef  GPIO_InitStructure;

void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
	}
}

void GPIO_Configuration(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = RED_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GREEN_LED;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BLUE_LED;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//????и║?ии?
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
int main(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC,ENABLE);
	GPIO_Configuration();
	while(1)
	{	
		Delay(100000);
		GPIO_SetBits(GPIOC,RED_LED);
		Delay(100000);
		GPIO_SetBits(GPIOA,GREEN_LED);
		Delay(100000);
		GPIO_SetBits(GPIOB,BLUE_LED);
		Delay(100000);
		GPIO_ResetBits(GPIOC,RED_LED);
		Delay(100000);
		GPIO_ResetBits(GPIOA,GREEN_LED);
		Delay(100000);
		GPIO_ResetBits(GPIOB,BLUE_LED);
		if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)){
				while(1){
					GPIO_ResetBits(GPIOC,RED_LED);
					GPIO_ResetBits(GPIOA,GREEN_LED);
					GPIO_ResetBits(GPIOB,BLUE_LED);
					Delay(1000000);
					GPIO_SetBits(GPIOC,RED_LED);
					Delay(1000000);
					GPIO_ResetBits(GPIOC,RED_LED);
					GPIO_SetBits(GPIOA,GREEN_LED);
					Delay(1000000);
					GPIO_SetBits(GPIOC,RED_LED);
					GPIO_SetBits(GPIOA,GREEN_LED);
					Delay(1000000);
					GPIO_SetBits(GPIOB,BLUE_LED);
					GPIO_ResetBits(GPIOC,RED_LED);
					GPIO_ResetBits(GPIOA,GREEN_LED);
					Delay(1000000);
					GPIO_SetBits(GPIOC,RED_LED);
					Delay(1000000);
					GPIO_ResetBits(GPIOC,RED_LED);
					GPIO_SetBits(GPIOA,GREEN_LED);
					Delay(1000000);
					GPIO_SetBits(GPIOC,RED_LED);
					GPIO_SetBits(GPIOA,GREEN_LED);
					Delay(1000000);
					}
			}
		}
}

