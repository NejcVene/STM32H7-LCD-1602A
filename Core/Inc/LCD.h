/*
 * LCD.h
 *
 *  Created on: Jul 12, 2023
 *      Author: Nejc
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <stdint.h>
#include <stdbool.h>
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

#define CURSOR_BLINK 0x0F
#define CURSOR 0x0E
#define BLINK 0x0D
#define NO_BLINK_NO_CURSOR 0x0C
#define CLEAR 0x01
#define SCROLL_DISPLAY_LEFT 0x18
#define SCROLL_DISPLAY_RIGHT 0x1C

void LCD_Init(bool, bool);
void LCD_Write(char *);
void LCD_Write_Char(char);
void LCD_Pos_Cursor(uint8_t, uint8_t);
void LCD_Clear(void);
void LCD_Scroll_Display_Left(void);
void LCD_Scroll_Display_Right(void);
void LCD_Custom_Char(uint8_t, uint8_t);

#endif /* INC_LCD_H_ */
