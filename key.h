#ifndef KEY_H_
#define KEY_H_

//ͷ�ļ�����//
#include "reg51.h"

//λ����//
#define KEY P2

//ȫ�ֱ�������//
extern unsigned char Red_duan[8];
extern unsigned char Number[10][4];

//��������//
void delay(unsigned short int a);
unsigned char Matrixkey_scan();

#endif
