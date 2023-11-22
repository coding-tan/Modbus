#ifndef __BSP_GPS_H
#define __BSP_GPS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1
    
//�������鳤��
#define GPS_Buffer_Length 80
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2 

typedef struct SaveData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//�Ƿ��ȡ��GPS����
	char isParseData;	//�Ƿ�������
	char UTCTime[UTCTime_Length];		//UTCʱ��
	char latitude[latitude_Length];		//γ��
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//����
	char E_W[E_W_Length];		//E/W
	char isUsefull;		//��λ��Ϣ�Ƿ���Ч
} _SaveData;


void clrStruct(void);
void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);

extern _SaveData Save_Data;
#endif /* __BSP_GPS_H */
