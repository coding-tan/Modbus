#ifndef _modbus_
#define _modbus_

#include <stdint.h>
#include "modbusCRC.h"
#include "usart.h"

#define RS485_RT_1 GPIO_SetBits(GPIOA, GPIO_Pin_5)     //485发送状态
#define RS485_RT_0 GPIO_ResetBits(GPIOA, GPIO_Pin_5)   //485置接收状态

typedef struct
{
 uint8_t myadd;//本设备的地址
 uint8_t rcbuf[100]; //MODBUS接收缓冲区
 uint16_t timout;//MODbus的数据断续时间	
 uint8_t recount;//MODbus端口已经收到的数据个数
 uint8_t timrun;//MODbus定时器是否计时的标志
 uint8_t  reflag;//收到一帧数据的标志
 uint8_t Sendbuf[100]; //MODbus发送缓冲区	

}MODBUS;


extern MODBUS modbus;
void Modbus_Init(void);
void Mosbus_Event(void);
	

#endif

