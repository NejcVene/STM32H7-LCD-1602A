/*
 * LCD.c
 *
 *  Created on: Jul 12, 2023
 *      Author: Nejc
 */


#include "LCD.h"

extern TIM_HandleTypeDef timer;
void __LCD_Delay(uint16_t delay) {

	__HAL_TIM_SET_COUNTER(&timer, 0);
	uint32_t val = 0;
	while (__HAL_TIM_GET_COUNTER(&timer) < delay) {
		val = __HAL_TIM_GET_COUNTER(&timer);
	}

}

void __LCD_Write4Bits(uint8_t value) {

	HAL_GPIO_WritePin(DATA4_PORT, DATA4_PIN, (value >> 3) & 0x01);
	HAL_GPIO_WritePin(DATA3_PORT, DATA3_PIN, (value >> 2) & 0x01);
	HAL_GPIO_WritePin(DATA2_PORT, DATA2_PIN, (value >> 1) & 0x01);
	HAL_GPIO_WritePin(DATA1_PORT, DATA1_PIN, (value >> 0) & 0x01);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 1);
	__LCD_Delay(120);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 0);
	__LCD_Delay(120);

}

void __LCD_Send(uint8_t value, int state) {

	HAL_GPIO_WritePin(RS_PORT, RS_PIN, state);
	__LCD_Write4Bits(value >> 4);
	__LCD_Write4Bits(value);

}

void __LCD_Cmd(uint8_t value) {
	__LCD_Send(value, 0);
}

void __LCD_Data(uint8_t value) {
	__LCD_Send(value, 1);
}

void LCD_Write(char *str) {

	while (*str) {
		__LCD_Data(*str++);
		// HAL_Delay(1000);
	}

}

void LCD_Pos_Cursor(int row, int col) {

	switch (row) {
		case 0:
			col |= 0x80;
	        break;
	    case 1:
	        col |= 0xC0;
	        break;
	}
	__LCD_Cmd(col);

}

void LCD_Clear() {

	__LCD_Cmd(0x01);

}

void LCD_Init(void) {

	// Init
	__LCD_Delay(50000);
	__LCD_Cmd(0x30);
	__LCD_Delay(4500);
	__LCD_Cmd(0x30);
	__LCD_Delay(150);
	__LCD_Cmd(0x30);

	// Go to 4 bit mode
	__LCD_Delay(10);
	__LCD_Cmd(0x20);
	__LCD_Delay(50);

	// Set display lines and font
	__LCD_Cmd(0x28);
	__LCD_Delay(50);

	// Display on/off
	__LCD_Cmd(0x08);
	__LCD_Delay(50);

	// Display clear
	__LCD_Cmd(0x01);
	__LCD_Delay(1500);

	// Entry mode set
	__LCD_Cmd(0x06);
	__LCD_Delay(50);

	// Display on/off
	__LCD_Cmd(0x0F);

}


