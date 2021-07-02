// RSA_BH.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <NTL/ZZ.h>
#include "common_tools.h"
#include <string>
#include "DES.h"
#include "ANSI X9.17.h"
#include <math.h>
#include "Alice.h"
#include "Bob.h"
#include "AES.h"
#include <fstream>
#include <conio.h>
using namespace NTL;
using namespace std;
extern bitset<64> s;
#define BLOCK_SIZE 16
#define length1 512
#define length2 1024
void process(string k1,string k2,string in_filename,string out_filename,int length=512)
{
	Alice alice;
	cout << endl << "一、Alice生成一对RSA公钥(n,b)和私钥(p,q,a)" << endl;
	alice.Gen_key(length);

	cout << endl<<"二、Alice把公钥传输给Bob" << endl;
	Bob bob;
	bob.B = alice.B;
	bob.N = alice.N;

	cout << endl << "三、Bob收到公钥(b,n)" << endl;
	cout << "b = " << bob.B << endl;
	cout << "n = " << bob.N << endl;

	cout << endl << "四、生成128bit随机数作为临时密钥k" << endl;
	bitset<128> k;
	k = bob.gen_k(k1, k2);
	cout << "k = " << k.to_string() << endl;

	cout << endl << "五、用Alice的公钥加密k得到c1" << endl;
	ZZ c1 = bob.compute_c1(k, bob);
	cout << "c1 = " << c1 << endl;

	cout << endl << "六、用会话密钥k加密文件m得到c2" << endl;
	bob.compute_c2(k, in_filename);

	cout << endl << "七、把(c1,c2)发给Alice" << endl;


	cout << endl << "八、Alice用Alice的RSA私钥解密c1得到k" << endl;
	k = alice.de_c1_get_k(c1, alice);
	cout << "k = " << k << endl;

	cout << endl << "九、用k解密c2得到m" << endl;
	alice.de_c2_to_m(k, out_filename);

	cout << endl << "十、输出m" << endl<<endl;
}
int main() {
	string in_filename = "m.txt", out_filename = "result.txt";
	string k1 = "12345678", k2 = "abcdefgh";
	int length = 512;
	//随机生成ANSI算法中要用到的DES初始密钥k1,k2
	k1 = strRand(8);
	k2 = strRand(8);
	bool loop = true;
	while (loop) {
		int sel = menu();
		switch (sel) {
			case 0:
				loop = false;
				break;
			case 1:
				cout << "请输入需要加密文件的文件名/文件路径：" << endl;
				cin >> in_filename;
				cout << "请输入解密出来保存的文件名/文件路径：" << endl;
				cin >> out_filename;
				cout << "已读入文件名" << endl;
				wait_for_end();
				break;
			case 2:
				cout << "请输入随机生成ANSI算法中要用到的DES初始密钥k1,k2：（k1,k2各64bit，如k1=12345678,k2=abcdefgh）" << endl;
				cin >> k1 >> k2;
				wait_for_end();
				break;
			case 3:
				while (1) {
					cout << "请选择随机素数p、q的长度,输入“1”表示512，输入“2”表示1024(默认512bit)：" << endl;
					char sel;
					sel = _getche();
					if (sel == '1') {
						length = 512;
						break;
					}
					else if (sel == '2') {
						length = 1024;
						break;
					}
					else
						cout << endl;
				}
				wait_for_end();
				break;
			case 4:
				cout << "输入文件：" << in_filename.c_str() << endl;
				cout << "输出文件：" << out_filename.c_str() << endl;
				cout << "DES初始密钥k1:" << k1.c_str() << " k2:" << k2.c_str() << endl;
				cout << "随机素数p、q的长度为:" <<length<< endl;
				process(k1, k2, in_filename, out_filename,length);
				wait_for_end();
				break;
			default:
				break;
		}
		system("cls");
	}
	
	return 0;
}

