#ifndef LED_H_
#define LED_H_

//ͷ�ļ�����//
#include "reg51.h"

//λ����//
#define ROW 		P1
#define LED_RED	P0

//ȫ�ֱ�������//
extern unsigned char Red_duan[8];
extern const unsigned char Number[10][4]; 

//ȫ�ֺ�������//
void Display_Red(unsigned char duan	,	unsigned char wei);


#endif
