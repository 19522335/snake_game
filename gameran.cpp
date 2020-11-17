#include<iostream>
#include"kmin_console.h"
using namespace std;
#define Ran 254
#define Max 100
#define Lwall 4
#define Rwall 104
#define Uwall 4
#define Dwall 24
struct Point{
	int x;
	int y;
};

Point Conran[Max];
int Sodot = 5;

bool Kiemtradungtuong()
{
	if (Conran[0].y == Uwall)
		return false;
	if (Conran[0].y == Dwall)
		return false;
	if (Conran[0].x == Lwall)
		return false;
	if (Conran[0].x == Lwall)
		return false;
}

void Taotuong()
{
	
	for (int i = Lwall; i <= Rwall; i++)
	{
		gotoXY(i, Uwall);
		cout << (char)220;
	}
	for (int i = Uwall + 1; i <= Dwall; i++)
	{
		gotoXY(Lwall, i);
		cout << (char)221;

		gotoXY(Rwall, i);
		cout << (char)222;
	}
	for (int i = Lwall ; i <= Rwall; i++)
	{
		gotoXY(i, Dwall);
		cout << (char)223;
	}
}
int main()
{
	Taotuong();
	
	

	cout << endl;
	return 0;
}
//186 dọc 205 ngang