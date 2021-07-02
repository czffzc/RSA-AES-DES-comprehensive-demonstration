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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_end(void)
{
	const char* prompt = "������End����...";
	char input_str[1024];

	while (1) {
		cout << prompt;
		cin >> input_str;

		/* ��ջ����� */
		cin.clear();
		cin.ignore(1024, '\n');
		//		fgets(input_str, sizeof(input_str), stdin);

				/* �����ں���Χ�����˳�����ѭ�� */
		if (_strcmpi(input_str, "end") == 0)
			break;
	}

	return;
}
//��ӡ�˵���ѡ�е��ַ���
const char* game6789_get_menuitem(const char* menu[], const char sel)
{
	int i;
	for (i = 0; menu[i]; i++)
		if (menu[i][0] == sel) //ÿ���˵��ַ����ĵ�[0]���ַ��Ƿ�ѡ����
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

//���Լ�⣬tΪ���Դ���
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
//���ɳ���Ϊlength������ַ���
string strRand(int length) {			// length: �����ַ����ĳ���
	char tmp;							// tmp: �ݴ�һ�������
	string buffer;						// buffer: ���淵��ֵ

	// ���������бȽ���Ҫ:
	std::random_device rd;					// ����һ�� std::random_device ���� rd
	std::default_random_engine random(rd());	// �� rd ��ʼ��һ������������� random

	for (int i = 0; i < length; i++) {
		tmp = random() % 36;	// ���һ��С�� 36 ��������0-9��A-Z �� 36 ���ַ�
		if (tmp < 10) {			// ��������С�� 10���任��һ�����������ֵ� ASCII
			tmp += '0';
		}
		else {				// ���򣬱任��һ����д��ĸ�� ASCII
			tmp -= 10;
			tmp += 'A';
		}
		buffer += tmp;
	}
	return buffer;
}

