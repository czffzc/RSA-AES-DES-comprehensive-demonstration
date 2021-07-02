#include"Bob.h"
#include "DES.h"
#include "AES.h"
#include "ANSI X9.17.h"
#include <NTL/ZZ.h>
#include <fstream>
#include<string.h>
#include<string>
#include <bitset>
extern bitset<64> s;
Bob::Bob()
{
    //ctor
}

Bob::~Bob()
{
    //dtor
}

ZZ Bob::compute_c1(bitset<128>k, Bob bob)
{
	ZZ c1, K(0);
	ZZ j(1);
	for (int i = 0; i < 128; i++) {
		K += k[i] * j;
		j = j * 2;
	}
	c1 = PowerMod(K, bob.B, bob.N);
	return c1;
}

/*
生成128bit的随机数k最为临时的会话密钥
*/
bitset<128> Bob::gen_k(string key1, string key2 )
{
	srand((unsigned)time(NULL));//系统时间初始化种子
	for (int i = 0; i < 64; i++) {
		s[i] = rand() % 2;
	}//随机产生s
	bitset<128> k;
	int m = 2;
	bitset<64>* x = new bitset<64>[m];

	ANSI(s, m, key1, key2, x);

	for (int i = 0; i < 64; i++) {
		k[i] = x[0][i];
	}
	for (int i = 64; i < 128; i++) {
		k[i] = x[1][i - 64];
	}
	return k;
}

//PKCS7Padding的填充方式为当数据长度不足数据块长度时, 缺几位补几个几,
void PKCS7Padding(string in_filename)
{
	long int size = 0;
	ifstream fin(in_filename.c_str(), ios::binary);
	if (!fin) {
		cout << "输入文件"<< in_filename.c_str()<<"打开失败" << endl;
		exit(1);
	}
	ofstream fout("m_padding.txt", ios::binary);
	if (!fout) {
		cout << "输出文件打开失败！" << endl;
		exit(1);
	}

	if (fin.is_open()) {
		fin.seekg(0, ios::end);
		size = fin.tellg();
		cout << "要进行填充的文件大小为：" << dec<<size <<"字节"<< endl;
	}
	long int block_num = size / BLOCK_SIZE + 1;
	long int k = size % BLOCK_SIZE;
	long int j = size / BLOCK_SIZE;
	long int padding = BLOCK_SIZE - k;
	cout << "填充字符为：" << padding<<endl;
	fin.seekg(0, ios::beg);
	char ch;
	while (fin.get(ch)) {
		fout.put(ch);
		//cout << ch;
	}
	for (long int i = 0; i < padding; i++)
		fout.put(padding);
	fin.close();
	fout.close();
}

//用k加密文件m得到c2，c2保存在一个新的文件中
void Bob::compute_c2(bitset<128> k, string in_filename)
{

	PKCS7Padding(in_filename);

	ifstream fin("m_padding.txt", ios::binary);//是填充过的文件
	if (!fin) {
		cout << "输入文件打开失败" << endl;
		exit(1);
	}
	ofstream fout("c2.txt", ios::binary);
	if (!fout) {
		cout << "输出文件打开失败！" << endl;
		exit(1);
	}
	//先用PSCS7Padding，然后再用AES算法加密
	byte key[16];
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < 8; j++) {
			key[i][j] = k[i * 8 + j];
		}
	cout << "密钥是k：";
	for (int i = 0; i < 16; ++i)
		cout << hex << key[i].to_ulong() << " ";
	cout << endl;
	word w[4 * (Nr + 1)];
	KeyExpansion(key, w);

	byte plain[16];
	char temp[16];
	while (fin.read(temp, sizeof(temp))) {
		for (int i = 0; i < BLOCK_SIZE; i++)
			for (int j = 0; j < 8; j++) {
				plain[i] = charToBitset64(temp[i]);
			}

		encrypt(plain, w);//加密一组明文
		//把加密后的一组明文写入文件c2,bitset<8>转化为char
		for (int i = 0; i < BLOCK_SIZE; i++)
		{
			int t = 0, m = 1;
			for (int k = 0; k < 8; k++) {
				t = t + plain[i][k] * m;
				m = m * 2;
			}
			temp[i] = char(t);
		}
		fout.write(temp, sizeof(temp));
	}
	fin.close();
	fout.close();
}