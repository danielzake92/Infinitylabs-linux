#include <iostream>
#include <typeinfo>
#include <cstdio>

class X
{
    int m_a;

    public:
        explicit X(int a_);
        explicit X():m_a(15){}
        void Foo();
        //friend int main();
        friend void Foo(const X &x_);
};

X::X(int a_): m_a(a_){}

void X::Foo()
{
    printf("in Foo method -> m_a = %d\n", m_a);
}

void Foo(const X &x_)
{
    printf("in friend Foo -> m_a = %d\n", x_.m_a);
}

int main()
{
    X x1(5);
    X x2;

    x1.Foo();

    //printf("in main -> m_a = %d\n", x1.m_a);

    Foo(x1);


}