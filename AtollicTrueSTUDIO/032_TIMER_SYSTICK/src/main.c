#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t count;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}
//-> The function of Systick interrupt <-//				//-->"stm32f4xx_it.c" We need to delete the version in this file
void SysTick_Handler()
{
	if(count > 0)
		count--;
}
void delay_ms(uint32_t time)
{
	count = time;

	while(count);
}
int main(void)
{
	GPIO_Config();
	SysTick_Config(SystemCoreClock/1000);         		//->Interrupt happens at 1ms
	/*
	 *SystemCoreClock/1000 		--> 1ms
	 *SystemCoreClock/100000 	--> 10us
	 *SystemCoreClock/1000000 	--> 1us
	*/
	while (1)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay_ms(1000);
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
