#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

struct TNode;
struct TMem;
struct stackNode;
class TStack;
class TText;


struct TMem {
	TNode* pFirst, * pLast, * pFree;
};


struct TNode {
	char str[101];
	TNode* pNext, * pDown;
	bool Garbage;
	static TMem mem;
	TNode(char* _str = nullptr, TNode* _Next = nullptr, TNode* _Down = nullptr) {

		for (int i = 0; i < 100; i++) {
			if (_str != nullptr) {
				str[i] = *_str;
				_str++;
			}
			else {
				str[i] = '\0';
				break;
			}
		}
		str[100] = '\0';
		pNext = _Next;
		pDown = _Down;
		Garbage = false;
	}

	void* operator new (size_t size) {
		TNode* tmp = mem.pFree;
		mem.pFree = tmp->pNext;
		tmp->pNext = nullptr;
		return tmp;
	}
	void operator delete(void* p) {
		if (p == nullptr)
			return;
		TNode* tmp = (TNode*)p;
		tmp->pDown = nullptr;
		tmp->pNext = mem.pFree;
		mem.pFree = tmp;
	}
	static void InitMem(size_t size = 100) {
		if (size < 1 || size>1e6) {
			throw "Uncorrect size";
		}
		mem.pFirst = (TNode*) new char[sizeof(TNode) * size];
		mem.pFree = mem.pFirst;
		mem.pLast = mem.pFirst;
		for (int i = 0; i < size - 1; i++) {
			mem.pLast->pNext = mem.pLast + 1;
			mem.pLast->pDown = nullptr;
			mem.pLast->str[0] = '\0';
			mem.pLast++;
		}
		mem.pLast->pDown = nullptr;
		mem.pLast->pNext = nullptr;
	}
	static void CleanMem(TText& t);
	static void PrintFreeLinks() {
		TNode* tmp;
		tmp = mem.pFree;
		cout << "List of free links :\n";
		int k = 0;
		while (tmp != nullptr) {
			if (tmp->str[0] != '\0') {
				k++;
				cout << tmp->str << "\n";
			}
			tmp = tmp->pNext;
		}
		if (k == 0) {
			cout << "*empty\n";
		}
	}
};
