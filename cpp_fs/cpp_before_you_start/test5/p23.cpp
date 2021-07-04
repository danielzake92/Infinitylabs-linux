#include <iostream>
#include <typeinfo>

struct X
{
    int m_b;
    X(int a_, int b_);

    void Inc();
    void Dec();

    friend void foo(X &x);

    int m_a;
};

X::X(int a_, int b_): m_a(a_), m_b(b_)
{}

void X::Inc()
{
    ++m_a;
    ++m_b;
    std::cout << "this:" << this << std::endl;
            }
void X::Dec()
{
    --m _a;
    --m_b;
    std::cout << "this:" << this << std::endl;
}

void foo(X &x)
{
    x.m_a = 5;
    x.m_b = 8;
}

void Inc()
{
}

struct Y
{
    int y_x;
};
struct Z
{
    Y z_y;
    int z_x;
};

int main()
{
    X x1(7, -55);
    X x2(x1);

    //X x3;

    Inc();

    x1.Inc();
    x1.Inc();
    x2.Dec();

    foo(x1);

    return 0;
}