/*
 * LCD.h
 *
 *  Created on: Jul 12, 2023
 *      Author: Nejc
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <stdint.h>
#include "stm32h7xx_hal.h"

#define RS_PORT GPIOB
#define RS_PIN GPIO_PIN_7

#define E_PORT GPIOB
#define E_PIN GPIO_PIN_6

#define DATA1_PORT GPIOG
#define DATA1_PIN GPIO_PIN_3

#define DATA2_PORT GPIOA
#define DATA2_PIN GPIO_PIN_6

#define DATA3_PORT GPIOK
#define DATA3_PIN GPIO_PIN_1

#define DATA4_PORT GPIOA
#define DATA4_PIN GPIO_PIN_8

#define timer htim3

void __LCD_Delay(uint16_t delay);
void __LCD_Write4Bits(uint8_t value);
void __LCD_Send(uint8_t value, int state);
void __LCD_Cmd(uint8_t value);
void __LCD_Data(uint8_t value);

void LCD_Init(void);
void LCD_Write(char *str);
void LCD_Pos_Cursor(int row, int col);
void LCD_Clear(void);

#endif /* INC_LCD_H_ */
