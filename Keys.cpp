#include "Keys.h"
using namespace NTL;
Keys::Keys()
{
    //ctor
}

Keys::~Keys()
{
    //dtor
}
void Keys::setq(ZZ value)
{
    q = value;
}

void Keys::setp(ZZ value)
{
    p = value;
}

void Keys::setn(ZZ value)
{
    n = value;
}

void Keys::setphi(ZZ value)
{
    phi = value;
}

void Keys::seta(ZZ value)
{
    a = value;
}

void Keys::setb(ZZ value)
{
    b = value;
}

ZZ Keys::getp()
{
    return p;
}

ZZ Keys::getq()
{
    return q;
}

ZZ Keys::getn()
{
    return n;
}

ZZ Keys::getphi()
{
    return phi;
}

ZZ Keys::geta()
{
    return a;
}

ZZ Keys::getb()
{
    return b;
}