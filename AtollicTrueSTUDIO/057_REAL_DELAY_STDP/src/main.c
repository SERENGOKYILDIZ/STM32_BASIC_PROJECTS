#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_init_struct;

	GPIO_init_struct.GPIO_Pin =  GPIO_Pin_13;
	GPIO_init_struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_init_struct.GPIO_OType = GPIO_OType_PP;
	GPIO_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_init_struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_init_struct);
}
void Delay(uint32_t time)
{
	while(time--);             // 8 cycle

	/*
	* @brief
	* 4 cycle (For while) + 4 cycle (For "time--") = 8 cycle (Tdelay)
	* fdelay = fsys/Tdelay => (168Mhz) / (8 cycle) => 21Mhz (The Delay function frequency)
	* The Delay Fucntion Time; T = Value/fdelay
	* Let the Value = 21Mhz; T = 21Mhz/21Mhz => 1 second
	* */

	/*
	while(time>0)
	{
		time--; // 8 cycle
	}
	*/
}
int main(void)
{
	GPIO_Config();
	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		Delay(21000000);                   	// 1 second
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		Delay(21000000);                   	// 1 second
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
