/*
 * Nokia5110.h
 *
 *  Created on: Aug 14, 2024
 *      Author: Semi Eren GÖKYILDIZ
 */

#ifndef INC_NOKIA5110_H_
#define INC_NOKIA5110_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

/*
 * RTS = PD8
 * CE  = PD9
 * DC  = PD10
 * */

extern uint8_t frameBuff[504];

bool Nokia5110_Init(SPI_HandleTypeDef* HPSIX, DMA_HandleTypeDef* HDMAX);
void Nokia5110_Reset(void);
void Nokia5110_Clear(void);
bool Nokia5110_Update(void);
bool Nokia5110_bufferWrite(uint8_t* data, uint16_t lenght);
bool Nokia5110_Write(uint8_t data, uint8_t mode);

void Nokia5110_setPixel(uint8_t x, uint8_t y, bool state);

#endif /* INC_NOKIA5110_H_ */
