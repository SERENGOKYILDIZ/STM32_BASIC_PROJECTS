#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_OCInitTypeDef TIMOC_InitStruct;             					//->PWM Settings

uint16_t adc_value;
uint8_t pwm_value;

uint32_t map(uint32_t A, uint32_t B, uint32_t C, uint32_t D, uint32_t E)
{
	return (A * E) / C;
}
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

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN; 			//->Because we'll use Input of Analog.
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void ADC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;

	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_Cmd(ADC1, ENABLE);
}
uint16_t Read_ADC()
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);   //->This apply settings of regular ADC.

	ADC_SoftwareStartConv(ADC1);                                                 //->This start ADC in software.

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);                       //->Wait End of conversion flag.

	return ADC_GetConversionValue(ADC1) >> 4;                                    //->Return the value of ADC.
	/*
	 * @brief We did shift 4 bits to the right. Because we read 0xff0 to the adc.
	 * */
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
}
int main(void)
{
	GPIO_Config();
	ADC_Config();
	TIM_Config();
	while (1)
	{
		/*
		 * @brief
		 * ADC Value = 0-4095
		 * PWM Value = 0-99
		 *
		 * So we writed map function.*/
		adc_value = Read_ADC();           				//->Read the value of ADC.
		pwm_value = map(adc_value, 0, 4095, 0, 99);     //->Do the adc value set 0 between 99.
		//For D12
		TIMOC_InitStruct.TIM_Pulse = pwm_value;
		TIM_OC1Init(TIM4, &TIMOC_InitStruct);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		//For D13
		TIMOC_InitStruct.TIM_Pulse = pwm_value;
		TIM_OC2Init(TIM4, &TIMOC_InitStruct);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
		//For D14
		TIMOC_InitStruct.TIM_Pulse = pwm_value;
		TIM_OC3Init(TIM4, &TIMOC_InitStruct);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		//For D15
		TIMOC_InitStruct.TIM_Pulse = pwm_value;
		TIM_OC4Init(TIM4, &TIMOC_InitStruct);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
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
