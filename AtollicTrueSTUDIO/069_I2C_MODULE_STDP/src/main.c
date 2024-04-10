#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t m_address = 0x4e;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);                 //->SCL Pin
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);                 //->SDA Pin

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

}
void I2C_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}
void I2C_Write(uint8_t adr, uint8_t data)
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));      					//->Is line busy?

	I2C_GenerateSTART(I2C1, ENABLE);                    					//->I2C1 start

	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));         	//->Did selected the Master Mode

	I2C_Send7bitAddress(I2C1, m_address, I2C_Direction_Transmitter);      	//->First, Send the address of slave

	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING)));    	//->Did send the data

	I2C_SendData(I2C1, data);                                            	//->Send the data

	I2C_GenerateSTOP(I2C1, ENABLE);                    				   		//->I2C1 stop
}
void delay(uint32_t time)
{
	while(time--);
}
int main(void)
{
	GPIO_Config();
	I2C_Config();
	int count = 0;
	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			count++;
			delay(168000);
		}
		switch(count)
		{
			case 0:
			I2C_Write(m_address, 0x00);
			break;

			case 1:
			I2C_Write(m_address, 0x01);
			break;

			case 2:
			I2C_Write(m_address, 0x02);
			break;

			case 3:
			I2C_Write(m_address, 0x04);
			break;

			case 4:
			I2C_Write(m_address, 0x08);
			break;

			case 5:
			I2C_Write(m_address, 0x10);
			break;

			case 6:
			I2C_Write(m_address, 0x20);
			break;

			case 7:
			I2C_Write(m_address, 0x40);
			break;

			case 8:
			I2C_Write(m_address, 0x80);
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
