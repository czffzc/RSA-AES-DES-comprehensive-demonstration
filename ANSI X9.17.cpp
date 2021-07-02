/*伪随机数比特生成器*/
#define _CRT_SECURE_NO_WARNINGS
#include "DES.h"
#include<string.h>
#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;
bitset<64> s;
/*
输入：随机64bit种子 s，整数m，两个DES密钥k1，k2
返回 m个64bit xi,   xi需要动态内存申请 ，返回需要保存下来的s
*/
void ANSI(bitset<64>s,int m,string key1,string key2,bitset<64>* x)
{
	char DTBuffer[9]; // 当前时间
	memset(DTBuffer, 0, 9);
	//?获取当前时间，每次计算时都会改变
	SYSTEMTIME st;
	GetLocalTime(&st);
	sprintf(DTBuffer, "%2d%2d%2d%2d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	// 三重DES加密
	//bitset<64> encrypt3DES(string C, string Key)
	bitset<64>I = encrypt3DES(string(DTBuffer),key1+key2);
	/*DES(DTBuffer, Key1, TRUE);
	DES(DTBuffer, Key2, FALSE);
	DES(DTBuffer, Key1, TRUE);*/
	// 保存结果到临时数组I
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
用于测试ANSI算法
*/

//第一个s随机生成，后面的s更新之后存储起来。


int ANSI_test()
{

	srand((unsigned)time(NULL));//系统时间初始化种子
	for (int i = 0; i < 64; i++) {
		s[i] = rand() % 2;
	}
	//随机产生
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