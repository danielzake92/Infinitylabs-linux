#include <iostream>
#include <typeinfo>

struct X
{
public://8 +4 + 4
    X(): m_a(5) {std::cout << "X Ctor this -> " << this << std::endl;}
    ~X() {std::cout << "X Dtor this ->" << this << std::endl;}
    double m_a;    
private:
};

struct Y: public X
{
public://8(x) + 4(m_b) + 4(pad)= 16
    Y() 
    {
        std::cout << "Y Ctor this -> " << this << std::endl;
    }
    ~Y() 
    {
        std::cout << "Y Dtor this -> " << this << std::endl;
    }

private:
    int m_b;
};

void Foo(X &x)
{
    Y *y1 = static_cast<Y*>(&x);
    std::cout << "Foo " << std::endl;
}

int main()
{
    Y y1;
    Foo(y1);

    return 0;
}