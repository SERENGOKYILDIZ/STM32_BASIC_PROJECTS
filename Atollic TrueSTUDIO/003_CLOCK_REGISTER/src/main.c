#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
uint32_t system_clock;

//--> Using HSE with Register config <--//
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
int main(void)
{
	system_clock = SystemCoreClock;
	RCC_Config();
	system_clock = SystemCoreClock;
	while (1)
	{

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
