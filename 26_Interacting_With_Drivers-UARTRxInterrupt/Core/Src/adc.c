/*
 * adc.c
 *
 *  Created on: Oct. 31, 2022
 *      Author: cdsmi
 */
#include "stm32wbxx_hal.h"
#include "adc.h"

void adc_init(void){
	RCC->AHB1ENR |= (1U<<0);			//= 0x00000001 (Enable clock for GPIOA)  |= means that only the bits that we want to change will change
	RCC->APB2ENR |= (1U<<8); 			//Enable clock for ADC1

	GPIOA->MODER |= 0xC;				//1100 (Set PA1 as analog)

	ADC1->CR = 0;						//Software trigger(CR : Control Register)
	ADC1->SQR3 = 1;						//Conversion sequence starts at ch 1
	ADC1->SQR1 = 0;						//Conversion sequence length 1
	ADC1->CR |= 1;						//Enable ADC1
}

uint32_t read_analog_sensor(void)
{
	ADC1->CR |= (1U<<30);
	while((ADC1->ISR & 2))				//2 = b10 (Waiting for conversion to complete)
	{ }
	return ADC1->DR;
}
