#pragma once

#include<bitset>
#include<string.h>
using namespace std;
/*
64bit 明文  64bit密钥
*DES加密
*/

bitset<64> encryptDES(bitset<64>& plain, bitset<64>key);

/*
64bit 密文  64bit密钥
*DES解密
*/

bitset<64> decryptDES(bitset<64>& cipher, bitset<64>key);


/*
* 
*3DES加密 ，可以传入字符串或者二进制明文
*/

bitset<64> encrypt3DES(string C, string Key);
bitset<64> encrypt3DES(bitset<64> plain, string Key);

/*
*3DES解密
*/
bitset<64> decrypt3DES(bitset<64> M, string Key);
/*
*bitset转为16进制输出
*/
void BitsetTochar(bitset<64>plain);


/*
*1位char转成8位二进制
*/
bitset<8> charToBitset64(const char c);
/*
*8位char转成64位二进制
*/
bitset<64> charToBitset64(const char s[8]);

/*
*16位char转成128位二进制
*/
bitset<128> charToBitset128(const char s[16]);