#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_OCInitTypeDef TIMOC_InitStruct;             					//->PWM Settings

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);       	//->Set AF Pin of D12 for TIM4
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);       	//->Set AF Pin of D13 for TIM4
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);       	//->Set AF Pin of D14 for TIM4
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);       	//->Set AF Pin of D15 for TIM4

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}
void PWM_Config()
{
	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;                  //->It is PWM MODE1
	TIMOC_InitStruct.TIM_OutputState = ENABLE;                      //->It is for output
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //->Polarity is HIGH
}
void TIM_Config()
{
	/*@brief
	 * Timer_Tick_Freq = Timer_CLK/(Prescaler + 1)
	 * Timer_CLK = 84Mhz
	 * Prescaler = 8399 (we can this)
	 * Timer_Tick_Freq = 84000000/(8399 + 1) => 10000Hz
	 *
	 * PWM_Freq = Timer_Tick_Freq/(Period + 1)
	 * Timer_Tick_Freq = 10000Hz
	 * Period = 9999 (we can this)
	 * PWM_Freq = 10000Hz/(9999 + 1) => 1Hz
	 * */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_Prescaler = 8399;
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_Cmd(TIM4, ENABLE);
}
int main(void)
{
	GPIO_Config();
	TIM_Config();
	PWM_Config();
	while (1)
	{
		/*@brief
		 * Pulse = [(Period + 1)x(DutyCycle)]
		 * */

		//D12, Duty Cycle = %100
		TIMOC_InitStruct.TIM_Pulse = 9999; 							//->Pulse = [(9999 + 1)x(%100)] => 9999
		TIM_OC1Init(TIM4, &TIMOC_InitStruct);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);           //->Open TIM4 -> CH1

		//D13, Duty Cycle = %75
		TIMOC_InitStruct.TIM_Pulse = 7499; 							//->Pulse = [(9999 + 1)x(%75)] => 7499
		TIM_OC2Init(TIM4, &TIMOC_InitStruct);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);           //->Open TIM4 -> CH2

		//D14, Duty Cycle = %50
		TIMOC_InitStruct.TIM_Pulse = 4999; 							//->Pulse = [(9999 + 1)x(%50)] => 4999
		TIM_OC3Init(TIM4, &TIMOC_InitStruct);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);           //->Open TIM4 -> CH3

		//D15, Duty Cycle = %25
		TIMOC_InitStruct.TIM_Pulse = 2499; 							//->Pulse = [(9999 + 1)x(%25)] => 2499
		TIM_OC4Init(TIM4, &TIMOC_InitStruct);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);           //->Open TIM4 -> CH4
	}
}











void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
