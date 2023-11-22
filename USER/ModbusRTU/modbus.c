#include "modbus.h"
//#include "usart3.h"


MODBUS modbus;
extern uint16_t Reg[];

uint8_t timeout = 2;

/*
因为波特率 9600
1位数据的时间为 1000000us/9600bit/s=104us
一个字节为    104us*10位  =1040us
所以 MODBUS确定一个数据帧完成的时间为   1040us*3.5=3.64ms  ->10ms
*/

void Modbus_Init()
{
	modbus.myadd=3;  //本从设备的地址
	modbus.timrun=0; //MODbus定时器停止计时
	
}

void Modbud_fun3()  //3号功能码处理  ---主机要读取本从机的寄存器
{
    uint16_t Regadd;
	uint16_t Reglen;
	uint16_t byte;
	uint16_t i,j;
	uint16_t crc;
	
	Regadd=modbus.rcbuf[2]*256+modbus.rcbuf[3];  //得到要读取的寄存器的首地址
	Reglen=modbus.rcbuf[4]*256+modbus.rcbuf[5];  //得到要读取的寄存器的数量
	
	i=0;
	modbus.Sendbuf[i++]=modbus.myadd;//本设备地址
    modbus.Sendbuf[i++]=0x03;        //功能码      
    byte=Reglen*2;   //每个寄存器是两个字节，要返回的数据字节数=长度*2
 // modbus.Sendbuf[i++]=byte/256;  
	modbus.Sendbuf[i++]=byte%256;
	
	for(j=0;j<Reglen;j++)
	{
	  modbus.Sendbuf[i++]=Reg[Regadd+j]/256;
		modbus.Sendbuf[i++]=Reg[Regadd+j]%256;		
	}
	crc=crc16(modbus.Sendbuf,i);
	modbus.Sendbuf[i++]=crc/256;  
	modbus.Sendbuf[i++]=crc%256;
	
	for(j=0;j<i;j++)
	{
        HAL_UART_Transmit(&huart1, &modbus.Sendbuf[j], sizeof(modbus.Sendbuf[j]),timeout);
	}

}

void Modbud_fun6()  //6号功能码处理
{
    uint16_t Regadd;
	uint16_t val;
	uint16_t i,crc,j;
	i=0;
    Regadd=modbus.rcbuf[2]*256+modbus.rcbuf[3];  //得到要修改的地址 
	val=modbus.rcbuf[4]*256+modbus.rcbuf[5];     //修改后的值
	Reg[Regadd]=val;  //修改本设备相应的寄存器
	
	//以下为回应主机
	
	modbus.Sendbuf[i++]=modbus.myadd;//本设备地址
    modbus.Sendbuf[i++]=0x06;        //功能码 
    modbus.Sendbuf[i++]=Regadd/256;
	modbus.Sendbuf[i++]=Regadd%256;
	modbus.Sendbuf[i++]=val/256;
	modbus.Sendbuf[i++]=val%256;
	crc=crc16(modbus.Sendbuf,i);
	modbus.Sendbuf[i++]=crc/256;  
	modbus.Sendbuf[i++]=crc%256;
    
    printf("\r\n进入到fun6程序\r\n");
	
	for(j=0;j<i;j++)
	{
         HAL_UART_Transmit(&huart1, &modbus.Sendbuf[j], sizeof(modbus.Sendbuf[j]),timeout);
		 
	}
}

void Mosbus_Event()
{
	uint16_t crc;
	uint16_t rccrc;
    //printf("\r\n modbus.flag = %d", modbus.reflag);
    if(modbus.reflag==0)  //没有收到modbus的数据包
    {
      return;
    }
    printf("\r\n进入到Mosbus_Event程序\r\n");
    crc= crc16(&modbus.rcbuf[0], modbus.recount-2);       //计算校验码，原数据包含两个校验码
    rccrc=modbus.rcbuf[modbus.recount-2]*256 + modbus.rcbuf[modbus.recount-1];  //收到的校验码
    if(crc==rccrc)  //数据包符号CRC校验规则
    { 
      if(modbus.rcbuf[0] == modbus.myadd)  //确认数据包是否是发给本设备的 
        {
          switch(modbus.rcbuf[1])  //分析功能码
            {
              case 0:     break;
              case 1:     break;
              case 2:     break;
              case 3:     Modbud_fun3();    break;   //3号功能码处理
              case 4:     break;
              case 5:     break;
              case 6:     Modbud_fun6();     break;   //6号功能码处理			
            //....				
            }
        }
        else if(modbus.rcbuf[0] == 0)   //广播地址
        {
        
        }
    }

    modbus.recount=0;   //
    modbus.reflag=0;	
}

















