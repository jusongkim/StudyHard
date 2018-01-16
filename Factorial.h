#pragma once

#define MAX_STACK 15

HANDLE m_hPushEvent;
HANDLE m_hPopEvent;

int m_nInData = 1;
int m_nSavePush = 0;
int m_nSavePop = 0;

BOOL m_bEnd = FALSE;

class Stack
{
public:
	Stack() : pnArray(NULL), nTop(0) {};
	int* pnArray;
	int nTop;

	BOOL Push(int data); //return true is succes
	int Pop();
	void Print();
};

Stack m_Stack;