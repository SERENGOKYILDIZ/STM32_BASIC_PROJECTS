#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

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
void delay(uint32_t time)
{
	while(--time);
}
int main(void)
{
	GPIO_Config();
	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			delay(3360000);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		}
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
