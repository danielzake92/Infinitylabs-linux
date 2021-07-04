#include <iostream>
#include <fstream>
#include <dlfcn.h>

#define FILE_NAME "./libtest.so"
#define FILE_NAME2 "./libtest2.so"

void Test1(void);
void Test2(void);
void Test3(void);
void Test4(void);
void foo(int j, int i = 3, float  = 4.586);

extern "C" void Foo(int, int);

void bar();
int bar(int x);
void bar(float f, float f2, float *fptr);

void fobar(float f);
void fobar(double d);
void fobar(float *f);

void jara(char c);


int main()
{

	std::cout << "*******\nTest1()\n*******" << std::endl;
	Test1();
	std::cout << "*******\nTest2()\n*******" << std::endl;
	Test2();
	std::cout << "*******\nTest3()\n*******" << std::endl;
	Test3();
	std::cout << "*******\nTest4()\n*******" << std::endl;
	Test4();
	return 0;
}

void Test1(void)
{
	int i = 5;
	std::cout << "hello i = " << i << std::endl; //increas type safe, reduce error
												//provide inheritability

	// std::cin >> i;

	// std::cout << "hello i = " << i << std::endl;

	std::cerr << "error has qccured" << std::endl;

	std::clog << "Thas a log file" << std::endl;

	// endl is flushing the buffer

}
void Test2(void)
{
	foo(86,4);
}
void Test3(void)
{
	float f = 10.536;

	bar();
	bar(10);
	bar(f, 2*f, &f);

	int i = 5;
	fobar(5.6);
	float f2 = 5;
	fobar(&f2);

	unsigned char uc = 140;

	jara(uc);
}
typedef void (*func_t)(int, int);
void Test4(void)
{
	void *handle1 = NULL;
	void *handle2 = NULL;
	void (*fptr)(int);
	void (*fptr2)(int, int);
	

	handle1 = dlopen(FILE_NAME,RTLD_LAZY);
	handle2 = dlopen(FILE_NAME2,RTLD_LAZY);

	/* *(void**)(&fptr) = dlsym(handle,"my_func1"); */
	fptr = reinterpret_cast<void (*)(int)>(dlsym(handle1,"_Z3bari")); 

	fptr2 = reinterpret_cast<void (*)(int, int)>(dlsym(handle2,"Foo")); 



	(*fptr)(5);
	(*fptr2)(5,6);

	Foo(6,7);

	dlclose(handle1);
	dlclose(handle2);
}

	//c style comments canot be nested, but the can 
	//comment multy line 


void foo(int j, int i , float f)
{
	std::cout << "j = " << j << std::endl;
	std::cout << "i = " << i << std::endl;
	std::cout << "f = " << f << std::endl;
}

void fobar(float f)
{
	std::cout << "f = " << f << std::endl;
}
void fobar(double d)
{
	std::cout << "d = " << d << std::endl;
}
void fobar(float *f)
{
	std::cout << "f = " << *f << std::endl;
}

void jara(char c)
{
	std::cout << "c = " << c << std::endl;
}
