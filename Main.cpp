
#include<Windows.h>
#include<string>
#include<conio.h>
#include"TText.h"
#include<ctime>

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

void InsOperator(TText& proc) {
	int ls;
	int nd;
	cout << " Enter line number:\n";
	int fl = 0;
	int r;
	while (1) {
		cin >> r;
		fl = 0;
		proc.reset();
		for (int i = 0; i < r-1; i++, proc.goNext()) {
			if (proc.isEnd()) {
				fl = 1;
				break;
			}
		}
		if (r == 0) {
			return;
		}
		if (fl) {
			cout << " Enter correct line :\n";
		}
		else {
			break;
		}
	}
	nd = -1;
	ls = -1;
	cout << " Insert Next (1) / Down (2) ?\n";
	while (1) {
		cin >> nd;
		if (nd == 0) {
			return;
		}
		if (nd != 1 && nd != 2) {
			cout << " Enter correct code of operation :\n";
		}else {
			break;
		}
	}
	cout << " Line (1) / Section (2) ?\n";
	while (1) {
		cin >> ls;
		if (ls == 0) {
			return;
		}
		if (ls != 1 && ls != 2) {
			cout << " Enter correct code of operation :\n";
		}else {
			break;
		}
	}
	cout << " Enter name :\n";
	char* nstr=new char[101];
	cin >> nstr;
	if (ls==1) {
		if (nd==1) {
			proc.InsNextLine(nstr);
		}
		else {
			proc.InsDownLine(nstr);
		}
	}
	else {
		if (nd == 1) {
			proc.InsNextSection(nstr);
		}
		else {
			proc.InsDownSection(nstr);
		}
	}
}

void DelOperator(TText&proc) {
	int ls;
	int nd;
	cout << " Enter line number:\n";
	int fl = 0;
	int r;
	while (1) {
		cin >> r;
		fl = 0;
		proc.reset();
		for (int i = 0; i < r-1; i++, proc.goNext()) {
			if (proc.isEnd()) {
				fl = 1;
				break;
			}
		}
		if (r == 0) {
			return;
		}
		if (fl) {
			cout << " Enter correct line :\n";
		}else {
			break;
		}
	}
	nd = -1;
	ls = -1;
	cout << " Delete Next (1) / Down (2) ?\n";
	while (1) {
		cin >> nd;
		if (nd == 0) {
			return;
		}
		if (nd != 1 && nd != 2) {
			cout << " Enter correct code of operation :\n";
		}else {
			break;
		}
	}
	try{
		if (nd == 1) {
			proc.delNext();
		}
		else {
			proc.delDown();
		}
	}
	catch (...) {
		cout << "Cant delete in this position\n";
		Sleep(1300);
	}
	
}

void TextProcess() {
	TNode::InitMem();
	TText proc;
	proc.Load("input.txt");
	int r;
	while (1) {
		proc.Print();
		cout << " Operators: INS (1), DEL (2), EXIT (0)\n";
		cin >> r;
		switch (r) {
		case 1:
			InsOperator(proc);
			break;
		case 2:
			DelOperator(proc);
			break;
		}
		if (r == 0)
			break;
		clrscr();
	}
	TNode::PrintFreeLinks();
	cout << "Clean left memory.\n";
	TNode::CleanMem(proc);
	TNode::PrintFreeLinks();
}

TMem TNode::mem;

int main() {
	TextProcess();
}