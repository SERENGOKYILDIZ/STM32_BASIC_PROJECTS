#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define Buffer_Lenght 1
uint32_t adc_value[Buffer_Lenght];

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
	RCC->AHB1ENR |= 0x1; 				//->Clock of GPIOA = Enabled
	GPIOA->MODER |= 0x3;                //->A0 = Analog Input.
	GPIOA->OTYPER |= 0x1;       		//->A0 = Open Drain.
	GPIOA->OSPEEDR |= 0x3;   			//->A0 = Very High speed.
}
void ADC_Config()
{
	//Clock
	RCC->APB2ENR |= (1<<8);             //->Clock of ADC1 = Enabled
	ADC->CCR |= (1 << 16);              //->PCLK2 = 4div (84Mhz/4 = 21Mhz) ("21Mhz<30Mhz" must meet the requirement)

	//ADC1
	ADC1->CR1 |= 1 << 8;                //->Scan Mode = Enabled
	ADC1->CR1 |= (0 << 24);             //->Resolution = 12 bit

	ADC1->CR2 |= 1 << 0;                //->ADC = Enabled
	ADC1->CR2 |= 1 << 1;                //->Continuous Conversion Mode = Enabled
	ADC1->CR2 |= 1 << 8;                //->DMA Mode = Enabled
	ADC1->CR2 |= 1 << 9;                //->DMA Requests = Enabled
	ADC1->CR2 |= 1 << 10;               //->EOC Flag = Enabled
	ADC1->CR2 |= 1 << 30;               //->Start Conversion

	ADC1->SQR1 |= (Buffer_Lenght - 1) << 20;  //->How many ADCs are reading. (1 In our project)
}
void DMA_Config()
{
	RCC->AHB1ENR |= 1 << 22;        	//->DMA2 Clock = Enabled

	while((DMA2_Stream4->CR & 0x1) == 1); //->If DMA2_Stream4's first bit of CR Register is 1, wait until it is 0.

	DMA2_Stream4->CR |= 0 << 6;        	//->Peripheral to Memory
	DMA2_Stream4->CR |= 1 << 8;         //->Circular Mode = Enabled
	DMA2_Stream4->CR |= 0 << 9;         //->Peripheral Inc = Disabled
	DMA2_Stream4->CR |= 1 << 10;        //->Memory Inc = Enabled
	DMA2_Stream4->CR |= 2 << 11;        //->Peripheral Data Size = 32bit
	DMA2_Stream4->CR |= 2 << 13;        //->Memory Data Size = 32bit
	DMA2_Stream4->CR |= 3 << 16;        //->Priority level = Very High
	DMA2_Stream4->CR |= 0 << 25;        //->Channel = Channel 0

	DMA2_Stream4->NDTR |= 1;            //->How many DMA channels. (1 In out project)

	DMA2_Stream4->PAR |= (uint32_t) &ADC1->DR;       	//->It is ADC1 data register.
	DMA2_Stream4->M0AR |= (uint32_t) &adc_value;       	//->It is our value.

	DMA2_Stream4->FCR |= 1 << 0;                        //->FIFO threshold = 1/2 full FIFO

	DMA2_Stream4->CR |= 1 << 0;         //->Stream4 = Enabled
}
int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	DMA_Config();

	ADC1->CR2 |= 1 << 30;              	//->ADC and DMA are started
	while (1)
	{

	}
}




void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  return -1;
}
