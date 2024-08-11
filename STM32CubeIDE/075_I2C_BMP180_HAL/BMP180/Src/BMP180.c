/*
 * BMP180.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Semi Eren GÖKYILDIZ
 */
#include "BMP180.h"

I2C_HandleTypeDef* BMP180_hi2c;

/* Calibration Values */
int16_t AC1;
int16_t AC2;
int16_t AC3;
uint16_t AC4;
uint16_t AC5;
uint16_t AC6;
int16_t B1;
int16_t B2;
int16_t MB;
int16_t MC;
int16_t MD;

/* Temperature Values */
int16_t unCompTemperature;
float Temperature;
int32_t tX1;
int32_t tX2;
int32_t tB5;

/* Presure Values */
uint32_t unCompPresure;
float Presure, PresureATM;
int32_t pX1;
int32_t pX2;
int32_t pX3;
uint32_t pB3;
uint32_t pB4;
uint32_t pB6;
uint32_t pB7;

/* Oversampling value */
uint8_t oss = 0x03;

/* Conversion Time values */
uint8_t ultra_high_conversion_time = 26; //25.5ms

void BMP180_Init(I2C_HandleTypeDef *HI2CX)
{
	BMP180_hi2c = HI2CX;

	/* Catching The Bug */
	if(HAL_I2C_IsDeviceReady(BMP180_hi2c, BMP180_DEVICE_WRITE_REGISTER_ADDRESS, 1, 100) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET); //->If there is a problem, the red led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	/*------------------*/

	BMP180_Get_Calibration_Value();
}

void BMP180_Get_Calibration_Value()
{
	int a = 0;

	uint8_t calibBuff[BMP180_CALIBRATION_VALUE_LENGHT] = {0};

	HAL_I2C_Mem_Read(BMP180_hi2c, BMP180_DEVICE_READ_REGISTER_ADDRESS, BMP180_CALIBRATION_ADDRESS, 1, calibBuff, BMP180_CALIBRATION_VALUE_LENGHT, 100);

	AC1 = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	AC2 = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	AC3 = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	AC4 = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	AC5 = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	AC6 = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	B1  = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	B2  = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	MB  = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	MC  = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;
	MD  = (uint16_t)((calibBuff[a] << 8) | calibBuff[a+1]); a+=2;


	/* Catching The Bug */
	if(AC1 == 0x0000 || AC1 == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(AC2 == 0x0000 || AC2 == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(AC3 == 0x0000 || AC3 == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(AC4 == 0x0000 || AC4 == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(AC5 == 0x0000 || AC5 == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(AC6 == 0x0000 || AC6 == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(B1  == 0x0000 || B1  == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(B2  == 0x0000 || B2  == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(MB  == 0x0000 || MB  == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(MC  == 0x0000 || MC  == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	if(MD  == 0x0000 || MD  == 0xffff)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); //->If there is a problem, the blue led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	/*------------------*/
}

void BMP180_Get_Uncompansated_Temperature()
{
	uint8_t rData[2] = {0};
	uint8_t wData[1];
	wData[0] = 0x2e;

	HAL_I2C_Mem_Write(BMP180_hi2c, BMP180_DEVICE_WRITE_REGISTER_ADDRESS, 0xf4, 1, wData, 1, 100);
	HAL_Delay(5); //We must delay 4.5ms.

	HAL_I2C_Mem_Read(BMP180_hi2c, BMP180_DEVICE_READ_REGISTER_ADDRESS, 0xf6, 1, rData, 2, 100);
	unCompTemperature = (uint16_t)((rData[0] << 8) | rData[1]);
}

float BMP180_Get_Temperature()
{
	BMP180_Get_Uncompansated_Temperature();

	tX1 = ((int32_t)unCompTemperature - (int32_t)AC6) * (int32_t)AC5 / 32768;
	tX2 = ((int32_t) MC * 2048) / (tX1 + (int32_t)MD);

	/* Catching The Bug */
	if(tX1 == 0 && MD == 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET); //->If there is a problem, the orange led lights up on the DISC.
		while(1); //It waits because there is a error.
	}
	/*------------------*/

	tB5 = tX1 + tX2;
	Temperature = (float)((tB5 + 8) / 16) * 0.1;

	return Temperature;
}

void BMP180_Get_Uncompansated_Presure()
{
	uint8_t rData[3] = {0};
	uint8_t wData[1];
	wData[0] = 0x34 | (oss << 6);

	HAL_I2C_Mem_Write(BMP180_hi2c, BMP180_DEVICE_WRITE_REGISTER_ADDRESS, 0xf4, 1, wData, 1, 100);
	HAL_Delay(ultra_high_conversion_time); //We must delay "conversion time"ms.

	HAL_I2C_Mem_Read(BMP180_hi2c, BMP180_DEVICE_READ_REGISTER_ADDRESS, 0xf6, 1, rData, 3, 100);
	unCompPresure = (rData[0] << 16 | rData[1] << 8 | rData[2]) >> (8 - (uint8_t)oss);
}

float BMP180_Get_Presure()
{
	BMP180_Get_Uncompansated_Presure();

	pB6 = tB5 - 4000;
	pX1 = (B2 * (pB6 * pB6 / 4096)) / 2048;
	pX2 = AC2 * pB6 / 2048;
	pX3 = pX1 + pX2;
	pB3 = (((AC1 * 4 + pX3) << (uint8_t)oss) + 2) / 4;
	pX1 = AC3 * pB6 / 8192;
	pX2 = (B1 * (pB6 * pB6 / 4096)) / 65536;
	pX3 = ((pX1 + pX2) + 2) / 4;
	pB4 = AC4 * (unsigned long)(pX3 * 32768) / 32768;
	pB7 = ((unsigned long)unCompPresure - pB3) * (50000 >> (uint8_t)oss);
	if(pB7 < 0x80000000)
		Presure = (pB7 * 2) / pB4;
	else
		Presure = (pB7 / pB4) * 2;
	pX1 = (Presure / 256) * (Presure / 256);
	pX1 = (pX1 * 3038) / 65536;
	pX2 = (-7357 * Presure) / 65536;
	Presure = Presure + (pX1 + pX2 + 3791) / 16;          //hPa
	PresureATM = Presure * 0.00000986923;                 //Atm

	return Presure;
}
