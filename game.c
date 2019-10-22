#include "game.h"

//变量定义//
snake_position * p_head;//蛇头结构体的指针
food_position food;//食物位置结构体	
unsigned char random_x;
unsigned char random_y;//食物的横纵坐标随机数
enum dirction snake_dirction;//最近的移动方向
enum dirction dirction_last;//上次的移动方向
unsigned char Game_state;//游戏状态变量，为非零正在游戏，为零游戏结束
unsigned char xxh[8]={0x01	,	0x02	,	0x04	,	0x08	,	0x10	,	0x20	,	0x40	,	0x80};

/*****游戏初始化函数*****/
void Game_init()
{
	//初始化数组得到一个堆
	static snake_position xdata malloc_space[20];
	//等待任意按键
	while(!Matrixkey_scan());	
	init_mempool(malloc_space	, sizeof(malloc_space));
	//建立最初蛇身位置的链表(反向建立链表)
	p_head	=	malloc(sizeof(snake_position));
	p_head	->x	=	5;
	p_head	->y	=	8;
	p_head	->p_next	=	NULL;//将链表最后一个成员中的指针设为NULL
	Add_snake_chain(5,	7);
	Add_snake_chain(5,	6);
	//初始化移动方向
	snake_dirction	=	left;
	dirction_last	=	left;
	//初始化食物位置
	Update_food();
	//初始化游戏状态变量
	Game_state	=	1;
	//开启定时器1
	TR1=1;
}

/*****添加蛇链表成员*****/
void Add_snake_chain(unsigned char x_	,	unsigned char y_)
{
	snake_position *p_new;
	p_new	=	malloc(sizeof(snake_position));//动态分配
	p_new	->x	=	x_;
	p_new	->y	=	y_;
	p_new	->p_next	=	p_head;
	p_head	=	p_new;	
}

/*****释放链表*****/
void Free_shake_chain()
{
	snake_position *p_;
	p_=	p_head; 
	while(p_!=NULL)
	{									 
		free(p_);
		p_=	p_->p_next;
	}
}

/*****判断是否吃到食物*****/
unsigned char Judje_eat()
{	
	if((p_head->x	==	food.x)&&(p_head	->y	==	food.y))
		return 0;
	else 
		return 1;
}

/*****判断是否死亡(撞墙或撞到自己)*****/
unsigned char Judje_die()
{	
	unsigned char x_head	=	p_head->x;
	unsigned char	y_head	=	p_head->y;
	snake_position * p_	=	p_head;
	//是否撞墙
	if((p_head->x	<=	0)||(p_head->x	>=	9)||(p_head->y	<=	0)|	(p_head->y	>=	9))
	{
		return 1;
	}
	//是否撞到自己
	p_	=	p_->p_next;//为了不与头比较
	while(p_!=NULL)
	{
		if((x_head	==	p_->x)&&(y_head	==	p_->y))
		{
			return 1;
		}
		p_	=	p_->p_next;
	}
	return 0;
}

/*****更新蛇身位置函数*****/
void Update_snake(unsigned char i)
{
	snake_position * p_	=	p_head;//为了使指针p_head不变

ET1	=	0;

	if(i	==	0)//吃到食物了
	{
		if(snake_dirction	==	up)
		{
			Add_snake_chain(p_head->x	-	1,p_head->y);
		}
		else if(snake_dirction	==	down)
		{
			Add_snake_chain(p_head->x	+	1,p_head->y);
		}
		else if(snake_dirction	==	left)
		{
			Add_snake_chain(p_head->x,p_head->y	-	1);
		}
		else if(snake_dirction	==	right)
		{
			Add_snake_chain(p_head->x,p_head->y	+	1);
		}
	}
	else if(i	==	1)//未吃到食物
	{
		//后面的身体顺上
		unsigned char x_last	=	p_->x;
		unsigned char y_last	=	p_->y;//要将前面部位的位置赋给后面的部位多以赋值之前先将后面的值保存起来
		unsigned char x_tem;
		unsigned char y_tem;
		while(p_->p_next	!=	NULL)
		{
			x_tem	=	p_->p_next->x;
			y_tem	=	p_->p_next->y;
			p_->p_next->x	=	x_last;
			p_->p_next->y	=	y_last;
			x_last	=	x_tem;
			y_last	=	y_tem;
			p_	=	p_->p_next;
		}
		//头的位置看移动方向
		if(snake_dirction	==	up)
		{
			p_head->x	-=	1;
		}
		else if(snake_dirction	==	down)
		{
			p_head->x	+=	1;
		}
		else if(snake_dirction	==	left)
		{
			p_head->y	-=	1;
		}
		else if(snake_dirction	==	right)
		{
			p_head->y	+=	1;
		}
		dirction_last	=	snake_dirction;
	}

ET1	=	1;

}

/******更新食物位置函数****/
void Update_food()
{
	snake_position *	p_;
	food.x	=	rand()%	8	+	1;
	food.y	=	rand()%	8	+	1;
	for(p_=	p_head	;	p_!=NULL	;	p_=	p_->p_next)
	{
		if((food.x	==	p_->x)||(food.y	==	p_->y))
		{
			Update_food();//如果与蛇重合则递归调用再次计算
		}
	}	
}

/*****处理数据函数*****/
void Process_data()
{
	snake_position *p_;
	//对段选数据初始化
	unsigned char i;
	for(i=0;i<8;i++)
	{
		Red_duan[i]=0x00;
	}
	for(p_=p_head	;	p_!=NULL	;	p_=p_->p_next)
	{
		if(	(p_->y	<	9)&&(p_->y	>	0)&&(p_->x	>	0)&&(p_->x	<	9)	)
		{	
			Red_duan[	p_->y-1	]	+=	xxh[	p_->x-1	];
		}
	}
	if((p_head->y	!=	food.y)||(p_head->x	!=	food.x))
	{	
		Red_duan[	food.y-1	]	+=	xxh[	food.x-1	];
	}
}

/*****计算蛇身长度*****/
unsigned char Get_length()
{
	snake_position *	p_;
	unsigned char number=0;
	p_=p_head;
	while(p_!=NULL)
	{
		number++;
		p_=p_->p_next;
	}
	return number;
}
