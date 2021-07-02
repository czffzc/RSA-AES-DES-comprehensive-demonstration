/*α���������������*/
#define _CRT_SECURE_NO_WARNINGS
#include "DES.h"
#include<string.h>
#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;
bitset<64> s;
/*
���룺���64bit���� s������m������DES��Կk1��k2
���� m��64bit xi,   xi��Ҫ��̬�ڴ����� ��������Ҫ����������s
*/
void ANSI(bitset<64>s,int m,string key1,string key2,bitset<64>* x)
{
	char DTBuffer[9]; // ��ǰʱ��
	memset(DTBuffer, 0, 9);
	//?��ȡ��ǰʱ�䣬ÿ�μ���ʱ����ı�
	SYSTEMTIME st;
	GetLocalTime(&st);
	sprintf(DTBuffer, "%2d%2d%2d%2d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	// ����DES����
	//bitset<64> encrypt3DES(string C, string Key)
	bitset<64>I = encrypt3DES(string(DTBuffer),key1+key2);
	/*DES(DTBuffer, Key1, TRUE);
	DES(DTBuffer, Key2, FALSE);
	DES(DTBuffer, Key1, TRUE);*/
	// ����������ʱ����I
	//x=(bitset<64>)mallocx[m];
	for (int i = 0; i < m; i++) {
		x[i] = encrypt3DES(I^s,key1+key2);
		s= encrypt3DES(x[i]^I, key1 + key2);
	}
	/*cout << x[0].to_string() << endl;
	cout << x[1].to_string() << endl;*/
	//return s;
}
/*
���ڲ���ANSI�㷨
*/

//��һ��s������ɣ������s����֮��洢������


int ANSI_test()
{

	srand((unsigned)time(NULL));//ϵͳʱ���ʼ������
	for (int i = 0; i < 64; i++) {
		s[i] = rand() % 2;
	}
	//�������
	//string key = "12345678abcdefgh";
	string key1 = "12345678";
	string key2 = "abcdefgh";
	int m = 15;
	bitset<64>* x = new bitset<64>[m];
	ANSI(s,m,key1,key2,x);
	delete[] x;

	for (int i = 0; i < m; i++) {
		BitsetTochar(x[i]);
	}
	return 0;
}