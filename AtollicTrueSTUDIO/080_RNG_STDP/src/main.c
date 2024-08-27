#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t myRandonNumber;
uint32_t count;
uint32_t heads, tails;
float ratio, ratioHeads, ratioTails;

void RNG_Config()
{
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);

	RNG_Cmd(ENABLE);
}

void delay(uint32_t time)
{
	/*
	 * ===============================
	 * -> (while) it takes 4 cycles
	 * -> (time--) it takes 4 cycles
	 *
	 * -> That's a total of 8 cycles.
	 * ===============================
	 * -> Our freq is 168Mhz;
	 * -> 168Mhz/8 = 21Mhz ; 1 second = 21Mhz
	 * ===============================
	 *
	 * -> We can write 21Mhz for 1 second.
	 *
	 * */
	while(time--);
}

int main(void)
{
	RNG_Config();
	while (1)
	{
		myRandonNumber = RNG_GetRandomNumber();
		//delay(21000000);

		count++;
		if(count <= 10000000)
		{
			if(myRandonNumber < 2147483648) heads++;
			else tails++;
		}
		else
		{
			ratio = (float)heads / tails;
			ratioHeads = (float)heads / 10000000;
			ratioTails = (float)tails / 10000000;
			/*
			 * According to one theory, if a coin flip is played 10 million times,
			 * the ratio of the number of heads tails should be 1.
			 * Because the ratio is 1/2, the ratio of each other should be 1.
			 */
			RNG_Cmd(DISABLE);
		}
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
