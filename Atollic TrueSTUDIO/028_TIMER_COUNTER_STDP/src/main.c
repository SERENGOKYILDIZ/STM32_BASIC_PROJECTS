#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count;

void TIMER_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  	//->Enabled clock of TIM2

	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //->Divide APB1 Timer clock by 1.
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //->The Settings of Counter is Up.
	TIM_InitStruct.TIM_Period = 1999;                      	//->The Value of Auto-Reload Register is 1999.
	TIM_InitStruct.TIM_Prescaler = 41999;                   //->The Value of Prescaler is 41999.
	TIM_InitStruct.TIM_RepetitionCounter = 0;               //->Number of repetitions is 1 (n+1).

	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

	TIM_Cmd(TIM2, ENABLE);

	/*
	 * @brief
	 * 		Second(s) = [(Period + 1)*(Prescaler + 1)]/ABP1_TIMER_CLOCK
	 *
	 * @Example Period:1999, Prescaler:41999, ABP1_TIM_CLK:82Mhz, t=?
	 * t = [(1999 + 1)*(41999 + 1)]/ABP1_TIMER_CLOCK => t = 1s
	 * --->Overflow occurs in 1 second.
	 *
	 * */
}
int main(void)
{
	TIMER_Config();
	while (1)
	{
		count = TIM_GetCounter(TIM2);
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
