#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

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
void GPIO_Config(void)
{
	RCC->AHB1ENR = 0x9; 				//->GPIOA and GPIOD clock's enabled.

	//Settings of GPIOD
	GPIOD->MODER |= (0x55 << 24);   	//->D12, D13, D14, D15 = Output.
	GPIOD->OTYPER |= (0xff << 3);       //->D12, D13, D14, D15 = Open-drain.
	GPIOD->OSPEEDR |= (0xff << 24);   	//->D12, D13, D14, D15 = Very High speed.
}
void EXTI_Config()
{
	RCC->APB2ENR |= 1 << 14;           	//->SYSCFG(EXTI) = Enabled.
	SYSCFG->EXTICR[0] = 0x000;          //->EXTI = GPIOA.

	NVIC_EnableIRQ(EXTI0_IRQn);         //->Interrupt for EXTI0 = Enable.
	NVIC_EnableIRQ(EXTI1_IRQn);         //->Interrupt for EXTI1 = Enable.
	NVIC_EnableIRQ(EXTI2_IRQn);         //->Interrupt for EXTI2 = Enable.

	NVIC_SetPriority(EXTI0_IRQn, 0);    //->Priority of EXTIO = 0.
	NVIC_SetPriority(EXTI1_IRQn, 1);    //->Priority of EXTIO = 1.
	NVIC_SetPriority(EXTI2_IRQn, 2);    //->Priority of EXTIO = 2.

	//@brief The priority of EXTI is EXTI0.

	EXTI->IMR = 0x7;                    //->0111 = These became interrupts.
	EXTI->RTSR = 0x7;                   //->0111 = These became rising trigger.
}
void delay(uint32_t time)
{
	while(--time);
}
///--> EXTI0 Interrupt Function <--///
void EXTI0_IRQHandler()
{
	if(EXTI->PR & 1)    					//->Check the flag of EXTI0
	{
		GPIOD->ODR = (1 << 12);
		delay(33600000);
		EXTI->PR = 1; 						//->Clear flag
	}
}
///--> EXTI1 Interrupt Function <--///
void EXTI1_IRQHandler()
{
	if(EXTI->PR & (1 << 1))    				//->Check the flag of EXTI1
	{
		GPIOD->ODR = (1 << 13);
		delay(33600000);
		EXTI->PR = (1 << 1); 				//->Clear flag
	}
}
///--> EXTI2 Interrupt Function <--///
void EXTI2_IRQHandler()
{
	if(EXTI->PR & (1 << 2))    				//->Check the flag of EXTI2
	{
		GPIOD->ODR = (1 << 15);
		delay(33600000);
		EXTI->PR = (1 << 2); 				//->Clear flag
	}
}
int main(void)
{
	//Settings of Clock
	RCC_Config();

	//Settings of GPIO
	GPIO_Config();

	//Settings of External Interrupt
	EXTI_Config();

	while (1)
	{
		GPIOD->ODR = (0xf << 12);           //->All bits became SET.
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
