/*
 * LCD.c
 *
 *  Created on: Jul 12, 2023
 *      Author: Nejc
 */


#include "LCD.h"

extern TIM_HandleTypeDef timer;

/*
 * @brief Function to delay in microseconds
 * @param delay: value in microseconds to delay
 * @retval None
 */
void __LCD_Delay(uint16_t delay) {

	__HAL_TIM_SET_COUNTER(&timer, 0);
	while (__HAL_TIM_GET_COUNTER(&timer) < delay);

}

/*
 * @brief Function to write individual bits to the pins
 * @param value: value to write
 * @retval None
 */
void __LCD_Write4Bits(uint8_t value) {

	HAL_GPIO_WritePin(DATA4_PORT, DATA4_PIN, (value >> 3) & 0x01);
	HAL_GPIO_WritePin(DATA3_PORT, DATA3_PIN, (value >> 2) & 0x01);
	HAL_GPIO_WritePin(DATA2_PORT, DATA2_PIN, (value >> 1) & 0x01);
	HAL_GPIO_WritePin(DATA1_PORT, DATA1_PIN, value & 0x01);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 1);
	__LCD_Delay(120);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 0);
	__LCD_Delay(120);

}

/*
 * @brief Function to send data to the LCD and enable RS pin
 * @param value: value to send
 * @param state: state to set RS (register select) pin [0, 1]
 * @retval None
 */
void __LCD_Send(uint8_t value, int state) {

	HAL_GPIO_WritePin(RS_PORT, RS_PIN, state);
	__LCD_Write4Bits(value >> 4);
	__LCD_Write4Bits(value);

}

/*
 * @brief Function to send command to the LCD
 * @param value: command to send
 * @retval None
 */
void __LCD_Cmd(uint8_t value) {

	__LCD_Send(value, 0);

}

/*
 * @brief Function to send data to the LCD
 * @param value: value to send
 * @retval None
 */
void __LCD_Data(uint8_t value) {

	__LCD_Send(value, 1);

}

/*
 * @brief Function to write to the LCD
 * @param value: value to write to the LCD
 * @retval None
 */
void LCD_Write(char *value) {

	while (*value) {
		__LCD_Data(*value++);
		__LCD_Delay(5000);
		// HAL_Delay(1000);
	}

}

/*
 * @brief Function to write a single character to the LCD
 * @param character: value to write
 * @retval None
 */
void LCD_Write_Char(char character) {

	__LCD_Data(character);
	__LCD_Delay(5000);

}

/*
 * @brief Function to set the cursor position
 * @param row: row to set the cursor [0, 1]
 * @param col: column to set the cursor [0, 15]
 * @retval None
 */
void LCD_Pos_Cursor(uint8_t row, uint8_t col) {

	switch (row) {
		case 0:
			col |= 0x80;
	        break;
	    case 1:
	        col |= 0xC0;
	        break;
	    default:
	    	row = 0;
	    	col = 0;
	    	break;
	}
	__LCD_Cmd(col);

}

/*
 * @brief Function to clear the display
 * @param None
 * @retval None
 */
void LCD_Clear(void) {

	__LCD_Cmd(CLEAR);

}

/*
 * @brief Function to scroll the display right
 * @param None
 * @retval None
 */
void LCD_Scroll_Display_Right(void) {

	__LCD_Cmd(SCROLL_DISPLAY_RIGHT);

}

/*
 * @brief Function to scroll the display left
 * @param None
 * @retval None
 */
void LCD_Scroll_Display_Left(void) {

	__LCD_Cmd(SCROLL_DISPLAY_LEFT);

}

/*
 * @brief Function to initialize the LCD
 * @param cursor: true/false to enable cursor
 * @param blinking: true/false to enable blinking
 * @retval None
 */
void LCD_Init(bool cursor, bool blinking) {

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
	if (cursor && blinking) {
		__LCD_Cmd(CURSOR_BLINK);
	} else if (cursor) {
		__LCD_Cmd(CURSOR);
	} else if (blinking) {
		__LCD_Cmd(BLINK);
	} else {
		__LCD_Cmd(NO_BLINK_NO_CURSOR);
	}

	__LCD_Delay(50000);
	LCD_Pos_Cursor(0, 0);

}


