#include <iostream>
#include <cstdio>
#include <NTL/ZZ.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <bitset>
#include <random>
#include "common_tools.h"
using namespace NTL;
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_end(void)
{
	const char* prompt = "请输入End继续...";
	char input_str[1024];

	while (1) {
		cout << prompt;
		cin >> input_str;

		/* 清空缓冲区 */
		cin.clear();
		cin.ignore(1024, '\n');
		//		fgets(input_str, sizeof(input_str), stdin);

				/* 输入在合理范围内则退出输入循环 */
		if (_strcmpi(input_str, "end") == 0)
			break;
	}

	return;
}
//打印菜单中选中的字符串
const char* game6789_get_menuitem(const char* menu[], const char sel)
{
	int i;
	for (i = 0; menu[i]; i++)
		if (menu[i][0] == sel) //每个菜单字符串的第[0]个字符是否选择项
			return menu[i];
	return NULL;
}

long witness(const ZZ& n, const ZZ& x)
{
	ZZ m, y, z;
	long j, k;

	if (x == 0) return 0;

	// compute m, k such that n-1 = 2^k * m, m odd:

	k = 1;
	m = n / 2;
	while (m % 2 == 0) {
		k++;
		m /= 2;
	}

	z = PowerMod(x, m, n); // z = x^m % n
	if (z == 1) return 0;

	j = 0;
	do {
		y = z;
		z = (y * y) % n;
		j++;
	} while (j < k && z != 1);

	return z != 1 || y != n - 1;
}

//素性检测，t为测试次数
long PrimeTest(const ZZ& n, long t)
{
	if (n <= 1) return 0;

	// first, perform trial division by primes up to 2000

	PrimeSeq s;  // a class for quickly generating primes in sequence
	long p;

	p = s.next();  // first prime is always 2
	while (p && p < 2000) {
		if ((n % p) == 0) return (n == p);
		p = s.next();
	}

	// second, perform t Miller-Rabin tests

	ZZ x;
	long i;

	for (i = 0; i < t; i++) {
		x = RandomBnd(n); // random number between 0 and n-1

		if (witness(n, x))
			return 0;
	}

	return 1;
}
void test_prime()
{
	ZZ n;

	cout << "n: ";
	cin >> n;

	if (PrimeTest(n, 10))
		cout << n << " is probably prime\n";
	else
		cout << n << " is composite\n";
}
//生成长度为length的随机字符串
string strRand(int length) {			// length: 产生字符串的长度
	char tmp;							// tmp: 暂存一个随机数
	string buffer;						// buffer: 保存返回值

	// 下面这两行比较重要:
	std::random_device rd;					// 产生一个 std::random_device 对象 rd
	std::default_random_engine random(rd());	// 用 rd 初始化一个随机数发生器 random

	for (int i = 0; i < length; i++) {
		tmp = random() % 36;	// 随机一个小于 36 的整数，0-9、A-Z 共 36 种字符
		if (tmp < 10) {			// 如果随机数小于 10，变换成一个阿拉伯数字的 ASCII
			tmp += '0';
		}
		else {				// 否则，变换成一个大写字母的 ASCII
			tmp -= 10;
			tmp += 'A';
		}
		buffer += tmp;
	}
	return buffer;
}

