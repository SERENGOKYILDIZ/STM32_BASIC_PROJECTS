#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t myRandomNumber;

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

void RNG_Config(void)
{
	RCC->AHB2ENR |= (1 << 6);           //-> The clock RNG is enable

	RNG->CR |= (1 << 2);              	//-> RNGEN is enable
}

void delay(uint32_t time)
{
	/*
	 * ===============================
	 * -> (while) it takes 4 cycles
	 * -> (time--) it takes 4 cycles
	 *
	 * -> That's a total of 8 cycles.
	 * ===============================
	 * -> Our freq is 168Mhz;
	 * -> 168Mhz/8 = 21Mhz ; 1 second = 21Mhz
	 * ===============================
	 *
	 * -> We can write 21Mhz for 1 second.
	 *
	 * */
	while(time--);
}

int main(void)
{
	RCC_Config();
	RNG_Config();
	while (1)
	{
		myRandomNumber = RNG->DR;     	//->Reading RNG data.
		delay(21000000);
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
