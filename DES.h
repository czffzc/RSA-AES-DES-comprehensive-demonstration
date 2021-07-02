#pragma once

#include<bitset>
#include<string.h>
using namespace std;
/*
64bit ����  64bit��Կ
*DES����
*/

bitset<64> encryptDES(bitset<64>& plain, bitset<64>key);

/*
64bit ����  64bit��Կ
*DES����
*/

bitset<64> decryptDES(bitset<64>& cipher, bitset<64>key);


/*
* 
*3DES���� �����Դ����ַ������߶���������
*/

bitset<64> encrypt3DES(string C, string Key);
bitset<64> encrypt3DES(bitset<64> plain, string Key);

/*
*3DES����
*/
bitset<64> decrypt3DES(bitset<64> M, string Key);
/*
*bitsetתΪ16�������
*/
void BitsetTochar(bitset<64>plain);


/*
*1λcharת��8λ������
*/
bitset<8> charToBitset64(const char c);
/*
*8λcharת��64λ������
*/
bitset<64> charToBitset64(const char s[8]);

/*
*16λcharת��128λ������
*/
bitset<128> charToBitset128(const char s[16]);