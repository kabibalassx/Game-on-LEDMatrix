# Game-on-LEDMatrix
A game console based on 51 SCM and a LEDmatrix , controlled by 5 keys.

---

## 目录
### 一、实现目标
### 二、主要数据结构
### 三、程序文件组成部分
### 四、程序流程图
### 五、下一步目标
### 六、下一步修改
### 七、硬件电路设计

---

## 一、实现目标

### 1.游戏内容

* 蛇初始有三格长度，地图上随机出现亮点，每吃掉一个亮点长度便增加一
 * 每吃完一个亮点才出现第二个亮点，同一时刻地图上只有一个亮点
 * 被吃掉的亮点的地方变成贪吃蛇的头部，吃掉的下一秒在移动方向上长出一个头来
* 蛇不能撞墙，不能碰到自己，碰到自己则游戏结束
 * 蛇约半秒种移动一次位置
 * 蛇头与边界与身体接触后的半秒后不转向判定为游戏结束 
* 将蛇长度的长度记录下来，在游戏结束时显示在LED点阵上
* 蛇不能回头撞自己

### 2.输入与输出
* 按矩阵键盘的任意键开始游戏 
* 通过矩阵按键上S2、S5、S6、S7控制上下左右
* 按键不可连按，用一个变量存储最近检测到的按下的按键，在蛇移动位置时一最后一次按下的按键为准
* LED点阵显示方式为按列从左到右动态扫描，扫描换列由定时器0控制，蛇移动位置由定时器1控制

## 二、主要数据结构
* 蛇身体位置
用一个结构体变量`snake_position`记录蛇某个部位的位置，并从尾到头组成单项链表，在game文件中
```c
typedef struct snake_position_struction{
    unsigned char x;//横坐标，范围为1到9
    unsigned char y;//纵坐标，范围为1到9
    struct snake_position_struction *p;
}snake_position;
snake_positio snake;
```

* 食物亮点位置
用一个结构体`food_position`记录，在game文件中
```c
typedef struct food_position_struction{
    unsigned char x;
    unsigned char y;
}food_position;
food_position food;
```

* 一个`unsigned char`类型的数组用于在程序运行时记录处理得到的LED点阵的段选数据，程序开始时存储初始界面，在led文件中
```c
unsigned char Red_duan[8]; 
```

* 两个枚举类型的变量，一个记录最近按下的一个按键代表的方向信息，另一个记录上一个方向信息，用于判断蛇是否回头撞到自己，在game文件中

```c
enum dirction{up=1,down=2,left=3;right=4};
```

* 一个`unsigend char`类型的变量用于使主函数线程与中断函数线程通信游戏状态，在main文件中
```c
unsigned char Game_state;
```

* 一个`const unsigned char`类型的常量数组用于最后点阵显示两位数字的长度，在led文件中
```c
const unsigned char Number[4][10];
```

## 三、程序文件组成部分
### 1、main文件
包含主函数，定时器初初始化以及中断函数
```c
unsigned char mum;                  //定时器1中断次数
void Timer1_init();                 //定时器1初始化函数，暂不开启定时器
void Timer0_init();                 //定时器0初始化函数，开启定时器
void Timer1_interrupt(); interrupt 3//定时器1中断函数
void Timer0_interrupt(); interrupt 1//定时器0初始化函数
```

### 2、led文件
包含各种LED显示函数
```c
void Display_Red(unsigned char duan ; unsigend char wei);//给定位选与段选数据，点阵显示函数
```

### 3、game文件
游戏初始化函数
判定蛇是否吃到食物函数
判定蛇是否撞墙是否撞到自己函数
根据移动方向更行蛇身位置
将蛇身位置转换为段选数据
根据随机数计算下一个食物位置
计算蛇身长度的函数
```c
void Game_Init();           //游戏初始化函数，包括接受最开始的随机数，建立最开始长度为三的蛇身链表，初始化蛇移动方向
void Add_shanek_chain(unsigned char x_,unsigned char y_); //添加蛇身链表函数
void Free_shake_chain();    //释放蛇身链表函数
unsigned char Judje_eat();  //判断是否吃到食物，若吃到返回非零
unsigned char Judje_die();  //判断是否撞墙或者撞到自己，若撞到则返回非零
void Update_snake(unsigned char i);        //更新蛇身位置，输入为函数Juduje_eat()；的输出
void Updata_food();         //更新食物数据，内部检测食物是否与she蛇身重叠，使食物在蛇身以外的位置，输入为Judje_eat();的输出
void Process_data();        //将蛇身位置信息与食物位置信息转换为LEd点阵的段选数据，需要注意当蛇吃到食物时（蛇头与食物重合时）不要多次加蛇头处的信息
unsigned char Get_length(); //游戏结束时获取蛇身长度，并清空链表
```

### 4、key文件
包含按键检测函数
```c
void delay(unsigned short int a);   //延时函数，用于软件防抖
unsigned char Matrixkey_scan();     //矩阵键盘扫描函数
```

### 5、config文件
用于选择调试或运行程序

## 四、程序流程图

### 1、主函数
[主函数流程图](https://raw.githubusercontent.com/kabibalassx/Repository-for-pictures/master/Game%20on%20LEDMatrix%201.jpg)

### 2、定时器0中断函数
[定时器0中断函数](https://raw.githubusercontent.com/kabibalassx/Repository-for-pictures/master/Game%20on%20LEDMatrix%202.jpg)

### 3、定时器1中断函数
[定时器1中断函数](https://raw.githubusercontent.com/kabibalassx/Repository-for-pictures/master/Game%20on%20LEDMatrix%203.jpg)

## 五、下一步目标
* [ ]  1. 在游戏开始与结束时有音乐提示

* [ ]  2. 在吃到亮点时有音效提示

* [ ]  3. 利用74HC595串行输出数据给LED点阵，使蛇与食物显示两种颜色，使得点阵上显示的得分的十位与各位用不同颜色

* [ ]  4. 在EEPROM中存入一张随机数表

* [ ] 5. 优化LED点阵显示函数，不在按列动态扫描，用以提高亮度

## 六、下一步修改
    
1. 在led文件中添加
    ```c
    unsigned char Green_duan[8];
    unsigned char Write_595(unsigned char Red,unsigned char Green);//代替原来Display_red()函数中的输入段选信息
    ```
修改 `Display_red(unsigned char duan,unsigned char wei);` 函数为`Display_led(unsigend char Red_duan,unsigned char Green_duan,unsigned char wei);`通过74HC595的串行同时输出红色与绿色，修改位定义

1. 添加beep文件，包含函数：
    ```c
    //变量//
    const unsigned char code Music_start[ ];    //游戏开始音乐
    const unsigned char code Music_gameover[ ]; //游戏结束音乐
    
    void Prompt_music();    //在蛇吃到食物时发出提示音
    void Start_music();     //游戏开始提示音，插入到开启定时器1之前
    void Gameover_music();  //游戏结束提示音，在显示数字时
    ```

## 七、硬件电路设计
[原理图 & PCB工程链接](https://lceda.cn/kbbl/ji-yu-51dan-pian-ji-yu-LEDdian-zhen-de-you-hu-ji)


