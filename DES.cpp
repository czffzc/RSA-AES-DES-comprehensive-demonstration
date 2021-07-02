#include<iostream>
#include<bitset>
#include<fstream>
#include<string.h>
using namespace std;


//初始置换PI
int IP[] =
{
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

//逆初始置换FP
int FP[] =
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

//密钥置换IP1 64->56
int PC1[] =
{
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

//密钥置换IP2 56->48
int PC2[] =
{
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

//左循环移位
int shiftbit[] =
{
   1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

//扩展置换E 32->48 
int E[] =
{
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

//S盒
int S[8][4][16] =
{
    //S1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    //S2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    //S3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    //S4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    //S5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    //S6
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    //S7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    //S8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

//置换运算P
int P[] =
{
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};
/*
*1位char转成8位二进制
*/
bitset<8> charToBitset64(const char c)
{
    bitset<8> bits;
        for (int j = 0; j < 8; ++j)
            bits[j] = ((c >> j) & 1);
    return bits;
}
/*
*8位char转成64位二进制
*/
bitset<64> charToBitset64(const char s[8])
{
    bitset<64> bits;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            bits[i * 8 + j] = ((s[i] >> j) & 1);
    return bits;
}

/*
*16位char转成128位二进制
*/
bitset<128> charToBitset128(const char s[16])
{
    bitset<128> bits;
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 8; ++j)
            bits[i * 8 + j] = ((s[i] >> j) & 1);
    return bits;
}
/*
*轮函数F 接受32位数据和48位子密钥，返回32位数据
*/
bitset<32> F(bitset<32> R, bitset<48> K)
{
    bitset<48> expandR;

    //扩展置换 32->48
    for (int i = 0; i < 48; i++)
        expandR[47 - i] = R[32 - E[i]];

    //异或
    expandR = expandR ^ K;

    //S盒运算
    bitset<32> R_1;
    int x = 0;
    for (int i = 0; i < 48; i = i + 6)
    {
        int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
        int col = expandR[47 - i - 1] * 8 + expandR[47 - i - 2] * 4 + expandR[47 - i - 3] * 2 + expandR[47 - i - 4];
        int num = S[i / 6][row][col];
        bitset<4> binary(num);
        R_1[31 - x] = binary[3];
        R_1[31 - x - 1] = binary[2];
        R_1[31 - x - 2] = binary[1];
        R_1[31 - x - 3] = binary[0];
        x += 4;
    }

    //P置换
    bitset<32>tmp = R_1;
    for (int i = 0; i < 32; ++i)
        R_1[31 - i] = tmp[32 - P[i]];

    return R_1;
}

/*
*28位密钥左移
*/

bitset<28> CShift(bitset<28> k, int shift)
{
    bitset<28> tmp = k;

    for (int i = 27; i >= 0; i--)
    {
        if (i - shift < 0)
            k[i] = tmp[i - shift + 28];
        else
            k[i] = tmp[i - shift];
    }
    return k;
}

/*
*生成子密钥
*/

void generateKeys(bitset<64>Key, bitset<48>subKey[])
{
    bitset<56> realKey;
    bitset<28> C;
    bitset<28> D;
    bitset<48> tmpkey;

    //去除校验位
    for (int i = 0; i < 56; ++i)
        realKey[55 - i] = Key[64 - PC1[i]];
    for (int round = 0; round < 16; ++round)
    {
        for (int i = 28; i < 56; ++i)
            C[i - 28] = realKey[i];
        for (int i = 0; i < 28; ++i)
            D[i] = realKey[i];

        // 左移
        C = CShift(C, shiftbit[round]);
        D = CShift(D, shiftbit[round]);

        //生成48位子密钥
        for (int i = 28; i < 56; ++i)
            realKey[i] = C[i - 28];
        for (int i = 0; i < 28; ++i)
            realKey[i] = D[i];

        for (int i = 0; i < 48; ++i)
            tmpkey[47 - i] = realKey[56 - PC2[i]];

        subKey[round] = tmpkey;
    }
}

/*
64bit 明文  64bit密钥
*DES加密
*/

bitset<64> encryptDES(bitset<64>& plain, bitset<64>key)
{
    bitset<64> cipher;
    bitset<64> currentBits;
    bitset<32> L;
    bitset<32> R;
    bitset<32> tmpL;
    bitset<48> subKey[16];

    generateKeys(key, subKey);

    //初始置换IP
    for (int i = 0; i < 64; ++i)
        currentBits[63 - i] = plain[64 - IP[i]];
    for (int i = 32; i < 64; ++i)
        L[i - 32] = currentBits[i];
    for (int i = 0; i < 32; ++i)
        R[i] = currentBits[i];

    //十六轮加密
    for (int round = 0; round < 16; ++round)
    {
        tmpL = R;
        R = L ^ F(R, subKey[round]);
        L = tmpL;
    }

    for (int i = 0; i < 32; ++i)
        cipher[i] = L[i];
    for (int i = 32; i < 64; ++i)
        cipher[i] = R[i - 32];

    //结尾置换FP
    currentBits = cipher;
    for (int i = 0; i < 64; ++i)
        cipher[63 - i] = currentBits[64 - FP[i]];

    return cipher;
}


/*
64bit 密文  64bit密钥
*DES解密
*/

bitset<64> decryptDES(bitset<64>& cipher, bitset<64>key)
{
    bitset<64> plain;
    bitset<64> currentBits;
    bitset<32> L;
    bitset<32> R;
    bitset<32> tmpL;
    bitset<48> subKey[16];

    generateKeys(key, subKey);
    //初始置换IP
    for (int i = 0; i < 64; ++i)
        currentBits[63 - i] = cipher[64 - IP[i]];

    for (int i = 32; i < 64; ++i)
        L[i - 32] = currentBits[i];
    for (int i = 0; i < 32; ++i)
        R[i] = currentBits[i];

    //十六轮加密
    for (int round = 0; round < 16; ++round)
    {
        tmpL = R;
        R = L ^ F(R, subKey[15 - round]);
        L = tmpL;
    }

    for (int i = 0; i < 32; ++i)
        plain[i] = L[i];
    for (int i = 32; i < 64; ++i)
        plain[i] = R[i - 32];

    //结尾置换FP
    currentBits = plain;
    for (int i = 0; i < 64; ++i)
        plain[63 - i] = currentBits[64 - FP[i]];

    return plain;
}

/*
*3DES加密
*/

bitset<64> encrypt3DES(string C, string Key)
{
    bitset<64>plain;
    bitset<128>key;
    bitset<64>Lkey;
    bitset<64>Rkey;
    bitset<64>cipher;
    bitset<64>tmp;


    plain = charToBitset64(C.c_str());
    key = charToBitset128(Key.c_str());

    for (int i = 64; i < 128; ++i)
        Lkey[i - 64] = key[i];
    for (int i = 0; i < 64; ++i)
        Rkey[i] = key[i];

    tmp = encryptDES(plain, Lkey);
    tmp = decryptDES(tmp, Rkey);
    cipher = encryptDES(tmp, Lkey);

    return cipher;
}


bitset<64> encrypt3DES(bitset<64> plain, string Key)
{
    //bitset<64>plain;
    bitset<128>key;
    bitset<64>Lkey;
    bitset<64>Rkey;
    bitset<64>cipher;
    bitset<64>tmp;


    //plain = charToBitset64(C.c_str());
    key = charToBitset128(Key.c_str());

    for (int i = 64; i < 128; ++i)
        Lkey[i - 64] = key[i];
    for (int i = 0; i < 64; ++i)
        Rkey[i] = key[i];

    tmp = encryptDES(plain, Lkey);
    tmp = decryptDES(tmp, Rkey);
    cipher = encryptDES(tmp, Lkey);

    return cipher;
}


/*
*3DES解密
*/

bitset<64> decrypt3DES(bitset<64> M, string Key)
{
    bitset<64>cipher;
    bitset<128>key;
    bitset<64>Lkey;
    bitset<64>Rkey;
    bitset<64>plain;
    bitset<64>tmp;

    cipher = M;
    key = charToBitset128(Key.c_str());

    for (int i = 64; i < 128; ++i)
        Lkey[i - 64] = key[i];
    for (int i = 0; i < 64; ++i)
        Rkey[i] = key[i];

    tmp = decryptDES(cipher, Lkey);
    tmp = encryptDES(tmp, Rkey);
    plain = decryptDES(tmp, Lkey);

    return plain;
}


/*
*bitset转为16进制输出
*/
void BitsetTochar(bitset<64>plain)
{
    int result[64];
    int byte[16];
    for (int i = 0; i < 64; i++)
        result[i] = plain[i];
    for (int j = 0; j < 16; j++)
    {
        int temp = result[j * 4] + result[j * 4 + 1] * 2 + result[j * 4 + 2] * 4 + result[j * 4 + 3] * 8;
        byte[j] = temp;
    }
    //cout << "解密结果为:"<<endl;
    for (int i = 0; i < 16; i++)
        cout << hex << byte[15 - i];
    cout << endl;
}


int DES_test()
{

    //测试DES
    bitset<64> M(0x893D51EC4B563B53);
    bitset<64> key1(0x0123456789ABCDEF);
    //P=4E6F772069732074 68652074696D6520 666F7220616C6C20
    //C=3FA40E8A984D4815 6A271787AB8883F9 893D51EC4B563B53
    cout << "Test DES" << endl << "M = 4E6F772069732074" << endl;
    cout << "key = 0123456789ABCDEF" << endl;

    bitset<64> temp_plain = decryptDES(M, key1);//
    cout << "C' = ";
    BitsetTochar(temp_plain);
    cout << endl;

    //测试3DES
    string C = "11111111";
    string key = "12345678abcdefgh";

    cout << "Test 3DES" << endl << "C = 3131313131313131" << endl;
    cout << "key1 = 12345678" << endl;
    cout << "key2 = abcdefgh" << endl;

    bitset<64> cipher = encrypt3DES(C, key);
    cout << "M = ";
    BitsetTochar(cipher);

    cout << "C' = ";
    bitset<64> plain = decrypt3DES(cipher, key);
    BitsetTochar(plain);

    system("pause");
    return 0;
}