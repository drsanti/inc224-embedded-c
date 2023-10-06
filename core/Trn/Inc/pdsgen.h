
/*
************************************************************
* PDSGEN Source File                                       *
* (Programmable Digital Signal Generator)                  *
************************************************************
* File:    pdsgen.h                                        *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  13 March 2023                                   *
************************************************************
*/

#ifndef __PDSGEN_H__
#define __PDSGEN_H__

	#include <gpio.h>

	typedef enum PDSGEN_NUM_TYPE {
		PDSGEN_NUM_0,
		PDSGEN_NUM_1,
		PDSGEN_NUM_2,
		PDSGEN_NUM_3,
		PDSGEN_NUM_4,
		PDSGEN_NUM_5,
		PDSGEN_NUM_6,
		PDSGEN_NUM_7,
		PDSGEN_NUM_COUNT
	}pdsgen_num_t;


	typedef enum PDSGEN_LEVEL_TYPE {
		PDSGEN_LEVEL_LOW,
		PDSGEN_LEVEL_HIGH,
	}pdsgen_level_t;


	typedef enum PDSGEN_MODE_TYPE {
		PDSGEN_MODE_LOW,
		PDSGEN_MODE_HIGH,
		PDSGEN_MODE_IDLE,
		PDSGEN_MODE_ONESHOT,
		PDSGEN_MODE_REPEAT,
		PDSGEN_MODE_CONTINUOUS,
	}pdsgen_mode_t;


	typedef enum PDSGEN_STATE_TYPE {
		PDSGEN_STATE_DELETED,
		PDSGEN_STATE_RUNNING,
		PDSGEN_STATE_COMPLETED
	}pdsgen_state_t;


	typedef struct PDSGEN_STRUCT{
		pdsgen_num_t 	id;				/** Id of the pdsgen object 	*/
		pdsgen_mode_t   mode;			/** Mode of the pdsgen object 	*/
		pdsgen_state_t  state;			/** State of the pdsgen object	*/
		gpio_num_t 		gpio_num;		/** Target GPIO to be controlled*/
		pdsgen_level_t  level;			/** Signal level of the GPIO	*/
		bool 			invert;			/** Signal level inversion flag	*/
		uint16_t 		head_time;		/** head (low)  				*/
		uint16_t 		active_time;	/** body (high) 				*/
		uint16_t 		total_time;		/** time period in a cycle 		*/
		uint16_t 		tail_time;		/** tail (low)  				*/
		uint16_t        cycles;			/** Used in REPEAT				*/
		uint16_t 		ticks;			/** Internally used 			*/
		int8_t 			fsm;			/** Internally used 			*/
		uint16_t 		repeat;			/** Internally used 			*/
	}pdsgen_t;


	/**
	 * Initializes all pdsgen objects and logic of the GPIOs (GPIO_RB_<7:4>, LED<3:0>) to default values.
	 * Note: All LEDs are turned off (GPIO_RB_<7:4> are set to logic HIGH) by defaults.
	*/
	// sys_error_t pdsgen_init(void);


	/**
	 * Returns a pdsgen object specified by the `pdsgen_num`.
	 * Parameter:
	 * - pdsgen_num: Id of desired pdsgen. 
	*/
	pdsgen_t * pdsgen_get_object(pdsgen_num_t pdsgen_num);


	/**
	 * Resets all parameters of the given pdsgen object to default values.
	 * Parameter:
	 * - pdsgen: Signal object.
	*/
	sys_error_t pdsgen_reset_object(pdsgen_t * pdsgen);


	/**
	 * Updates the GPIO's logic depending on the `level` and `invert` parameters of the pdsgen object.
	 * Parameter:
	 * - pdsgen: Signal object.
	*/
	sys_error_t pdsgen_gpio_level_update(pdsgen_t * pdsgen);


	/**
	 * Enables the pdsgen polarity inversion.
	 * Parameters:
	 * - pdsgen_num: Id of desired pdsgen. 
	 * - invert: Invert flag, true: invert, false: non-invert.
	*/
	sys_error_t pdsgen_invert_enable(pdsgen_num_t pdsgen_num, bool invert);


	/**
	 * Terminate the pdsgen. The logic of GPIO is not changed (keep the previous value).
	 * Parameter:
	 * - pdsgen_num: Id of desired pdsgen.
	*/
	sys_error_t pdsgen_level_terminate(pdsgen_num_t pdsgen_num);


	/**
	 * Sets pdsgen level to the given pdsgen value.
	 * Parameters:
	 * - pdsgen_num: Id of the pdsgen object.
	 * - pdsgen_level: Level of the pdsgen.
	 * Note:
	 * - If the GPIO's logic will be inverted if the `pdsgen->invert` is `true`.
	*/
	sys_error_t pdsgen_level_set(pdsgen_num_t pdsgen_num, pdsgen_level_t pdsgen_level);


	/**
	 * Toggles the pdsgen level of the target pdsgen object.
	 * Parameter:
	 * - pdsgen_num: Id of the pdsgen object.
	 * Note:
	 * - The parameters of the pdsgen object will be updated depended on the GPIO's level.
	*/
	sys_error_t pdsgen_level_toggle(pdsgen_num_t pdsgen_num);


	/**
	 * Creates oneshot-pdsgen with the given parameters.
	 * Parameters:
	 * - pdsgen_num: Id of the pdsgen object.
	 * - gpio_num: Id of target GPIO to be controlled.
	 * - head_time: Tick count for the pdsgen head (low).
	 * - active_time: Tick count of the pdsgen active (high).
	 * 
	 * |<--head (low)--->|-->active (high)-->|low| end
	 * 
	 * Note:
	 * - The pdsgen level (low/high) of the GPIO can be inverted depended on the `pdsgen->invert` value.
	*/
	sys_error_t pdsgen_create_oneshot(pdsgen_num_t pdsgen_num, gpio_num_t gpio_num, uint16_t head_time, uint16_t active_time);


	/**
	 * Creates repeat-pdsgen with the given parameters.
	 * Parameters:
	 * - pdsgen_num: Id of the pdsgen object.
	 * - gpio_num: Id of target GPIO to be controlled.
	 * - head_time: Tick count for the pdsgen head (low).
	 * - active_time: Tick count of the pdsgen active (high).
	 * - total_time: Tick count of the pdsgen period.
	 * - cycles: Number of pdsgen cycles.
	 * 
	 * |<--head (low)--->|-->active (high)-->|<--tail (low)-->| repeat
	 * |<-----------------------period----------------------->|
	 * 
	 * Note:
	 * - The pdsgen level (low/high) of the GPIO can be inverted depended on the `pdsgen->invert` value.
	*/
	sys_error_t pdsgen_create_repeat(pdsgen_num_t pdsgen_num, gpio_num_t gpio_num, uint16_t head_time, uint16_t active_time, uint16_t total_time, uint16_t cycles);


	/**
	 * Creates continuous-pdsgen with the given parameters.
	 * Parameters:
	 * - pdsgen_num: Id of the pdsgen object, PDSGEN_NUM_<7:0>.
	 * - gpio_num: Id of target GPIO to be controlled.
	 * - head_time: Tick count for the pdsgen head (low).
	 * - active_time: Tick count of the pdsgen active (high).
	 * - total_time: Tick count of the pdsgen period.
	 * 
	 * |<--head (low)--->|-->active (high)-->|<--tail (low)-->| infinite 
	 * |<------------------------period---------------------->|
	 * 
	 * Note:
	 * - The pdsgen level (low/high) of the GPIO can be inverted depended on the `pdsgen->invert` value.
	*/
	sys_error_t pdsgen_create_continuous(pdsgen_num_t pdsgen_num, gpio_num_t gpio_num, uint16_t head_time, uint16_t active_time, uint16_t total_time);



	sys_error_t pdsgen_synchronize_all(void);
	sys_error_t pdsgen_synchronize(pdsgen_num_t pdsgen_num_dst, pdsgen_num_t pdsgen_num_src);

	sys_error_t pdsgen_restart(pdsgen_num_t pdsgen_num);
	
	/**
	 * Generate continuous PWM signal on the given GPIO.
	 * Parameters:
	 * - pdsgen_num:Id of PDSGEN object, PDSGEN_NUM_<7:0>
	 * - gpio_num: Id of GPIO.
	 * - frequency: Frequency, 0.00001526Hz-100Hz.
	 * - duty_ratio: Duty cycle ratio, 0.0-1.0.
	 * - shift_ratio: Shifting ratio, 0.0-1.0.
	 * Note:
	 * - The `duty_ratio + shift_ratio` must be less than 1.0.
	 * - The timing resolution of all parameter is 1ms approximately.
	*/
	sys_error_t pdsgen_pwm_create_continuous(pdsgen_num_t pdsgen_num, gpio_num_t gpio_num, float frequency, float duty_ratio, float shift_ratio);
	
	sys_error_t pdsgen_pwm_create_repeat(
				pdsgen_num_t pdsgen_num, gpio_num_t gpio_num, 
				float frequency, float duty_ratio, float shift_ratio, int16_t cycles);	
	
	/**
	 * Executes pdsgen's operation and control GPIO's level connected to the pdsgen object.
	 * This function must be called by the main loop every 1 ms.
	*/
	void pdsgen_exec(void);



#endif //__PDSGEN_H__
