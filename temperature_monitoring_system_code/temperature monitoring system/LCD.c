#include "LCD.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>
void LCD_vInit(void)
{
	_delay_ms(200);
	DIO_vsetPINDir('D',0,1);
	DIO_vsetPINDir('D',1,1);
	DIO_vsetPINDir('D',2,1);
	DIO_vsetPINDir('D',3,1);
	DIO_vsetPINDir('D',4,1);
	DIO_vsetPINDir('D',5,1);
	DIO_vsetPINDir('D',6,1);
	DIO_vsetPINDir('D',7,1);
	DIO_vsetPINDir('B',EN,1);
	DIO_vsetPINDir('B',RW,1);
	DIO_vsetPINDir('B',RS,1);
	DIO_write('B',RW,0);
	LCD_vSend_cmd(EIGHT_BITS); //8 bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1); 
}


static void send_falling_edge(void)
{
	DIO_write('B',EN,1);
	_delay_ms(2);
	DIO_write('B',EN,0);
	_delay_ms(2);
}
void LCD_vSend_cmd(char cmd)
{
	
	DIO_write_port('D',cmd);
	DIO_write('B',RS,0);
	send_falling_edge();
	_delay_ms(1);
}

void LCD_vSend_char(char data)
{
	
	DIO_write_port('D',data);
	DIO_write('B',RS,1);
	send_falling_edge();
	_delay_ms(1);
}


void LCD_vSend_string(char *data)
{
	while((*data)!='\0')
	{
		LCD_vSend_char(*data);
		data++;
	}
}
void LCD_clearscreen()
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_movecursor(char row,char coloumn)
{
	char data ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
}
