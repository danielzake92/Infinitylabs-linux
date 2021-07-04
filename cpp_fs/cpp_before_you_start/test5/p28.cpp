#include <iostream>


class X
{
    public:
        X() : m_id(++s_cntr) {}
        int GetId() { std::cout << m_id << std:: endl; return m_id;}
        void Print2() {std::cout << "non static print" << std::endl; m_id = 5;}
        static void Print1(void) {std::cout << "static print" << std::endl;} 

    private:
        int m_id;
        static int s_cntr;
};

int X::s_cntr = 0;



int main()
{
    X x1;
    X x2;

    X::Print1();

    x1.GetId();
    x2.GetId();

    x1.Print1();
    x1.Print2();

    std::cout << "size of X ->" << sizeof(X) << std::endl;

    return 0;
}