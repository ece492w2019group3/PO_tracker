/*
 * adc.c
 *
 *  Created on: Mar 17, 2018
 *      Author: dannick
 */
#include <hps.h>
#include <socal.h>
#include <stdint.h>

#include "adc.h"

void ADCInit(void){
    // Auto Read From the ADC
    alt_write_word(ADC_AUTO_BASE, 1);
}

int32_t* getADCChannel(int channel_num)
{
	int32_t* channel = 0;
	switch(channel_num)
	{
		case 0:
			channel = ADC_CH2_BASE;
			break;
		case 1:
			channel = ADC_CH4_BASE;
			break;
		case 2:
			channel = ADC_CH6_BASE;
			break;
		default:
			channel = NULL;
			break;
	}
	return channel;
}

int32_t getCurrentVolume(int8_t tape_num)
{
	int32_t* channel = getADCChannel(tape_num);
	int32_t raw = (0xFFF & alt_read_word(channel));
	return calculateVolume(raw, tape_num);
}

int32_t getTargetVolume(int8_t tape_num, int16_t dispense_volume)
{
	return getCurrentVolume(tape_num) - dispense_volume;
}

int32_t calculateVolume(int32_t raw_value, int8_t tape_num){
	float height = ((float)raw_value - 2289.2)/61.09;
	// Radius 4.7 cm => pi*4.7^2
	float volume = 69.3977817178 * calculateHeight(raw_value, tape_num);
	return (int32_t)volume;
}

float calculateHeight(int32_t raw_value, int8_t tape_num){
	float height = 0;
	switch(tape_num){
		case 0:
			height = ((float)raw_value - 2423.5)/61.345;
			break;
		case 1:
			height = ((float)raw_value - 2150.5)/60.695;
			break;
		case 2:
			height = ((float)raw_value - 2289.2)/61.090;
			break;
		default:
			height = -1;
			break;
	}
	return height;
}
