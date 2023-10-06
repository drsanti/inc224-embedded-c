/*
************************************************************
* QUEUE Header File                                        *
************************************************************
* File:    queue.h                                         *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  13 February 2023                                *
************************************************************
*/


#ifndef __QUEUE_H__

    #define __QUEUE_H__

    #include <hal.h>
	#include <mcu.h>
	
    /********************************************************
     * ERROR CODE OF THE QUEUE
     ********************************************************/
    // #define QUEUE_ERROR_NONE    0 // Queue operation success.
    // #define QUEUE_ERROR_EMPTY   1 // Queue is empty.
    // #define QUEUE_ERROR_FULL    2 // Queue is full.

	typedef enum QUEUE_ERROR_TYPE {
		QUEUE_OK,
		QUEUE_EMPTY,
		QUEUE_FULL
	}queue_error_t;

    /********************************************************
     * DATA STRUCTURE OF THE QUEUE
     ********************************************************/
    typedef struct QUEUE_TYPE{
        char    *buf;   /* Buffer, an array of bytes        */
        uint16_t put;   /* Put index                        */
        uint16_t get;   /* Get index                        */
        uint16_t cnt;   /* Number of bytes in the queue     */
        uint16_t len;   /* Number of bytes of queue size    */
        uint16_t err;   /* Error code of the q operations   */
    }queue_t;

    /********************************************************
     * Initializes the queue object.
     * Parameters:
     * - queue: Queue object.
     * - buffer: Buffer of characters.
     * - length: Buffer length in bytes.
     ********************************************************/
    queue_error_t queue_init(queue_t *queue, char *buffer, uint16_t length);


    /********************************************************
     * Puts a byte of data into queue buffer.
     * Returns zero if the operation is failed.
     * Parameters:
     * - queue: Queue object.
     * - data: A byte data.
     ********************************************************/
    queue_error_t queue_put(queue_t *queue, char data);


    /********************************************************
     * Puts a byte of data into queue buffer.
     * Returns zero if the operation is failed.
     * Parameters:
     * - queue: Queue object.
     * - data: Out put byte data.
     ********************************************************/
    queue_error_t queue_get(queue_t *queue, char *data);


    /********************************************************
     * Returns free space of the queue buffer in bytes.
     * Parameter:
     * - queue: Queue object.
     ********************************************************/
    uint16_t queue_space(queue_t *queue);


    /*******************************************************
    * Resets the queue object. All parameters are cleared.
	* Parameter:
    * - queue: Queue object.
    *******************************************************/
    queue_error_t queue_reset(queue_t *queue);

#endif // __QUEUE_H__
