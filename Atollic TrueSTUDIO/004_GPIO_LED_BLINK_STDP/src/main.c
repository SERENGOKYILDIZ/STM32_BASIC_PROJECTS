#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void GPIO_Config()
{
	/*
	 * @brief The GPIOD port is connected to the AHB1 clock signal line. (Look the block of diagram)
	 *
	 * Open Drain = The current is transferred directly.
	 * Push-Pull = It is divided into 3.Pull-up, Pull-down, No-pull (open drain)
	*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);								//->We activated the clock signal of GPIOD (So we activated AHB1)

	//Define of GPIO_Init
	GPIO_InitTypeDef GPIO_init_struct; 													//->We created a GPIO adjustment structure.

	//Settings of GPIO
	GPIO_init_struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 	//->We determined the pins we will use.
	GPIO_init_struct.GPIO_Mode = GPIO_Mode_OUT; 									    //->We set our pins as output.
	GPIO_init_struct.GPIO_OType = GPIO_OType_PP; 										//->We set the state of output.
	GPIO_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL; 									    //->We set the push-pull of output.
	GPIO_init_struct.GPIO_Speed = GPIO_Speed_100MHz; 									//->We set the speed of output.

	GPIO_Init(GPIOD, &GPIO_init_struct); 												//->We transferred the adjustments to the GPIO.
}

int main(void)
{
	GPIO_Config(); 																		//->Program goes the function.
	while (1)
	{
		//->We sets pins.
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
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
