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
void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 19999;
	TIM_InitStruct.TIM_Prescaler = 83;
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_Cmd(TIM4, ENABLE);

	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;                  //->It is PWM MODE1
	TIMOC_InitStruct.TIM_OutputState = ENABLE;                      //->It is for output
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //->Polarity is HIGH
}
void delay(uint32_t time)
{
	while(time--);
}
int main(void)
{
	GPIO_Config();
	TIM_Config();
	while (1)
	{
		/*
		 * @brief We need 50Hz or 20ms for Servo Motor.
		 * Period = 20ms = 20000us (We can write 19999)
		 *
		 * Timer_Tick_Freq = (Period + 1) x PWM_Freq
		 * Timer_Tick_Freq = (19999 + 1) x 50 => 1MHz
		 *
		 * PSC = (Timer_Tick_Freq / Timer_CLK) - 1
		 * PSC = [(84000000) / (1000000)] - 1 => 83
		 * */
		/*
		 * The first value of Servo Motor = 0.5ms
		 * 0.5ms/20ms => %2.5 duty cycle (Start Value)
		 * (%2.5) x (20000) => 500 (Start Value of Period)
		 * */
		//For D12 (Servo motor)
		TIMOC_InitStruct.TIM_Pulse = 500;
		TIM_OC1Init(TIM4, &TIMOC_InitStruct);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		/*
		 * @brief The "while(time--);" code takes place at 8 cycles.
		 * 1 second = (168Mhz)/8 => 21Mhz
		 * */
		delay(21000000);                          			//->(168Mhz) / (8cycle) => 21Mhz

		/*
		 * The second value of Servo Motor = 1.5ms
		 * 1.5ms/20ms => %7.5 duty cycle (Start Value)
		 * (%7.5) x (20000) => 1500 (Start Value of Period)
		 * */
		//For D12 (Servo motor)
		TIMOC_InitStruct.TIM_Pulse = 1500;
		TIM_OC1Init(TIM4, &TIMOC_InitStruct);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		delay(21000000);                                 	//->(168Mhz) / (8cycle) => 21Mhz

		/*
		 * The second value of Servo Motor = 2.5ms
		 * 2.5ms/20ms => %12.5 duty cycle (Start Value)
		 * (%12.5) x (20000) => 2500 (Start Value of Period)
		 * */
		//For D12 (Servo motor)
		TIMOC_InitStruct.TIM_Pulse = 2500;
		TIM_OC1Init(TIM4, &TIMOC_InitStruct);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		delay(21000000);                                 	//->(168Mhz) / (8cycle) => 21Mhz
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
