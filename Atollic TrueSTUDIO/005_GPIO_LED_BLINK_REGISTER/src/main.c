#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

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
	RCC->AHB1ENR |= 1 << 3; 				//-> We enabled the clock line of GPIOD.

	//Pin of 12 became output.
	GPIOD->MODER |= 1 << 24;
	GPIOD->MODER &= ~(1 << 25);

	//Pin of 13 became output.
	GPIOD->MODER |= 1 << 26;
	GPIOD->MODER &= ~(1 << 27);

	//Pin of 14 became output.
	GPIOD->MODER |= 1 << 28;
	GPIOD->MODER &= ~(1 << 29);

	//Pin of 15 became output.
	GPIOD->MODER |= 1 << 30;
	GPIOD->MODER &= ~(1 << 31);

	//->Anyway, we didn't do anything because the default settings are push-pull.

	GPIOD->OSPEEDR |= 0xff000000; 			//-> All pins became very speed.
	//GPIOD->OSPEEDR |= 0xff << 24; 		//-> Any way of another.

	//->Anyway, we didn't do anything because the default settings are pull-up/pull-down.
}
int main(void)
{
	//Settings of Clock
	RCC_Config();
	//Settings of GPIO
	GPIO_Config();

	while (1)
	{
		GPIOD->ODR |= 1 << 12; 			//-> Pin of 12 became set.
		GPIOD->ODR |= 1 << 13; 			//-> Pin of 13 became set.
		GPIOD->ODR |= 1 << 14; 			//-> Pin of 14 became set.
		GPIOD->ODR |= 1 << 15; 			//-> Pin of 15 became set.
		for(int i=0; i<1680000; i++); 	//-> Program waits.

		GPIOD->ODR &= ~(1 << 12); 		//-> Pin of 12 became reset.
		GPIOD->ODR |= 1 << 13; 			//-> Pin of 13 became set.
		GPIOD->ODR |= 1 << 14; 			//-> Pin of 14 became set.
		GPIOD->ODR |= 1 << 15;			//-> Pin of 15 became set.
		for(int i=0; i<1680000; i++); 	//-> Program waits.
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
