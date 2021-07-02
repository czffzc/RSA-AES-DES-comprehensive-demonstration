#pragma once
#include <iostream>  
#include <bitset>  
#include <string>  
using namespace std;
typedef bitset<8> byte;
typedef bitset<32> word;

const int Nr = 10;  // AES-128��Ҫ 10 �ּ���  
const int Nk = 4;   // Nk ��ʾ������Կ�� word ����  

/**
 *  ����
 */
void encrypt(byte in[4 * 4], word w[4 * (Nr + 1)]);

/**
 *  ����
 */
void decrypt(byte in[4 * 4], word w[4 * (Nr + 1)]);

void KeyExpansion(byte key[4 * Nk], word w[4 * (Nr + 1)]);
int TEST_AES();