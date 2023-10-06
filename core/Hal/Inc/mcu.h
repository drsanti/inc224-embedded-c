/*
************************************************************
* MCU Header File                                          *
************************************************************
* File:    mcu.h                                           *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  08 February 2023                                *
************************************************************
*/


#ifndef __MCU_H__

    #define	__MCU_H__

	#include <hal.h>

	/********************************************************
     * CPU clock frequency. 32MHz.
     ********************************************************/
    #define FOSC            32e6        // CPU clock frequency, 32 MHz.
    #define CONFIG_FOSC     FOSC        // CPU clock frequency, 32 MHz.

    /********************************************************
     * Peripherals clock frequency. 16MHz.
     ********************************************************/
    #define FCY             (FOSC/2)    // Peripherals clock frequency, 16 MHz.
    #define CONFIG_FCY      FCY         // Peripherals clock frequency, 16 MHz.

    /********************************************************
     * Use libpic30. The FCY must be declared first.
     ********************************************************/
    #include <libpic30.h>


	/*******************************************************
     * Performs critical section
     *******************************************************/

	
	#define PERFORM_CRITICAL_SECTION(action) {		\
        register int16_t old_ipl;               	\
        SET_AND_SAVE_CPU_IPL(old_ipl, 7);       	\
        action;                                 	\
        RESTORE_CPU_IPL(old_ipl);              		\
    }
	

	/*******************************************************
     * Disable and Enable ISE of Timer1
     *******************************************************/
	#define TIMER1_ISR_DISABLE()    IEC0bits.T1IE=0
	#define TIMER1_ISR_ENABLE()     IEC0bits.T1IE=1

    #define Mcu_Restart()           {__delay_ms(1000); __asm__ volatile ("reset");}

    /*******************************************************
     * mcu_init
     * Initializes CPU clock and IOs. It calls mcu_clock_init() and mcu_io_init()
     *******************************************************/
    void mcu_init(void);

    /*******************************************************
     * mcu_clock_init
     * Initializes CPU clock.
     *******************************************************/
    void mcu_clock_init(void);

    /*******************************************************
     * mcu_io_init
     * Initializes IOs.
     *******************************************************/
    void mcu_io_init(void);

    /*******************************************************
     * mcu_unlock_remap
     * Unlocks IOs remapping.
     *******************************************************/
    void mcu_unlock_remap(void);

    /*******************************************************
     * mcu_lock_remap
     * Locks IOs remapping.
     *******************************************************/
    void mcu_lock_remap(void);


#endif // __MCU_H__
