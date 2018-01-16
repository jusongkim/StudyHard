// Factorial.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//
#include "stdafx.h"
#include "afxmt.h"
#include "Factorial.h"

#include <windows.h>
#include <process.h>
#include <ctime>


DWORD WINAPI PushThreadProc(LPVOID lpParam)
{
	BOOL bStop = FALSE;

	while (!bStop)
	{
		::WaitForSingleObject(m_hPushEvent, INFINITE);
		
		int nRan = 0;
		if (m_nSavePush <= 0)
		{
			nRan = rand() % m_nInData + 1;

			for (int i = 0; i < nRan; i++)
				m_Stack.Push(i + 1);

			m_nSavePush = m_nInData - nRan;
		}
		else
		{
			nRan = rand() % m_nSavePush + 1;

			for (int i = 0; i < nRan; i++)
				m_Stack.Push(i + (m_nInData - m_nSavePush + 1));

			m_nSavePush = abs(m_nSavePush - nRan);
		}

		SetEvent(m_hPopEvent);

		//������
		if ( m_bEnd )
			bStop = TRUE;
	}

	return 0;
}

DWORD WINAPI PopThreadProc(LPVOID lpParam)
{	
	BOOL bStop = FALSE;
		
	while (!bStop)
	{
		::WaitForSingleObject(m_hPopEvent, INFINITE);
		
		int nRan = 1;

		if (m_Stack.nTop > 0)
		{
//			srand((unsigned int)time(NULL));
			nRan = rand() % (m_Stack.nTop) + 1;
		}

		if (m_nSavePush == 0)
			nRan = m_Stack.nTop;

		for (int i = 0; i < nRan; i++)
			printf("%d ", m_Stack.Pop());

		if (m_nSavePush == 0 )
			printf("\n");

		SetEvent(m_hPushEvent);

		//������
		if (m_bEnd)
			bStop = TRUE;
	}
	
	
	//m_hPushEvent.SetEvent();

	return 0;
}


BOOL Stack::Push(int data)
{
	if (pnArray == NULL)
		return FALSE;

	if (nTop == m_nInData)
		return FALSE;

	pnArray[nTop++] = data;

	return TRUE;
}

int Stack::Pop()
{
	if (pnArray == NULL)
		return 0;

	if (nTop == -1)
		return 0;

	return pnArray[--nTop];
}

void Stack::Print()
{
	if (pnArray == NULL)
		return;

	for (int i = 0; i < nTop; i++)
		printf("%d ", pnArray[i]);

	printf("\n");
}


int main()
{
	/////////////////////////////////////////////
	// Push������ = ���ÿ� �Էµ� N�� 1~N������ ���ڸ� ������� �״´�.
	// Pop������ = ���ÿ��� ���ڸ� ������ ����Ѵ�
	// *Push,Pop�����尣 push,pop�� �Ͼ�� �ð� ������ ���� �����ϴ�.

	/////////////////////////////////////////////
	//
	// Push, Pop ������ �� ����ȭ �̺�Ʈ ����
	//
	/////////////////////////////////////////////
	m_hPushEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (m_hPushEvent == NULL)
		return -1;
	m_hPopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (m_hPopEvent == NULL)
		return -1;

	HANDLE hThread[2];
	DWORD dwThreadID[2];

	hThread[0] = (HANDLE)CreateThread(NULL, 0, PushThreadProc, NULL, 0, &dwThreadID[0]);
	if (hThread[1] == NULL)
		return -1;

	hThread[1] = (HANDLE)CreateThread(NULL, 0, PopThreadProc, NULL, 0, &dwThreadID[1]);
	if (hThread[0] == NULL)
		return -1;
	
	while (m_nInData)
	{
		// N�� �Է�
		while (TRUE)
		{
			scanf("%d", &m_nInData);
			if (m_nInData > 0 && m_nInData <= 16)
			{
				break;
			}
			else if (m_nInData == 0)
			{
				return 0;
			}
			else
			{
				// �Է°��� 0~16�� ������ ���´�.
			}
		}

		// Nũ���� ���� �޸� �Ҵ�
		m_Stack.pnArray = (int*)malloc(sizeof(int) * m_nInData);

		SetEvent(m_hPushEvent);
		WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

		// ��� ��
		if (m_Stack.pnArray != NULL)
			free(m_Stack.pnArray);
	}

	if (m_Stack.pnArray != NULL)
		free(m_Stack.pnArray);

//	GetExitCodeThread(hPopThread, 0);
//	GetExitCodeThread(hPushThread, 0);

	for (int i = 0; i < 2; i++)
	{
		if (hThread[i] != NULL)
			CloseHandle(hThread[i]);
	}

	return 0;
}

// īŻ�� ��
/*
using namespace std;

void findAllCases(vector<string>& results, char str[], int strCnt, int pushCnt, int popCnt)
{
	if (pushCnt < 0 || popCnt < 0)
		return;

	if (pushCnt == 0 && popCnt == 0)
	{
		str[strCnt] = 0;
			results.push_back(str);
		return;
	}

	if (pushCnt > 0)
	{
		str[strCnt] = 'A';
			findAllCases(results, str, strCnt + 1, pushCnt - 1, popCnt);
	}

	if (pushCnt < popCnt)
	{
		str[strCnt] = 'B';
			findAllCases(results, str, strCnt + 1, pushCnt, popCnt - 1);
	}
}

int main()
{
	char str[1000];
	vector<string> results;

	findAllCases(results, str, 0, 3, 3);
	string abc;
	int a=0;
	for (int i = 0; i < results.size(); i++)
	{
		//printf("%s\n", results[i]);
		cout << results[i] << endl;
		a++;
	}
	printf("%d", a);

	return 0;
}
*/

// ���丮��
/*
int T[10]; //nPr�� �̷�� ������ ��츦 ����
int data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

void swap(int *i, int *j) {
	int temp = *i;
	*i = *j;
	*j = temp;
}
//T[]���� q�� ���
void process(int q) {
	for (int i = q - 1; i >= 0; i--) {
		printf("%d ", T[i]);		
	}
	printf("\n");
}
//data[]���� �տ������� n���� ���� �� r���� �����ؼ� ������ ����ϴ� �Լ�. q�� ��� �� ��� ���� ����
void Perm(int n, int r, int q) {
	if (r == 0) {
		process(q);
		return;
	}
	for (int i = n - 1; i >= 0; i--) {
		swap(&data[i], &data[n - 1]); //n-1�� ��� index�� swap�ؼ� �پ��� ������ �����.
		T[r - 1] = data[n - 1];		  //T�� �ڿ������� ����� ����	
		Perm(n - 1, r - 1, q);		  //����  index�� ���� 	
		swap(&data[i], &data[n - 1]);
	}
}

int main() {
	Perm(10, 10, 10);
	return 0;
}
*/