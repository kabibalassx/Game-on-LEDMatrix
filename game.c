#include "game.h"

//��������//
snake_position * p_head;//��ͷ�ṹ���ָ��
food_position food;//ʳ��λ�ýṹ��	
unsigned char random_x;
unsigned char random_y;//ʳ��ĺ������������
enum dirction snake_dirction;//������ƶ�����
enum dirction dirction_last;//�ϴε��ƶ�����
unsigned char Game_state;//��Ϸ״̬������Ϊ����������Ϸ��Ϊ����Ϸ����
unsigned char xxh[8]={0x01	,	0x02	,	0x04	,	0x08	,	0x10	,	0x20	,	0x40	,	0x80};

/*****��Ϸ��ʼ������*****/
void Game_init()
{
	//��ʼ������õ�һ����
	static snake_position xdata malloc_space[20];
	//�ȴ����ⰴ��
	while(!Matrixkey_scan());	
	init_mempool(malloc_space	, sizeof(malloc_space));
	//�����������λ�õ�����(����������)
	p_head	=	malloc(sizeof(snake_position));
	p_head	->x	=	5;
	p_head	->y	=	8;
	p_head	->p_next	=	NULL;//���������һ����Ա�е�ָ����ΪNULL
	Add_snake_chain(5,	7);
	Add_snake_chain(5,	6);
	//��ʼ���ƶ�����
	snake_dirction	=	left;
	dirction_last	=	left;
	//��ʼ��ʳ��λ��
	Update_food();
	//��ʼ����Ϸ״̬����
	Game_state	=	1;
	//������ʱ��1
	TR1=1;
}

/*****����������Ա*****/
void Add_snake_chain(unsigned char x_	,	unsigned char y_)
{
	snake_position *p_new;
	p_new	=	malloc(sizeof(snake_position));//��̬����
	p_new	->x	=	x_;
	p_new	->y	=	y_;
	p_new	->p_next	=	p_head;
	p_head	=	p_new;	
}

/*****�ͷ�����*****/
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

/*****�ж��Ƿ�Ե�ʳ��*****/
unsigned char Judje_eat()
{	
	if((p_head->x	==	food.x)&&(p_head	->y	==	food.y))
		return 0;
	else 
		return 1;
}

/*****�ж��Ƿ�����(ײǽ��ײ���Լ�)*****/
unsigned char Judje_die()
{	
	unsigned char x_head	=	p_head->x;
	unsigned char	y_head	=	p_head->y;
	snake_position * p_	=	p_head;
	//�Ƿ�ײǽ
	if((p_head->x	<=	0)||(p_head->x	>=	9)||(p_head->y	<=	0)|	(p_head->y	>=	9))
	{
		return 1;
	}
	//�Ƿ�ײ���Լ�
	p_	=	p_->p_next;//Ϊ�˲���ͷ�Ƚ�
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

/*****��������λ�ú���*****/
void Update_snake(unsigned char i)
{
	snake_position * p_	=	p_head;//Ϊ��ʹָ��p_head����

ET1	=	0;

	if(i	==	0)//�Ե�ʳ����
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
	else if(i	==	1)//δ�Ե�ʳ��
	{
		//���������˳��
		unsigned char x_last	=	p_->x;
		unsigned char y_last	=	p_->y;//Ҫ��ǰ�沿λ��λ�ø�������Ĳ�λ���Ը�ֵ֮ǰ�Ƚ������ֵ��������
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
		//ͷ��λ�ÿ��ƶ�����
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

/******����ʳ��λ�ú���****/
void Update_food()
{
	snake_position *	p_;
	food.x	=	rand()%	8	+	1;
	food.y	=	rand()%	8	+	1;
	for(p_=	p_head	;	p_!=NULL	;	p_=	p_->p_next)
	{
		if((food.x	==	p_->x)||(food.y	==	p_->y))
		{
			Update_food();//��������غ���ݹ�����ٴμ���
		}
	}	
}

/*****�������ݺ���*****/
void Process_data()
{
	snake_position *p_;
	//�Զ�ѡ���ݳ�ʼ��
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

/*****����������*****/
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
