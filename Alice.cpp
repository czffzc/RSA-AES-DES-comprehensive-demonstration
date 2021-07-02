#include"Alice.h"
#include"common_tools.h"
#include "AES.h"
#include "DES.h"
using namespace std;
using namespace NTL;
extern bitset<64>s;
Alice::Alice()
{
    //ctor
}
Alice::~Alice()
{
    //dtor
}
void Alice::setA(ZZ value) {
    A = value;
}
void Alice::setP(ZZ value)
{
    P = value;
}
void Alice::setQ(ZZ value)
{
    Q = value;
}
void Alice::setN(ZZ value)
{
    N= value;
}
ZZ Alice::getA()
{
    return A;
}
ZZ Alice::getP()
{
    return P;
}
ZZ Alice::getQ()
{
    return Q;
}
void Alice::Gen_key(int length)//Alice ����p,q,n,a,b
{
    do {
        NTL::GenPrime(P, length);
        NTL::GenPrime(Q, length);
    } while (P == Q);
    
    key.setp(P);
    key.setq(Q);
    N = P * Q;
    key.setn(key.getp() * key.getq());
    
    key.setphi((key.getp() - 1) * (key.getq() - 1));

    NTL::GenPrime(B, length);
    key.setb(B);
    
    NTL::InvMod(A, key.getb(), key.getphi());
    key.seta(A);

    setA(A);
    setP(P);
    setQ(Q);
    setN(N);

    cout << "p = " << key.getp() << endl
         << "q = " << key.getq() << endl;
    cout << "n = " << key.getn() << endl;
    cout << "phi = " << key.getphi() << endl;
    cout << "b = " << key.getb() << endl;
    cout << "a = " << key.geta() << endl;

}

/*
* ��Alice��RSA˽Կ����c1�õ�k��k=c1^a mod n
*/
bitset<128> Alice::de_c1_get_k(ZZ c1, Alice alice)
{
    ZZ key;
    key = PowerMod(c1, alice.getA(), alice.N);
    bitset<128>k;
    for (int i = 0; i < k.size(); i++) {
        k[i] = key % 2;
        key = key / 2;
    }
    return k;
}

/*ȥ���*/
void de_PKCS7Padding2(string out_filename)
{
    long int size = 0;
    ifstream fin("m_padding_2.txt", ios::binary);
    if (!fin) {
        cout << "�����ļ���ʧ��" << endl;
        exit(1);
    }
    //char* out = new char[4];

    ofstream fout(out_filename.c_str(), ios::binary);
    if (!fout) {
        cout << "����ļ���ʧ�ܣ�" << endl;
        exit(1);
    }
    if (fin.is_open()) {
        fin.seekg(0, ios::end);
        size = fin.tellg();
        cout << "Ҫȥ�����ļ���СΪ��" << dec<<size << "�ֽ�"<<endl;
    }
    char ch;
    int tmp = 0;
    fin.seekg(-1, ios::end);
    fin.get(ch);//��ȡ������ļ������һ���ַ�
    if (0x00 < ch <= 0x16) {
        tmp = ch;
    }
    fin.seekg(0, ios::beg);
    cout <<"ȥ����ַ�Ϊ��"<<tmp << endl;
    if (tmp > size)
        return;//�޷�ȥ���
    for (long int i = 0; i < size - tmp; i++) {
        fin.get(ch);
        fout.put(ch);
    }
    fin.close();
    fout.close();
}

/*
* ��k����c2�õ�m
*/
void Alice::de_c2_to_m(bitset<128> k, string out_filename)
{

    ofstream fout("m_padding_2.txt", ios::binary);
    if (!fout) {
        cout << "����ļ���ʧ�ܣ�" << endl;
        exit(1);
    }

    ifstream fin("c2.txt", ios::binary);//���������ļ�
    if (!fin) {
        cout << "�����ļ���ʧ��" << endl;
        exit(1);
    }
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
        decrypt(plain, w);//����һ������
        //�ѽ��ܺ��һ������д���ļ�c2,bitset<8>ת��Ϊchar
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            int t = 0, m = 1;
            for (int k = 0; k < 8; k++) {
                t = t + plain[i][k] * m;
                m = m * 2;
            }
            temp[i] = char(t);
            //plain[i] = charToBitset64(temp[i]);
        }
        fout.write(temp, sizeof(temp));
    }
    fin.close();
    fout.close();
    de_PKCS7Padding2(out_filename);
}
//byte key[16] = { 0x2b, 0x7e, 0x15, 0x16,
//			0x28, 0xae, 0xd2, 0xa6,
//	   0xab, 0xf7, 0x15, 0x88,
//	   0x09, 0xcf, 0x4f, 0x3c };