#ifndef _modbus_
#define _modbus_

#include <stdint.h>
#include "modbusCRC.h"
#include "usart.h"

#define RS485_RT_1 GPIO_SetBits(GPIOA, GPIO_Pin_5)     //485����״̬
#define RS485_RT_0 GPIO_ResetBits(GPIOA, GPIO_Pin_5)   //485�ý���״̬

typedef struct
{
 uint8_t myadd;//���豸�ĵ�ַ
 uint8_t rcbuf[100]; //MODBUS���ջ�����
 uint16_t timout;//MODbus�����ݶ���ʱ��	
 uint8_t recount;//MODbus�˿��Ѿ��յ������ݸ���
 uint8_t timrun;//MODbus��ʱ���Ƿ��ʱ�ı�־
 uint8_t  reflag;//�յ�һ֡���ݵı�־
 uint8_t Sendbuf[100]; //MODbus���ͻ�����	

}MODBUS;


extern MODBUS modbus;
void Modbus_Init(void);
void Mosbus_Event(void);
	

#endif

