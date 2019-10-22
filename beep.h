#ifndef BEEP_H_
#define BEEP_H_

//全局变量声明//
const unsigned char code Music_start[];		//游戏开始音乐
const unsigned char code Music_gamepver[];//游戏结束音乐

//全局函数声明//
void Prompt();				//吃到食物提示音
void Start_music();		//游戏开始提示音
void Gameover_music();//游戏结束提示音

#endif
