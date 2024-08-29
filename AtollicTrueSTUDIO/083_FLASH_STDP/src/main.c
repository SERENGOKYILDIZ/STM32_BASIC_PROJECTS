#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t myData;

void Flash_Write(uint32_t address, uint32_t data)
{
	FLASH_Unlock();
	FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3);
	FLASH_ProgramWord(address, data);
	FLASH_Lock();
}

uint32_t Flash_Read(uint32_t address)
{
	uint32_t myFlashData = *(uint32_t *)address;
	return myFlashData;
}

int main(void)
{
	Flash_Write(0x080e0000, 0x55);
	myData = Flash_Read(0x080e0000);
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
