/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"

void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
		
	}
}

void GPIO_Configuration(void)
{
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOA, ENABLE);	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 

		
	//??COL????
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	GPIO_SetBits(GPIOC,GPIO_Pin_5);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	//??ROW????
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);//?PA3
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);//?PA2
	//??? ?5?6?7?8 ??,??

}

int main(void)
{
	GPIO_Configuration(); 				//???????
	uint8_t Character[8][8]={
													0,0,0,0,0,0,0,0,
													0,1,1,0,0,1,1,0,
													1,1,1,1,1,1,1,1,
													1,1,1,1,1,1,1,1,
													0,1,1,1,1,1,1,0,
													0,0,1,1,1,1,0,0,
													0,0,0,1,1,0,0,0,
													0,0,0,0,0,0,0,0,
												};
	while(1)
	{		
		int i,j;
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			if(Character[i][j]==1)
			{
				if(i==0)
				GPIO_ResetBits(GPIOA,GPIO_Pin_6);
				if(i==1)
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
				if(i==2)
				GPIO_ResetBits(GPIOA,GPIO_Pin_12);
				if(i==3)
				GPIO_ResetBits(GPIOC,GPIO_Pin_5);
				if(i==4)
				GPIO_ResetBits(GPIOB,GPIO_Pin_8);
				if(i==5)
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
				if(i==6)
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
				if(i==7)
				GPIO_ResetBits(GPIOC,GPIO_Pin_9);
				if(j==0)
					GPIO_SetBits(GPIOC,GPIO_Pin_2);//?PA2
				if(j==1)
					GPIO_SetBits(GPIOA,GPIO_Pin_11);
				if(j==2)
					GPIO_SetBits(GPIOC,GPIO_Pin_3);
				if(j==3)
					GPIO_SetBits(GPIOA,GPIO_Pin_0);
				if(j==4)
					GPIO_SetBits(GPIOC,GPIO_Pin_6);
				if(j==5)
					GPIO_SetBits(GPIOB,GPIO_Pin_9);
				if(j==6)
					GPIO_SetBits(GPIOC,GPIO_Pin_8);
				if(j==7)
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
				GPIO_ResetBits(GPIOC,GPIO_Pin_8);
				GPIO_ResetBits(GPIOB,GPIO_Pin_9);
				GPIO_ResetBits(GPIOC,GPIO_Pin_6);
				GPIO_ResetBits(GPIOA,GPIO_Pin_0);
				GPIO_ResetBits(GPIOC,GPIO_Pin_3);//?PA3
				GPIO_ResetBits(GPIOA,GPIO_Pin_11);
				GPIO_ResetBits(GPIOC,GPIO_Pin_2);//?PA2
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
				GPIO_SetBits(GPIOA,GPIO_Pin_12);
				GPIO_SetBits(GPIOC,GPIO_Pin_5);
				GPIO_SetBits(GPIOB,GPIO_Pin_8);
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOC,GPIO_Pin_9);
			}
				
		}
	}
}	
