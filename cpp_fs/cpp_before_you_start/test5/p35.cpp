#include <iostream>
#include <typeinfo>

using namespace std;
struct X
{
    X() {cerr << "X Ctor1" << endl; throw bad_cast();cerr << "X Ctor2" << endl;}
    X(int) {cerr << "X Ctor (int)" << endl;}
    ~X() {cerr << "X Dtor" << endl;}
};

struct Y
{
    Y() {cerr << "Y Ctor" << endl;}
    ~Y() {cerr << "Y Dtor" << endl;}
};

class L
{
public:
    L(): m_x(2) {cerr << "L Ctor" << endl;}
    ~L() {cerr << "L Dtor" << endl;}
private:
    Y m_y;
    X m_x;
};

class M
{
public:
    M() {cerr << "M Ctor" << endl;}
    ~M() {cerr << "M Dtor" << endl;}
private:
    X m_x;
    Y m_y;
};

class N
{
public:
    N() {cerr << "N Ctor" << endl;}
    ~N() {cerr << "N Dtor" << endl;}
private:
    Y m_y;
    X m_x;
};

class J
{
public:
    J(): m_y(new Y), m_x(new X) {cerr << "J Ctor" << endl;}
    ~J() {cerr << "J Dtor" << endl; delete m_x; delete m_y;}
private:
    Y *m_y;
    X *m_x;
};

class K
{
public:
    K(): m_y(NULL), m_x(NULL)
    {
        try
        {
            m_y = new Y;
            m_x = new X;
        }
        catch(bad_alloc& e)
        {
            delete m_y;
            delete m_x;
            cerr << "exception cout. what: " << e.what() << endl;
        }
    }
    ~K() {cerr << "K Dtor" << endl; delete m_x; delete m_y;}
private:
    Y *m_y;
    X *m_x;
};

int main()
{
    try
    {
        K var1; //X Y L M N J K
    }
    catch(exception& e)
    {
        cerr << "exception cout. what: " << e.what() << endl;
    }
    return 0;
}