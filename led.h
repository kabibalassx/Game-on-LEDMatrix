#ifndef LED_H_
#define LED_H_

//头文件包含//
#include "reg51.h"

//位定义//
#define ROW 		P1
#define LED_RED	P0

//全局变量声明//
extern unsigned char Red_duan[8];
extern const unsigned char Number[10][4]; 

//全局函数声明//
void Display_Red(unsigned char duan	,	unsigned char wei);


#endif
