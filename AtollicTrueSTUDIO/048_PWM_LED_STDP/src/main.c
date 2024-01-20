#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_OCInitTypeDef TIMOC_InitStruct;             					//->PWM Settings

uint32_t delay_count;

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
void TIM_Config()
{
	/*@brief
	 * Timer_Tick_Freq = Timer_CLK/(Prescaler + 1)
	 * Timer_CLK = 84Mhz
	 * PSC = 83 (we can this)
	 * Timer_Tick_Freq = 84000000/(83 + 1) => 1000000Hz
	 *
	 * Period = [Timer_Tick_Freq / PWM_Freq] - 1
	 * PWM_Freq = 10000 (We want this)
	 * Timer_Tick_Freq = 1000000Hz
	 * Period = [1000000Hz / 10000] - 1 => 99
	 * */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 99;
	TIM_InitStruct.TIM_Prescaler = 83;
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_Cmd(TIM4, ENABLE);

	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;                  //->It is PWM MODE1
	TIMOC_InitStruct.TIM_OutputState = ENABLE;                      //->It is for output
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //->Polarity is HIGH

	SysTick_Config(SystemCoreClock/1000);  							//->SysTick become Interrupt per 1ms
}
//SysTick Interrupt
void SysTick_Handler(void)
{
	if(delay_count > 0)
		delay_count--;
}
//Delay Function
void delay_ms(uint32_t time)
{
	delay_count = time;
	while(delay_count);
}
int main(void)
{
	GPIO_Config();
	TIM_Config();
	while (1)
	{
		for(int i=0;i<=100;i++)
		{
			//For D12
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC1Init(TIM4, &TIMOC_InitStruct);
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
			//For D13
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC2Init(TIM4, &TIMOC_InitStruct);
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
			//For D14
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC3Init(TIM4, &TIMOC_InitStruct);
			TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
			//For D15
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC4Init(TIM4, &TIMOC_InitStruct);
			TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
		}
		for(int i=100;i>=0;i--)
		{
			//For D12
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC1Init(TIM4, &TIMOC_InitStruct);
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
			//For D13
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC2Init(TIM4, &TIMOC_InitStruct);
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
			//For D14
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC3Init(TIM4, &TIMOC_InitStruct);
			TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
			//For D15
			TIMOC_InitStruct.TIM_Pulse = i;
			TIM_OC4Init(TIM4, &TIMOC_InitStruct);
			TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
			delay_ms(20);
		}
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
