#include <iostream>

using namespace std;

void Test1(void);
void Test2(void);

class B
{
public:
    virtual ~B(){}
    virtual void Foo(int a)
    {
        std::cout<<a<<std::endl;
    }
};

class D : public B
{
public:
    virtual int Foo(int a)
    {
        std::cout<<2*a <<std::endl;
    }

    // virtual int Foo(int a, int b) //functions as overload
    // {
    //     std::cout<<a + b<<std::endl;
    //     return a + b;
    // }
};

class X
{
public:
    X(): x1(0), x2(1)
    {
        //cout << "X::Ctor" << endl;
    }
    ~X()
    {
        
    }
    X(X &xx): x1(xx.x1), x2(1){cout << "X::Cctor" << endl;}
    X& operator=(const X&){return *this;}
private:
    int x1;
    const int x2;
};


X foo(X s)
{
    X s2(s);
    return s2;
}

void Bar(void)
{
    std::cout<<"bar"<<std::endl;
}

void Test1(void)
{
    size_t s1 = 5;
    size_t s2 = 10;
    size_t s3 = 100;
    size_t s4 = 1000;
    int *ptr1 = new int[s1];
    int *ptr2 = new int[s2];
    int *ptr3 = new int[s3];
    int *ptr4 = new int[s4];

    X x1;

    foo(x1);

    std::cout<< (char*)ptr2 - (char*)ptr1 - s1 * sizeof(int) <<std::endl;
    std::cout<< (char*)ptr3 - (char*)ptr2 - s2 * sizeof(int) <<std::endl;
    std::cout<< (char*)ptr4 - (char*)ptr3 - s3 * sizeof(int) <<std::endl;

    Bar();

    delete[] ptr1;
    delete[] ptr2;
    delete[] ptr3;
    delete[] ptr4;
}

void Test2(void)
{
    size_t s1 = 5;
    size_t s2 = 10;
    size_t s3 = 100;
    size_t s4 = 1000;
    X *ptr1 = new X[s1];
    X *ptr2 = new X[s2];
    X *ptr3 = new X[s3];
    X *ptr4 = new X[s4];

    X x1;

    std::cout<<sizeof(X)<<std::endl;

    foo(x1);

    std::cout<< (char*)ptr2 - (char*)ptr1 - s1 * sizeof(X) <<std::endl;
    std::cout<< (char*)ptr3 - (char*)ptr2 - s2 * sizeof(X) <<std::endl;
    std::cout<< (char*)ptr4 - (char*)ptr3 - s3 * sizeof(X) <<std::endl;



    Bar();

    delete[] ptr1;
    delete[] ptr2;
    delete[] ptr3;
    delete[] ptr4;
}


int main()
{
    //Test1();
    //Test2();

    b->Foo(5);

    //D d1;

    //d1.Foo(5, 7);



    return 0;
}