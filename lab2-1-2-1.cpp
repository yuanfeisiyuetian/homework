/* Includes ---------------*/
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"



GPIO_InitTypeDef        GPIO_InitStructure;

void Delay(__IO uint32_t nCount)
{
   while(nCount--);

 }

void GPIO_Configuration(void)
{
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}                                         
int main(void)
{ 
	GPIO_Configuration();
	int truthtable[8][3]={{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
	int x=0;
	int i=0;
   while (1)
   {
		 i=x%8;
		 GPIO_WriteBit(GPIOB,GPIO_Pin_4,truthtable[i][0]);
		 GPIO_WriteBit(GPIOB,GPIO_Pin_6,truthtable[i][1]);
		 GPIO_WriteBit(GPIOA,GPIO_Pin_7,truthtable[i][2]);

		 Delay(2000000);
	   x++;
		 
   }
}