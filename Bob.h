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
	//生成128bit的随机数k最为临时的会话密钥

	bitset<128> gen_k(string key1 = "12345678", string key2 = "abcdefgh");

	ZZ compute_c1(std::bitset<128> k, Bob bob);//c1=k^bob.b mod bob.n
	//PKCS7Padding的填充方式为当数据长度不足数据块长度时, 缺几位补几个几,

	//用k加密文件m得到c2，c2保存在一个新的文件中
	void compute_c2(bitset<128> k, string in_filename);
private:
	ZZ C1, C2;
};

