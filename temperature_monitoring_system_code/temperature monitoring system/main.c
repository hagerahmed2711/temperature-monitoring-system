#include <avr/io.h>
#include "ADC_driver.h"
#include "LCD.h"
unsigned short temperature;
uint16_t digital_value;
int main(void)
{
	DIO_vsetPINDir('C',0,1);
	DIO_vsetPINDir('C',1,1);
	DIO_vsetPINDir('C',2,1);
	adc_init();
	LCD_vInit();
	LCD_vSend_string("temperature=");
	
	while (1)
	{
		digital_value=adc_read(0);
		temperature=(digital_value*500)/1023;
		if(temperature<10)
		{
			LCD_movecursor(1,13);
			LCD_vSend_char(30);
			LCD_vSend_char((temperature%10)+48);
			LCD_vSend_char(0xDF);
			LCD_vSend_char('c');
		}
		else if( temperature<100)
		{
			LCD_movecursor(1,13);
			LCD_vSend_char((temperature/10)+48);
			LCD_vSend_char((temperature%10)+48);
			LCD_vSend_char(0XDF);
			LCD_vSend_char('c');
			
			if(temperature<=20)
			{
				DIO_write('C',1,1);
			}
			else if (temperature>30&&temperature<50)
			{
				DIO_write('C',0,1);
			}
			else if (temperature>=50)
			{
				DIO_write('C',0,1);
				DIO_write('C',2,1);
			}
			else
			{
				DIO_write('C',0,0);
				DIO_write('C',1,0);
				DIO_write('C',2,0);
			}
		}
	}
}

