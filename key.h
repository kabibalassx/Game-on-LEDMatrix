#ifndef KEY_H_
#define KEY_H_

//头文件包含//
#include "reg51.h"

//位定义//
#define KEY P2

//全局变量定义//
extern unsigned char Red_duan[8];
extern unsigned char Number[10][4];

//函数声明//
void delay(unsigned short int a);
unsigned char Matrixkey_scan();

#endif
