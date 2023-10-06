/*
************************************************************
* ANALOG Header File                                       *
************************************************************
* File:    analog.h                                        *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  11 March 2023                                   *
************************************************************
*/

#ifndef __ANALOG_H__
#define __ANALOG_H__

    #include <hal.h>
    #include <adc.h>
    #include <serial.h>

    #if USE_TERNION_BOARD >= 1
    /** Ternion Board has 6 channels of ADCs        */
    typedef enum ANALOG_NUM_TYPE {
        ANALOG_NUM_0,       /** TRN: AN0 LDR0 RA0   */
        ANALOG_NUM_1,       /** TRN: AN1 LDR1 RA1   */
        ANALOG_NUM_2,       /** TRN: AN2 PSW0 RB0   */
        ANALOG_NUM_3,       /** TRN: AN3 PSW1 RB1   */
        ANALOG_NUM_4,       /** TRN: AN4 PSW2 RB2   */
        ANALOG_NUM_5,       /** TRN: AN5 PSW3 RB3   */
        ANALOG_NUM_COUNT    /** TRN: Channel Count  */
    }analog_num_t;
    #else
    /** Original Boar has 4 channel of ADCs         */
        typedef enum ANALOG_NUM_TYPE {
        ANALOG_NUM_0,       /** ORG: AN0      RA0    */
        ANALOG_NUM_1,       /** ORG: AN1 LDR1 RA1    */
        ANALOG_NUM_2,       /** ORG: AN2      RB0    */
        ANALOG_NUM_3,       /** ORG: AN3      RB1    */
        ANALOG_NUM_COUNT    /** ORG: Channel Count   */
    }analog_num_t;
    #endif


    typedef void (*analog_callback_t)(void *);

    typedef struct ANALOG_STRUCT {
        analog_num_t        id;
        gpio_num_t          gpio_num;
        int16_t             value;
        int16_t             min;
        int16_t             max;
        int16_t             previous;
        int16_t             delta;
        int16_t             threshold;
        int16_t             divisor_shift_bits;
        analog_callback_t   callback;

        uint16_t            sampling_count;     /** Sample counter. Reset every sampling interval      */
        uint16_t            sampling_interval;  /** Sampling interval   */
        analog_callback_t   sampling_callback;  /** Sampling callback   */
        //
        uint16_t            event_loop_count;   /** Loop counter. Reset when the event callback is called */
        uint16_t            event_call_interval;/** Interval between the calls when the change is detected */
    }analog_t;




    analog_t* analog_get_object(analog_num_t analog_num);

    /**
     * Initialize analog input pins RA_<1:0> (LDR<1:0>) and RB_<3:0> (AN<5:2>).
     * Note:
     * - The RB_<3:0> are also used as digital input pins connected to PSW<3:0>.
     * - Calling this function will disable the digital input function of the RB_<3:0> pins.
    */
    sys_error_t analog_init(analog_num_t analog_num, gpio_num_t gpio_num);


    /**
     * Returns 10-bit data of the desired adc channel specified by the analog_num.
     * Parameter:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
    */
    int16_t analog_read_raw(analog_num_t analog_num);


    /**
     * Returns input voltage of the desired adc channel specified by the analog_num.
     * Parameter:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
    */
    double analog_read_voltage(analog_num_t analog_num);


    /**
     * Returns percentage input of the desired adc channel specified by the analog_num.
     * Parameter:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
    */
    double analog_read_percent(analog_num_t analog_num);


    /**
     * Sets change-detection callback of an desired analog input.
     * Parameters:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
     * - analog_callback: Callback function to be called when the change is detected.
    */
    sys_error_t analog_set_detection_callback(analog_num_t analog_num, analog_callback_t analog_callback);


    /**
     * Sets detection threshold of an desired analog input.
     * Parameters:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
     * - threshold: Detection threshold value. If the delta is greater than the threshold, the callback function will be called.
    */
    sys_error_t analog_set_detection_threshold(analog_num_t analog_num, int16_t threshold);


    sys_error_t analog_set_divisor_n_bits(analog_num_t analog_num, int16_t divisor_n_bits);

    sys_error_t analog_set_event_call_interval(analog_num_t analog_num, uint16_t interval);

    /**
     * Creates a analog detector of the desired analog input channel with the given parameters.
     * Parameters:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
     * - threshold: Detection threshold value. If the delta is greater than the threshold, the callback function will be called.
     * - detection_callback: Callback function to be called every sampling interval (1-65535 ms).
    */
    sys_error_t analog_create_detector(analog_num_t analog_num, uint16_t detection_threshold, analog_callback_t detection_callback);



    /**
     * Sets sampling callback of the desired analog input channel.
     * Parameters:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
     * - sampling_callback: Callback function to be called every sampling interval.
    */
    sys_error_t analog_set_sampling_callback(analog_num_t analog_num, analog_callback_t sampling_callback);


    /**
     * Sets sampling interval of the desired analog input channel.
     * Parameters:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
     * - sampling_interval: Sampling interval for calling the sampling callback function.
    */
    sys_error_t analog_set_sampling_interval(analog_num_t analog_num, uint16_t sampling_interval);



    /**
     * Creates an analog sampler of the desired analog input channel with the given parameters.
     * Parameters:
     * - analog_num: Channel index of the analog input, ANALOG_NUM_<5:0>.
     * - sampling_interval: Sampling interval for calling the sampling callback function.
     * - sampling_callback: Callback function to be called every sampling interval (1-65535 ms).
    */
    sys_error_t analog_create_sampler(analog_num_t analog_num, uint16_t sampling_interval, analog_callback_t sampling_callback);


    /**
     * Executes read operation of selected (scanned) channels of ADCs.
     * This function must be called by the main loop every 1 ms (system tick).
    */
    void analog_exec_read(void);

#endif // __ANALOG_H__