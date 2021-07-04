#include <iostream>
#include <fstream>

void bar();
void bar(int x);
void bar(float f, float f2, float *fptr);

void bar()
{
	std::cout << "first type of func\n" <<std::endl;
}

void bar(int i)
{
	std::cout << "second type and i = " << i <<"\n"<<std::endl;
}
void bar(float f1, float f2, float *fptr)
{
	std::cout << "third type and f = " << f1 <<"\n"<<std::endl;
}