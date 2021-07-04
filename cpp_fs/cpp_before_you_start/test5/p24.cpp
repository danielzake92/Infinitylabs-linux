#include <iostream>
#include <typeinfo>

struct X
{
    explicit X(int);
    explicit X();
    ~X();
    void Foo();
    void Bar();
    void Bar() const;

    int m_a;
    int *m_p;
};
X::X(): m_a(0), m_p(0) {}
X::X(int a_): m_a(a_), m_p(new int(a_)) {}

X::~X() { delete m_p; m_p = 0;}

void X::Foo() { ++m_a; --(*m_p);}

void X::Bar()
{
    std::cout << "bar non const" << std::endl;
}

void X::Bar() const
{
    std::cout << "bar const" << std::endl;
    std::cout << m_a << std::endl;
    std::cout << *m_p << std::endl;
    std::cout << m_p << std::endl;
    // m_a = 0; // ---1---
    // m_p = 0; // ---2---
    *m_p = 10; // ---3---
    //Foo() = 0; // ---5---
}

void Fifi(const X& x_)
{
    //x_.Foo();//---4---
    x_.Bar();
    std::cout<<*x_.m_p<<std::endl;
    
}

int main()
{
    X x1(1);
   

    x1.Foo();
    x1.Bar();

    Fifi(x1);

    std::cout<<*x1.m_p<<std::endl;

    return 0;
}

