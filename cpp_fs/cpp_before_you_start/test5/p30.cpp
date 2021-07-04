#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std;

class X
{
public:

    X(): m_a(0) {cout<< "A::Ctor " << endl;}
    ~X() {cout<< "A::Dtor " << endl;}
    
    int m_a;
};

struct BadDog: public runtime_error
{
    BadDog(const string& s = "This is bad dog"): runtime_error(s) {}
};

void Fifi()
{
    throw BadDog("bad joke\n"); cerr << "Fifi() after throw" << endl;
}
void Foo()
{
    X x1;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}
void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}
int main() {
    try
    {
        Bar();
    }
    catch(BadDog& b)
    {
        cerr << "Bad Dog exception: " << b.what(); exit(3);
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exiting."; exit(2);
    }
    catch(exception& r)
    {
        cerr << "unknown exception:" << r.what();
        exit(4);
    }
    catch(...)
    {
        cerr << "main error ";
    }
    return 0;
}