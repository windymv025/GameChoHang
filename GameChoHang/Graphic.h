#pragma once
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <string>

#define BLACK			 0
#define BLUE		   	 1
#define GREEN			 2
#define CYAN			 3
#define RED				 4
#define MAGENTA			 5
#define Brown			 6
#define LIGHT_GRAY		 7
#define Dark_GRAY		 8
#define LIGHT_BLUE		 9
#define LIGHT_GREEN		10
#define LIGHT_CYAN		11
#define LIGHT_RED		12
#define LIGHT_MAGENTA	13
#define YELLOW			14
#define WHITE			15

//move cusor to column x row y
void goToXY(int x, int y);
//Change text color
void setcolor(int color);
//wait for time/1000 seconds
void delay(clock_t time);
// Hàm xóa màn hình.
void XoaManHinh();
// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height);
// Hàm vẽ đường thẳng nối 2 điểm (x1,y1) và (x2,y2)
void line(int x1, int x2, int y1, int y2);
//Hàm vẽ hình chữ nhật (left, top) -> (right, top) -> (right, bottom) -> (left, bottom)
void rectangle(int left, int top, int right, int bottom);
//Hàm in chữ ra màn hình tại vị trí (x, y)
void outtextxyCenter(int x, int y, const char* str);
