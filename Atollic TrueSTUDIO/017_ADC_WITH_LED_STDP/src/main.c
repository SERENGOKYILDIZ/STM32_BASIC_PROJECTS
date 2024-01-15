#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t adc_value;
float adc_voltage;

void GPIO_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
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
	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);   //->This apply settings of regular ADC.

	ADC_Cmd(ADC1, ENABLE);
}
uint16_t Read_ADC()
{
	ADC_SoftwareStartConv(ADC1);                                                 //->This start ADC in software.

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);                       //->Wait End of conversion flag.

	return ADC_GetConversionValue(ADC1);                                         //->Return the value of ADC.
}
int main(void)
{
	//->The Settings of GPIO<-//
	GPIO_Config();
	//->The Settings of ADC<-//
	ADC_Config();
	while (1)
	{
		adc_value = Read_ADC();
		adc_voltage = (0.00005035477) * adc_value;
		if(adc_voltage < 0.5)
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
		else if(adc_voltage >= 0.5 && adc_voltage <= 1.0)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
		else if(adc_voltage >= 1.0 && adc_voltage <= 2.0)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
		else if(adc_voltage >= 2.0 && adc_voltage <= 3.0)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
		else
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
		}
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
