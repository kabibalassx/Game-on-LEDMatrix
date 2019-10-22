/*********************************************
̰������Ϸ
P2���Ӿ������
P0,P1����LED����ĺ�������
*********************************************/

//ͷ�ļ�����//
#include "reg51.h"
#include "config.h"
#include "game.h"
#include "key.h"
#include "led.h"
#include "stdlib.h"
#include "beep.h"

//��������//
unsigned char num_timer1;//��ʱ��1�жϴ���
unsigned char num_timer0;

//��������//
void Timer1_init();
void Timer0_init();
void Timer1_interrupt();
void Timer0_interrupt();


#ifdef RUN_Process

/*****������*****/
void main()
{
	unsigned char k;
	unsigned char i;
	Timer0_init();
	Timer1_init();
	while(1)
	{	
		Game_init();
		while(1)
		{
			//�Ӽ��̶�ȡ��������
			k	=	Matrixkey_scan();
			if(k==2)
			{
				if(dirction_last	!=	down)
					snake_dirction	=	up;
			}
			else if(k==6)
			{
				if(dirction_last	!=	up)
					snake_dirction	=	down;
			}
			else if(k==5)
			{
				if(dirction_last	!=	right)
					snake_dirction	=	left;
			}
			else if(k==7)
			{
				if(dirction_last	!=	left)
					snake_dirction	=	right;
			}
			//�����Ϸ�Ƿ����
			if(Game_state==0)//������
			{
				k	=	Get_length();//�õ�������
				for(i=0;i<8;i++)//��ѡ���ݹ���
				{
					Red_duan[i]	=	0x00;
				}
				for(i=0;i<4;i++)//ת��������Ϊ��ѡ����
				{
					Red_duan[i]		=	Number[k/10][i];
					Red_duan[i+4]	=	Number[k%10][i];
				}
				break;
			}
		}
		Free_shake_chain();
	}	
}
		
/*****��ʱ��1��ʼ������*****/
void Timer1_init()
{
  TMOD	|=0x10;
	TH1		=	(65536	-	50000)/256;//��ֵ50����	
	TL1		=	(65536	-	50000)%256;
	ET1		=	1;
	EA		=	1;
	TR1		=	0;//����ͣ
	num_timer1	=	0;
}

/*****��ʱ��0��ʼ������*****/
void Timer0_init()
{
	TMOD	|=0x01;
	TH0		=	(65536-100)/256;//��ֵ0.1����
	TL0		=	(65536-100)%256;
	ET0		=	1;
	TR0		=	1;
	num_timer0	=	0;
}

/*****��ʱ��1�жϺ���*****/
void Timer1_interrupt() interrupt 3
{
  unsigned char a;
	TH1	=	(65536-50000)/256;
  TL1	=	(65536-50000)%256;
  num_timer1	++;
  if(num_timer1==20)//һ����
  {
   	num_timer1	=	0;
		//�ж��Ƿ�����
		a	=	Judje_die();
		if(a	==	0)
		{
			//�ж��Ƿ�Ե�ʳ��
			a	=	Judje_eat();
			if(a	==	0)
			{
				Update_food();
			}
			Update_snake(a);
			Process_data();//ת��λ������Ϊ��ѡ����
  	}
		else if(a	==	1)
		{
			Game_state	=	0;//��Ϸ����
			TR1	=	0;
		}
	}
}

/*****��ʱ��0�жϺ���*****/
void Timer0_interrupt() interrupt 1
{
		TH0	=	(65536-100)/256;
    TL0	=	(65536-100)%256;
		Display_Red(Red_duan[num_timer0]	,	0xff	-	xxh[num_timer0]);
		num_timer0	++;
		if(num_timer0	==	8)
		{
			num_timer0	=	0;
		}
}

#endif










#ifdef DEBUG_MatrixLeds

/*****��ʱ����*****/
void delay_()
{
	unsigned char i;
	for(i=0;i<100;i++);
}

/*****��ʱ��0��ʼ������*****/
void Timer0_init()
{
	TMOD	|=0x01;
	TH0		=	(65536-5000)/256;//��ֵ0.1����
	TL0		=	(65536-5000)%256;
	EA	=	1;
	ET0		=	1;
	TR0		=	1;
	num_timer0	=	0;
}
/*****��ʱ��0�жϺ���*****/
void Timer0_interrupt() interrupt 1
{
	TH0	=	(65536-5000)/256;
  TL0	=	(65536-5000)%256;
	Display_Led(Red_duan[num_timer0]	,	0xff-xxh[num_timer0]);
	delay_();
	num_timer0++;
	if(num_timer0	==	0x08)
	{
		num_timer0	=	0x00;
	}
}

/*****������*****/
void main()
{
	Timer0_init();//��ʱ��0��ʼ������
	Red_duan[0]	=	0x01;								
	Red_duan[1]	=	0x02;
	Red_duan[2]	=	0x04;
	Red_duan[3]	=	0x01;
	Red_duan[4]	=	0x01;
	Red_duan[5]	=	0x01;
	Red_duan[6]	=	0x01;
	Red_duan[7]	=	0x01;
	while(1)
	{	
	}
}

#endif









#ifdef DEBUG_74HC595

/*****������*****/
void main()
{
	
}

#endif









#ifdef DEBUG_beep

/*****������*****/
void main()
{
	
}

#endif


