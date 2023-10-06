/*
************************************************************
* UART Header File                                         *
************************************************************
* File:    uart.h                                          *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  10 February 2023                                *
* Update:  12 February 2023                                *
*          + Add rxd event and subscriber.                 *    
************************************************************
*/

#ifndef __UART_H__
#define __UART_H__

#include <gpio.h>


#define UART_PRINTF_BUFFER_LENGTH 	128

/**
 * ENUM
*/
typedef enum UART_NUM_TYPE
{
	UART_NUM_1,			/*! UART channel 1	*/	/* -> Computer 		*/
	UART_NUM_2			/*! UART channel 2	*/	/* -> Wi-Fi module 	*/
} uart_num_t;


/**
 * Set baudrate of the target uart.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - baudrate: Baudrate of the target uart.
 */
int16_t uart_baudrate_set(uart_num_t uart_num, uint32_t baudrate);


/**
 * Enable RX interrupt of the target uart.
 *  * Parameter:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
*/
int16_t uart_enable_rx_intr(uart_num_t uart_num);


/**
 * Disable RX interrupt of the uart.
 * Parameter:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
*/
int16_t uart_disable_rx_intr(uart_num_t uart_num);



/**
 * Enable TX interrupt of the uart.
 * Parameter:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
*/
int16_t uart_enable_tx_intr(uart_num_t uart_num);


/**
 * Disable TX interrupt of the target uart.
 * Parameter:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
*/
int16_t uart_disable_tx_intr(uart_num_t uart_num);


/**
 * Enable transmitting operation of the target uart.
 * Parameter:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
*/
int16_t uart_enable_tx(uart_num_t uart_num);


/**
 * Disable transmitting operation of the target uart.
 * Parameter:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
*/
int16_t uart_disable_tx(uart_num_t uart_num);


/**
 * Put a character to the target uart.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - data: Character to put to the target uart.
*/
int16_t uart_put_char(uart_num_t uart_num, char data);


/**
 * Put a byte to the target uart.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - byte: Byte to put to the target uart.
*/
int16_t uart_put_byte(uart_num_t uart_num, char byte);

/**
 * Puts a character to the target uart TX buffer without waiting.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - data: Character to put to the target uart.
*/
int16_t uart_put_char_async(uart_num_t uart_num, char data);

/**
 * Checks if the TX operation ready.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * Return:
 * - If the TX operation is ready, returns 1, otherwise returns 0.
*/
bool uart_is_tx_ready(uart_num_t uart_num);

/**
 * Return a character received from the target uart.
 * This function blocks until a character is received.
 * Parameter:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
*/
char uart_get_char(uart_num_t uart_num);


/**
 * Write the given string the target uart.
 * This function blocks until a all characters are written.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - string: String data to be written to the target uart.
*/
int16_t uart_write_string(uart_num_t uart_num, const char* string);


/**
 * Write the given bytes data the target uart.
 * This function blocks until a all bytes are written.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - bytes: Bytes data to be written to the target uart.
 * - length: Number of bytes of the byte data.
*/
int16_t uart_write_bytes(uart_num_t uart_num, const uint8_t* bytes, uint16_t length);


/**
 * Print formatted string to the target uart.
 * This function blocks until a characters are sent.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - format: Format of the string to be printed to the target uart.
*/
int16_t uart_printf(uart_num_t uart_num, const char *format, ...);


/**
 * Initialize the target uart with default hardware settings of the Ternion boards.
 * Parameters:
 * - uart_num: Id of the target uart (UART_NUM_1 or UART_NUM_2).
 * - baudrate: Baudrate of the the target uart.
*/
int16_t uart_init(uart_num_t uart_num, int32_t baudrate);



/**
 * STRUCTURE
 * Holds data of the uart rxd.
 * Members:
 * - uart_num: Id of uart.
 * - rxd_data: Received byte data.
*/
typedef struct UART_RXD_DATA_TYPE {
	uart_num_t	uart_num;
	char		rxd_data;
}uart_rxd_data_t;

/**
 * Callback function prototype of the uart rxd.
*/
typedef void (*uart_rxd_callback_t)(uart_rxd_data_t * uart_rxd_data);


/**
 * Subscribe to uart rxd event.
 * Parameters:
 * - uart_num: Id of target uart.
 * - callback: Callback function called when a byte received.
 * Note:
 * - The target uart must be initialized using the uart_enable_rx_intr function to activate the rxd event capability.
*/
int16_t uart_rxd_subscribe(uart_num_t uart_num, uart_rxd_callback_t uart_rxd_callback);


#endif // __UART_H__
