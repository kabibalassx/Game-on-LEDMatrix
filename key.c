#include "key.h"

/*****�ӳٺ���*****/
void delay(unsigned short int a)
{
	while(a--);
}

/*****������̼�⺯��*****/
unsigned char Matrixkey_scan()
{
	unsigned char KeyValue=0;
	unsigned char a;//���ڼ�ⰴ������
	KEY	=	0x0f;
	if(KEY	!=	0x0f)//��ȡ�����Ƿ���
	{
		delay(1000);//��ʱ10ms��������
		if(KEY	!=	0x0f)//�ٴμ������Ƿ���
		{	
			//������
			KEY	=	0X0F;
			switch(KEY)
			{
				case(0X07):	KeyValue	=	1;break;
				case(0X0b):	KeyValue	=	2;break;
				case(0X0d): KeyValue	=	3;break;
				case(0X0e):	KeyValue	=	4;break;
			}
			//������
			KEY	=	0XF0;
			switch(KEY)
			{
				case(0X70):	KeyValue	=	KeyValue			;break;
				case(0Xb0):	KeyValue	=	KeyValue	+	4	;break;
				case(0Xd0): KeyValue	=	KeyValue	+	8	;break;
				case(0Xe0):	KeyValue	=	KeyValue	+	12;break;
			}
			while((a<50)&&(KEY!=0xf0))	 //��ⰴ�����ּ��
			{
				delay(1000);
				a++;
			}
		}
	}
	return KeyValue;
}

