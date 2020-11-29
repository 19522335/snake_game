// Snake Hunter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include"Control_Library.h"
#include "wtypes.h"
#include<time.h> 
using namespace std;

#define DOT_SNAKE 254
#define MAX 100

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//#define Top_Wall 0
//#define Bottom_Wall 1080/20
//#define Left_Wall 0
//#define Right_Wall 1920/20


// Get the horizontal and vertical screen sizes in pixel
/*void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}*/

struct ToaDo
{
	int x, y;
};

ToaDo snake[MAX];
ToaDo FakeFood[MAX];
int numberOfFakeFoods = 1;
int numberOfDots = 11; // số nốt ban đầu của rắn
int direction = RIGHT; // khởi tạo hướng đi ban đầu 

int point = 0;
// điểm số khi người chơi bắt đầu

// khởi tạo rắn
void init_Snake(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
{
	snake[0].x = Left_Wall + 11;
	snake[1].x = Left_Wall + 10;
	snake[2].x = Left_Wall + 9;
	snake[3].x = Left_Wall + 8;
	snake[4].x = Left_Wall + 7;
	snake[5].x = Left_Wall + 6;
	snake[6].x = Left_Wall + 5;
	snake[7].x = Left_Wall + 4;
	snake[8].x = Left_Wall + 3;
	snake[9].x = Left_Wall + 2;
	snake[10].x = Left_Wall + 1;
	snake[0].y = snake[1].y = snake[2].y = snake[3].y = snake[4].y = snake[5].y = snake[6].y = snake[7].y = snake[8].y = snake[9].y = snake[10].y = Bottom_Wall/2 + 1;
}

// hiển thị rắn
void display_Snake(int direction, int SnakeX, int SnakeY)
{
	noCursorType();
	switch (direction)
	{
	case UP:
		for (int i = 1; i < numberOfDots; i++)
		{
			gotoXY(snake[0].x, snake[0].y);
			cout << "^";
			if (snake[i].x == SnakeX) {
				if (snake[i].y == SnakeY){
					if (snake[i + 1].x == SnakeX + 1) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)192;
					}
					else {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)217;
					}
				}
				else {
					gotoXY(snake[i].x, snake[i].y);
					cout << (char)179;
				}
			}
			else {
				gotoXY(snake[i].x, snake[i].y);
				cout << (char)196;
			}
		}
		break;

	case DOWN:
		for (int i = 1; i < numberOfDots; i++)
		{
			gotoXY(snake[0].x, snake[0].y);
			cout << "v";
			if (snake[i].x == SnakeX) {
				if (snake[i].y == SnakeY) {
					if (snake[i + 1].x == SnakeX + 1) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)218;	
					}
					else {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)191;
					}
				}
				else {
					gotoXY(snake[i].x, snake[i].y);
					cout << (char)179;
				}
			}
			else {
				gotoXY(snake[i].x, snake[i].y);
				cout << (char)196;
			}
		}
		break;

	case LEFT:
		for (int i = 1; i < numberOfDots; i++)
		{
			gotoXY(snake[0].x, snake[0].y);
			cout << "<";
			if (snake[i].y == SnakeY) {
				if (snake[i].x == SnakeX) {
					if (snake[i + 1].y == SnakeY + 1) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)191;
					}
					else {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)217;
					}
				}
				else {
					gotoXY(snake[i].x, snake[i].y);
					cout << (char)196;
				}
			}
			else {
				gotoXY(snake[i].x, snake[i].y);
				cout << (char)179;
			}
		}
		break;

	case RIGHT:
		for (int i = 1; i < numberOfDots; i++)
		{
			gotoXY(snake[0].x, snake[0].y);
			cout << ">";
			if (snake[i].y == SnakeY) {
				if (snake[i].x == SnakeX) {
					if (snake[i + 1].y == SnakeY + 1) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)218;
					}
					else {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)192;
					}
				}
				else {
					gotoXY(snake[i].x, snake[i].y);
					cout << (char)196;
				}
			}
			else {
				gotoXY(snake[i].x, snake[i].y);
				cout << (char)179;
			}
		}
		break;
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
void do_events(int& direct, int &SnakeX,int &SnakeY)
{
	int key = inputKey();
	if ((key == 'w' || key == 'W' || key == KEY_UP) && direct != DOWN && direct != UP) {
		direct = UP;
		SnakeX = snake[0].x;
		SnakeY = snake[0].y;
	}
	else if ((key == 's' || key == 'S' || key == KEY_DOWN) && direct != UP && direct != DOWN) {
		direct = DOWN;
		SnakeX = snake[0].x;
		SnakeY = snake[0].y;
	}
	else if ((key == 'd' || key == 'D' || key == KEY_RIGHT) && direct != LEFT && direct != RIGHT) {
		direct = RIGHT;
		SnakeX = snake[0].x;
		SnakeY = snake[0].y;
	}
	else if ((key == 'a' || key == 'A' || key == KEY_LEFT) && direct != RIGHT && direct != LEFT) {
		direct = LEFT;
		SnakeX = snake[0].x;
		SnakeY = snake[0].y;
	}
}

// vẽ tường
void draw_wall(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall){
	// draw corner
	gotoXY(Left_Wall, Top_Wall);
	cout << char(201);
	gotoXY(Left_Wall, Bottom_Wall);
	cout << char(200);
	gotoXY(Right_Wall, Bottom_Wall);
	cout << char(188);
	gotoXY(Right_Wall, Top_Wall);
	cout << char(187);
	// Draw left + right wall
	for (int y = Top_Wall + 1; y <= Bottom_Wall - 1; y++) {
		gotoXY(Left_Wall, y);
		cout << (char)186;
		gotoXY(Right_Wall, y);
		cout << (char)186;
	}

	//Draw Top + bottom wall
	for (int x = Left_Wall + 1; x <= Right_Wall - 1; x++) {
		gotoXY(x, Top_Wall);
		cout << (char)205;
		gotoXY(x, Bottom_Wall);
		cout << (char)205;
	}
	cout << "\n";
	cout << "Point: " << endl;
}

// kiểm tra gắn chết
bool check_Gameover(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
{
	// đụng tường trên
	if (snake[0].y == Top_Wall)
		return true;
	// đụng tường dưới
	if (snake[0].y == Bottom_Wall)
		return true;
	// đụng tường trái
	if (snake[0].x == Left_Wall)
		return true;
	// đụng tường phải
	if (snake[0].x == Right_Wall)
		return true;
	// ăn dính fake food
	for (int i = 0; i < numberOfFakeFoods; i++)
		if (snake[0].x == FakeFood[i].x && snake[0].y == FakeFood[i].y)
			return true;
	// tự hủy
	for (int i = 1; i < numberOfDots; i++)
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return true;
	return false;

}


// hiển thị mồi ăn đc, màu vàng
ToaDo display_food(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
{
	int x = Left_Wall + 1 + rand() % (Right_Wall - Left_Wall - 1); // a + rand() % (b - a + 1) random from a to b
	int y = Top_Wall + 1 + rand() % (Bottom_Wall - Top_Wall - 1);
	//tránh việc mồi spawn trên con rắn
	for (int i = 1; i < numberOfDots; i++) {
		if (snake[i].x == x && snake[i].y == y) {
			x = Left_Wall + 1 + rand() % (Right_Wall - Left_Wall - 1);
			y = Top_Wall + 1 + rand() % (Bottom_Wall - Top_Wall - 1);
		}
	}
	gotoXY(x, y);
	setTextColor(6);
	cout << (char)111;
	return ToaDo{ x, y };
}
//hiển thị fake food, màu đỏ
ToaDo display_FAKEfood(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
{
	int x = Left_Wall + 1 + rand() % (Right_Wall - Left_Wall - 1); // a + rand() % (b - a + 1) random from a to b
	int y = Top_Wall + 1 + rand() % (Bottom_Wall - Top_Wall - 1);
	gotoXY(x, y);
	setTextColor(4);
	cout << 'o';
	return ToaDo{ x, y };
}
// rắn ăn mồi
bool checkEatFood(ToaDo food)
{
	if (snake[0].x == food.x && snake[0].y == food.y)
		return true;
	return false;
}

// thêm nốt cho rắn 
void addDots()
{
	snake[numberOfDots] = snake[numberOfDots - 1];
	numberOfDots++;
}

// bắt đầu game
void run_game(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
{
	ToaDo food = display_food(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);// hiển thị thức ăn và trả về tọa độ 		
							 // vòng lặp trò chơi
	int SnakeX,SnakeY; // lấy toạ độ thân rắn lúc quẹo 
	while (true)
	{
		gotoXY(Left_Wall + 7, Bottom_Wall + 1);
		cout << point;
		do_events(direction,SnakeX,SnakeY);
		move(direction);
		display_Snake(direction, SnakeX, SnakeY);
		if (checkEatFood(food) == true)
		{
			food = display_food(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
			addDots();
			point++;
			numberOfFakeFoods++;
			FakeFood[numberOfFakeFoods] = display_FAKEfood(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
		}
		if (check_Gameover(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall) == true)
			break;

		Sleep(100);
	}
}
// kết thúc game

int main()
{
	int Left_Wall = 0,
		Top_Wall = 0,
		Right_Wall = 100,
		Bottom_Wall = 20;
	//GetDesktopResolution(Right_Wall, Bottom_Wall);*/
	init_Snake(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	draw_wall(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	run_game(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	system("Pause");
	return 0;
}