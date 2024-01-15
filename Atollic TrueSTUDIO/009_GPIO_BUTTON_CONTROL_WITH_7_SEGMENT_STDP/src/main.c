#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 * @brief dasdasdasd
 * @pin A0: Button
 * @pin A1: 7 Segment A
 * @pin A2: 7 Segment B
 * @pin A3: 7 Segment C
 * @pin A4: 7 Segment D
 * @pin A5: 7 Segment E
 * @pin A6: 7 Segment F
 * @pin A7: 7 Segment G
 */
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//->Open the clock of GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 		//->Open the clock of GPIOD

	GPIO_InitTypeDef GPIO_InitStruct;                     		//->Define the structure of GPIO_init.

	//For Button
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;                      //->GPIO Pin  = A0.
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;              		//->GPIO Mode = Input.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;              	//->GPIO Output Type = Push-pull.
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;              	//->GPIO Pull-up/Pull-down = Pull-down.
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;             //->GPIO Speed = 100Mhz.

	GPIO_Init(GPIOA, &GPIO_InitStruct);                         //->Apply settings to GPIOA.

	//For Leds
	GPIO_InitStruct.GPIO_Pin =
			GPIO_Pin_1 | GPIO_Pin_2
			| GPIO_Pin_3 | GPIO_Pin_4
			| GPIO_Pin_5 | GPIO_Pin_6
			| GPIO_Pin_7;										//->GPIO Pin  = A1, A2, A3, A4, A5, A6, A7.
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;              	//->GPIO Mode = Output.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;              	//->GPIO Output Type = Push-pull.
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;              	//->GPIO Pull-up/Pull-down = no-pull.
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;             //->GPIO Speed = 100Mhz.

	GPIO_Init(GPIOA, &GPIO_InitStruct);                         //->Apply settings to GPIOD.
}
void delay(uint32_t time)
{
	while(--time);
}
int main(void)
{
	GPIO_Config();
	uint8_t count;
	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) //->Read Button
		{
			while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			delay(1680000);
			count++;
		}
		switch(count) //->Write 7 Segment
		{
		case 0:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		break;

		case 1:
		GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
		GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3);
		break;

		case 2:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_6);
		break;

		case 3:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6);
		break;

		case 4:
		GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
		break;

		case 5:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_5);
		break;

		case 6:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		break;

		case 7:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
		break;

		case 8:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
		break;

		case 9:
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		break;

		case 10:
		count = 0;
		break;
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
