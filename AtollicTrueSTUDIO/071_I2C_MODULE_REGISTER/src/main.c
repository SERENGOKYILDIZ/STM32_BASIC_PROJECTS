#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t module_address = 0x4e;

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
void GPIO_Config(void)
{
	RCC->AHB1ENR |= 0x3; 				//->Clock of GPIOA and GPIOB = Enabled

	GPIOB->MODER |= (2 << 20);          //->B10 = Alternate function Mode.
	GPIOB->MODER |= (2 << 22);          //->B11 = Alternate function Mode.
	GPIOB->AFR[1] |= (4 << 8);          //->AF4 for B10.
	GPIOB->AFR[1] |= (4 << 12);         //->AF4 for B11.
	GPIOB->OTYPER |= (1 << 11);         //->B11 = Open-Drain.
	GPIOB->OTYPER |= (1 << 12);         //->B12 = Open-Drain.
}
void I2C_Config()
{
	RCC->APB1ENR |= 1 << 22;           	//->Clock of I2C2 = Enabled

	I2C2->CR2 |= 0x08;                  //->The Freq of I2C2 = 8Mhz
	I2C2->CCR |= 0x28;                  //->The Freq of I2C2 Working = 100KHz
	I2C2->TRISE |= 0x09;                //->For CR2 REG
	I2C2->CR1 |= 0x01;                  //->Periph of I2C2 = Enabled
}
void I2C_Write(uint8_t address, uint8_t data)
{
	I2C2->CR1 |= (1 << 8);			    //->Send start bit.
	while(!(I2C2->SR1 & (0x1)));        //->Wait for start.
	I2C2->DR = module_address;          //->Send slave address byte.
	while(!(I2C2->SR1 & (0x2)));        //->Wait for send slave address.
	while(!(I2C2->SR2 & (0x1)));        //->Wait for check master/slave mode.

	/*
	 * @brief Here was closed because the module does not have a registration address.
	 * */

	//I2C2->DR = address;                 //->Send register address byte.
	//while(!(I2C2->SR1 & (1 << 7)));     //->Wait for TXE empty.

	I2C2->DR = data;                   	//->Send data byte.
	while(!(I2C2->SR1 & (1 << 2)));     //->Wait for BTF successful.
	I2C2->CR1 |= (1 << 9);			    //->Send stop bit.

}
uint8_t I2C_Read()
{

}
void delay(uint32_t time)
{
	while(time--);
}
int main(void)
{
	RCC_Config();
	GPIO_Config();
	I2C_Config();
	int count = 0;
	while (1)
	{
		if(GPIOA->IDR & 0x1)
		{
			while(GPIOA->IDR & 0x1);
			delay(2100000);
			count++;
		}
		switch(count)
		{
			case 0:
			I2C_Write(module_address, 0x00);
			break;

			case 1:
			I2C_Write(module_address, 0x01);
			break;

			case 2:
			I2C_Write(module_address, 0x02);
			break;

			case 3:
			I2C_Write(module_address, 0x04);
			break;

			case 4:
			I2C_Write(module_address, 0x08);
			break;

			case 5:
			I2C_Write(module_address, 0x10);
			break;

			case 6:
			I2C_Write(module_address, 0x20);
			break;

			case 7:
			I2C_Write(module_address, 0x40);
			break;

			case 8:
			I2C_Write(module_address, 0x80);
			break;

			default:
			count = 0;
			break;
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
