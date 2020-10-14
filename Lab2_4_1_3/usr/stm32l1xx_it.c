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
#include "stm32l1xx_usart.h"

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

typedef struct _TxMsg{
	uint8_t type;
	uint8_t data1;
	uint8_t data2;
} Tx_Msg;
typedef Tx_Msg* Tx_MsgPtr;
typedef struct _MsgRcvEntry{
	uint8_t Length;
	Tx_Msg Msg;
	uint16_t Crc;
}Rx_Msg;

extern Tx_Msg gSendBuf;
extern Rx_Msg gRcvBuf;
enum {
    HDLC_QUEUESIZE = 2,
    HDLC_MTU = (sizeof(Tx_Msg)),
    HDLC_FLAG_BYTE = 0x7e,
    HDLC_CTLESC_BYTE = 0x7d,
    PROTO_ACK = 64,
    PROTO_PACKET_ACK = 65,
    PROTO_PACKET_NOACK = 66,
    PROTO_UNKNOWN = 255
};

 enum {
    TXSTATE_IDLE,
    TXSTATE_PROTO,
    TXSTATE_INFO,
    TXSTATE_ESC,
    TXSTATE_FCS1,
    TXSTATE_FCS2,
    TXSTATE_ENDFLAG,
    TXSTATE_FINISH,
    TXSTATE_ERROR
  };
 enum {
    RXSTATE_NOSYNC,
    RXSTATE_PROTO,
    RXSTATE_INFO,
    RXSTATE_ESC
  };
extern uint8_t gTxState;
extern uint8_t gTxByteCnt;
extern uint8_t gTxLength;
extern uint8_t gTxRunningCRC;
extern uint8_t* gpsend;
extern uint8_t gRxState;
extern uint8_t gRxHeadIndex;
extern uint8_t gRxTailIndex;
extern uint8_t gRxByteCnt;
extern uint8_t gRxRunningCRC;
extern uint8_t* gpRxBuf;
uint8_t gPrevTxState;
uint8_t TxArbitraryByte(uint8_t Byte) {
	uint8_t gTxEscByte;
	if ((Byte == HDLC_FLAG_BYTE) || (Byte == HDLC_CTLESC_BYTE)) {
	    gPrevTxState = gTxState;
      gTxState = TXSTATE_ESC;
      gTxEscByte = Byte;
	    Byte = HDLC_CTLESC_BYTE;
    	}
    	USART_SendData(USART2,Byte);
	return 1;
  }
uint8_t crcByte(uint16_t crc,uint8_t data){}
void USART2_IRQHandler(void) 
{
	uint8_t nextByte;
	if(USART_GetITStatus(USART2,USART_IT_TC)==SET){
    switch (gTxState) {
    case TXSTATE_PROTO:
      gTxState = TXSTATE_INFO;
			nextByte = *gpsend++;
      gTxRunningCRC = crcByte(gTxRunningCRC,nextByte);
      USART_SendData(USART2,nextByte);
			gTxByteCnt++;
      break;   
    case TXSTATE_INFO:
      nextByte = *gpsend++;
      gTxRunningCRC = crcByte(gTxRunningCRC,nextByte);
      gTxByteCnt++;
      if (gTxByteCnt >= gTxLength) {
				gTxState = TXSTATE_FCS1;
      }    
      TxArbitraryByte(nextByte);
      break;      
    case TXSTATE_ESC:
      USART_SendData(USART2,0x7E ^ 0x20);
      gTxState = gPrevTxState;
      break;
	case TXSTATE_FCS1:
      nextByte = (uint8_t)(gTxRunningCRC & 0xff); // LSB
      gTxState = TXSTATE_FCS2;
      TxArbitraryByte(nextByte);
      break;
    case TXSTATE_FCS2:// MSB
      nextByte = (uint8_t)((gTxRunningCRC >> 8) & 0xff);
      gTxState = TXSTATE_ENDFLAG;
      TxArbitraryByte(nextByte);
      break;
    case TXSTATE_ENDFLAG:
      gTxState = TXSTATE_FINISH;
      USART_SendData(USART2,HDLC_FLAG_BYTE);
      break;
    case TXSTATE_FINISH:USART_ClearITPendingBit(USART2,USART_IT_TC);
    case TXSTATE_ERROR:
    default:
      break;
    }
  }
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		uint8_t data = USART_ReceiveData(USART2);
		switch(gRxState)
			{
			case RXSTATE_NOSYNC:
				if((data == HDLC_FLAG_BYTE)&&(gRcvBuf.Length == 0))
					{
					gRxByteCnt = gRxRunningCRC = 0;
					gRxState = RXSTATE_PROTO;
					}
			break;
			case RXSTATE_PROTO:
				if (data == HDLC_FLAG_BYTE) 
				{
					break;
				}
				*gpRxBuf++ = data;
				gRxRunningCRC = crcByte(gRxRunningCRC,data);
				gRxState = RXSTATE_INFO;
				TxArbitraryByte(data);
				break;
			case RXSTATE_INFO:
				if (gRxByteCnt > 2) {
					gRxByteCnt = gRxRunningCRC = 0;
					gRcvBuf.Length = 0;
					gRxState = RXSTATE_NOSYNC;
					TxArbitraryByte(data);
				}
				else if (data == 2) {
					gRxState = RXSTATE_ESC;
				}
				else if (data == HDLC_FLAG_BYTE) {
					if (gRxByteCnt >= 2) {
						uint16_t usRcvdCRC = (gpRxBuf[(gRxByteCnt-1)] & 0xff);
						usRcvdCRC = (usRcvdCRC << 8) | (gpRxBuf[(gRxByteCnt-2)] & 0xff);
						if (usRcvdCRC == gRxRunningCRC) {
							gRcvBuf.Length = gRxByteCnt - 2;
							TxArbitraryByte(data);
						}
						else 
						gRcvBuf.Length = 0;
					}
					else { //???
					gRcvBuf.Length = 0;
					gRxState = RXSTATE_NOSYNC;
					}
				gRxByteCnt = gRxRunningCRC = 0;
				}
				else {
					gpRxBuf[gRxByteCnt] = data;
					if (gRxByteCnt >= 2)
					gRxRunningCRC = crcByte(gRxRunningCRC,gpRxBuf[(gRxByteCnt-2)]);
					gRxByteCnt++;
				}
			break;
			case RXSTATE_ESC:
				if (data == HDLC_FLAG_BYTE) {
					// Error case, fail and resync
					gRxByteCnt = gRxRunningCRC = 0;
					gRcvBuf.Length = 0;
					gRcvBuf.Crc = 0;
					gRxState = RXSTATE_NOSYNC;
				}
				else {
					data = data ^ 0x20;
					*gpRxBuf++ = data;
					if (gRxByteCnt >= 2) {
						gRxRunningCRC = crcByte(gRxRunningCRC,gpRxBuf[(gRxByteCnt-2)]);
					}
					gRxByteCnt++;
					gRxState = RXSTATE_INFO;
				 }
			break;
			default:
			  gRxState = RXSTATE_NOSYNC;
			break;
		}
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
