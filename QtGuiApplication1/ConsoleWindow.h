#pragma once
#include <cstdlib>
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;
class ConsoleWindow
{
private:
	ConsoleWindow(){}
	~ConsoleWindow(){}
	ConsoleWindow(ConsoleWindow const&) = delete;
	ConsoleWindow(ConsoleWindow &&) = delete;
	ConsoleWindow& operator= (ConsoleWindow const&) = delete;
	ConsoleWindow& operator= (ConsoleWindow &&) = delete;

	static ConsoleWindow * Instance;

public:
	
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

	static ConsoleWindow& getInstance() {
		if (!Instance) {
			Instance = new ConsoleWindow;
		}
		return *Instance;
	}

	void Clear() {
		system("cls");
	}

	void Wait() {
		system("pause");
	}

	string GetKey() {
		if (KEY_DOWN(37)) return "LEFT";
		if (KEY_DOWN(39)) return "RIGHT";
		return "NULL";
	}

	void SetColor(int color)
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, color);
	}

	void MoveCursor(int x, int y)
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);///获取输出流句柄
		COORD coord;///定义COORD结构体(包含X和Y两个成员)
		coord.X = x * 2;	///设置结构体X轴
		coord.Y = y;		///设置结构体Y轴
		SetConsoleCursorPosition(hOut, coord);///设置光标位置
		CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };///修改光标宽带和显示
		SetConsoleCursorInfo(hOut, &cursor_info);///设置光标不可见◇","☆"
	}

	void ToLoc(int &x, int &y) {
		x /= 20;
		y = 35 - y / 20;
	}

	void DrawR(int x,int y ,int lx,int ly,int co) {
		ToLoc(x, y);
		SetColor(co);
		lx /= 20;
		ly /= 20;
		for (int i = y; ly; i--,ly--) {
			MoveCursor(x, i);
			for (int j = lx; j; j--) {
				printf("█");
			}
		}
	}
	void DrawC(int x, int y, int co) {
		ToLoc(x, y);
		SetColor(co);
		MoveCursor(x, y);
		printf("◎");
	}
};


