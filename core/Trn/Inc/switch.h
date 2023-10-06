/*
************************************************************
* SWITCH Header File                                       *
************************************************************
* File:    switch.h                                        *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  12 March 2023                                   *
************************************************************
*/

#ifndef __SWITCH_H__
#define __SWITCH_H__

    #include <analog.h>
    #include <serial.h>

    typedef enum SWITCH_MODE_TYPE 
    {
        SWITCH_MODE_DIGITAL,
        #if  USE_TERNION_BOARD >= 1
            SWITCH_MODE_ANALOG,
        #endif
    }switch_mode_t;

    typedef enum SWITCH_NUM_TYPE 
    {
        SWITCH_NUM_0,           /** TRN: AN2 PSW0 RB0   ORG: RB4 */      
        SWITCH_NUM_1,           /** TRN: AN3 PSW1 RB1   ORG: RB5 */       
        SWITCH_NUM_2,           /** TRN: AN4 PSW2 RB2   ORG: RB6 */
        SWITCH_NUM_3,           /** TRN: AN5 PSW3 RB3   ORG: RB7 */
        SWITCH_NUM_COUNT        /** Channel Count   */
    }switch_num_t;

    typedef enum SWITCH_STATE_TYPE 
    {
        SWITCH_STATE_OFF,
        SWITCH_STATE_ON,
        SWITCH_STATE_HOLD,
        SWITCH_STATE_REPEAT
    }switch_state_t;


    typedef void (*switch_callback_t)(void *);

    typedef struct SWITCH_STRUCT 
    {
        switch_num_t        id;
        switch_mode_t       mode;       /** Operation mode of the switch    */
        gpio_num_t          gpio_num;
        int8_t              on_value;   /** ON level value. 0 by default.   */
        switch_state_t      state;
        switch_callback_t   callback;
        int16_t             ticks;      /** Internal used for FSM */
        int16_t             interval;   /** Internal used for FSM */
        int16_t             data;       /** Internal used for FSM */
    }switch_t;


    sys_error_t switch_init(switch_num_t switch_num, gpio_num_t gpio_num, switch_mode_t switch_mode, int16_t switch_on_value);


    /**
    * Initialize switch object with the given parameters.
    * Parameters:
    * - switch_num: Id of the switch.
    * - gpio_num: PIO connected to the switch.
    * - switch_mode: Operation mode of the switch (SWITCH_MODE_ANALOG is supported only in TERNION).
    * - switch_on_value: ON value of the switch.
    */
    sys_error_t switch_create_detector(switch_num_t switch_num, gpio_num_t gpio_num,  switch_mode_t switch_mode, switch_callback_t switch_callback);


    /**
     * Returns the switch object specified by the switch_num.
     * Parameter:
     * - switch_num: Id of the desired switch, SWITCH_NUM_<3:0>.
    */
    switch_t * switch_get_object(switch_num_t switch_num);


    /**
     * Returns the switch object specified by the switch_num.
     * Parameter:
     * - switch_num: Id of the desired switch, SWITCH_NUM_<3:0>.
    */
    switch_t * switch_get_object(switch_num_t switch_num);


    /**
     * Sets on-level value of the desired switch.
     * Parameters:
     * - switch_num: Id of the switch.
     * - switch_on_value: ON value of the switch.
    */
    sys_error_t switch_set_on_level(switch_num_t switch_num, int16_t switch_on_value);


    /**
     * Sets the state-change callback function for the desired switch.
     * Parameters:
     * - switch_num: Id of the desired switch, SWITCH_NUM_<3:0>.
     * - switch_callback: Callback function to be called when the switch state is changed.
    */
    sys_error_t switch_set_callback(switch_num_t switch_num, switch_callback_t switch_callback);


    /**
     * Create a switch detector for the desired switch.
     * Parameters:
     * - switch_num: Id of the desired switch, SWITCH_NUM_<3:0>.c
    * - gpio_num: GPIO to connect to the switch.
     * - switch_mode: Operation mode of the desired switch, SWITCH_MODE_ANALOG or SWITCH_MODE_DIGITAL.
     * - switch_callback: Callback function to be called when the switch state is changed.
    */
    sys_error_t switch_create_detector(switch_num_t switch_num, gpio_num_t gpio_num,  switch_mode_t switch_mode, switch_callback_t switch_callback);



    int16_t switch_get_level(switch_num_t switch_num);

    /**
     * Executes switch's callback
     * This function must be called by the main loop every 1 ms.
    */
    void switch_exec(void);


#endif // __SWITCH_H__