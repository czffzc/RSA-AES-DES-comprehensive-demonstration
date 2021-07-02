#pragma once
#include <iostream>
#include<fstream>
#include <random>
#include <NTL/ZZ.h>
#include "Keys.h"
#include<bitset>
#include"ANSI X9.17.h"
#define BLOCK_SIZE 16
using namespace NTL;
class Alice
{
public:
	Alice();
	virtual ~Alice();
	void setA(ZZ value);
	void setP(ZZ value);
	void setQ(ZZ value);
	void setN(ZZ value);
	ZZ getA();
	ZZ getP();
	ZZ getQ();
	void Gen_key(int length=512);//产生密钥p,q,n,a,b：随机素数p、q 默认长度为512
	//ZZ compute_c1(bitset<128>k);
	ZZ B, N;//公钥
	bitset<128> de_c1_get_k(ZZ c1, Alice alice);//用Alice的RSA私钥解密c1得到k，k=c1^a mod n
	void de_c2_to_m(bitset<128> k, string out_filename = "result.jpg");//用k解密c2得到m
private:
	Keys key;
	ZZ A, P, Q;//私钥
};
/*去填充*/
void de_PKCS7Padding2(string out_filename);