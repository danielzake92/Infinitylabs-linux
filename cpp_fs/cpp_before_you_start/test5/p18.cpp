#include <iostream>
#include <typeinfo>



void Foo(const double&);
void Bar(double&);



int main()
{
    std::cout <<"**********\nEX18\n**********"<< std::endl;
    
    int i = 5;
    int &ref = i;

    std::cout << "adress of i: " << &i <<std::endl;
    Foo(i);
    Bar(*(reinterpret_cast<double *>(&ref))); //reinterpret only for pointers or integers

    return 0;
}


void Foo(const double& a_d)
{
    std::cout << "adress in Foo: " << &a_d << "\n value in Foo: "<< a_d <<std::endl;
}
void Bar(double& d)
{
    std::cout << "adress in Bar: " << &*reinterpret_cast<int *>(&d) <<"\n value in Bar: "<< *reinterpret_cast<int *>(&d) << std::endl;
}

