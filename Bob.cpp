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
����128bit�������k��Ϊ��ʱ�ĻỰ��Կ
*/
bitset<128> Bob::gen_k(string key1, string key2 )
{
	srand((unsigned)time(NULL));//ϵͳʱ���ʼ������
	for (int i = 0; i < 64; i++) {
		s[i] = rand() % 2;
	}//�������s
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

//PKCS7Padding����䷽ʽΪ�����ݳ��Ȳ������ݿ鳤��ʱ, ȱ��λ��������,
void PKCS7Padding(string in_filename)
{
	long int size = 0;
	ifstream fin(in_filename.c_str(), ios::binary);
	if (!fin) {
		cout << "�����ļ�"<< in_filename.c_str()<<"��ʧ��" << endl;
		exit(1);
	}
	ofstream fout("m_padding.txt", ios::binary);
	if (!fout) {
		cout << "����ļ���ʧ�ܣ�" << endl;
		exit(1);
	}

	if (fin.is_open()) {
		fin.seekg(0, ios::end);
		size = fin.tellg();
		cout << "Ҫ���������ļ���СΪ��" << dec<<size <<"�ֽ�"<< endl;
	}
	long int block_num = size / BLOCK_SIZE + 1;
	long int k = size % BLOCK_SIZE;
	long int j = size / BLOCK_SIZE;
	long int padding = BLOCK_SIZE - k;
	cout << "����ַ�Ϊ��" << padding<<endl;
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

//��k�����ļ�m�õ�c2��c2������һ���µ��ļ���
void Bob::compute_c2(bitset<128> k, string in_filename)
{

	PKCS7Padding(in_filename);

	ifstream fin("m_padding.txt", ios::binary);//���������ļ�
	if (!fin) {
		cout << "�����ļ���ʧ��" << endl;
		exit(1);
	}
	ofstream fout("c2.txt", ios::binary);
	if (!fout) {
		cout << "����ļ���ʧ�ܣ�" << endl;
		exit(1);
	}
	//����PSCS7Padding��Ȼ������AES�㷨����
	byte key[16];
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < 8; j++) {
			key[i][j] = k[i * 8 + j];
		}
	cout << "��Կ��k��";
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

		encrypt(plain, w);//����һ������
		//�Ѽ��ܺ��һ������д���ļ�c2,bitset<8>ת��Ϊchar
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