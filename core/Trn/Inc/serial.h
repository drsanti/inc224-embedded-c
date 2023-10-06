
#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <uart.h>
#include <queue.h>

typedef enum SERIAL_NUM_TYPE 
{
    SERIAL_NUM_1 = UART_NUM_1,
    SERIAL_NUM_2 = UART_NUM_2
}serial_num_t;

/**
 * Initializes SERIALx and its RX and TX queues.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - baudrate: Baudrate of the target uart.
 * - rx_buffer_size: Buffer size of the RX queue.
 * - tx_buffer_size: Buffer size of the TX queue.
 * Note:
 * - This function initializes uart and its RX and TX queues.
 * - The rx interrupt enabled, and the rxd subscribe is performed.
*/
int16_t serial_init(serial_num_t serial_num, int32_t baudrate, int32_t rx_buffer_size, int32_t tx_buffer_size);


/**
 * Reads a received byte from RX queue.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - byte: Output byte data.
 * Return:
 * - If no data in budder, returns QUEUE_EMPTY, otherwise return QUEUE_OK.
*/
int16_t serial_read_byte(serial_num_t serial_num, char *byte);

/**
 * Gets number of bytes stored in RX queue.
 * Parameter:
 * - serial_num: Id of the target uart.
*/
int16_t serial_byte_count(serial_num_t serial_num);


/**
 * Reads all bytes from the RX queue.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - buffer: Output buffer.
 * Return:
 * - Number of bytes copied from the RX queue.
*/
int16_t serial_read_buffer(serial_num_t serial_num, char *buffer);


/**
 * Synchonous puts character to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - string: Character to be written to the target uart.
*/
int16_t serial_put_char(serial_num_t serial_num, char character);


/**
 * Synchonous puts byte data to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - byte: Byte data to be written to the target uart.
*/
int16_t serial_put_byte(serial_num_t serial_num, uint8_t byte);


/**
 * Asynchronous puts character to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - string: String to be written to the target uart.
*/
int16_t serial_put_char_async(serial_num_t serial_num, char character);


/**
 * Asynchronous puts byte data to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - byte: Byte data to be written to the target uart.
*/
int16_t serial_put_byte_async(serial_num_t serial_num, uint8_t byte);


/**
 * Synchonous writes the given bytes data the target uart.
 * Parameters:
 * - serial_num: Id of the target uart (SERIAL_NUM_1 or SERIAL_NUM_2).
 * - bytes: Bytes data to be written to the target uart.
 * - length: Number of bytes of the byte data.
*/
int16_t serial_write_bytes(serial_num_t serial_num, const uint8_t* bytes, uint16_t length);


/**
 * Synchonous writes the given bytes data the target uart.
 * Parameters:
 * - serial_num: Id of the target uart (SERIAL_NUM_1 or SERIAL_NUM_2).
 * - bytes: Bytes data to be written to the target uart.
 * - length: Number of bytes of the byte data.
*/
int16_t serial_write_bytes_async(serial_num_t serial_num, const uint8_t* bytes, uint16_t length);



/**
 * Synchonous writes string to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - string: String to be written to the target uart.
*/
int16_t serial_write_string(serial_num_t serial_num, char* string);


/**
 * Asynchronous writes string to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - string: String to be written to the target uart.
*/
int16_t serial_write_string_async(serial_num_t serial_num, char* string);




/**
 * Synchonous writes string to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - string: String to be written to the target uart.
*/
int16_t serial_write_string(serial_num_t serial_num, char* string);


/**
 * Asynchronous writes string to the target uart.
 * Parameters:
 * - serial_num: Id of the target uart.
 * - string: String to be written to the target uart.
*/
int16_t serial_write_string_async(serial_num_t serial_num, char* string);


/**
 * Create formatted string specified by the `format` and save to the `buffer`.
 * Parameters:
 * - buffer: Pointer to character buffer used to save the output string.
 * - format: Format of the string to be constructed.
*/
char * serial_sprintf(char *buffer, const char *format, ...);

/**
 * Print formatted string to the target uart.
 * This function blocks until a characters are sent.
 * Parameters:
 * - serial_num: Id of the target uart (SERIAL_NUM_1 or SERIAL_NUM_2).
 * - format: Formate of the string to be printed to the target uart.
*/
int16_t serial_printf(serial_num_t serial_num, const char *format, ...);



/**
 * Asynchronous print formatted string to the target uart.
 * This function blocks until a characters are sent.
 * Parameters:
 * - serial_num: Id of the target uart (SERIAL_NUM_1 or SERIAL_NUM_2).
 * - format: Formate of the string to be printed to the target uart.
*/
int16_t serial_printf_async(serial_num_t serial_num, const char *format, ...);

/**
 * Execution function of the serial ports (UART1 and UART2).
 * Note:
 * - This function must be called from the system main loop.
*/
void serial_exec_transmitter(void);


void serial_exec_receiver(void);



typedef void (*serial_callback_t)(void *);

typedef struct SERIAL_LINE_RECEIVER_STRUCT
{
	serial_num_t 	    serial_num;
	char* 		        line_data;
    uint16_t            max_length;
	uint16_t	        byte_count;
    serial_callback_t   line_callback;
    int16_t             fsm;
}serial_line_receiver_t;

typedef struct SERIAL_BYTE_RECEIVER_STRUCT
{
    serial_num_t        serial_num;
	char                byte_data;
    serial_callback_t   byte_callback;
}serial_byte_receiver_t;

sys_error_t serial_create_byte_receiver(serial_num_t serial_num, serial_callback_t byte_received_callback);
sys_error_t serial_create_line_receiver(serial_num_t serial_num, uint16_t max_length, serial_callback_t line_received_callback);


#endif // __SERIAL_H__
