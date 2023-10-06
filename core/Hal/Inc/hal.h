/*
************************************************************
* HAL Header File                                          *
************************************************************
* File:    hal.h                                           *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  08 February 2023                                *
************************************************************
*/

#ifndef __HAL_H__

    #define	__HAL_H__

    /********************************************************
     * Type Definition Header
     ********************************************************/
    #include <hardware.h>
    #include <typedefs.h>


    /********************************************************
     * XC16 Header.
     ********************************************************/
    #include <xc.h>


    /********************************************************
     * HAL Return Types.
     ********************************************************/
    typedef enum {
        HAL_ERR = -1,
        HAL_OK = 0
    }hal_error_t;

#endif // __HAL_H__
