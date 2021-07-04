#include <iostream>

class X
{
public:
    X(double d): m_a(d) 
    {
        std::cout << "X Ctor " << std::endl;
    }
    virtual ~X() {}
private:
    double m_a;    
};

class Y: public X
{
public://8(x) + 4(m_b) + 4(pad)= 16
    Y(double d, int i) : X(d), m_b(i) 
    {
        std::cout << "Y Ctor " << std::endl;
    }
private:
    int m_b;
};

int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    X &x1 = y1;
    X &x2 = y2;

    x1 = x2;
    y3 = y4;

    return 0;
}