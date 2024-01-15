#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

///--> GPIO Init Function <--///
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//->Open the clock of GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 		//->Open the clock of GPIOD

	GPIO_InitTypeDef GPIO_InitStruct;                     		//->Define the structure of GPIO_init.

	//For Button
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;                      //->GPIO Pin  = A0.
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;              		//->GPIO Mode = Input.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;              	//->GPIO Output Type = Push-pull.
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;              	//->GPIO Pull-up/Pull-down = Pull-down.
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;             //->GPIO Speed = 100Mhz.

	GPIO_Init(GPIOA, &GPIO_InitStruct);                         //->Apply settings to GPIOA.

	//For Leds
	GPIO_InitStruct.GPIO_Pin =
			GPIO_Pin_12 | GPIO_Pin_13
			| GPIO_Pin_14 | GPIO_Pin_15;						//->GPIO Pin  = D12, D13, D14, D15.
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;              	//->GPIO Mode = Output.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;              	//->GPIO Output Type = Push-pull.
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;              	//->GPIO Pull-up/Pull-down = no-pull.
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;             //->GPIO Speed = 100Mhz.

	GPIO_Init(GPIOD, &GPIO_InitStruct);                         //->Apply settings to GPIOD.

}
///--> External Interrupt Init Function <--///
void EXTI_Config(void)
{
	//For External Interrupt
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 			//->Open the clock of External Interrupt.

	EXTI_InitTypeDef EXTI_InitStruct;                           	//->Define the structure of EXTI_Init.
	NVIC_InitTypeDef NVIC_InitStruct;                           	//->Define the structure of NVIC_Init.

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, GPIO_PinSource0);	//->Select the pin of A0 for EXTI.

	EXTI_InitStruct.EXTI_Line = EXTI_Line0;                     	//->Line became Line0.
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;                    		//->Line became ENABLE.
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;                //->Line Mode became Interrupt Mode.
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;             //->Line Trigger became Rising.

	EXTI_Init(&EXTI_InitStruct);                                  	//->Apply settings to EXTI.

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;                   //->IRQ Channel became EXTI0.
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                	//->IRQ Channel became ENABLE.
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;        	//->Priority became 0 (So the top Priority is).
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;        	        //->Priority became 0 (So the top Priority is).

	NVIC_Init(&NVIC_InitStruct);                                    //->Apply settings to NVIC.
}
///--> Delay Function <--///
void delay(uint32_t time)
{
	while(--time);
}
///--> External Interrupt Function <--///
void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)    					//->Check the flag of Line1
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_All);                       	//->All pins in the GPIOD became RESET.
		delay(1680000);
		GPIO_SetBits(GPIOD, GPIO_Pin_All);                       	//->All pins in the GPIOD became SET.
		delay(1680000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_All);                       	//->All pins in the GPIOD became RESET.
		delay(1680000);
		GPIO_SetBits(GPIOD, GPIO_Pin_All);                       	//->All pins in the GPIOD became SET.
		delay(1680000);

		EXTI_ClearITPendingBit(EXTI_Line0);                         //->Clear flag
	}
}
int main(void)
{
	//SETTINGS GPIO//
	GPIO_Config();
	//SETTINGS EXTERNAL INTERRUPT//
	EXTI_Config();
	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_All);                       	//->All pins in the GPIOD became SET.
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
