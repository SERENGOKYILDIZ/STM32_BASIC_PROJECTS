/*
 * BMP180.h
 *
 *  Created on: Aug 11, 2024
 *      Author: Semi Eren GÖKYILDIZ
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include "stm32f4xx_hal.h"

/* BMP180 Devices Addresses */
#define BMP180_DEVICE_WRITE_REGISTER_ADDRESS 0xee
#define BMP180_DEVICE_READ_REGISTER_ADDRESS  0xef

/* BMP180 Calibration Address*/
#define BMP180_CALIBRATION_ADDRESS 0xaa

/* BMP180 Calibration Value Lenght */
#define BMP180_CALIBRATION_VALUE 11
#define BMP180_CALIBRATION_VALUE_LENGHT (BMP180_CALIBRATION_VALUE*2)

/* Calibration Values */
extern int16_t AC1;
extern int16_t AC2;
extern int16_t AC3;
extern uint16_t AC4;
extern uint16_t AC5;
extern uint16_t AC6;
extern int16_t B1;
extern int16_t B2;
extern int16_t MB;
extern int16_t MC;
extern int16_t MD;

/* Temperature Values */
extern int16_t unCompTemperature;
extern float Temperature;
extern int32_t tX1;
extern int32_t tX2;
extern int32_t tB5;

/* Presure Values */
extern uint32_t unCompPresure;
extern float Presure, PresureATM;
extern int32_t pX1;
extern int32_t pX2;
extern int32_t pX3;
extern uint32_t pB3;
extern uint32_t pB4;
extern uint32_t pB6;
extern uint32_t pB7;

/* Oversampling value */
extern uint8_t oss;

/* Conversion Time values */
extern uint8_t ultra_high_conversion_time; //25.5ms

void BMP180_Init(I2C_HandleTypeDef* HI2CX);
void BMP180_Get_Calibration(void);
void BMP180_Get_Calibration_Value(void);
void BMP180_Get_Uncompansated_Temperature(void);
float BMP180_Get_Temperature(void);
void BMP180_Get_Uncompansated_Presure(void);
float BMP180_Get_Presure(void);

#endif /* INC_BMP180_H_ */
