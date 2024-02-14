#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

char str[50];

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); 	//->For AF pins. (We do USART TX pin that A2 pin)

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;  					//->For USART pins.
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;      				//->Which pins become USART pins.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void USART_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2, &USART_InitStruct);

	USART_Cmd(USART2, ENABLE);
}
void USART_Puts(USART_TypeDef* USARTx, volatile char *data)
{
	while(*data)
	{
		while(!(USARTx->SR & 0x40)); 			//->Wait USART
		USART_SendData(USARTx, *data);
		*data++;
	}
}
void delay(uint32_t time)
{
	while(time--);
}
int main(void)
{
	GPIO_Config();
	USART_Config();
	while (1)
	{
		sprintf(str, "Hello World!\n");
		USART_Puts(USART2, str);
		delay(21000);
	}
}











void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
