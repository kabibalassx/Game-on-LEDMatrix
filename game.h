#ifndef GAME_H_
#define GAME_H_

//头文件包含//
#include "reg51.h"
#include "stdlib.h"
#include "key.h"
#include "led.h"

//结构体类型、枚举类型定义//
typedef struct snake_position_struction{
	unsigned char x;
	unsigned char y;
	struct snake_position_struction * p_next;
}snake_position;
typedef struct food_position_struction{
	unsigned char x;
	unsigned char y;
}food_position;
enum dirction{up=1	,	down=2	,	left=3	,	right=4};

//全局变量声明//
extern unsigned char Game_state;
extern struct snake_position_struction * p_head;
extern enum dirction snake_dirction;
extern enum dirction dirction_last;
extern unsigned char xxh[8];

//全局函数声明//
void Game_init();
void Add_snake_chain(unsigned char x_,	unsigned char y_);
void Free_shake_chain();
unsigned char Judje_eat();
unsigned char Judje_die();
void Update_snake(unsigned char i);
void Update_food();
void Process_data();
unsigned char Get_length();


#endif
