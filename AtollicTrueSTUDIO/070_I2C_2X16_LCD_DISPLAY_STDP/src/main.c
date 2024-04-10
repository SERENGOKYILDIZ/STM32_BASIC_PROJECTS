#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "i2c-lcd.h"

uint8_t m_address = 0x4e;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);                 //->SCL Pin
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);                 //->SDA Pin

	GPIO_InitTypeDef GPIO_InitStruct;
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
	lcd_init();
	while (1)
	{
		lcd_send_cmd(0x80);
		lcd_sende_string("Semi Eren");
		delay(63000000);
		lcd_send_cmd(0xc3);
		lcd_sende_string("Gokyildiz");
		delay(63000000);
		lcd_send_cmd(0x01);
		delay(2100000);
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
