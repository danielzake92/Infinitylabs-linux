#include <iostream>
#include <typeinfo>
#include <cstring>

typedef struct refer refer_t;

void TestInts(void);
void TestDoubles(void);
void TestPtrs(void);
refer_t TestStruct(refer_t structy);

struct refer
{
    int i;
    char c;
    double d[100];
    char name[100];
};


int main()
{
    std::cout <<"**********\nTestInts()\n**********"<< std::endl;
    TestInts();
    std::cout <<"*************\nTestDoubles()\n*************"<< std::endl;
    TestDoubles();
    std::cout <<"**********\nTestPtrs()\n**********"<< std::endl;
    TestPtrs();
    return 0;
}
void TestInts(void)
{
    int i = 8;
    int &ip = i;
    ip = 9;

    const int &i_ref = 5;

    std::cout <<"i ="<< i << std::endl;
    std::cout <<"ip =" <<ip << std::endl;
    std::cout <<"i_ref =" <<i_ref << std::endl;
}
void TestDoubles(void)
{
    double d = 8.56;
    const double &dp = d;

    d = 4435.23;

    std::cout <<"d ="<< d << std::endl;
    std::cout <<"dp =" <<dp << std::endl;
}
void TestPtrs(void)
{
    int i = 5;
    int *pi = &i;

    int *&pii = pi;

    *pii = 7;

    refer_t a;
    refer_t &b = a;

    refer_t *ptra = &a;
    refer_t *&c = ptra;

    int &vlad = a.i;

    a = TestStruct(a);


    std::cout <<"b.c ="<< b.c << std::endl;
    std::cout <<"b.i ="<< b.i << std::endl;
    std::cout <<"a.c ="<< a.c << std::endl;
    std::cout <<"a.i ="<< a.i << std::endl;
    std::cout <<"vlad ="<< vlad << std::endl;

    std::cout <<"sizeof(a) = "<< sizeof(a) << std::endl;
    std::cout <<"sizeof(b, a referenced structure) = "<< sizeof(b) << std::endl; /* the same as a */

    std::cout <<"address of a = "<< &a << std::endl; /* the same as a */
    std::cout <<"address of b, a referenced structure = "<< &b << std::endl; /* the same as a */

    std::cout <<"sizeof(ptra) = "<< sizeof(ptra) << std::endl;
    std::cout <<"sizeof(c, a referenced ptr to structure) = "<< sizeof(c) << std::endl; /* the same as a */


    std::cout <<"*pi ="<< *pi << std::endl;
    std::cout <<"*pii =" <<*pii << std::endl;
    
}

refer_t TestStruct(refer_t structy)
{
    structy.c = 'a';
    structy.i = 3;
    strcpy(structy.name,"daniel");
    return structy;
}

