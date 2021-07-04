#include <iostream>
#include <typeinfo>

struct X
{
	explicit X():i(3){}
	const int i;
	int y;
};

int main()
{
	X a;


	return 0;
}
