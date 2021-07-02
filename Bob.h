#pragma once
#include <iostream>
#include <random>
#include <NTL/ZZ.h>
#include "Keys.h"
#include <string.h>
#include <bitset>
#define BLOCK_SIZE 16
using namespace NTL;
using namespace std;
void PKCS7Padding(string in_filename);
class Bob
{
public:
	Bob();
	virtual ~Bob();
	ZZ B,N;
	//ZZ compute_c1(bitset<128> k,ZZ e, ZZ m);	
	//����128bit�������k��Ϊ��ʱ�ĻỰ��Կ

	bitset<128> gen_k(string key1 = "12345678", string key2 = "abcdefgh");

	ZZ compute_c1(std::bitset<128> k, Bob bob);//c1=k^bob.b mod bob.n
	//PKCS7Padding����䷽ʽΪ�����ݳ��Ȳ������ݿ鳤��ʱ, ȱ��λ��������,

	//��k�����ļ�m�õ�c2��c2������һ���µ��ļ���
	void compute_c2(bitset<128> k, string in_filename);
private:
	ZZ C1, C2;
};

