#include "Graphic.h"

//move cusor to column x row y
void goToXY(int x, int y)
{
	COORD coordinate = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

//Change text color
void setcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//wait for time/1000 seconds
void delay(clock_t time)
{
	clock_t goal;
	goal = time + clock();
	while (goal > clock()) {}
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

//// Hàm thay đổi kích cỡ của khung cmd.
//void resizeConsole(int width, int height)
//{
//	HWND console = GetConsoleWindow();
//	RECT r;
//	GetWindowRect(console, &r);
//	MoveWindow(console, r.left, r.top, width, height, TRUE);
//}

// Hàm vẽ đường thẳng nối 2 điểm (x1,y1) và (x2,y2)
void line(int x1, int y1, int x2, int y2)
{
	double a;
	double b;
	int t;
	int n;
	if (x1 != x2 && y1 != y2)
	{
		a = (y1 - y2) * 1.0 / (x1 - x2);
		b = y1 - a * x1;

		if (x1 > x2)
		{
			t = x2;
			n = x1;
		}
		else
		{
			t = x1;
			n = x2;
		}
		while (n - t > 0)
		{
			goToXY(t, (int)a * t + b);
			printf_s("*");
			t++;
		}
	}
	else if (x1 == x2 && y1 != y2)
	{
		if (y1 > y2)
		{
			t = y2;
			n = y1;
		}
		else
		{
			t = y1;
			n = y2;
		}
		while (n - t > 0)
		{
			goToXY(x1, t);
			printf_s("|");
			t++;
		}
	}
	else if (x1 != x2 && y1 == y2)
	{
		if (x1 > x2)
		{
			t = x2;
			n = x1;
		}
		else
		{
			t = x1;
			n = x2;
		}
		while (n - t >= 0)
		{
			goToXY(t, y1);
			printf_s("*");
			t++;
		}
	}
	else
	{
		goToXY(x1, y1);
		printf_s(".");
	}
}

//Hàm vẽ hình chữ nhật (left, top) -> (right, top) -> (right, bottom) -> (left, bottom) -> (left, top)
void rectangle(int left, int top, int right, int bottom)
{
	line(left, top, right, top);
	line(right, top, right, bottom);
	line(right, bottom, left, bottom);
	line(left, bottom, left, top);
}

//Hàm in chữ ra màn hình tại vị trí (x, y)
void outtextxyCenter(int x, int y, const char* str)
{
	goToXY(x - strlen(str) / 2, y);
	printf_s(str);
}
