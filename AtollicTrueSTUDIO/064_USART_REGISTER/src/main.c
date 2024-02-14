#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

char Rx_buff[50];
int i=0;

void RCC_Config(void)
{
	//Settings of Opening HSE
	RCC->CR &= ~(1 << 0);               //->HSION = 0, (HSI=OFF)
	while((RCC->CR & 0X3));				//->Wait HSI deactivate.
	RCC->CR |= (1 << 16); 				//->HSEON = 1, (HSE=ON)
	while(!(RCC->CR & (1 << 17))); 		//->Wait HSE active

	//Settings of PLL
	RCC->CR |= (1<<19); 				//->CSSON = 1.
	RCC->PLLCFGR |= (1 << 22); 			//->PLLSRC = 1, (PLL Source = HSE)
	RCC->PLLCFGR |= (4<<0); 			//->PLL_M = 4
	RCC->PLLCFGR |= (168<<6); 			//->PLL_N = 168
	RCC->PLLCFGR |= 0x00; 				//->PLL_P = 2

	//Settings of Prescaler
	RCC->CFGR = 0x0;                    //->AHB  Prescaler = 1
	RCC->CFGR |= (5 << 10);             //->APB1 Prescaler = 4
	RCC->CFGR |= (4 << 13);             //->APB2 Prescaler = 2

	RCC->CR = (1<<19);                  //-> HSERDY Flag clear.
	RCC->CR = (1<<23);                  //-> CSS Flag clear.
	SystemCoreClockUpdate();
}
void GPIO_Config(void)
{
	RCC->AHB1ENR |= 0x2; 				//->Clock of GPIOB = Enabled
	GPIOB->MODER |= (2 << 20);          //->B10 = Alternate function Mode.
	GPIOB->MODER |= (2 << 22);          //->B11 = Alternate function Mode.
	GPIOB->AFR[1] |= (7 << 8);          //->AF7 for B10.
	GPIOB->AFR[1] |= (7 << 12);         //->AF7 for B11.
}
void USART_Config()
{
	RCC->APB1ENR |= (1 << 18);        	//->Clock of USART3 = Enabled

	USART3->BRR = 0x1112;               //->Baud rate = 9600
	USART3->CR1 |= (1 << 2);            //->RX = Enabled
	USART3->CR1 |= (1 << 3);            //->TX = Enabled
	USART3->CR1 |= (1 << 5);            //->RXNE (RX Interrupt) = Enabled
	USART3->CR1 |= (0 << 10);           //->Parity = None
	USART3->CR1 |= (0 << 12);           //->Word Lenght = 8 bit

	USART3->CR2 |= (0 << 12);           //->Stop bit = 1 bit

	USART3->CR1 |= (1 << 13);           //->USART = Enabled
}
void NVIC_Config()
{
	NVIC->ISER[1] |= 1 << 7;            //->Read the flag of TXE
}



void USART3_IRQHandler()
{
	volatile int Str;
	Str = USART3->SR;
	Rx_buff[i] = USART3->DR;
	i++;
}
void Send_Char(char ch)
{
	while(!(USART3->SR & 0x80));    	 //->Check the flag of TXE
	USART3->DR = ch;
}
void Send_Message(char *Str)
{
	while(*Str)
	{
		Send_Char(*Str);
		Str++;
	}
}
int main(void)
{
	RCC_Config();
	GPIO_Config();
	USART_Config();
	NVIC_Config();
	while (1)
	{
		Send_Message("Hello World\n");
		for(int i=0;i<1000000;i++);
	}
}














void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
