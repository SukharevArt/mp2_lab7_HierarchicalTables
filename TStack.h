#pragma once
#include"TNode.h"
struct stackNode
{
	TNode* val;
	stackNode* pNext;
};

class TStack {
	stackNode* pHead;
public:
	TStack() {
		pHead = nullptr;
	}
	~TStack() {
		while (pHead!=nullptr) {
			stackNode* del = pHead;
			pHead = pHead->pNext;
			delete del;
		}
	}	
	void clear() {
		while (pHead!=nullptr) {
			stackNode* del = pHead;
			pHead = pHead->pNext;
			delete del;
		}
	}
	void push(TNode* _val) {
		stackNode* newn = new stackNode;
		newn->val = _val;
		newn->pNext = pHead;
		pHead = newn;
	}
	TNode* pop() {
		if (pHead == nullptr) {
			throw "empty stack";
		}
		stackNode* del = pHead;
		TNode* tt = pHead->val;
		pHead = pHead->pNext;
		delete del;
		return tt;
	}
	TNode* back() {
		if (pHead == nullptr) {
			throw "empty stack";
		}
		return pHead->val;
	}
	bool empty() {
		return pHead == nullptr;
	}
};