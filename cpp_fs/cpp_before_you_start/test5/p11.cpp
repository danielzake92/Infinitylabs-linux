#include <iostream>
#include <typeinfo>

void bar(char, int, short);
void bar(signed char, int, short);
void bar(char,unsigned int,unsigned short);



int main()
{
    std::cout <<"**********\nEX11\n**********"<< std::endl;

    char c = -'a';
    unsigned char uc = 'a';

    int i = -105;
    unsigned int ui = 326;

    short s = -56;
    unsigned short us = 3265;

    bar(c, i, s);//bar(char ,int ,short)

    //bar(uc, i,us ); //bar(unsigned char, int, unsigned shor)

    bar(uc, i, s);

    return 0;
}

void bar(char, int, short)
{
    std::cout<<"#1) void bar(char, int, short)"<<std::endl;
}
/*****************************************************************************/
void bar(signed char, int, short)
{
    std::cout<<"#2) void bar(signed char, int, short)"<<std::endl;
}
/*****************************************************************************/
void bar(char,unsigned int,unsigned short)
{
    std::cout<<"#3) void bar(char,unsigned int,unsigned short)"<<std::endl;
}

