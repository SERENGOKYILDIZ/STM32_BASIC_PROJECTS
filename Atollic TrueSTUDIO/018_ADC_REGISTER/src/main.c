#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t adc_value;

void RCC_Config(void)
{
	/*
	 * @brief:
	 * We can change a specific byte value with '|=' (OR).
	 * We can write the new value over the current value with '&=' (AND).
	 * The '~' sign takes the reverse of the expression.
	 *
	 *
	 *@clock:
	 *(PLL_M:4, PLL_N:168, PLL_P:2)
	 *SYSCLK = [(8Mhz/4)*168/2] = 168Mhz
	 *-//////////////////////
	 *SYSCLK = 168Mhz
	 *AHB    = 168Mhz (Prescaler:1)
	 *APB1   = 42Mhz  (Prescaler:4)
	 *APB2   = 84Mhz  (Prescaler:2)
	 *-///////////////////////
	*/

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
	ADC1->CR1 |= (2 << 24);             //->Resolution = 8 bit
	ADC1->CR2 |= (1 << 0);              //->ADC = Enabled
	ADC1->SMPR2 |= (3 << 0);            //->The Channel0 of Sample Cycle = 56 cycles
}
uint8_t Read_ADC()
{
	uint8_t value;

	ADC1->CR2 |= (1<<30);              	//->Start Conversion

	while(!(ADC1->SR & 0x2));           //->Wait Flag of End of conversion

	value = ADC1->DR;                   //->Read value

	return value;
}
void delay(uint32_t time)
{
	while(--time);
}
int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	while (1)
	{
		adc_value = Read_ADC();
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
