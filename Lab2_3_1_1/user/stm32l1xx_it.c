/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    20-April-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "stm32l1xx.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_tim.h"
/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

uint16_t capture = 0;;
extern uint16_t CCR1_Val;
extern uint16_t CCR2_Val;
extern uint16_t CCR3_Val;
extern uint16_t CCR4_Val;
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_CC1)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
		capture = TIM_GetCapture1(TIM3);
		TIM_SetCompare1(TIM3,capture+CCR1_Val);
	}
	else if(TIM_GetITStatus(TIM3,TIM_IT_CC2)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC2);
		capture = TIM_GetCapture2(TIM3);
		TIM_SetCompare2(TIM3,capture+CCR2_Val);
	}
	else if(TIM_GetITStatus(TIM3,TIM_IT_CC3)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC3);
		capture = TIM_GetCapture3(TIM3);
		TIM_SetCompare3(TIM3,capture+CCR3_Val);
	}
	else
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC4);
		capture = TIM_GetCapture4(TIM3);
		TIM_SetCompare4(TIM3,capture+CCR4_Val);
	}
}

void SysTick_Handler(void)
{
	
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
//void EXTI15_10_IRQHandler(void){
//		if(EXTI_GetITStatus(EXTI_Line13) != RESET){
//			GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
//			EXTI_ClearITPendingBit(EXTI_Line13);
//		}
//}
// void EXTI0_IRQHandler(void)
// {
//   if(EXTI_GetITStatus(EXTI_Line0) != RESET)
//   {
//     /* Toggle LED1 */
//     //STM_EVAL_LEDToggle(LED1);
//     GPIO_ToggleBits(GPIOB, GPIO_Pin_7);
//     /* Clear the EXTI line 0 pending bit */
//     EXTI_ClearITPendingBit(EXTI_Line0);
//   }
// }
 
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
