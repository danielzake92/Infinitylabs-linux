#include <iostream>
#include <typeinfo>

struct X
{
    explicit X(); //initialization function without parameters is named //C1Ev && C2Ev
    // default constructor (often abbriviated as: ctor)
    explicit X(int a_, int b_ = 0); //regular (non default) ctor
    ~X(); // deinitialization functoin is called destructor (Dtor)
    X(const X& other_); //copy initialization function is called copy constructor or ctor

    X& operator=(const X& other_);// assignment operator;


    int m_a;
    const int m_b;
};

//why the X::x? the code after the colon is called intiailization list
X::X(): m_a(3), m_b(4) //implementation of the default Ctor. -> this called initialization list
{
    //m_a = 3;
    //m_b = 4; // not allowed becuase it needs to be init through intializer list
    
    std::cout<< "this:" << this << "X defualt Ctor. m_a: " << m_a <<
                                   "m_b:" << m_b << std::endl; 
}

X::X(int a_, int b_): m_a(a_), m_b(b_) //implementation of the second Ctor
{
    std::cout<< "this:" << this << "X int int Ctor. m_a: " << m_a <<
                                   "m_b:" << m_b << std::endl; 
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b)  //implementation of the copy Ctor
{
    std::cout<< "this:" << this << "X copy Ctor. m_a: " << m_a <<
                                   "m_b:" << m_b << std::endl; 
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    // m_b = other_.m_b;

    std::cout<< "this:" << this << "X assignment operator. m_a: " << m_a <<
                                   "does not change m_b" << m_b << std::endl;

    return *this;
}

X::~X()
{
    std::cout<< "this:" << this << "X Dtor. m_a: " << m_a <<
                                   "m_b:" << m_b << std::endl; 
}

struct Y
{
    explicit Y();
    explicit Y(int a, double d);
    void Print(void);
    ~Y();

    Y(Y &obj);

    int a;
    double d;
};

//Y:: ~Y(){} //if the destructor defined in the struct his a weak symbol;

Y::Y()
{
    a = 5;
    d = 5.5;
}

Y::Y(int a_, double d_)
{
    a = a_;
    d = d_;
}

Y::Y(Y &obj)
{
    a = obj.a;
    d = obj.d;
}

void Y::Print(void)
{
    std::cout<< "a = " << a << ", d = " << d << std::endl;
}

struct Z
{
    explicit Z(int i, int j);
    void Print(void);
    int i;
    int j;
    int &i_ref;
};

Z::Z(int i_, int j_) :i_ref(j)
{
    if (i_ > 0)
    {
        i = i_;
    }
    else
    {
        i = 0;
    }

    if (j_ > 0)
    {
        j = j_;
    }
    else
    {
        j = 0;
    }
    
}

void Z::Print(void)
{
    std::cout<< "i = " << i << ", j = " << j << " i_ref = " << i_ref << std::endl;
}

struct W 
{
    X m_x;
    int m_i;

    //explicit W(): m_x(1,2), m_i(0){}

};

int main()
{
    X x1;
    X x2;
    X x3;
    
    
    // X x1;
    // X x2(7);
    // X *px = new X(x2);
    // X x3(9, 10);
    // X x4(x1);

    //X x7 = x3; //copy constructor

    // double *xp = new double;

    // delete  xp; 

    // // x1 = x3;

    // delete px; px = 0;

    // Y y1;
    // Y y2(10, 1.4);
    // Y y3(y2);

    // {
    //     Y y1; //destruction at end of block/function
    //     y1.Print();
    // }

    // y1.Print();
    // y2.Print();
    // y3.Print();
    
    // std::cout<< "sizeof X = " << sizeof(y2) << std::endl;
    // // std::cout<< "sizeof Y = " << sizeof(x1) << std::endl;

    // {
    //     Z z1(6, 7);
    //     Z z2(-6, -7);

    //     z1.Print();

    //     z2.Print();
    // }

    W w1;
    //w1.m_x.m_a = 250;
    // w1.m_x.m_b = 750;

    W w2(w1);
    W w3 = w1;

    //w3 = w1;

    return 0;
}
