/************************************************************
 * File:    pwm.h                                           *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  21 March 2023                                   *
 ************************************************************/

#ifndef __PWM_H__
#define __PWM_H__

#include <pmap.h>

#define PWM_DRIVE_LED_ACTIVE_LOW

typedef enum PWM_NUM_TYPE
{
	PWM_NUM_0,
	PWM_NUM_1,
	PWM_NUM_2,
	PWM_NUM_3,
	PWM_NUM_4,
	PWM_NUM_COUNT
}pwm_num_t;

typedef enum PWM_GROUP_TYPE
{
	PWM_GROUP_A,	/** Driven by Timer2 */
	PWM_GROUP_B		/** Driven by Timer3 */
}pwm_group_t;

typedef struct PWM_STRUCT
{
	pwm_num_t	id;
	pwm_group_t group;
	rpo_num_t 	rpo_num;
	uint16_t 	period_ticks;
	uint16_t 	operation_tick;
	float       cycle_time;
	float 		frequency;
	float 		duty_ratio;
	float 		shift_ratio;
}pwm_t;

sys_error_t pwm_init(void);

pwm_t *pwm_get_object(pwm_num_t pwm_num);

sys_error_t pwm_create(pwm_num_t pwm_num, pwm_group_t pwm_group, float frequency, float duty_ratio, float phase_shift, rpo_num_t rpo_num);

sys_error_t pwm_set_group(pwm_num_t pwm_num, pwm_group_t pwm_group);

sys_error_t pwm_start(pwm_num_t pwm_num);

sys_error_t pwm_stop(pwm_num_t pwm_num);

sys_error_t pwm_group_start(pwm_group_t pwm_group);

sys_error_t pwm_group_stop(pwm_group_t pwm_group);

sys_error_t pwm_set_frequency(pwm_group_t pwm_group, float frequency);

sys_error_t pwm_set_duty_ratio(pwm_num_t pwm_num, float duty_ratio);

sys_error_t pwm_set_phase_shift(pwm_num_t pwm_num, float shift_ratio);

sys_error_t pwm_stop_all(void);

sys_error_t pwm_start_all(void);

sys_error_t pwm_set_operation_time(pwm_num_t pwm_num, uint16_t operation_time);

pwm_group_t pwm_get_group_from_num(pwm_num_t pwm_num);

void pwm_exec(void);

#endif // __PWM_H__
