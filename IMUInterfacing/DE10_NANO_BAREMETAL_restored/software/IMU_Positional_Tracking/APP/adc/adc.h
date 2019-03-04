/*
 * adc.h
 *
 *  Created on: Mar 17, 2018
 *      Author: dannick
 */

#ifndef APP_ADC_H_
#define APP_ADC_H_

#define ADC_MAKE_BASE(base)  ((void *) (((char *)  (ALT_LWFPGASLVS_ADDR))+ (base)))

// ADC Read Addresses
#define ADC_CH0 0x00001200
#define ADC_CH0_BASE ADC_MAKE_BASE(ADC_CH0)
#define ADC_CH1 0x00001204
#define ADC_CH1_BASE ADC_MAKE_BASE(ADC_CH1)
#define ADC_CH2 0x00001208
#define ADC_CH2_BASE ADC_MAKE_BASE(ADC_CH2)
#define ADC_CH3 0x0000120C
#define ADC_CH3_BASE ADC_MAKE_BASE(ADC_CH3)
#define ADC_CH4 0x00001210
#define ADC_CH4_BASE ADC_MAKE_BASE(ADC_CH4)
#define ADC_CH5 0x00001214
#define ADC_CH5_BASE ADC_MAKE_BASE(ADC_CH5)
#define ADC_CH6 0x00001218
#define ADC_CH6_BASE ADC_MAKE_BASE(ADC_CH6)
#define ADC_CH7 0x0000121C
#define ADC_CH7_BASE ADC_MAKE_BASE(ADC_CH7)

// ADC Write Addresses
#define ADC_UP 0x00001200
#define ADC_UP_BASE ADC_MAKE_BASE(ADC_UP)
#define ADC_AUTO 0x00001204
#define ADC_AUTO_BASE ADC_MAKE_BASE(ADC_AUTO)

void ADCInit(void);
int32_t* getADCChannel(int channel_num);
int32_t getTargetVolume(int8_t tape_num, int16_t dispense_volume);
int32_t getCurrentVolume(int8_t tape_num);
int32_t calculateVolume(int32_t raw_value, int8_t tape_num);
float calculateHeight(int32_t raw_value, int8_t tape_num);

#endif /* APP_ADC_H_ */
