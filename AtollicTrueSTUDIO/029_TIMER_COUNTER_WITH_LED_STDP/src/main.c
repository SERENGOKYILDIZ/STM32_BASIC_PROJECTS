#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count;

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
void TIMER_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  	//->Enabled clock of TIM2

	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //->Divide APB1 Timer clock by 1.
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //->The Settings of Counter is Up.
	TIM_InitStruct.TIM_Period = 3999;                      	//->The Value of Auto-Reload Register is 3999.
	TIM_InitStruct.TIM_Prescaler = 41999;                   //->The Value of Prescaler is 41999.
	TIM_InitStruct.TIM_RepetitionCounter = 0;               //->Number of repetitions is 1 (n+1).

	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

	TIM_Cmd(TIM2, ENABLE);
}
int main(void)
{
	GPIO_Config();
	TIMER_Config();
	// t = 2s
	while (1)
	{
		count = TIM_GetCounter(TIM2);

		if(count == 1999) 									//if t = 1s
			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

		else if(count == 3999) 								//if t = 2s
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
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
