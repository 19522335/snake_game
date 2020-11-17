// Snake Hunter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "DieuKhien.h"
#include<ctime> 
using namespace std;

#define DOT_SNAKE 254
#define MAX 100

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define WALL_TOP 1
#define WALL_BOTTOM 13
#define WALL_LEFT 5
#define WALL_RIGHT 50

struct ToaDo
{
	int x, y;
};

ToaDo snake[MAX];
int numberOfDots = 3; // số nốt ban đầu của rắn
int direction = RIGHT; // khởi tạo hướng đi ban đầu 

// điểm số khi người chơi bắt đầu
int point = 0;

// khởi tạo rắn
void init_Snake()
{
	snake[0].x = WALL_LEFT + 3;
	snake[1].x = WALL_LEFT + 2;
	snake[2].x = WALL_LEFT + 1;
	snake[0].y = snake[1].y = snake[2].y = WALL_TOP + 1;
}

// hiển thị rắn
void display_Snake()
{
	for (int i = 0; i < numberOfDots; i++)
	{
		gotoXY(snake[i].x, snake[i].y);
		cout << (char) DOT_SNAKE ;
	}
}

// di chuyển
void move(int direct)
{
	// xóa đuôi cũ
	gotoXY(snake[numberOfDots - 1].x, snake[numberOfDots - 1].y);
	cout << " ";

	for (int i = numberOfDots - 1; i > 0; i--)
		snake[i] = snake[i - 1];

	switch (direct)
	{
	case UP:
		snake[0].y--;
		break;

	case DOWN:
		snake[0].y++;
		break;

	case LEFT:
		snake[0].x--;
		break;

	case RIGHT:
		snake[0].x++;
		break;
	}
}

// đổi hướng theo phím bấm
void do_events(int& direct)
{
	int key = inputKey();
	if ((key == 'w' || key == 'W' || key == KEY_UP) && direct != DOWN)
		direct = UP;
	else if ((key == 's' || key == 'S' || key == KEY_DOWN) && direct != UP)
		direct = DOWN;
	else if ((key == 'd' || key == 'D' || key == KEY_RIGHT) && direct != LEFT)
		direct = RIGHT;
	else if ((key == 'a' || key == 'A' || key == KEY_LEFT) && direct != RIGHT)
		direct = LEFT;
}

// vẽ tường
void draw_wall()
{
	// hiển thị tường trái
	for (int y = WALL_TOP + 1; y <= WALL_BOTTOM; y++)
	{
		gotoXY(WALL_LEFT, y);
		cout << (char)221;
	}
	//  hiển thị tường trên
	for (int x = WALL_LEFT; x <= WALL_RIGHT; x++)
	{
		gotoXY(x, WALL_TOP);
		cout << (char)220;
		gotoXY(x, WALL_BOTTOM);
		cout << (char)223;
	}
	//  hiển thị tường phải
	for (int y = WALL_TOP + 1; y <= WALL_BOTTOM - 1; y++)
	{
		gotoXY(WALL_RIGHT, y);
		cout << (char)222;
	}
}

// kiểm tra gắn chết


// kết thúc game


// hiển thị mồi


// rắn ăn mồi


// thêm nốt cho rắn 

// bắt đầu game


int main()
{
	init_Snake();
	draw_wall();
	while (true)
	{
		gotoXY(WALL_LEFT, WALL_BOTTOM + 1);
		do_events(direction);
		move(direction);
		display_Snake();
		Sleep(400);
	}
	
	system("Pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
