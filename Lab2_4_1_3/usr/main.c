/*includes ----*/

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_conf.h"
#include "stm32l1xx_it.h"
#include "stm32l1xx_usart.h"
#include "stdio.h"

GPIO_InitTypeDef  GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;;
USART_InitTypeDef USART_InitStructure;

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

Tx_Msg gSendBuf = {65,1,2};
Rx_Msg gRcvBuf;

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



uint8_t gTxState = TXSTATE_PROTO;
uint8_t gTxByteCnt = 0;
uint8_t gTxLength = sizeof(gSendBuf);
uint8_t gTxRunningCRC = 0;
uint8_t* gpsend = (uint8_t*)(&gSendBuf);
uint8_t gRxState = RXSTATE_NOSYNC;
uint8_t gRxHeadIndex = 0;
uint8_t gRxTailIndex = 0;
uint8_t gRxByteCnt = 0;
uint8_t gRxRunningCRC = 0;
uint8_t* gpRxBuf = (uint8_t*)(&gRcvBuf.Msg);



void Configuration(void)
{
	/*GPIOD Periph clock enable*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	USART_InitStructure.USART_BaudRate = 19200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART2,&USART_InitStructure);
	//配置接收中断
	//USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	USART_ClearITPendingBit(USART2,USART_IT_TC);		
	
	//灯亮的管脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//USART2 TX PA9

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//RX PA10

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

	USART_Cmd(USART2,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}


int main(void)
{
	Configuration();

	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
//	USART_ITConfig(USART2,USART_IT_TC,ENABLE);
//	USART_SendData(USART2,HDLC_FLAG_BYTE);
	while(1);
}	
