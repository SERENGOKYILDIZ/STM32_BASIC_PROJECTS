/*
 * Nokia5110.c
 *
 *  Created on: Aug 14, 2024
 *      Author: Semi Eren GÖKYILDIZ
 */

#include "Nokia5110.h"

#define MODE_COMMAND 0
#define MODE_DATA    1

#define ERROR_CODE    0
#define SUCCES_CODE   1

SPI_HandleTypeDef* hspix;
DMA_HandleTypeDef* hdma_spix_tx;

/*
GPIO_TypeDef *GPIOX_RTS;
uint16_t RTS_pin;

GPIO_TypeDef *GPIOX_CE;
uint16_t CE_pin;

GPIO_TypeDef *GPIOX_DC;
uint16_t DC_pin;
*/

uint8_t frameBuff[504];

bool Nokia5110_Init(SPI_HandleTypeDef* HPSIX, DMA_HandleTypeDef* HDMAX)
{
	hspix = HPSIX;
	hdma_spix_tx = HDMAX;

	Nokia5110_Reset();

	if(!Nokia5110_Write(0x21, 0))
		return false;
	if(!Nokia5110_Write(0xc0, 0))
		return false;
	if(!Nokia5110_Write(0x07, 0))
		return false;
	if(!Nokia5110_Write(0x13, 0))
		return false;
	if(!Nokia5110_Write(0x20, 0))
		return false;
	if(!Nokia5110_Write(0x0c, 0))
		return false;

	return true;
}

void Nokia5110_Reset()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);   		//RST pin is low
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);   			//RST pin is high
}

void Nokia5110_Clear()
{
	for(int i;i<504;i++) frameBuff[i] = 0x00;
}

bool Nokia5110_Update()
{
	if(!Nokia5110_Write(0x80, 0)) return false;                    	//Move to X = 0
	if(!Nokia5110_Write(0x40, 0)) return false;                    	//Move to Y = 0
	if(!Nokia5110_bufferWrite(frameBuff, 504)) return false;    	//It writing buffer data
	return true;
}

bool Nokia5110_bufferWrite(uint8_t* data, uint16_t lenght)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);			//CE pin is low
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);			//DC pin is high for command send
	HAL_SPI_Transmit_DMA(hspix, data, lenght);
	return true;
}

bool Nokia5110_Write(uint8_t data, uint8_t mode)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);			//CE pin is low

	if(mode == MODE_COMMAND)
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);		//DC pin is low for data send
	else if(mode == MODE_DATA)
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);		//DC pin is high for command send
	else 															//The writing process is canceled
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);			//CE pin is high
		return ERROR_CODE;
	}

	HAL_SPI_Transmit_DMA(hspix, &data, 1);


	return SUCCES_CODE;
}

void Nokia5110_setPixel(uint8_t x, uint8_t y, bool state)
{
	uint8_t Bi;
	uint16_t By;

	if(x < 0 || x >= 84 || y < 0 || y >= 84) return;

	By = (y / 8) * 84 + x;
	Bi = y % 8;

	if(state)
		frameBuff[By] |= (1 << Bi);
	else
		frameBuff[By] &= ~(1 << Bi);
}
