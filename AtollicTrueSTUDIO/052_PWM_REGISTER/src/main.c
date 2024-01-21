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
void GPIO_Config()
{
	RCC->AHB1ENR |= 1 << 3;                                		//->GPIOD Clock enable

	GPIOD->MODER |= 2 << 24 | 2 << 26 | 2 << 28 | 2 << 30;      //->D12, D13, D14, D15 = AF
	GPIOD->AFR[1] |= 2 << 16 | 2 << 20 | 2 << 24 | 2 << 28;    	//->D12, D13, D14, D15 = TIM4
}
void TIM_Config()
{
	RCC->APB1ENR |= 1<<2;              						//->Enabled clock of TIM4.

	TIM4->CR1 |= 0<<4;             							//->Counter mode is upcounter.
	TIM4->CR1 |= 0<<5;             							//->Center aligned mode is edge-aligned mode.
	TIM4->CR1 |= 0<<8;             							//->Set the clock division to 1.
	TIM4->CCMR1 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12; 		//->CCP1&CCP2 output selected, CCP1&CCP2 = PWM mode 1
	TIM4->CCMR2 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12; 		//->CCP3&CCP4 output selected, CCP3&CCP4 = PWM mode 1
	TIM4->CCER  |= 1 << 0 | 1 << 4 | 1 << 8 | 1 << 12;      //->CCP1&CCP2&CCP3&CCP4 = output enabled
	TIM4->PSC = 8399;                                       //->Prescaler = 8399
	TIM4->ARR = 9999;                                       //->Period = 9999

	TIM4->CCR1 = 2499;                                       //->Channel1 Pulse = 2499
	TIM4->CCR2 = 4999;                                       //->Channel2 Pulse = 4999
	TIM4->CCR3 = 7499;                                       //->Channel3 Pulse = 7499
	TIM4->CCR4 = 9999;                                       //->Channel4 Pulse = 9999

	TIM4->CR1 |= 1 << 0;                                    //->Counter mode = enabled
}
int main(void)
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	while (1)
	{

	}
}












void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
