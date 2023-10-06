/*
************************************************************
* GPIO Header File                                         *
************************************************************
* File:    gpio.h                                          *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  08 February 2023                                *
* Update:  12 February 2023                                *
*          + Add gpio inputs change event and subscriber.  *
************************************************************
*/


/**          TRN    ORG
 * ---------------------
 * LED0 <--> RB4    RA2
 * LED1 <--> RB5    RA4
 * LED2 <--> RB6    RB2
 * LED3 <--> RB7    RB3
*/                          
                          
/**          TRN    ORG    
 * --------------------
 * PSW0 <--> RB0    RB4	
 * PSW1 <--> RB1    RB5	
 * PSW2 <--> RB2    RB6	
 * PSW3 <--> RB3    RB7	
*/                          
                          
/**          TRN    ORG    
 * --------------------
 *  AN0 <--> RA0    RA0    
 *  AN1 <--> RA1    RA1    
 *  AN2 <--> RB0    RB0    
 *  AN3 <--> RA1    RB1    
*/                          
                          
/*
+------------------------------+    +------------------------------+  
|           TERNION            |    |           ORIGINAL           |
+--------+--------+------------+    +--------+--------+------------+
|  IO_a  |  IO_b  |    GPIO    |    |  IO_a  |  IO_b  |    GPIO    |
+--------+--------+------------+    +--------+--------+------------+
|  LED0  |        |     RB4    |    |  LED0  |        |     RA2    |
+--------+--------+------------+    +--------+--------+------------+
|  LED1  |        |     RB5    |    |  LED1  |        |     RA4    |
+--------+--------+------------+    +--------+--------+------------+
|  LED2  |        |     RB6    |    |  LED2  |        |     RB2    |
+--------+--------+------------+    +--------+--------+------------+
|  LED3  |        |     RB7    |    |  LED3  |        |     RB3    |
+--------+--------+------------+    +--------+--------+------------+
|  PSW0  |   AN2  |     RB0    |    |  PSW0  |        |     RB4    |
+--------+--------+------------+    +--------+--------+------------+
|  PSW1  |   AN3  |     RB1    |    |  PSW1  |        |     RB5    |
+--------+--------+------------+    +--------+--------+------------+
|  PSW2  |   AN4  |     RB2    |    |  PSW2  |        |     RB6    |
+--------+--------+------------+    +--------+--------+------------+
|  PSW3  |   AN5  |     RB3    |    |  PSW3  |        |     RB7    |
+--------+--------+------------+    +--------+--------+------------+
|  LDR0  |   AN0  |     RA0    |    |  AN0   |        |     RA0    |
+--------+--------+------------+    +--------+--------+------------+
|  LDR1  |   AN1  |     RA1    |    |  AN1   |        |     RA1    |
+--------+--------+------------+    +--------+--------+------------+
|  AINx  |  PSW0  |     RB2    |    |  AN2   |        |     RA2    |
+--------+--------+------------+    +--------+--------+------------+
|  AINx  |  PSW1  |     RB5    |    |  AN3   |        |     RA3    |
+--------+--------+------------+    +--------+--------+------------+
|  AINx  |  PSW2  |     RB6    |    
+--------+--------+------------+    
|  AINx  |  PSW3  |     RB7    |    
+--------+--------+------------+    
*/




#ifndef __GPIO_H__
#define __GPIO_H__


#include <mcu.h>


typedef enum GPIO_REG_TYPE
{
	GPIO_RA_0 = 0x0000,						/*  0: AN0 LDR0 		*/
	GPIO_RA_1,								/*  1: AN1 LDR1 		*/
	GPIO_RA_2,								/*  2: 					*/
	GPIO_RA_3,								/*  3: 					*/
	GPIO_RA_4,								/*  4: BOOT				*/

	/* RA5 - RA15 are not defined */

	GPIO_RB_0 = 0x0010,						/*  16: AN2 PSW0		*/
	GPIO_RB_1,								/*  17: AN3 PSW2		*/
	GPIO_RB_2,								/*  18: AN4 PSW3		*/
	GPIO_RB_3,								/*  19: AN5 PSW4		*/
	GPIO_RB_4,								/*  20: 	LED0		*/
	GPIO_RB_5,								/*  21: 	LED1		*/
	GPIO_RB_6,								/*  22: 	LED2		*/
	GPIO_RB_7,								/*  23: 	LED3		*/
	GPIO_RB_8,								/*  24: 				*/
	GPIO_RB_9,								/*  25: 				*/
	GPIO_RB_10,								/*  26: 				*/
	GPIO_RB_11,								/*  27: 				*/
	GPIO_RB_12,								/*  28: AN12 U1RX		*/
	GPIO_RB_13,								/*  29: AN11 U1TX		*/
	GPIO_RB_14,								/*  30: AN10 U2RX		*/
	GPIO_RB_15								/*  31: AN9  U1TX		*/
}gpio_reg_t;


typedef enum GPIO_NUM_TYPE
{
	GPIO_NUM_0 = 0x0000,					/*  0: AN0				*/
	GPIO_NUM_1,								/*  1: AN1				*/
	GPIO_NUM_2,								/*  2: 					*/
	GPIO_NUM_3,								/*  3: 					*/
	GPIO_NUM_4,								/*  4: 					*/

	/* NUM5 - NUM15 are not defined */

	GPIO_NUM_16 = 0x0010, 					/*  16: RB0 AN2 PSW0	*/
	GPIO_NUM_17,							/*  17: RB1 AN3 PSW2	*/
	GPIO_NUM_18,							/*  18: RB2 AN4 PSW3	*/
	GPIO_NUM_19,							/*  19: RB3 AN5 PSW4	*/
	GPIO_NUM_20,							/*  20: RB4 LED0		*/
	GPIO_NUM_21,							/*  21: RB5 LED1		*/
	GPIO_NUM_22,							/*  22: RB6 LED2		*/
	GPIO_NUM_23,							/*  23: RB7 LED3		*/
	GPIO_NUM_24,							/*  24: RB8 			*/
	GPIO_NUM_25,							/*  25: RB9 			*/
	GPIO_NUM_26,							/*  26: RB10 			*/
	GPIO_NUM_27,							/*  27: RB11			*/
	GPIO_NUM_28,							/*  28: RB12 AN12  U1RX	*/
	GPIO_NUM_29,							/*  29: RB13 AN11  U1TX	*/
	GPIO_NUM_30,							/*  30: RB14 AN10  U2RX	*/
	GPIO_NUM_31								/*  31: RB15 AN9   U1TX	*/
}gpio_num_t;


/**          ORG    TRN
 * --------------------
 * LED0 <--> RA2	RB4
 * LED1 <--> RA4	RB5
 * LED2 <--> RB2	RB6
 * LED3 <--> RB3	RB7
	*/
typedef enum GPIO_LED_NUM_TYPE
{
	#if USE_TERNION_BOARD >= 1
		GPIO_LED_NUM_0	= GPIO_RB_4,
		GPIO_LED_NUM_1	= GPIO_RB_5,
		GPIO_LED_NUM_2	= GPIO_RB_6,
		GPIO_LED_NUM_3	= GPIO_RB_7
	#else
		GPIO_LED_NUM_0	= GPIO_RA_2,
		GPIO_LED_NUM_1	= GPIO_RA_4,
		GPIO_LED_NUM_2	= GPIO_RB_2,
		GPIO_LED_NUM_3	= GPIO_RB_3
	#endif // USE_TERNION_BOARD >= 1
}gpio_led_num_t;


/**          ORG    TRN
 * --------------------
 * PSW0 <--> RB4	RB0
 * PSW1 <--> RB5	RB1
 * PSW2 <--> RB6	RB2
 * PSW3 <--> RB7	RB3
*/
typedef enum GPIO_PSW_NUM_TYPE
{
	#if USE_TERNION_BOARD >= 1
		GPIO_PSW_NUM_0	= GPIO_RB_0,
		GPIO_PSW_NUM_1	= GPIO_RB_1,
		GPIO_PSW_NUM_2	= GPIO_RB_2,
		GPIO_PSW_NUM_3	= GPIO_RB_3
	#else
		GPIO_PSW_NUM_0	= GPIO_RB_4,
		GPIO_PSW_NUM_1	= GPIO_RB_5,
		GPIO_PSW_NUM_2	= GPIO_RB_6,
		GPIO_PSW_NUM_3	= GPIO_RB_7
	#endif // USE_TERNION_BOARD >= 1
}gpio_psw_num_t;


/**         ORG    TRN
 * -------------------
 * AN0 <--> RA0    RA0
 * AN1 <--> RA1    RA1
 * AN2 <--> RB0    RB0
 * AN3 <--> RB1    RA1
*/
typedef enum GPIO_ADC_NUM_TYPE
{

	GPIO_ADC_NUM_0	= GPIO_RA_0,
	GPIO_ADC_NUM_1	= GPIO_RA_1,
	GPIO_ADC_NUM_2	= GPIO_RB_0,
	GPIO_ADC_NUM_3	= GPIO_RB_1,

	#if USE_TERNION_BOARD >= 1
		GPIO_ADC_NUM_4	= GPIO_RB_2,
		GPIO_ADC_NUM_5	= GPIO_RB_3
	#endif // USE_TERNION_BOARD >= 0
}gpio_adc_num_t;






typedef enum GPIO_MODE_TYPE
{
	GPIO_MODE_ANALOG,
	GPIO_MODE_DIGITAL
} gpio_mode_t;

typedef enum GPIO_LEVEL_TYPE
{
	GPIO_LEVEL_LOW,
	GPIO_LEVEL_HIGH,
}gpio_level_t;


typedef enum GPIO_DIRECTION_TYPE 
{
	GPIO_DIRECTION_OUTPUT,
	GPIO_DIRECTION_INPUT,
}gpio_direction_t;


typedef enum GPIO_GROUP_TYPE 
{
	GPIO_GROUP_A,
	GPIO_GROUP_B,
} gpio_group_t;


/**
 * Address of TRIS Registers
 */
#define TRIS_BASE	0x02C0
#define TRISA_ADDR 	TRIS_BASE + 0x0000
#define TRISB_ADDR 	TRIS_BASE + 0x0008
#define TRISC_ADDR 	TRIS_BASE + 0x0010

/**
 * Address of PORT Registers
 */
#define PORT_BASE 	0x02C2
#define PORTA_ADDR 	PORT_BASE + 0x0000
#define PORTB_ADDR 	PORT_BASE + 0x0008
#define PORTC_ADDR 	PORT_BASE + 0x0010

/**
 * Address of LAT Registers
 */
#define LAT_BASE 	0x02C4
#define LATA_ADDR 	LAT_BASE + 0x0000
#define LATB_ADDR 	LAT_BASE + 0x0008
#define LATC_ADDR 	LAT_BASE + 0x0010

/**
 * Address of ODC Registers
 */
#define ODC_BASE 	0x02C6
#define ODCA_ADDR 	ODC_BASE + 0x0000
#define ODCB_ADDR 	ODC_BASE + 0x0008
#define ODCC_ADDR 	ODC_BASE + 0x0010

/**
 * Helper function.
 * Returns a channel index of analog input (AN).
* Parameter:
 * - gpio_num
 * Outgoing Calls:
 * - None
 */
int16_t gpio_get_an_index(gpio_num_t gpio_num);


/**
 * Helper function
 * Returns CN index of the given gpio_num.
* Parameter:
 * - gpio_num
 * Outgoing Calls:
 * - None
 */
int16_t gpio_get_cn_index(gpio_num_t gpio_num);


/**
 * Helper function
 * Returns an bit index of gpio.
* Parameter:
 * - gpio_num
 * Outgoing Calls:
 * - None
 */
int16_t gpio_get_bit_index(gpio_num_t gpio_num);


/**
 * Helper function.
 * Returns a group name of gpio.
 * Parameter:
 * - gpio_num
 * Outgoing Calls:
 * - None
 */
gpio_group_t gpio_get_group(gpio_num_t gpio_num);


/**
 * Helper function
 * Return a pointer that points to a proper register.
 * Parameters:
 * - gpio_num
 * - reg_a
 * - reg_b
 * Outgoing Calls:
 * - None
*/
int16_t * gpio_select_reg(gpio_num_t gpio_num, int16_t *reg_a, int16_t *reg_b);


/**
 * Helper function
 * Return a pointer that points to TRISA or TRISB.
 * - gpio_num
 * Outgoing Calls:
 * - gpio_select_reg
*/
int16_t * gpio_get_tris_reg(gpio_num_t gpio_num);


/**
 * Helper function
 * Return a pointer that points to LATA or LATB.
 * Parameter:
 * - gpio_num
 * Outgoing Calls:
 * - gpio_select_reg
*/
int16_t * gpio_get_lat_reg(gpio_num_t gpio_num);


/**
 * Helper function
 * Return a pointer that points to PORTA or PORTB.
 * Parameters:
 * - gpio_num
 * Outgoing Calls:
 * - gpio_select_reg
*/
int16_t * gpio_get_port_reg(gpio_num_t gpio_num);


/**
 * Helper function
 * Return a pointer that points to ODCA or ODCB.
 * Parameters:
 * - gpio_num
 * Outgoing Calls:
 * - gpio_select_reg
*/
int16_t * gpio_get_odc_reg(gpio_num_t gpio_num);


/**
 * Helper function
 * Return a 16-bit mask of the target gpio.
 * Outgoing Calls:
 * - gpio_get_bit_index
*/
int16_t gpio_get_bit_mask(gpio_num_t gpio_num);


/*******************************************************************/
/*                          GPIO APIs                              */
/*******************************************************************/


/**
 * Sets direction of a target GPIO.
 * Parameters:
 * - gpio_num: Id of target GPIO.
 * - gpio_direction: Direction of target GPIO.
*/
sys_error_t gpio_set_direction(gpio_num_t gpio_num, gpio_direction_t gpio_direction);


/**
 * Enables analog input mode and changes GPIO's direction to input mode.
 * Parameter:
 * - gpio_num: Id of target GPIO.
 * Note:
 * - Make it as function to improve the call graph.
 */
sys_error_t gpio_analog_enable(gpio_num_t gpio_num);


/**
 * Disable analog mode of the target GPIO.
 * Parameter:
 * - gpio_num: Id of the target GPIO.
 */
sys_error_t gpio_analog_disable(gpio_num_t gpio_num);


/**
 * Sets operation mode (analog or digital) of the GPIO.
 * Parameters:
 * - gpio_num: Id of target GPIO.
 * - gpio_mode: Operation mode of the GPIO.
 * Outgoing Calls:
 * - gpio_analog_enable
 * - gpio_analog_disable
*/
sys_error_t gpio_set_mode(gpio_num_t gpio_num, gpio_mode_t gpio_mode);


/**
 * Writes a bit data to the LAT register.
 * Parameters:
 * - gpio_num: Id of the GPIO.
 * - lat_level: Logic level to be written to the LAT register.
 * Outgoing Calls:
 * - gpio_get_lat_reg
 * - gpio_get_bit_mask
 */
sys_error_t gpio_set_lat_level(gpio_num_t gpio_num, gpio_level_t lat_level);


/**
 * Sets level of the GPIO to the given level.
 * Parameters:
 * - gpio_num: Id of target GPIO.
 * - gpio_level: Logic level to be written to GPIO.
 * Outgoing Calls:
 * - gpio_set_lat_level
 * Note:
 * - The GPIO must be set to digital output mode before call this function.
 */
sys_error_t gpio_set_level(gpio_num_t gpio_num, gpio_level_t gpio_level);


/**
 * Toggles level of the LAT register (not pin).
 * Parameter:
 * - gpio_num: Id of target gpio.
 * Outgoing Calls:
 * - gpio_lat_level_get
 * - gpio_lat_level_set
 */
sys_error_t gpio_toggle_lat_level(gpio_num_t gpio_num);


/**
 * Toggles level of the GPIO.
 * Parameter:
 * - gpio_num: Id of target gpio.
 * Outgoing Calls:
 * - gpio_lat_level_get
 * - gpio_level_set
 * Note:
 * - The GPIO must be set to digital output mode before call this function.
 */
sys_error_t gpio_toggle_level(gpio_num_t gpio_num);


/**
 * Returns level (bit data) from the GPIO.
 * Parameter:
 * - gpio_num: Id of target GPIO.
 * Outgoing Calls:
 * - gpio_get_bit_mask
 * - gpio_get_port_reg
 * Note:
 * - The GPIO must be set to digital input mode before call this function.
 */
int16_t gpio_get_level(gpio_num_t gpio_num) ;


/**
 * Enables open-drain of the GPIO.
 * Parameter:
 * - gpio_num: Id of target GPIO.
  * Outgoing Calls:
 * - gpio_get_odc_reg
 * - gpio_get_bit_mask
 */
sys_error_t gpio_open_drain_enable(gpio_num_t gpio_num);


/**
 * Disables open-drain of the GPIO.
 * Parameter:
 * - gpio_num: Id of target GPIO.
* Outgoing Calls:
 * - gpio_get_odc_reg
 * - gpio_get_bit_mask
 */
sys_error_t gpio_open_drain_disable(gpio_num_t gpio_num);


/**
 * Enables pin change notification of the GPIO.
 * Parameter:
 * - gpio_num: Id of target GPIO.
 * Outgoing Calls:
 * - gpio_get_cn_index
 * - gpio_get_bit_mask
 * 
 */
sys_error_t gpio_change_notification_enable(gpio_num_t gpio_num);




/**
 * Holds data of the gpio inputs change.
 * Members:
 * - gpio_ra_data: PORTA input data.
 * - gpio_rb_data: PORTB input data.
*/
typedef struct GPIO_INPUTS_CHANGE_DATA_TYPE {
	int16_t gpio_ra_data;
	int16_t gpio_rb_data;
} gpio_inputs_change_data_t;

/**
 * Callback function prototype of the the gpio inputs change.
*/
typedef void (*gpio_inputs_change_callback_t)(gpio_inputs_change_data_t * gpio_inputs_change_data);



/**
 * Set callback function of the pin change notification, both falling and rising edges.
 * Parameter:
 * - callback: Callback function called when the pin level is changed.
 * Outgoing Calls:
 * - None
 * Note:
 * - The GPIO must be initialized using the gpio_change_notification_enable function to activate the input change capability.
*/
sys_error_t gpio_change_notification_set_callback(gpio_inputs_change_callback_t callback);


const uint8_t *gpio_get_led_pins(void);
const uint8_t *gpio_get_adc_pins(void);
const uint8_t *gpio_get_psw_pins(void);

#endif //__GPIO_H__
