/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"
#include "stm32l1xx_rcc.h"

#define GREEN_LED GPIO_Pin_5
//#define BSRR_VAL 0x80

GPIO_InitTypeDef  GPIO_InitStructure;

void Delay(__IO uint32_t nCount)
{
	while (nCount--)
	{

	}
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GREEN_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}
int main(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOC, ENABLE);
	GPIO_Configuration();
	while (1)
	{
		if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)) {
			Delay(1000);
			if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))
				GPIO_SetBits(GPIOA, GREEN_LED);
		}
		else {
			Delay(1000);
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))
				GPIO_ResetBits(GPIOA, GREEN_LED);
		}
	}
}
