#include <iostream>
using namespace std;

struct Base
{
    Base() {cout << "Base Ctor" << endl;}
    ~Base() {cout << "Base Dtor" << endl;}
    Base(const Base &) {cout << "Base cctor" << endl;}
    virtual void print() {cout << "Base print" << endl;}
};

struct Derived : public Base
{
    Derived() {cout << "Derived Ctor" << endl;}
    ~Derived() {cout << "Derived Dtor" << endl;}
    Derived(const Derived &) {cout << "Derived cctor" << endl;}
    virtual void print() {cout << "Derived print" << endl;} 
};

void Print(Base p)
{
    p.print();
}

int main()
{
    Base b;
    Base *pb = new Derived;

    Print(b);
    Print(*pb);
    pb->print();

    delete pb;
    return 0;
}