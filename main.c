#define F_CPU 8000000UL
#include "usb.c"
#include <avr/io.h>
#include <stdio.h>

static volatile float AVcc;

void adc_init(void) {
	ADMUX = (0 << REFS1) | (1 << REFS0);
	ADMUX |= (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
	uint16_t adc_result = ADC;
	AVcc = adc_result;
	AVcc = 1.1 * 1023 / adc_result;
	usb_print("\n\r AVcc: ");
	usb_tx_float(AVcc);
	ADCSRA |= (1 << ADSC);
}


int main(void) {
	usb_init();
	adc_init();
	while (1);
}