#include <stdio.h>
#include<stdlib.h>
#include<conio.h>//按键控制
#include<windows.h>//光标移动
#include<time.h>//食物随机产生

//1.数据设计
//2.模块化设计
//3.实现过程

//////////////////////////////////////
//辅助宏定义
#define MAXSIZE  100
#define MAPWIDTH 90
#define MAPHIGHER 28

///////////////////////////////////////
//全局变量
int changeFlag = 0;
int key = 'w';

//1.数据设计
struct {
	int x;
	int y;
}food;
struct
{
	int x[MAXSIZE];
	int y[MAXSIZE];
	int len;
	int speed;
}snake;

//2.模块化设计
void map();//地图
void createFood();//产生食物
void hit();//按键操作
int snakeStatus();//蛇的状态，用来判断蛇吃东西和结束游戏
void gotoxy(int x, int y);//辅助函数，确定光标位置

//3.实现过程
int main() {

	map();
	while (1)
	{
		createFood();
		Sleep(snake.speed);
		hit();

	}
	system("pause");
	return 1;
}

void map() {
	//■：食物  ★：蛇身  □:墙壁
	srand((unsigned int)time(NULL));
	for (int i = 0; i <= MAPWIDTH; i += 2) {//上下边框
		gotoxy(i, 0);
		printf("□");
		gotoxy(i, MAPHIGHER);
		printf("□");
	}
	for (int i = 0; i <= MAPHIGHER; i++) {//左右边框
		gotoxy(0, i);
		printf("□");
		gotoxy(MAPWIDTH, i);
		printf("□");
	}
	//画蛇
	snake.x[0] = MAPWIDTH / 2;
	snake.y[0] = MAPHIGHER / 2;
	snake.len = 3;
	gotoxy(snake.x[0], snake.y[0]);
	printf("★");
	for (int i = 1; i < snake.len; i++) {
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("★");
	}
	food.x = rand() % (MAPWIDTH - 4) + 2;
	food.y = rand() % (MAPHIGHER - 2) + 1;
	//srand((int)time(NULL));//srand作为rand的种子（）内为系统时间；
	//computer = rand() % 3 + 1;//随机产生1-3任意一个整数，rand()%3是随机产生0-2之间的整数(包含0但不包含3)
	gotoxy(food.x, food.y);
	printf("■");
};//地图、蛇和第一个食物
void createFood() {
	if (snake.x[0] == food.x&&snake.y[0] == food.y) {//判断蛇有没有吃食物,吃了的话就产生新的食物
		srand((unsigned int)time(NULL));
		food.x = rand() % (MAPWIDTH - 4) + 2;
		food.y = rand() % (MAPHIGHER - 2) + 1;
		while (1)
		{
			int flag = 1;
			for (int i = 0; i <= snake.len - 1; i++) {
				if (snake.x[0] == food.x&&snake.y[0] == food.y)
				{
					flag = 0;
					break;
				}
				if (flag&&food.x % 2 == 0) {
					break;
				}
			}
			gotoxy(food.x, food.y);
			printf("■");
			changeFlag = 1;
		}
	};//产生食物
	void hit() {
		if (_kbhit) {
			fflush(stdin);
			key = _getch();
		}
		if (!changeFlag) {//擦除最后的位置
			gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);//数组从 0开始存
			printf("  ");
		}
		for (int i = snake.len - 1; i > 0; i--) {//后面的蛇身
			snake.x[i] = snake.x[i - 1];
			snake.y[i] = snake.y[i - 1];
		}//没有这段代码，蛇身不会消失
		switch (key)
		{
		case'w':
		case'W':
		case 72:
			snake.y[0] -= 1;
			break;
		case's':
		case'S':
		case 80:
			snake.y[0] += 1;
			break;
		case'a':
		case'A':
		case 75:
			snake.x[0] -= 2;
			break;
		case'd':
		case'D':
		case 77:
			snake.x[0] += 2;
			break;
		}
		gotoxy(snake.x[0], snake.y[0]);
		printf("★");
		changeFlag = 0;
		gotoxy(MAPWIDTH + 2, 0);
	};//按键操作
	int snakeStatus() {

	};//蛇的状态，用来判断蛇吃东西和结束游戏
	void gotoxy(int x, int y) {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(handle, coord);
	};//辅助函数，确定光标位置

	////测试按键
	//#include<stdio.h>
	//#include<conio.h>
	//int main() {
	//	char ch;
	//	while (1)
	//		if (_kbhit()) {
	//			ch = _getch();
	//			printf("%d\n", ch);
	//		}
	//		return 0;
	//}

	//fflush和sleep的用法
	//#include <windows.h> //win头文件
	//#include<stdio.h>
	//int main()
	//{
	//	int i;
	//	printf("你");
	//	fflush(stdout); //强制刷新缓存，输出显示
	//	for (i = 0; i < 10; i++)
	//	{
	//		Sleep(1000);    /* windows 使用Sleep，参数为毫秒 */
	//		printf(".");
	//		fflush(stdout);//强制刷新缓存，输出显示
	//	}
	//	printf("好\n");  /*输出“你”和“好”之间会间隔10秒,并输出10个点*/
	//	return 0;
	//}