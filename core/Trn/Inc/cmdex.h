/*
************************************************************
* CMDEX Header File                                        *
************************************************************
* File:    cmdex.h                                         *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  28 March 2023                                   *
************************************************************
*/

#ifndef __CMDEX_H__
#define __CMDEX_H__

	#include <pwm.h>
	#include <analog.h>
	#include <switch.h>
	#include <pdsgen.h>
    #include <serial.h>


	void cmdex_exec(char *p_line);
	
#endif // __CMDEX_H__
