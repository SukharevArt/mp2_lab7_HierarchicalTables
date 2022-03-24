
#include"TText.h"
#include<Windows.h>
#include<conio.h>

void clrscr() {
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);
	DWORD Count;
	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;
	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}
void gotoxy(int x, int y) {
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(Console,pos);
}

void goDownLink(){
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);
	DWORD Count;
	COORD zpos=buf.dwCursorPosition;
	int x, y;
	x = zpos.X;
	y = zpos.Y + 1;
	gotoxy(x, y);
}

void goUpLink(){
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);
	DWORD Count;
	COORD zpos=buf.dwCursorPosition;
	int x, y;
	x = zpos.X;
	y = max(zpos.Y - 1, 0);
	gotoxy(x, y);
}

void goNextLink(){
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);
	DWORD Count;
	COORD zpos=buf.dwCursorPosition;
	int x, y;
	x = zpos.X+1;
	y = zpos.Y;
	gotoxy(x, y);
}

void goHomeLink(){
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);
	DWORD Count;
	COORD zpos=buf.dwCursorPosition;
	int x, y;
	x = 0;
	y = 0;
	gotoxy(x, y);
}

enum { HOME = 71, DOWN = 80, NEXT = 77, UP = 72, ESC = 27, INS = 82, DEL = 83, ENTER = 13 };

int main() {
	TText file;
	file.Load("input.txt");
	file.Print();
	char ch;
	gotoxy(3, 3);
	do {
		ch = _getch();
		if (ch == ESC)
			break;
		switch (ch) {
		case HOME:goHomeLink(); break;
		case UP:goUpLink(); break;
		case DOWN:goDownLink(); break;
		case NEXT:goNextLink(); break;
		}

	} while (1);

}