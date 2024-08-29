#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t data;

void RCC_Config(void)
{
	//Settings of Opening HSE
	RCC->CR &= ~(1 << 0);               //->HSION = 0, (HSI=OFF)
	while((RCC->CR & 0X3));				//->Wait HSI deactivate.
	RCC->CR |= (1 << 16); 				//->HSEON = 1, (HSE=ON)
	while(!(RCC->CR & (1 << 17))); 		//->Wait HSE active

	//Settings of PLL
	RCC->CR |= (1<<19); 				//->CSSON = 1.
	RCC->PLLCFGR |= (1 << 22); 			//->PLLSRC = 1, (PLL Source = HSE)
	RCC->PLLCFGR |= (4<<0); 			//->PLL_M = 4
	RCC->PLLCFGR |= (168<<6); 			//->PLL_N = 168
	RCC->PLLCFGR |= 0x00; 				//->PLL_P = 2

	//Settings of Prescaler
	RCC->CFGR = 0x0;                    //->AHB  Prescaler = 1
	RCC->CFGR |= (5 << 10);             //->APB1 Prescaler = 4
	RCC->CFGR |= (4 << 13);             //->APB2 Prescaler = 2

	RCC->CR = (1<<19);                  //-> HSERDY Flag clear.
	RCC->CR = (1<<23);                  //-> CSS Flag clear.
	SystemCoreClockUpdate();
}

void Flash_Unlock()
{
	while((FLASH->SR & (1 << 16)) != 0);	    //-> Wait flash memory
	//Writing keys
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xcdef89ab;
	//Flash is opened!
}

void Flash_Erase()
{
	while((FLASH->SR & (1 << 16)) != 0);	    //-> Wait flash memory
	FLASH->CR |= (1 << 1);                      //-> Sector erase (SER set)
	FLASH->CR |= (11 << 3);                     //-> Select the Sector 11
	FLASH->CR |= (1 << 16);                     //-> Start erase
	while((FLASH->SR & (1 << 16)) != 0);	    //-> Wait flash memory

	if((FLASH->SR & (1 << 0)) != 0)             //-> If EOP is 1
	{
		FLASH->CR |= (1 << 0);                  //-> Clear EOP bit
	}
	else
	{
		//Error of erase
		Flash_Erase();
	}

	FLASH->CR &= ~(1 << 1);                      //-> SER reset
}

void Flash_Write(uint32_t address, uint32_t data)
{
	while((FLASH->SR & (1 << 16)) != 0);	    //-> Wait flash memory
	FLASH->CR |= (1 << 0);                      //-> Flash programming (PG set)
	FLASH->CR |= (2 << 8);                      //-> Program size = 32bit

	//* NOTE : The address must be in the sector 11 *//
	*(__IO uint32_t *)address = data;           //-> Data is writing to the address

	while((FLASH->SR & (1 << 16)) != 0);	    //-> Wait flash memory

	if((FLASH->SR & (1 << 0)) != 0)             //-> If EOP is 1
	{
		FLASH->CR |= (1 << 0);                  //-> Clear EOP bit
	}
	else
	{
		//Error of write
	}

	FLASH->CR &= ~(1 << 0);                      //-> Clear Flash programming (PG reset)
}

uint32_t Flash_Read(uint32_t address)
{
	uint32_t myFlashData;
	//myFlashData = *address;                   	//-> Data reading to the address
	myFlashData = *(uint32_t *)address;    		//-> Data reading to the address
	return myFlashData;
}

void Flash_Lock()
{
	while((FLASH->SR & (1 << 16)) != 0);	    //-> Wait flash memory
	FLASH->CR |= (1 << 31);                    	//-> The flash is locked
}

int main(void)
{
	RCC_Config();

	//Writing
	Flash_Unlock();
	Flash_Erase();
	Flash_Write(0x080e0000, 0x11abcdef);
	Flash_Lock();

	//Reading
	data = Flash_Read(0x080e0000);

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
