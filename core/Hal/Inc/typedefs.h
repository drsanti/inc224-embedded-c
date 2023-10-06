/*
************************************************************
* TYPEDEFS Header File                                     *
************************************************************
* File:    typedefs.h                                      *
* Author:  Asst.Prof.Dr.Santi Nuratch                      *
*          Embedded Computing and Control Laboratory       *
*          ECC-Lab, INC, KMUTT, Thailand                   *
* Update:  12 March 2023                                   *
************************************************************
*/

#ifndef __TYPE_DEFS_H__
#define __TYPE_DEFS_H__
    

     /********************************************************
     * Standard Headers.
     ********************************************************/
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <string.h>
    #include <stdarg.h>
    #include <math.h>


    /********************************************************
     * Default callback function type.
     ********************************************************/
    typedef void (*callback_t)(void *);


    /********************************************************
     * Default return type.
     ********************************************************/
    typedef enum SYSTEM_ERROR_TYPE{
        SYS_ERR = -1,
        SYS_OK = 0,
    }sys_error_t;

#endif // __TYPE_DEFS_H__