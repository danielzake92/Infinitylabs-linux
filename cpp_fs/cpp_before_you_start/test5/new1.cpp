#include <iostream>


int foo(int a)
{
    std::cout<<"int"<<std::endl;
    return 4;
}
double foo(int* iptr)
{
    std::cout<<"double"<<std::endl;
    return 4.0;
}


int main()
{
    int *ptr = NULL;
    foo(ptr);
    return 0;
}