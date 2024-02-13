#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define BufferLenght 1
uint16_t adc_value[BufferLenght];

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void ADC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonStruct;

	ADC_CommonStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;                    				//->For multi ADCs.
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    //->For external trigger
	ADC_InitStruct.ADC_ExternalTrigConv = 0;                                    //->None
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                             //->For continuous reading.
	ADC_InitStruct.ADC_NbrOfConversion = BufferLenght;                          //->How many ADCs are reading. (1 In our project)
	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_Cmd(ADC1, ENABLE);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	ADC_DMACmd(ADC1, ENABLE);                                                   //->Connect ADC to DMA
}
void DMA_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA_DeInit(DMA1_Stream0);

	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_Channel = DMA_Channel_0;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;          		//->It is ADC1 data register.
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&adc_value;                  //->It is our value.
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStruct.DMA_BufferSize = BufferLenght;                               //->How many DMA channels. (1 In our project)
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                       	//->The data typed address should change constantly.
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               //->The address from which the data is read must remain constant.
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);

	DMA_Cmd(DMA2_Stream0, ENABLE);
}
int main(void)
{
	GPIO_Config();
	ADC_Config();
	DMA_Config();

	ADC_SoftwareStartConv(ADC1);       	//->ADC and DMA are started
	while (1)
	{

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
