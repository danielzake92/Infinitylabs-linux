#include <iostream>
#include <typeinfo>

struct X
{
public://8 +4 + 4
    X() {std::cout << "X Ctor this -> " << this << std::endl;}
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

int main()
{
    X *xp = new Y[5];//allocs 5 places to y

    std::cout<< std::endl;

    std::cout<< (xp[0]).m_a <<std::endl;
    *((int*)((size_t*)xp + 1)) = 4; 
    std::cout<< ((xp[0]).m_a) <<std::endl;

    delete[] xp;

    return 0;
}