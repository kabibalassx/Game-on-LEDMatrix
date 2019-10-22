#include "key.h"

/*****延迟函数*****/
void delay(unsigned short int a)
{
	while(a--);
}

/*****矩阵键盘检测函数*****/
unsigned char Matrixkey_scan()
{
	unsigned char KeyValue=0;
	unsigned char a;//用于检测按键松手
	KEY	=	0x0f;
	if(KEY	!=	0x0f)//读取按键是否按下
	{
		delay(1000);//延时10ms进行消抖
		if(KEY	!=	0x0f)//再次检测键盘是否按下
		{	
			//测试列
			KEY	=	0X0F;
			switch(KEY)
			{
				case(0X07):	KeyValue	=	1;break;
				case(0X0b):	KeyValue	=	2;break;
				case(0X0d): KeyValue	=	3;break;
				case(0X0e):	KeyValue	=	4;break;
			}
			//测试行
			KEY	=	0XF0;
			switch(KEY)
			{
				case(0X70):	KeyValue	=	KeyValue			;break;
				case(0Xb0):	KeyValue	=	KeyValue	+	4	;break;
				case(0Xd0): KeyValue	=	KeyValue	+	8	;break;
				case(0Xe0):	KeyValue	=	KeyValue	+	12;break;
			}
			while((a<50)&&(KEY!=0xf0))	 //检测按键松手检测
			{
				delay(1000);
				a++;
			}
		}
	}
	return KeyValue;
}

