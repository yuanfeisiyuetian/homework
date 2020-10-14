/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"

#define GREEN_LED GPIO_Pin_5
//#define BSRR_VAL 0x80

GPIO_InitTypeDef  GPIO_InitStructure;

void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
		
	}
}

int main(void)
{
	/*GPIOD Periph clock enable*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	/*Configure PB7 in output pushpull mode*/
	GPIO_InitStructure.GPIO_Pin = GREEN_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	while(1)
	{
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		Delay (1000000);	//0.5s
	}
}

