#pragma once

#include<iostream>
#include<fstream>
#include"TStack.h"

using namespace std;

class TText {
private:
	TNode* pFirst, * pCurr;
	TStack st;
	TStack deleted;

	void PrintRec(int o){
		if (pCurr != nullptr) {
			cout << string(o*2, ' ') ;
			cout << pCurr->str << "\n";
			if (pCurr->pDown != nullptr) {
				//cout << string(o*2, ' ') << "{\n";
				goDownNode();
				PrintRec(o+1);
				//cout << string(o*2, ' ') << "}\n";
			}
			goNextNode();
			PrintRec(o);
		}
		if(!st.empty())
			retBack();
	}
	TNode* ReadRec(ifstream& fin) {
		TNode *pHead=nullptr, *pTemp=nullptr;
		char str[101];
		while (!fin.eof()) {
			fin.getline(str, 101, '\n');
			if (str[0] == '{') {
				pTemp->pDown = ReadRec(fin);
				continue;
			}
			if (str[0] == '}') {
				break;
			}
			if (pHead == nullptr) {
				pHead = pTemp = new TNode(str);
			}
			else {
				pTemp->pNext = new TNode(str);
				pTemp = pTemp->pNext;
			}
		}
		return pHead;
	}

public:
	TText() {
		pFirst = pCurr = nullptr;
	}
	~TText() {
		goFirst();
		while (pCurr != pFirst || haveDown() || haveNext()) {
			if (haveNext()) {
				goNextNode();
				st.back()->pNext = nullptr;
				continue;
			}
			if (haveDown()) {
				goDownNode();
				st.back()->pDown = nullptr;
				continue;
			}
			delete pCurr;
			retBack();
		}
		if(pFirst!=nullptr)
			delete pFirst;
	}
	void goNextNode() {
		if (pCurr == nullptr)
			throw "Empty Node";
		st.push(pCurr);
		pCurr = pCurr->pNext;
	}
	void goDownNode() {
		if (pCurr == nullptr)
			throw "Empty Node";
		st.push(pCurr);
		pCurr = pCurr->pDown;
	}
	void retBack() {
		if (st.empty()) {
			throw "Cant go back";
		}
		pCurr = st.pop();
	}
	void goFirst() {
		st.clear();
		pCurr = pFirst;
	}
	bool haveNext() {
		if (pCurr == nullptr) {
			throw "Empty Node";
		}
		return pCurr->pNext != nullptr;
	}
	bool haveDown() {
		if (pCurr == nullptr) {
			throw "Empty Node";
		}
		return pCurr->pDown != nullptr;
	}
	void InsNextLine(char *_str) {
		if (pCurr == nullptr)
			throw "Empty Node";
		TNode* nnew=new TNode(_str);
		nnew->pNext = pCurr->pNext;
		pCurr->pNext = nnew;
	}
	void InsDownLine(char *_str) {
		if (pCurr == nullptr)
			throw "Empty Node";
		TNode* nnew=new TNode(_str);
		nnew->pNext = pCurr->pDown;
		pCurr->pDown = nnew;
	}
	void InsNextSection(char *_str) {
		if (pCurr == nullptr)
			throw "Empty Node";
		TNode* nnew=new TNode(_str);
		nnew->pDown = pCurr->pNext;
		pCurr->pNext = nnew;
	}
	void InsDownSection(char *_str) {
		if (pCurr == nullptr)
			throw "Empty Node";
		TNode* nnew=new TNode(_str);
		nnew->pDown = pCurr->pDown;
		pCurr->pDown = nnew;
	}
	void delNext() {
		if (pCurr == nullptr)
			throw "Empty Node";
		if (pCurr->pNext == nullptr)
			throw "Haven't next node";
		deleted.push(pCurr->pNext);
		pCurr->pNext = pCurr->pNext->pNext;
	}
	void delDown() {
		if (pCurr == nullptr)
			throw "Empty Node";
		if (pCurr->pDown == nullptr)
			throw "Haven't down node";
		deleted.push(pCurr->pDown);
		pCurr->pDown = pCurr->pDown->pNext;
	}
	string GetCurr() {
		if (pCurr == nullptr)
			throw "not valid index";
		string s(pCurr->str);
		return s;
	}

	void clearDeleted() {
		while (!deleted.empty()) {
			TNode* del = deleted.pop();
			if (del->pDown != nullptr) {
				deleted.push(del->pDown);
			}
			if (del->pNext != nullptr) {
				deleted.push(del->pNext);
			}
			delete del;
		}
	}

	void Print() {
		goFirst();
		PrintRec(0);
	}
	void Load(string s) {
		ifstream fin;
		fin.open(s);

		pFirst = ReadRec(fin);
		fin.close();
	}

	void reset() {
		st.clear();
		if (pFirst == nullptr)
			return;
		st.push(pFirst);
		pCurr = pFirst;
		if(pCurr->pNext!=nullptr)
			st.push(pCurr->pNext);
		if(pCurr->pDown!=nullptr)
			st.push(pCurr->pDown);
	}
	bool isEnd() {
		return st.empty();
	}
	void goNext() {
		if (st.empty())
			throw "Not valid index of text";
		pCurr = st.pop();
		if (pCurr != pFirst) {
			if (pCurr->pNext != nullptr)
				st.push(pCurr->pNext);
			if (pCurr->pDown != nullptr)
				st.push(pCurr->pDown);
		}
	}

};