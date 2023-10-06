/************************************************************
 * File:    systick.ch                                      *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  16 February 2020                                *
 * Update:  24 February 2020                                *
 *          Added line detector & UartX_SetRxLineCallback() *
 ************************************************************
 * Update:  06 March February 2023                          *
 ************************************************************/


#ifndef __SYS_TICK__

    #define __SYS_TICK__

	#include <mcu.h>

    #define SYS_TICK_TIME_PER_TICK   1e-3

    /**
     * System clock structure.
     */
    typedef struct SYS_CLOCK_STRUCT{
        uint8_t     hh; // Hours    0-23
        uint8_t     mm; // Minutes  0-59
        uint8_t     ss; // Seconds  0-59
        uint16_t    ms; // Milliseconds 0-99
    }clock_t;

    
    /*
    * Initializes the system timer, the Timer1.
    */
    void system_tick_init(void);


    /**
     * Subscribes to the system tick isr.
     * The given callback function (listener) will be called in the ISR every tick (1 ms).
     * Parameter:
     *  - callback: Callback function or listener to be called on the system ticks.
    */
    void system_tick_isr_set_callback(callback_t callback);


    /**
     * Initializes and start the system tick.
    */
    void system_tick_start(void);


    /**
     * Stops the system tick.
    */
    void system_tick_stop(void);


    /**
     * Returns the system tick counter (uint32_t).
    */
    uint32_t system_tick_get_ticks(void);


    /**
     * Returns the system time in milliseconds (double).
    */
    double system_tick_get_time_millisec(void);


   /**
    * Returns the system time in microseconds (double).
    */
    double system_tick_get_time_microsec(void);


    /**
     * Returns the system clock (clock_t).
    */
    clock_t system_tick_get_clock(void);


    /**
     * Sets the system clock (clock_t).
     * Parameter:
     *  - clock: Pointer to the clock structure containing desired clock values.
    */
    void system_tick_set_clock(clock_t * clock);

    
    /**
     * Returns available ticks.
     * This function is designed to called by the main loop to consume the tick counter.
     * All the functions that need to be called every 1 ms (system tick interval) must be called
     * when this function return non-zero.
    */
    uint16_t system_tick_consume(void);

#endif // __SYS_TICK__
