/*
************************************************************
* TERNION Header File                                      *
************************************************************
* File:    ternion.h                                       *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  11 March 2023                                   *
************************************************************
*/

#ifndef __TERNION_H__
#define __TERNION_H__


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mcu.h>
#include <gpio.h>
#include <uart.h>
#include <serial.h>
#include <adc.h>
#include <pwm.h>
#include <systick.h>
#include <timer.h>
#include <analog.h>
#include <switch.h>
#include <pdsgen.h>
#include <cmdex.h>

typedef enum TRN_ERROR_TYPE
{
    TRN_OK      = 0,    /** No Error                */
    TRN_ERR     = -1,   /** Error                   */
    TRN_ERR_ARG = -2    /** Error Invalid Parameter */
}trn_err_t;


typedef struct TRN_LOOPER_STRUCT
{
    uint32_t    loop_counter;       /** Loop counter    */
    callback_t  loop_callback;      /** Internal Used   */
    uint16_t    current_ticks;      /** Internal Used   */ 
    uint16_t    desired_ticks;      /** Internal Used   */ 
}trn_looper_t;



/**
 * Initialize the Ternion to perform default operations.
 * Parameter:
 * - init_callback: Callback function to be called after the initialization is completed.
*/
trn_err_t ternion_init(callback_t init_callback);


/**
 * Assign a callback function for the event loop.
 * Parameters:
 * - interval: Time interval (in milliseconds) between the callback function execution.
 * - loop_callback: Callback function to be called from the event loop.
*/
trn_err_t ternion_loop_set(int32_t interval, callback_t loop_callback);



/**
 * Starts the event-loop of the Ternion.
 * Note: This function works as infinite loop.
*/
trn_err_t ternion_start(callback_t loop_callback);



    uint8_t ternion_read_led_data(void);

    uint8_t ternion_read_psw_data(void);

#endif // __TERNION_H__
