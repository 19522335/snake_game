﻿// Snake Hunter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include"Control_Library.h"
#include"wtypes.h"
#include<time.h> 
#include"string"

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
	snake[0].y = Bottom_Wall / 2 + 1;
	snake[1].y = snake[2].y = snake[3].y = snake[4].y = snake[5].y = snake[6].y = snake[7].y = snake[8].y = snake[9].y = snake[10].y = Bottom_Wall / 2 + 1;
}

// hiển thị rắn
void display_Snake(int direction, int SnakeX, int SnakeY, int SpeedX, int SpeedY)
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
				if (snake[i].y == SnakeY) {
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
					if (snake[i].y < SnakeY && snake[i].y>snake[0].y) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)179;
					}
				}
			}
		}
		Sleep(SpeedY);
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
					if (snake[i].y > SnakeY && snake[i].y < snake[0].y) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)179;
					}
				}
			}
		}
		Sleep(SpeedY);
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
					if (snake[i].x < SnakeX && snake[i].x > snake[0].x) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)196;
					}
				}
			}
		}
		Sleep(SpeedX);
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
					if (snake[i].x > SnakeX && snake[i].x < snake[0].x) {
						gotoXY(snake[i].x, snake[i].y);
						cout << (char)196;
					}
				}
			}
		}
		Sleep(SpeedX);
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
void do_events(int& direct, int& SnakeX, int& SnakeY)
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
void draw_wall(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall) {
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

	gotoXY(Right_Wall + 4, Top_Wall + 1);
	cout << "*** NOTE ***";
	gotoXY(Right_Wall + 4, Top_Wall + 3);
	cout << "Green food = Death.";
	gotoXY(Right_Wall + 4, Top_Wall + 5);
	cout << "Yellow food = Faster and longer.";
	gotoXY(Right_Wall + 4, Top_Wall + 7);
	cout << "Red food = Slower and shorter";
	gotoXY(Left_Wall, Bottom_Wall + 1);
	setTextColor(10);
	cout << "Point: " << point << endl;
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
	//for (int i = 0; i < numberOfFakeFoods; i++)
	//	if (snake[0].x == FakeFood[i].x && snake[0].y == FakeFood[i].y)
	//		return true;
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
	cout << (char)149;
	return ToaDo{ x, y };
}
//hiển thị fake food, màu đỏ
ToaDo display_FakeFood(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
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
	setTextColor(4);
	cout << (char)149;
	return ToaDo{ x, y };
}
ToaDo display_DeathFood(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
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
	setTextColor(2);
	cout << (char)149;
	return ToaDo{ x, y };
}
// rắn ăn mồi
bool checkEatFood(ToaDo food, int& SpeedX, int& SpeedY) {
	if (snake[0].x == food.x && snake[0].y == food.y) {
		SpeedX -= 2;
		SpeedY -= 6;
		return true;
	}
	return false;
}
bool checkEatFakeFood(ToaDo fake_food, int& SpeedX, int& SpeedY) {
	if (snake[0].x == fake_food.x && snake[0].y == fake_food.y) {
		SpeedX += 2;
		SpeedY += 6;
		return true;
	}
	return false;
}
bool checkEatDeathFood(ToaDo death_food) {
	if (snake[0].x == death_food.x && snake[0].y == death_food.y) {
		return true;
	}
	return false;
}
// thêm nốt cho rắn 
void addDots()
{
	snake[numberOfDots] = snake[numberOfDots - 1];
	numberOfDots++;
}

void subDots()
{
	snake[numberOfDots] = snake[numberOfDots + 1];
	numberOfDots--;
	gotoXY(snake[numberOfDots].x, snake[numberOfDots].y);
	cout << " ";
}

bool Display_GameOver(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall) {
	clrscr();
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
	gotoXY(Right_Wall / 2 - 7, Bottom_Wall / 2 - 1);
	cout << "GAME OVER!";
	gotoXY(Right_Wall / 2 - 7, Bottom_Wall / 2 + 1);
	cout << "Your POINT: " << point << endl;
	gotoXY(Right_Wall / 2 - 7, Bottom_Wall / 2 + 3);
	cout << "PLay again?";
	//gotoXY(Right_Wall / 2 - 5, Bottom_Wall / 2 + 4);
	//cout << "EXIT";
	gotoXY(Right_Wall / 2 - 7, Bottom_Wall / 2 + 4);
	cout << "Type \"yes\" to continue. ";
	gotoXY(Right_Wall / 2 + 7, Bottom_Wall / 2 + 3);
	string a;
	getline(cin, a);
	if (a == "yes" || a == "YES" || a == "Yes")
		return true;
	return false;
}

// bắt đầu game
void run_game(int Left_Wall, int Right_Wall, int Top_Wall, int Bottom_Wall)
{
	clrscr();
	init_Snake(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	draw_wall(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	ToaDo food = display_food(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);// hiển thị thức ăn và trả về tọa độ
	ToaDo fake_food = display_FakeFood(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	ToaDo death_food = display_DeathFood(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	int SnakeX, SnakeY; // lấy toạ độ thân rắn lúc quẹo 
	int SpeedX = 100, SpeedY = 130;
	// vòng lặp trò chơi
	while (true)
	{
		gotoXY(Left_Wall + 7, Bottom_Wall + 1);
		cout << point;
		do_events(direction, SnakeX, SnakeY);
		move(direction);
		display_Snake(direction, SnakeX, SnakeY, SpeedX, SpeedY);
		if (checkEatFood(food, SpeedX, SpeedY) == true)
		{
			food = display_food(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
			addDots();
			point++;
		}
		if (checkEatFakeFood(fake_food, SpeedX, SpeedY) == true)
		{
			fake_food = display_FakeFood(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
			subDots();
		}
		if (checkEatDeathFood(death_food) == true)
			break;
		if (check_Gameover(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall) == true) {
			break;
		}
	}
	Sleep(500);
	if (Display_GameOver(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall) == true) {
		point = 0;
		numberOfDots = 11;
		return run_game(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	}
	gotoXY(Left_Wall, Bottom_Wall + 1);
}
// kết thúc game

int main()
{
	int Left_Wall = 0,
		Top_Wall = 0,
		Right_Wall = 80,
		Bottom_Wall = 27;
	//GetDesktopResolution(Right_Wall, Bottom_Wall);*/
	run_game(Left_Wall, Right_Wall, Top_Wall, Bottom_Wall);
	system("Pause");
	return 0;
}