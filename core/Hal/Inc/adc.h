
#ifndef __ADC_H__
#define __ADC_H__

#include <uart.h>   /** Not required. It is included in the gpio.h */
#include <gpio.h>
 

/**
 * Initializes the ADC.
*/
int16_t adc_init(void);


/**
 * Removes the ANx connected to the target gpio into the scan-list.
*/
int16_t adc_scan_deselect(gpio_num_t gpio_num);


/**
 * Adds the ANx connected to the target gpio into the scan-list.
*/
int16_t adc_scan_select(gpio_num_t gpio_num);


/**
 * Get adc value (10-bit data) from the adc buffer.
*/
int16_t adc_read_raw(int16_t buffer_index);

#endif // __ADC_H__
