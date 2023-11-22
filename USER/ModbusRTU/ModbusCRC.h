#ifndef _MODBUS_CRC_H_
#define _MODBUS_CRC_H_
//==========================================
#include <stdint.h>
//==========================================

//------------------------------------------
//#ifdef _MODBUS_CRC_C_
//#define  global	   idata
//#else
//#define  global extern	 idata
//#endif
//------------------------------------------

 //==========================================
//#undef 	global
//==========================================
 uint16_t crc16( uint8_t *puchMsg, uint16_t usDataLen );
//==========================================
#endif

