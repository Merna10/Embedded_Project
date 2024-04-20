/*
 * lcd.c
 *
 *  Created on: Oct 3, 2022
 *      Author: merna
 */
#include <util/delay.h>
#include "common_macros.h"
#include "gpio.h"
#include "lcd.h"

/* FUNCTION DEFINATION*/

/*Initialize the LCD*/
void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID,PIN_OUTPUT );
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID,PIN_OUTPUT );
	_delay_ms(20);/*DELAY ALWAYS > 15MS*/
#if(LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	LCD_SendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#elif(LCD_DATA_BITS_MODE == 4)
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , PIN_OUTPUT);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif
	LCD_SendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

/*SEND COMMAND*/

void LCD_SendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);/*RS=0*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);/*E=1*/
	_delay_ms(1);
#if(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, command);/*WRITE COMMAND*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID,LOGIC_LOW);/*E=0*/
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(command,7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID,LOGIC_LOW);/*E=0*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID,LOGIC_HIGH);/*E=1*/
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(command,3));
	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /*E=0*/
	_delay_ms(1);

#endif

}

/*DISPLAY*/

void LCD_DisplayChar(uint8 data)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);/*RS=1*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);/*E=1*/
	_delay_ms(1);
#if(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, data);/*OUT COMMAND*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID,LOGIC_LOW);/*E=0*/
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(data,7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID,LOGIC_LOW);/*E=0*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID,LOGIC_HIGH);/*E=1*/
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(data,3));
	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /*E=0*/
	_delay_ms(1);

#endif
}

/*DISPLAY*/

void LCD_DisplayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_DisplayChar(Str[i]);
		i++;
	}
}

/*WRITE IN IN SPECIFIC ROW*/

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;
	switch(row)
	{
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = col+0x40;
		break;
	case 2:
		lcd_memory_address = col+0x10;
		break;
	case 3:
		lcd_memory_address = col+0x50;
		break;

	}
	LCD_SendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*DISPLAY IN SPECIFIC ROW*/

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col);
	LCD_DisplayString(Str);
}

/*NUMBERS*/

void LCD_intgerToString(int data)
{
	char str[16];
	itoa(data,str,10); /* 10 for decimal */
	LCD_DisplayString(str);
}

/*CLEAR*/

void LCD_clearScreen(void)
{
	LCD_SendCommand(LCD_CLEAR_COMMAND); /* CLEAR COMMAND */
}
