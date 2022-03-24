#pragma once

struct TNode {
	char str[101];
	TNode* pNext, * pDown;
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
	}
	
};