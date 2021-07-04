#include <iostream> //std::cout

using namespace std;

struct Base
{
public:

	Base(int a = 0) {cout<< "Base ctor"<< endl;}
	~Base() {cout<< "Base dtor"<< endl;}
	Base(const Base &) {cout<< "Base cctor"<< endl;}
	virtual void operator=(const Base &) {cout<< "Base ="<< endl;}
	virtual void print() {cout << "Base print" << endl;}

};

struct Derived : public Base
{
public:

	Derived() {cout<< "Derived ctor"<< endl;}
	~Derived() {cout<< "Derived dtor"<< endl;}
	Derived(const Derived &) {cout<< "Derived cctor"<< endl;}
	void operator=(const Derived &) {cout<< "Derived ="<< endl;}
	void print() {cout << "Derived print" << endl;}

};

void Print(Base p) {p.print();}


int main()
{
	Base b;
	Base *pb = new Derived;
	Derived drv(*static_cast<Derived*>(pb));
	Print(b);
	Print(*pb);
	pb->print();

	delete pb;

	return 0;
}