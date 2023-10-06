/************************************************************
 * File:    pmap.h                                          *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  21 March 2023                                   *
 ************************************************************/

#include <gpio.h>
#include <serial.h>

/**
+=================================================================+
|             SOURCES (MAPS FUNCTION TO OUTPUT)                   |
+============+====================+===============================+
|  Function  |  Output Function # |       Output Name             |
+============+====================+===============================+
|  NULL      |         0          |  NULL                         |
+------------+--------------------+-------------------------------+
|  C1OUT     |         1          |  Comparator 1 Output          |
|  C2OUT     |         2          |  Comparator 2 Output          |
+------------+--------------------+-------------------------------+
|  U1TX      |         3          |  UART1 Transmit               |
|  U1RTS     |         4          |  UART1 Request-to-Send        |
+------------+--------------------+-------------------------------+
|  U2TX      |         5          |  UART2 Transmit               |
|  U2RTS     |         6          |  UART2 Request-to-Send        |
+------------+--------------------+-------------------------------+
|  SDO1      |         7          |  SPI1 Data Output             |
|  SCK1OUT   |         8          |  SPI1 Clock Output            |
|  SS1OUT    |         9          |  SPI1 Slave Select Output     |
+------------+--------------------+-------------------------------+ 
|  SDO2      |         10         |  SPI2 Data Output             |
|  SCK2OUT   |         11         |  SPI2 Clock Output            |
|  SS2OUT    |         12         |  SPI2 Slave Select Output     |
+------------+--------------------+-------------------------------+
|  OC1       |         18         |  Output Compare 1             |
|  OC2       |         19         |  Output Compare 2             |
|  OC3       |         20         |  Output Compare 3             |
|  OC4       |         21         |  Output Compare 4             |
|  OC5       |         22         |  Output Compare 5             |
+------------+--------------------+-------------------------------+
*/
typedef enum PERIPHERAL_FUNCTION_TYPE
{
	PF_UNUSED,			/** 0	*/

	PF_C1OUT,			/** 1	*/
	PF_C2OUT,			/** 2	*/

	PF_U1TX,			/** 3	*/
	PF_U1RTS,			/** 4	*/

	PF_U2TX,			/** 5	*/
	PF_U2RTS,			/** 6	*/

	PF_SDO1,			/** 7	*/	
	PF_SCK1OUT,			/** 8	*/
	PF_SS1OUT,			/** 9	*/

	PF_SDO2,			/** 10	*/
	PF_SCK2OUT,			/** 11	*/
	PF_SS2OUT,			/** 12	*/

	/****************************/
	/*   13-17 are not defined  */
	/****************************/

	PF_OC1 = 18,		/** 18	Output Compare Channel 1 */
	PF_OC2,				/** 19	Output Compare Channel 2 */
	PF_OC3,				/** 20	Output Compare Channel 3 */
	PF_OC4,				/** 21	Output Compare Channel 4 */
	PF_OC5				/** 22	Output Compare Channel 5 */
}pf_num_t;



typedef enum RPO_NUM_TYPE
{
	RP_NUM_0  = GPIO_RB_0,		/** RB0  RPOR0<4:0>		*/
	RP_NUM_1  = GPIO_RB_1,		/** RB1  RPOR0<12:8>	*/

	RP_NUM_2  = GPIO_RB_2,		/** RB2  RPOR1<4:0>		*/		
	RP_NUM_3  = GPIO_RB_3,		/** RB3  RPOR1<12:8>	*/

	RP_NUM_4  = GPIO_RB_4,		/** RB4  RPOR2<4:0>		*/
	RP_NUM_5  = GPIO_RB_5,		/** RB5  RPOR2<12:8>	*/

	RP_NUM_6  = GPIO_RB_6,		/** RB6  RPOR3<4:0>		*/
	RP_NUM_7  = GPIO_RB_7,		/** RB7  RPOR3<12:8>	*/

	RP_NUM_8  = GPIO_RB_8,		/** RB8  RPOR4<4:0>		*/
	RP_NUM_9  = GPIO_RB_9,		/** RB9  RPOR4<12:8>	*/

	RP_NUM_10 = GPIO_RB_10,		/** RB10 RPOR5<4:0>		*/	
	RP_NUM_11 = GPIO_RB_11,		/** RB11 RPOR5<12:8>	*/	

	RP_NUM_12 = GPIO_RB_12,		/** RB12 RPOR6<4:0>		*/	
	RP_NUM_13 = GPIO_RB_13,		/** RB13 RPOR6<12:8>	*/	

	RP_NUM_14 = GPIO_RB_14,		/** RB14 RPOR7<4:0>		*/	
	RP_NUM_15 = GPIO_RB_15,		/** RB15 RPOR7<12:8>	*/	
}rpo_num_t;

/**
 * Maps peripheral function (peripheral output) to a desired pin (RPO pin).
 * Parameters:
 * - pf_num: Peripheral function id.
 * - rpo_num: RPO pin id, RP_NUM_<15:0>.
*/
sys_error_t pmap_map_peripheral_to_pin(pf_num_t pf_num, rpo_num_t rpo_num);
