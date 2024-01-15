#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i = 0;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);    	//->Enable clock of GPIOA

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void DAC2_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);         //->Enable clock of DAC

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_2, &DAC_InitStruct);

	DAC_Cmd(DAC_Channel_2, ENABLE);
}
void delay(uint32_t time)
{
	while(--time);
}
int main(void)
{
	GPIO_Config();
	DAC2_Config();
	while (1)
	{
		for(i = 0; i<4095; i++)
		{
			DAC_SetChannel2Data(DAC_Align_12b_R, i);
			delay(16800);
		}
		for(i = 4095; i>0; i--)
		{
			DAC_SetChannel2Data(DAC_Align_12b_R, i);
			delay(16800);
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
