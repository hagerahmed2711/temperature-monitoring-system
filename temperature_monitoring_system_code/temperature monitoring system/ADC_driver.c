#include <avr/io.h>
#include "std_macros.h"
void adc_init(){
	SET_BIT(ADMUX,REFS0); // vref =avcc
	// SET_BIT(ADCSRA,ADPS0); 
	SET_BIT(ADCSRA,ADPS1);// set division
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADEN); // enable
	
}
uint16_t adc_read(uint8_t channel){
	uint16_t x;
	ADMUX&=0XE0;
	ADMUX|=channel;
	SET_BIT(ADCSRA,ADSC);
	while(ADCSRA & (1<<ADSC));
	ADCSRA |= (1<<ADIF);
	x=ADC;
	return x;
}