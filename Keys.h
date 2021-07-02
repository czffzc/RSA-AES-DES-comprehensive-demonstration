#ifndef KEYS_H
#define KEYS_H
#include <iostream>
#include <NTL/ZZ.h>
using namespace NTL;
class Keys
{
public:
    Keys();
    virtual ~Keys();

    void setq(ZZ value);
    void setp(ZZ value);
    void setn(ZZ value);
    void setphi(ZZ value);
    void seta(ZZ value);
    void setb(ZZ value);
    ZZ getp();
    ZZ getq();
    ZZ getn();
    ZZ getphi();
    ZZ geta();
    ZZ getb();

protected:

private:
    ZZ p, q, n, phi, a, b;//phi表示n欧拉函数，a是私钥，b是公钥
};

#endif // KEYS_H