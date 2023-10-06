/*
************************************************************
* TIMER Header File                                        *
************************************************************
* File:    timer.h                                         *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  11 March 2023                                   *
************************************************************
*/

#ifndef __TIMER_H__
#define __TIMER_H__

    #include <hal.h>

    typedef enum TIMER_NUM_TYPE {
        TIMER_NUM_0,
        TIMER_NUM_1,
        TIMER_NUM_2,
        TIMER_NUM_3,
        TIMER_NUM_4,
        TIMER_NUM_5,
        TIMER_NUM_6,
        TIMER_NUM_7,
        TIMER_NUM_MAX,
    }timer_num_t;

    typedef enum TIMER_MODE_TYPE {
        TIMER_MODE_INTERVAL,    /** Continuous mode */
        TIMER_MODE_TIMEOUT      /** Oneshot mode    */
    }timer_mode_t;

    typedef enum TIMER_STATE_TYPE {
        TIMER_STATE_DELETED,
        TIMER_STATE_RUNNING,
        TIMER_STATE_PAUSED,
        TIMER_STATE_STOPED,
    }timer_state_t;

    typedef void (*timer_callback_t)(void *);

    typedef struct TIMER_STRUCT {
        int16_t             id;         /** Identity (unique id)*/
        int8_t              mode;       /** Operation mode      */
        int8_t              state;      /** Operation state     */
        uint16_t            ticks;      /** Current tick value  */
        uint16_t            reload;     /** Reload value        */
        uint16_t            alarms;     /** Alarm counter       */
        timer_callback_t    callback;   /** Callback function   */
    }timer_t;

    // typedef struct TIMER_EVENT_STRUCT {
    //     int16_t     id;         /** Identity (unique id)*/
    //     timer_t     *timer;     /** Timer structure     */
    // }timer_event_t;
    

    /**
     * Creates an interval timer with the given parameters.
     * Parameters:
     * - timer_num: Id of the timer.
     * - interval_value: Interval of the timer in the unit of milliseconds (1-65535).
     * - interval_callback: Callback function of the interval timer.
     * Note:
     * After the timer is created, its state is set to TIMER_RUNNING.
    */
    sys_error_t timer_create_interval(timer_num_t timer_num, uint16_t timer_interval, timer_callback_t timer_callback);


    /**
     * Creates a timeout timer with the given parameters.
     * Parameters:
     * - timer_num: Id of the timer.
     * - timeout_value: Timeout value of the timeout timer in the unit of milliseconds (1-65535).
     * - timer_callback: Callback function of the timeout timer.
     * Note:
     * After the timer is created, its state is set to TIMER_RUNNING.
    */
    sys_error_t timer_create_timeout(timer_num_t timer_num, uint16_t timeout_value, timer_callback_t timeout_callback);



    /**
     * Deletes the timer specified by the timer_num.
     * Parameter:
     * - timer_num: Id of the timer to be deleted.
    */
    sys_error_t timer_delete(timer_num_t timer_num);


    /**
     * Sets the callback function of the timer specified by the timer_num.
     * Parameters:
     * - timer_num: Id of the desired timer.
     * - timer_callback: Callback function to be called when the timer get timeout.
    */
    sys_error_t timer_set_callback(timer_num_t timer_num, timer_callback_t timer_callback);


    /**
     * Sets the period value of the timer (interval or timeout ) specified by the timer_num.
     * Parameters:
     * - timer_num: Id of the desired timer.
     * - timer_interval: Interval value (in milliseconds) of the timer.
    */
    sys_error_t  timer_set_period(timer_num_t timer_num, uint16_t timer_period);
        
        
    /**
     * Sets the operation mode of the timer specified by the timer_num.
     * Parameters:
     * - timer_num: Id of the desired timer.
     * - timer_mode: Operation mode of the timer.
    */
    sys_error_t  timer_set_mode(timer_num_t timer_num, timer_mode_t timer_mode);
        

    /**
     * Starts the timer specified by the timer_num.
     * Parameter:
     * - timer_num: Id of the timer to be started.
    */
    sys_error_t timer_start(timer_num_t timer_num);


    /**
     * Stops the timer specified by the timer_num.
     * Parameter:
     * - timer_num: Id of the timer to be stoped.
    */
    sys_error_t timer_stop(timer_num_t timer_num);


    /**
     * Pauses the timer specified by the timer_num.
     * Parameter:
     * - timer_num: Id of the timer to be paused.
    */
    sys_error_t timer_pause(timer_num_t timer_num);


    /**
     * Resumes the timer specified by the timer_num.
     * Parameter:
     * - timer_num: Id of the timer to be resumed.
    */
    sys_error_t timer_resume(timer_num_t timer_num);


    /**
     * Gets the timer object/structure.
     * Parameter:
     * - timer_num: Id of the timer to be returned.
    */
    timer_t* timer_get(timer_num_t timer_num);


    /**
     * Executes timer's tick (increase timer's tick).
     * This function must be called by the main loop every 1 ms.
    */
    void timer_exec_tick(void);


    /**
     * Executes timer's callback.
     * This function must be called by the main loop as fast as possible.
    */
    void timer_exec_callback(void);




    
    
#endif // __TIMER_H__