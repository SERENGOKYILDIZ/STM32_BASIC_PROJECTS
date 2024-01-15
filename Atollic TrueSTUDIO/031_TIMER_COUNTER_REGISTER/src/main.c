#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count;

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
void TIM_Config()
{
	RCC->APB1ENR |= 1<<0;              	//->Enabled clock of TIM2.

	TIM2->CR1 |= 0<<4;             		//->Counter mode is upcounter.
	TIM2->CR1 |= 0<<5;             		//->Center aligned mode is edge-aligned mode.
	TIM2->CR1 |= 0<<8;             		//->Set the clock division to 1.
	TIM2->SMCR |= 0<<0;            		//->Internal clock source.
	TIM2->EGR |= 1<<0;                 	//->Timer update generation.

	TIM2->PSC = 41999;                  //->Prescaler = 42000.
	TIM2->ARR = 2000;                   //->Auto-Reload = 2000.

	TIM2->CR1 |= 1<<0;                  //->Enabled counter.
}
int main(void)
{
	RCC_Config();
	TIM_Config();
	while (1)
	{
		count = TIM2->CNT;             	//->Read the value of TIM2 counter.
	}
}












void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
