/*********************************************
贪吃蛇游戏
P2链接矩阵键盘
P0,P1链接LED点阵的红绿排针
*********************************************/

//头文件包含//
#include "reg51.h"
#include "config.h"
#include "game.h"
#include "key.h"
#include "led.h"
#include "stdlib.h"
#include "beep.h"

//变量定义//
unsigned char num_timer1;//定时器1中断次数
unsigned char num_timer0;

//函数声明//
void Timer1_init();
void Timer0_init();
void Timer1_interrupt();
void Timer0_interrupt();


#ifdef RUN_Process

/*****主函数*****/
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
			//从键盘读取方向输入
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
			//检测游戏是否结束
			if(Game_state==0)//结束了
			{
				k	=	Get_length();//得到蛇身长度
				for(i=0;i<8;i++)//段选数据归零
				{
					Red_duan[i]	=	0x00;
				}
				for(i=0;i<4;i++)//转换蛇身长度为段选数据
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
		
/*****定时器1初始化函数*****/
void Timer1_init()
{
  TMOD	|=0x10;
	TH1		=	(65536	-	50000)/256;//初值50毫秒	
	TL1		=	(65536	-	50000)%256;
	ET1		=	1;
	EA		=	1;
	TR1		=	0;//先暂停
	num_timer1	=	0;
}

/*****定时器0初始化函数*****/
void Timer0_init()
{
	TMOD	|=0x01;
	TH0		=	(65536-100)/256;//初值0.1毫秒
	TL0		=	(65536-100)%256;
	ET0		=	1;
	TR0		=	1;
	num_timer0	=	0;
}

/*****定时器1中断函数*****/
void Timer1_interrupt() interrupt 3
{
  unsigned char a;
	TH1	=	(65536-50000)/256;
  TL1	=	(65536-50000)%256;
  num_timer1	++;
  if(num_timer1==20)//一秒钟
  {
   	num_timer1	=	0;
		//判断是否死亡
		a	=	Judje_die();
		if(a	==	0)
		{
			//判断是否吃到食物
			a	=	Judje_eat();
			if(a	==	0)
			{
				Update_food();
			}
			Update_snake(a);
			Process_data();//转换位置数据为段选数据
  	}
		else if(a	==	1)
		{
			Game_state	=	0;//游戏结束
			TR1	=	0;
		}
	}
}

/*****定时器0中断函数*****/
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

/*****延时函数*****/
void delay_()
{
	unsigned char i;
	for(i=0;i<100;i++);
}

/*****定时器0初始化函数*****/
void Timer0_init()
{
	TMOD	|=0x01;
	TH0		=	(65536-5000)/256;//初值0.1毫秒
	TL0		=	(65536-5000)%256;
	EA	=	1;
	ET0		=	1;
	TR0		=	1;
	num_timer0	=	0;
}
/*****定时器0中断函数*****/
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

/*****主函数*****/
void main()
{
	Timer0_init();//定时器0初始化函数
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

/*****主函数*****/
void main()
{
	
}

#endif









#ifdef DEBUG_beep

/*****主函数*****/
void main()
{
	
}

#endif


